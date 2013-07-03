#include "FairDbTableProxy.h"
#include "FairDbLogService.h"
#include "FairDbBinaryFile.h"           // for string, FairDbBinaryFile
#include "FairDbCache.h"                // for FairDbCache
#include "FairDbConnectionMaintainer.h"  // for FairDbConnectionMaintainer
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbResult.h"               // for FairDbResultNonAgg, etc
#include "FairDbTableRow.h"             // for FairDbTableRow
#include "FairDbTimerManager.h"         // for FairDbTimerManager, etc
#include "FairDbValidityRec.h"          // for FairDbValidityRec, etc
#include "FairDbValidityRecBuilder.h"   // for FairDbValidityRecBuilder
#include "SimFlag.h"                    // for SimFlag_t
#include "ValContext.h"                 // for ValContext
#include "ValRange.h"                   // for ValRange
#include "db_detector_def.h"            // for Detector, etc

#include "Riosfwd.h"                    // for ostream

#include <sys/select.h>                 // for time_t
#include <iostream>                     // for cout
#include <sstream>                      // IWYU pragma: keep
// for operator<<, basic_ostream, etc

using std::cout;
using std::endl;
using std::string;


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
    DBLOG("FairDb",FairDbLog::kInfo)  << "Can L2 cache " << this->GetRowName() << endl;
  }
  DBLOG("FairDb",FairDbLog::kInfo)  << "created "
                                    << fTableName.c_str() << " at " << this
                                    << ( fExists ? " (table exists)"
                                         : " (table missing)" )
                                    << endl;
  DBLOG("FairDb",FairDbLog::kInfo)<< "Connected Table Row  " << fTableRow << endl;

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
    const FairDb::Version& task,
    Bool_t findFullTimeWindow)
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Query fulltimewindow " << findFullTimeWindow <<  endl;
// is info in cache?
  if ( const FairDbResult* result = fCache->Search(vc,task)
     ) { return result; }

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  FairDbValidityRecBuilder builder(fDBProxy,vc,task,-1,findFullTimeWindow);


  if ( builder.NonAggregated() ) {
    DBLOG("FairDb",FairDbLog::kInfo) << " Non Composite Type  " << endl;
    FairDbValidityRec effVRec = builder.GetValidityRec(0);
    FairDbResult* result = const_cast<FairDbResult*>(Query(effVRec));
    result->CaptureExceptionLog(startGEL);
    return result;
  }


  DBLOG("FairDb",FairDbLog::kInfo) << "Composite Type " << endl;
  if ( this->CanReadL2Cache() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "reading cache ... " << endl;
    UInt_t numPresent  = 0;
    UInt_t numRequired = 0;
    Int_t maxRow = builder.GetNumValidityRec() - 1;
    for ( Int_t rowNo = 1; rowNo <= maxRow; ++rowNo ) {
      const FairDbValidityRec& vrec = builder.GetValidityRec(rowNo);
      if ( fCache->Search(vrec) ) { ++numPresent; }
      else if ( ! vrec.IsGap() ) { ++numRequired; }
    }
    if ( numRequired < numPresent )
      DBLOG("FairDb",FairDbLog::kInfo)  << "Skipping search of L2 cache; already have "
                                        << numPresent << " composites, and only require a further "
                                        << numRequired << endl;
    else { this->RestoreFromL2Cache(builder); }
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "now do the results --->  " << endl;
  FairDbResult* result = new FairDbResultAgg(fTableName,
      fTableRow,
      fCache,
      &builder,
      &fDBProxy);
  result->CaptureExceptionLog(startGEL);

  fCache->Adopt(result);
  this->SaveToL2Cache(builder.GetL2CacheName(),*result);
  return result;

}

