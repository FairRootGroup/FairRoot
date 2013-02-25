
#include "Detector.h"
#include "SimFlag.h"
#include "FairDbBinaryFile.h"
#include "FairDbCache.h"
#include "FairDbConnectionMaintainer.h"
#include "FairDbResult.h"
#include "FairDbTableProxy.h"
#include "FairDbTableRow.h"
#include "FairDbTimerManager.h"
#include "FairDbValidityRec.h"
#include "FairDbValidityRecBuilder.h"
#include "FairDbExceptionLog.h"

ClassImp(FairDbTableProxy)


FairDbTableProxy::FairDbTableProxy(FairDbMultConnector* cascader,
                                   const string& tableName,
                                   const string& vldSuffix,
                                   const FairDbTableRow* tableRow) :
  fMultConnector(cascader),
  fMetaData(tableName),
  fMetaValid(tableName+vldSuffix),
  fCanL2Cache(kFALSE),
  fCache(0),
  fDBProxy(*cascader,tableName,&fMetaData,&fMetaValid,this),
  fExists(0),
  fTableName(tableName),
  fTableRow(tableRow->CreateTableRow())
{

  fCache = new FairDbCache(*this,fTableName);
  this->RefreshMetaData();
  fExists = fDBProxy.TableExists();
  fCanL2Cache = tableRow->CanL2Cache();
  if ( fCanL2Cache ) {
    cout << "FairDbTableProxy: Can L2 cache " << this->GetRowName() << endl;
  }
  cout << "Creating FairDbTableProxy "
       << fTableName.c_str() << " at " << this
       << ( fExists ? " (table exists)"
            : " (table missing)" )
       << endl;
}


FairDbTableProxy::~FairDbTableProxy()
{
  delete fCache;
  delete fTableRow;

}

Bool_t FairDbTableProxy::CanReadL2Cache() const
{
  return fCanL2Cache && FairDbBinaryFile::CanReadL2Cache();

}
Bool_t FairDbTableProxy::CanWriteL2Cache() const
{
  return fCanL2Cache && FairDbBinaryFile::CanWriteL2Cache();

}
const FairDbResult* FairDbTableProxy::Query(const ValContext& vc,
    const FairDb::Task& task,
    Bool_t findFullTimeWindow)
{

  if ( const FairDbResult* result = fCache->Search(vc,task)
     ) { return result; }

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

// Make Global Exception Log bookmark
  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

// Build a complete set of effective validity record from the database.
  FairDbValidityRecBuilder builder(fDBProxy,vc,task,-1,findFullTimeWindow);

// Deal with non-aggregated data.

  if ( builder.NonAggregated() ) {

    FairDbValidityRec effVRec = builder.GetValidityRec(0);
//  Force off const - we haven't finished with FairDbResult yet!
    FairDbResult* result = const_cast<FairDbResult*>(Query(effVRec));
//  Record latest entries from Global Exception Log.
    result->CaptureExceptionLog(startGEL);
    return result;
  }

// Deal with aggregated data.


  if ( this->CanReadL2Cache() ) {
    UInt_t numPresent  = 0;
    UInt_t numRequired = 0;
    Int_t maxRow = builder.GetNumValidityRec() - 1;
    for ( Int_t rowNo = 1; rowNo <= maxRow; ++rowNo ) {
      const FairDbValidityRec& vrec = builder.GetValidityRec(rowNo);
      if ( fCache->Search(vrec) ) { ++numPresent; }
      else if ( ! vrec.IsGap() ) { ++numRequired; }
    }
    if ( numRequired < numPresent )
      cout << "Skipping search of L2 cache; already have "
           << numPresent << " aggregates, and only require a further "
           << numRequired << endl;
    else { this->RestoreFromL2Cache(builder); }
  }

  FairDbResult* result = new FairDbResultAgg(fTableName,
      fTableRow,
      fCache,
      &builder,
      &fDBProxy);
// Record latest entries from Global Exception Log.
  result->CaptureExceptionLog(startGEL);

  fCache->Adopt(result);
  this->SaveToL2Cache(builder.GetL2CacheName(),*result);
  return result;

}
//.....................................................................

const FairDbResult* FairDbTableProxy::Query(const string& context,
    const FairDb::Task& task,
    const string& data,
    const string& fillOpts)
{

  std::ostringstream os;
  os << context;
  if ( task != FairDb::kAnyTask
     ) { os << " and  Task = " << task; }
  os <<  ';' << data << ';' << fillOpts;
  string sqlQualifiers = os.str();


  cout    << "Extended query: sqlQualifiers: " << sqlQualifiers << endl;

//  See if there is one already in the cache.

  if ( const FairDbResult* result = fCache->Search(sqlQualifiers)
     ) { return result; }

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

// Make Global Exception Log bookmark
  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

// Build a complete set of effective validity records from the database.
  FairDbValidityRecBuilder builder(fDBProxy,context,task);

// For extended context queries, FairDbValidityRecBuilder will always
// assemble a result that has to be represented by a FairDbResultAgg

  FairDbResult* result = new FairDbResultAgg(fTableName,
      fTableRow,
      fCache,
      &builder,
      &fDBProxy,
      sqlQualifiers);
// Record latest entries from Global Exception Log.
  result->CaptureExceptionLog(startGEL);

  fCache->Adopt(result);
  return result;

}

const FairDbResult* FairDbTableProxy::Query(UInt_t seqNo,UInt_t dbNo)
{

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

// Make Global Exception Log bookmark
  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  // Apply SEQNO query to cascade member.
  FairDbResultSet* rs = fDBProxy.QueryValidity(seqNo,dbNo);
  FairDbValidityRec tr;
  FairDbResultNonAgg result(rs,&tr,0,kFALSE);
  delete rs;

  // If query failed, return an empty result.
  if ( result.GetNumRows() == 0 ) {
    FairDbResultNonAgg* empty = new FairDbResultNonAgg();
//  Record latest entries from Global Exception Log.
    empty->CaptureExceptionLog(startGEL);
    fCache->Adopt(empty);
    return empty;
  }

// Otherwise perform a validity rec query, but don't
// allow result to be used; it's validity has not been trimmed
// by neighbouring records.

  const FairDbValidityRec* vrec
  = dynamic_cast<const FairDbValidityRec*>(result.GetTableRow(0));
//  Force off const - we haven't finished with FairDbResult yet!
  FairDbResult* res = const_cast<FairDbResult*>(Query(*vrec,kFALSE));
// Record latest entries from Global Exception Log.
  res->CaptureExceptionLog(startGEL);
  return res;

}

const FairDbResult* FairDbTableProxy::Query(const FairDbValidityRec& vrec,
    Bool_t canReuse )
{

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

// Make Global Exception Log bookmark
  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  if ( canReuse ) {
    FairDbValidityRecBuilder builder(vrec,this->GetTableName());
    if ( this->RestoreFromL2Cache(builder) ) {
      const FairDbResult* res = fCache->Search(vrec);
      if ( res ) { return res; }
    }
  }

  unsigned int seqNo = vrec.GetSeqNo();
  FairDbResult* result = 0;

//  If no records, create an empty FairDbResult.
  if ( ! seqNo ) {
    result = new FairDbResultNonAgg(0,0,&vrec);
  }

//  If query does not apply to this table, report error and
//  produce an empty FairDbResult.

  else if (vrec.GetTableProxy()->GetTableName() != GetTableName() ) {

    cout   << "Unable to satisfy FairDbValidityRec keyed query:" << endl
           << vrec
           << " was filled by " << vrec.GetTableProxy()->GetTableName()
           << " not by this FairDbTableProxy ("
           << GetTableName() << ")" << endl;
    result = new FairDbResultNonAgg(0,0,&vrec);
  }

  else {


// Apply query, and build DiResult from its FairDbResultSet.

    FairDbResultSet* rs = fDBProxy.QuerySeqNo(seqNo,vrec.GetDbNo());
    result = new FairDbResultNonAgg(rs,fTableRow,&vrec);
    delete rs;
  }

// Record latest entries from Global Exception Log.
  result->CaptureExceptionLog(startGEL);

//  Cache in memory and on disk if required and return the results.

  fCache->Adopt(result);
  if ( canReuse ) { this->SaveToL2Cache(vrec.GetL2CacheName(),*result); }
  else { result->SetCanReuse(kFALSE); }

  return result;

}

//.....................................................................

void FairDbTableProxy::RefreshMetaData()
{
//
//
//  Purpose:  Refresh meta data for table.
//

  fDBProxy.StoreMetaData(fMetaData);
  fDBProxy.StoreMetaData(fMetaValid);

}
//.....................................................................

ValTimeStamp FairDbTableProxy::QueryOverlayCreationDate(const FairDbValidityRec& vrec,
    UInt_t dbNo)
{
  // Practice for claibrated data

  const ValRange& vr(vrec.GetValRange());
  ValContext vc((Detector::Detector_t) vr.GetDetectorMask(),
                (SimFlag::SimFlag_t) vr.GetSimMask(),
                vr.GetTimeStart());

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

  // Build a complete set of effective validity records from the
  // selected database.
  FairDbValidityRecBuilder builder(fDBProxy,vc,vrec.GetTask(),dbNo);

  // Pick up the validity record for the current aggregate.
  const FairDbValidityRec& vrecOvlay(builder.GetValidityRecFromAggNo(vrec.GetAggregateNo()));

  // If its a gap i.e. nothing is overlayed, return the start time, otherwise
  // return its Creation Date plus one minute.
  ValTimeStamp ovlayTS(vr.GetTimeStart());
  if ( ! vrecOvlay.IsGap() ) {
    time_t overlaySecs = vrecOvlay.GetCreationDate().GetSec();
    ovlayTS = ValTimeStamp(overlaySecs + 60,0);
  }

  cout << "Looking for overlay creation date for: "
       << vrec << "found it would overlap: "
       << vrecOvlay << " so overlay creation date set to "
       << ovlayTS.AsString("s") << endl;
  return ovlayTS;

}