const FairDbResult* FairDbTableProxy::Query(const string& context,
    const FairDb::Version& task,
    const string& data,
    const string& fillOpts)
{

  std::ostringstream os;
  os << context;
  if ( task != FairDb::kAnyVersion
     ) { os << " and  Version = " << task; }
  os <<  ';' << data << ';' << fillOpts;
  string sqlQualifiers = os.str();


  DBLOG("FairDb",FairDbLog::kInfo) << "Extended query: sqlQualifiers: " << sqlQualifiers << endl;

  // Is in cache ?
  if ( const FairDbResult* result = fCache->Search(sqlQualifiers)
     ) { return result; }

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections
  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;
  FairDbValidityRecBuilder builder(fDBProxy,context,task);

  FairDbResult* result = new FairDbResultAgg(fTableName,
      fTableRow,
      fCache,
      &builder,
      &fDBProxy,
      sqlQualifiers);

  result->CaptureExceptionLog(startGEL);

  fCache->Adopt(result);
  return result;

}

const FairDbResult* FairDbTableProxy::Query(UInt_t seqNo,UInt_t dbNo)
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Query 2 " << endl;
  FairDbConnectionMaintainer cm(fMultConnector);

  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  FairDbResultSet* rs = fDBProxy.QueryValidity(seqNo,dbNo);
  FairDbValidityRec tr;
  FairDbResultNonAgg result(rs,&tr,0,kFALSE);
  delete rs;

  if ( result.GetNumRows() == 0 ) {
    FairDbResultNonAgg* empty = new FairDbResultNonAgg();
    empty->CaptureExceptionLog(startGEL);
    fCache->Adopt(empty);
    return empty;
  }


  const FairDbValidityRec* vrec
  = dynamic_cast<const FairDbValidityRec*>(result.GetTableRow(0));

  FairDbResult* res = const_cast<FairDbResult*>(Query(*vrec,kFALSE));

  res->CaptureExceptionLog(startGEL);
  return res;

}

const FairDbResult* FairDbTableProxy::Query(const FairDbValidityRec& vrec,
    Bool_t canReuse )
{

  FairDbConnectionMaintainer cm(fMultConnector);  //Stack object to hold connections

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


  if ( ! seqNo ) {
    result = new FairDbResultNonAgg(0,0,&vrec);
  }


  else if (vrec.GetTableProxy()->GetTableName() != GetTableName() ) {

    MAXDBLOG("FairDb",FairDbLog::kError,20)
        << "Unable to satisfy FairDbValidityRec keyed query:" << endl
        << vrec
        << " was filled by " << vrec.GetTableProxy()->GetTableName()
        << " not by this FairDbTableProxy ("
        << GetTableName() << ")" << endl;
    result = new FairDbResultNonAgg(0,0,&vrec);
  }

  else {
    DBLOG("FairDb",FairDbLog::kInfo) << "Query(vc)  SEQNO" <<  seqNo << endl;
    FairDbResultSet* rs = fDBProxy.QuerySeqNo(seqNo,vrec.GetDbNo());
    result = new FairDbResultNonAgg(rs,fTableRow,&vrec);
    delete rs;
  }

  result->CaptureExceptionLog(startGEL);
//  Cache in memory and on disk
  fCache->Adopt(result);
  if ( canReuse ) { this->SaveToL2Cache(vrec.GetL2CacheName(),*result); }
  else { result->SetCanReuse(kFALSE); }

  return result;
}


void FairDbTableProxy::RefreshMetaData()
{
  fDBProxy.StoreMetaData(fMetaData);
  fDBProxy.StoreMetaData(fMetaValid);
}

ValTimeStamp FairDbTableProxy::QueryOverlayCreationDate(const FairDbValidityRec& vrec,
    UInt_t dbNo)
{
  const ValRange& vr(vrec.GetValRange());
  ValContext vc((Detector::Detector_t) vr.GetDetectorMask(),
                (SimFlag::SimFlag_t) vr.GetSimMask(),
                vr.GetTimeStart());

  FairDbConnectionMaintainer cm(fMultConnector);
  FairDbValidityRecBuilder builder(fDBProxy,vc,vrec.GetVersion(),dbNo);

  const FairDbValidityRec& vrecOvlay(builder.GetValidityRecFromAggNo(vrec.GetAggregateNo()));

  ValTimeStamp ovlayTS(vr.GetTimeStart());
  if ( ! vrecOvlay.IsGap() ) {
    time_t overlaySecs = vrecOvlay.GetCreationDate().GetSec();
    ovlayTS = ValTimeStamp(overlaySecs + 60,0);
  }

  DBLOG("FairDb",FairDbLog::kInfo)
      << "Looking for overlay creation date for: "
      << vrec << "found it would overlap: "
      << vrecOvlay << " so overlay creation date set to "
      << ovlayTS.AsString("s") << endl;
  return ovlayTS;
}

Bool_t FairDbTableProxy::RestoreFromL2Cache(const FairDbValidityRecBuilder& builder)
{

  const string name(builder.GetL2CacheName());
  DBLOG("FairDb",FairDbLog::kInfo)  << "RestoreFromL2Cache() Request to restore query result  " << name
                                    << endl;
  if ( ! this->CanReadL2Cache() ) { return kFALSE; }
  string cacheFileName;
  if (  name != ""
     ) cacheFileName =  this->GetTableName() + "_"
                          + this->GetRowName() + "_"
                          +  name + ".db_cache";
  FairDbBinaryFile bf(cacheFileName.c_str());
  if ( ! bf.IsOK() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "Caching disabled or cannot open "
                                      << bf.GetFileName() << endl;
    return kFALSE;
  }

  static bool warnOnce = true;
  if ( warnOnce ) {
    DBLOG("FairDb",FairDbLog::kWarning)   << "\n\n\n"
                                          << " WARNING:  Reading from the Level 2 cache has been activated.\n"
                                          << " *******   This should only be used for development and never for production !!!\n\n\n";
    warnOnce = false;
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "Restoring query result from " << bf.GetFileName() << endl;
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

    const FairDbValidityRec& vrec = result->GetValidityRec();
    UInt_t seqNo = vrec.GetSeqNo();
    DBLOG("FairDb",FairDbLog::kInfo)  << "Fix up L2 cache FairDbValidityRec, by replacing: " << vrec
                                      << "    with: " << builder.GetValidityRecFromSeqNo(seqNo) << endl;

    (const_cast<FairDbValidityRec&>(vrec)) = builder.GetValidityRecFromSeqNo(seqNo);

    if ( ! fCache->Search(vrec) ) {
      numRowsRest += result->GetNumRows();
      fCache->Adopt(result);
      result = 0;
    } else { numRowsIgn += result->GetNumRows(); }
  }
  DBLOG("FairDb",FairDbLog::kInfo) << "   a total of " << numRowsRest << " were restored ("
                                   << numRowsIgn << " ignored - already in memory)" << endl;

  delete result;
  result = 0;

  return numRowsRest > 0;
}

Bool_t FairDbTableProxy::SaveToL2Cache(const string& name, FairDbResult& res)
{

  DBLOG("FairDb",FairDbLog::kInfo)  << "Request to save query result as " << name
                                    << " data from DB? " << res.ResultsFromDb()
                                    << " can be saved? " << res.CanSave() << endl;
  if ( ! this->CanWriteL2Cache() || ! res.ResultsFromDb() || ! res.CanSave() ) { return kFALSE; }

  string cacheFileName;
  if (  name != ""
     ) cacheFileName =  this->GetTableName() + "_"
                          + this->GetRowName() + "_"
                          +  name + ".db_cache";

  FairDbBinaryFile bf(cacheFileName.c_str(),kFALSE);
  if ( bf.IsOK() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "Saving query result (" << res.GetNumRows()
                                      << " rows) to " << bf.GetFileName() << endl;
    FairDbTimerManager::gTimerManager.RecMainQuery();

    if ( dynamic_cast<FairDbResultNonAgg*>(&res) ) {
      UInt_t numNonAgg = 1;
      bf << numNonAgg;
    }
    bf << res;
    return kTRUE;
  }
  DBLOG("FairDb",FairDbLog::kInfo)  << "Caching disabled or cannot open "
                                    << bf.GetFileName() << endl;
  return kFALSE;
}

void FairDbTableProxy::SetSqlCondition(const string& sql)
{
  fDBProxy.SetSqlCondition(sql);
}