Bool_t FairDbTableProxy::RestoreFromL2Cache(const FairDbValidityRecBuilder& builder)
{

  const string name(builder.GetL2CacheName());
  cout << "Request to restore query result  " << name
       << endl;
  if ( ! this->CanReadL2Cache() ) { return kFALSE; }
  string cacheFileName;
  if (  name != ""
     ) cacheFileName =  this->GetTableName() + "_"
                          + this->GetRowName() + "_"
                          +  name + ".dbi_cache";
  FairDbBinaryFile bf(cacheFileName.c_str());
  if ( ! bf.IsOK() ) {
    cout << "Caching disabled or cannot open "
         << bf.GetFileName() << endl;
    return kFALSE;
  }

  static bool warnOnce = true;
  if ( warnOnce ) {
    cout  << "\n\n\n"
          << " WARNING:  Reading from the Level 2 cache has been activated.\n"
          << " *******   This should only be used for development and never for production !!!\n\n\n";
    warnOnce = false;
  }

  cout << "Restoring query result from " << bf.GetFileName() << endl;
  FairDbTimerManager::gTimerManager.RecMainQuery();

  FairDbResult* result    = 0;
  unsigned numRowsRest = 0;
  unsigned numRowsIgn  = 0;
  UInt_t numNonAgg     = 0;
  bf >> numNonAgg;

  while ( numNonAgg-- ) {
    if ( ! bf.IsOK() ) { break; }
    if ( ! result ) { result = new FairDbResultNonAgg; }
    bf >> *result;

//  The original query may have had a validity range truncated by
//  the time window, so replace its FairDbValidityRec with the one
//  just obtained from the database.
    const FairDbValidityRec& vrec = result->GetValidityRec();
    UInt_t seqNo = vrec.GetSeqNo();
    cout << "Fix up L2 cache FairDbValidityRec, by replacing: " << vrec
         << "    with: " << builder.GetValidityRecFromSeqNo(seqNo) << endl;
//  Sneaky end-run round const to fix-up FairDbValidityRec.
    (const_cast<FairDbValidityRec&>(vrec)) = builder.GetValidityRecFromSeqNo(seqNo);

//  Adopt only if not already in memory cache.
    if ( ! fCache->Search(vrec) ) {
      numRowsRest += result->GetNumRows();
      fCache->Adopt(result);
      result = 0;
    } else { numRowsIgn += result->GetNumRows(); }
  }
  cout << "   a total of " << numRowsRest << " were restored ("
       << numRowsIgn << " ignored - already in memory)" << endl;

  delete result;
  result = 0;

  return numRowsRest > 0;

}

Bool_t FairDbTableProxy::SaveToL2Cache(const string& name, FairDbResult& res)
{

  cout << "Request to save query result as " << name
       << " data from DB? " << res.ResultsFromDb()
       << " can be saved? " << res.CanSave() << endl;
  if ( ! this->CanWriteL2Cache() || ! res.ResultsFromDb() || ! res.CanSave() ) { return kFALSE; }

  string cacheFileName;
  if (  name != ""
     ) cacheFileName =  this->GetTableName() + "_"
                          + this->GetRowName() + "_"
                          +  name + ".dbi_cache";
  FairDbBinaryFile bf(cacheFileName.c_str(),kFALSE);
  if ( bf.IsOK() ) {
    cout << "Saving query result (" << res.GetNumRows()
         << " rows) to " << bf.GetFileName() << endl;
    FairDbTimerManager::gTimerManager.RecMainQuery();

    // if writing a FairDbResultNonAgg, add leading count of 1. (if writing
    // a FairDbResultAgg it will writes its one leading count.
    if ( dynamic_cast<FairDbResultNonAgg*>(&res) ) {
      UInt_t numNonAgg = 1;
      bf << numNonAgg;
    }
    bf << res;
    return kTRUE;
  }
  cout << "Caching disabled or cannot open "
       << bf.GetFileName() << endl;
  return kFALSE;

}

void FairDbTableProxy::SetSqlCondition(const string& sql)
{

  fDBProxy.SetSqlCondition(sql);

}
