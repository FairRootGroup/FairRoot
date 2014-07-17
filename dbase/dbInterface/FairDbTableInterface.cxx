/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbTableInterface.h"
#include "FairDbLogService.h"
#include "FairDbBufferFile.h"           // for string, FairDbBufferFile
#include "FairDbCache.h"                // for FairDbCache
#include "FairDbConnectionManager.h"  // for FairDbConnectionManager
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbResult.h"               // for FairDbResultNonCombo, etc
#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "FairDbStopWatchManager.h"         // for FairDbStopWatchManager, etc
#include "FairDbValRecord.h"          // for FairDbValRecord, etc
#include "FairDbValRecordFactory.h"   // for FairDbValRecordFactory
#include "DataType.h"                    // for DataType_t
#include "ValCondition.h"                 // for ValCondition
#include "ValInterval.h"                   // for ValInterval
#include "db_detector_def.h"            // for Detector, etc

#include "Riosfwd.h"                    // for ostream

#include <sys/select.h>                 // for time_t
#include <iostream>                     // for cout
#include <sstream>                      // IWYU pragma: keep
// for operator<<, basic_ostream, etc

using std::cout;
using std::endl;
using std::string;


ClassImp(FairDbTableInterface)


FairDbTableInterface::FairDbTableInterface(FairDbConnectionPool* cascader,
    const string& tableName,
    const string& vldSuffix,
    const FairDbObjTableMap* tableRow) :
  fConnectionPool(cascader),
  fMetaData(tableName),
  fMetaValid(tableName+vldSuffix),
  fCanCache(kFALSE),
  fCache(0),
  fDBProxy(*cascader,tableName,&fMetaData,&fMetaValid,this),
  fExists(0),
  fTableName(tableName),
  fObjTableMap(tableRow->CreateObjTableMap())
{

  fCache = new FairDbCache(*this,fTableName);
  this->RefreshMetaData();
  fExists = fDBProxy.TableExists();
  fCanCache = tableRow->CanCache();
  if ( fCanCache ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "Can  cache " << this->GetRowName() << endl;
  }
  DBLOG("FairDb",FairDbLog::kInfo)  << "created "
                                    << fTableName.c_str() << " at " << this
                                    << ( fExists ? " (table exists)"
                                         : " (table missing)" )
                                    << endl;
  DBLOG("FairDb",FairDbLog::kInfo)<< "Connected Table Row: " << fObjTableMap << endl;

}


FairDbTableInterface::~FairDbTableInterface()
{
  if (fCache) {delete fCache; fCache=NULL;}
  if (fObjTableMap) {delete fObjTableMap; fObjTableMap=NULL;}
}

Bool_t FairDbTableInterface::CanReadCache() const
{
  return fCanCache && FairDbBufferFile::CanReadCache();

}
Bool_t FairDbTableInterface::CanWriteCache() const
{
  return fCanCache && FairDbBufferFile::CanWriteCache();

}
const FairDbResult* FairDbTableInterface::Query(const ValCondition& vc,
    const FairDb::Version& task,
    Bool_t findFullTimeWindow)
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Query fulltimewindow " << findFullTimeWindow <<  endl;
// is info in cache?
  if ( const FairDbResult* result = fCache->Search(vc,task)
     ) { return result; }

  FairDbConnectionManager cm(fConnectionPool);  //Stack object to hold connections

  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  FairDbValRecordFactory factory(fDBProxy,vc,task,-1,findFullTimeWindow);


  if ( factory.NonAggregated() ) {
    DBLOG("FairDb",FairDbLog::kInfo) << " Non Composite Type  " << endl;
    FairDbValRecord effVRec = factory.GetValidityRec(0);
    FairDbResult* result = const_cast<FairDbResult*>(Query(effVRec));
    result->CaptureExceptionLog(startGEL);
    return result;
  }


  DBLOG("FairDb",FairDbLog::kInfo) << "Composite Type " << endl;
  if ( this->CanReadCache() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "reading cache ... " << endl;
    UInt_t numPresent  = 0;
    UInt_t numRequired = 0;
    Int_t maxRow = factory.GetNumValidityRec() - 1;
    for ( Int_t rowNo = 1; rowNo <= maxRow; ++rowNo ) {
      const FairDbValRecord& vrec = factory.GetValidityRec(rowNo);
      if ( fCache->Search(vrec) ) { ++numPresent; }
      else if ( ! vrec.IsGap() ) { ++numRequired; }
    }
    if ( numRequired < numPresent )
      DBLOG("FairDb",FairDbLog::kInfo)  << "Skipping search of  cache; already have "
                                        << numPresent << " composites, and only require a further "
                                        << numRequired << endl;
    else { this->RestoreFromCache(factory); }
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "now do the results --->  " << endl;
  FairDbResult* result = new FairDbResultCombo(fTableName,
      fObjTableMap,
      fCache,
      &factory,
      &fDBProxy);
  result->CaptureExceptionLog(startGEL);

  fCache->Accept(result);
  this->SaveToCache(factory.GetCacheName(),*result);
  return result;

}

const FairDbResult* FairDbTableInterface::Query(const string& context,
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

  FairDbConnectionManager cm(fConnectionPool);  //Stack object to hold connections
  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;
  FairDbValRecordFactory factory(fDBProxy,context,task);

  FairDbResult* result = new FairDbResultCombo(fTableName,
      fObjTableMap,
      fCache,
      &factory,
      &fDBProxy,
      sqlQualifiers);

  result->CaptureExceptionLog(startGEL);

  fCache->Accept(result);
  return result;

}

const FairDbResult* FairDbTableInterface::Query(UInt_t seqNo,UInt_t dbNo)
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Query 2 " << endl;
  FairDbConnectionManager cm(fConnectionPool);

  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  FairDbResultPool* rs = fDBProxy.QueryValidity(seqNo,dbNo);
  FairDbValRecord tr;
  FairDbResultNonCombo result(rs,&tr,0,kFALSE);
  delete rs;

  if ( result.GetNumRows() == 0 ) {
    FairDbResultNonCombo* empty = new FairDbResultNonCombo();
    empty->CaptureExceptionLog(startGEL);
    fCache->Accept(empty);
    return empty;
  }


  const FairDbValRecord* vrec
  = dynamic_cast<const FairDbValRecord*>(result.GetObjTableMap(0));

  FairDbResult* res = const_cast<FairDbResult*>(Query(*vrec,kFALSE));

  res->CaptureExceptionLog(startGEL);
  return res;

}

const FairDbResult* FairDbTableInterface::Query(const FairDbValRecord& vrec,
    Bool_t canReuse )
{

  FairDbConnectionManager cm(fConnectionPool);  //Stack object to hold connections

  UInt_t startGEL = FairDbExceptionLog::GetGELog().Size()+1;

  if ( canReuse ) {
    FairDbValRecordFactory factory(vrec,this->GetTableName());
    if ( this->RestoreFromCache(factory) ) {
      const FairDbResult* res = fCache->Search(vrec);
      if ( res ) { return res; }
    }
  }

  unsigned int seqNo = vrec.GetSeqNo();
  FairDbResult* result = 0;


  if ( ! seqNo ) {
    result = new FairDbResultNonCombo(0,0,&vrec);
  }


  else if (vrec.GetTableInterface()->GetTableName() != GetTableName() ) {

    MAXDBLOG("FairDb",FairDbLog::kError,20)
        << "Unable to satisfy FairDbValRecord keyed query:" << endl
        << vrec
        << " was filled by " << vrec.GetTableInterface()->GetTableName()
        << " not by this FairDbTableInterface ("
        << GetTableName() << ")" << endl;
    result = new FairDbResultNonCombo(0,0,&vrec);
  }

  else {
    DBLOG("FairDb",FairDbLog::kInfo) << "Query(vc)  SEQNO" <<  seqNo << endl;
    FairDbResultPool* rs = fDBProxy.QuerySeqNo(seqNo,vrec.GetDbNo());
    result = new FairDbResultNonCombo(rs,fObjTableMap,&vrec);
    delete rs;
  }

  result->CaptureExceptionLog(startGEL);
//  Cache (memory + disk )
  fCache->Accept(result);
  if ( canReuse ) { this->SaveToCache(vrec.GetCacheName(),*result); }
  else { result->SetCanReuse(kFALSE); }

  return result;
}


void FairDbTableInterface::RefreshMetaData()
{
  fDBProxy.CreateMetaData(fMetaData);
  fDBProxy.CreateMetaData(fMetaValid);
}

ValTimeStamp FairDbTableInterface::QueryOverlayCreationDate(const FairDbValRecord& vrec,
    UInt_t dbNo)
{
  const ValInterval& vr(vrec.GetValInterval());
  ValCondition vc((Detector::Detector_t) vr.GetDetectorMask(),
                  (DataType::DataType_t) vr.GetSimMask(),
                  vr.GetTimeStart());

  FairDbConnectionManager cm(fConnectionPool);
  FairDbValRecordFactory factory(fDBProxy,vc,vrec.GetVersion(),dbNo);

  const FairDbValRecord& vrecOvlay(factory.GetValidityRecFromAggNo(vrec.GetAggregateNo()));

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

Bool_t FairDbTableInterface::RestoreFromCache(const FairDbValRecordFactory& factory)
{

  const string name(factory.GetCacheName());
  DBLOG("FairDb",FairDbLog::kInfo)  << "RestoreFromCache() Request to restore query result  " << name
                                    << endl;
  if ( ! this->CanReadCache() ) { return kFALSE; }
  string cacheFileName;
  if (  name != ""
     ) cacheFileName =  this->GetTableName() + "_"
                          + this->GetRowName() + "_"
                          +  name + ".db_cache";
  FairDbBufferFile bf(cacheFileName.c_str());
  if ( ! bf.IsOK() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "Caching disabled or cannot open "
                                      << bf.GetFileName() << endl;
    return kFALSE;
  }

  static bool warnOnce = true;
  if ( warnOnce ) {
    DBLOG("FairDb",FairDbLog::kWarning)   << "\n\n\n"
                                          << " WARNING:  Reading from the Level 2 cache has been activated.\n"
                                          << " *******   This mode should be used only for development and not for production !!!\n\n\n";
    warnOnce = false;
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "Restoring query result from " << bf.GetFileName() << endl;
  FairDbStopWatchManager::gStopWatchManager.RecMainQuery();

  FairDbResult* result    = 0;
  unsigned numRowsRest = 0;
  unsigned numRowsIgn  = 0;
  UInt_t numNonAgg     = 0;
  bf >> numNonAgg;

  while ( numNonAgg-- ) {
    if ( ! bf.IsOK() ) { break; }
    if ( ! result ) { result = new FairDbResultNonCombo; }
    bf >> *result;

    const FairDbValRecord& vrec = result->GetValidityRec();
    UInt_t seqNo = vrec.GetSeqNo();
    DBLOG("FairDb",FairDbLog::kInfo)  << "Fix up  cache FairDbValRecord, by replacing: " << vrec
                                      << "    with: " << factory.GetValidityRecFromSeqNo(seqNo) << endl;

    (const_cast<FairDbValRecord&>(vrec)) = factory.GetValidityRecFromSeqNo(seqNo);

    if ( ! fCache->Search(vrec) ) {
      numRowsRest += result->GetNumRows();
      fCache->Accept(result);
      result = 0;
    } else { numRowsIgn += result->GetNumRows(); }
  }
  DBLOG("FairDb",FairDbLog::kInfo) << "   a total of " << numRowsRest << " were restored ("
                                   << numRowsIgn << " ignored - already in memory)" << endl;

  delete result;
  result = 0;

  return numRowsRest > 0;
}

Bool_t FairDbTableInterface::SaveToCache(const string& name, FairDbResult& res)
{

  DBLOG("FairDb",FairDbLog::kInfo)  << "Request to save query result as " << name
                                    << " data from DB? " << res.ResultsFromDb()
                                    << " can be saved? " << res.CanSave() << endl;
  if ( ! this->CanWriteCache() || ! res.ResultsFromDb() || ! res.CanSave() ) { return kFALSE; }

  string cacheFileName;
  if (  name != ""
     ) cacheFileName =  this->GetTableName() + "_"
                          + this->GetRowName() + "_"
                          +  name + ".db_cache";

  FairDbBufferFile bf(cacheFileName.c_str(),kFALSE);
  if ( bf.IsOK() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "Saving query result (" << res.GetNumRows()
                                      << " rows) to " << bf.GetFileName() << endl;
    FairDbStopWatchManager::gStopWatchManager.RecMainQuery();

    if ( dynamic_cast<FairDbResultNonCombo*>(&res) ) {
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

void FairDbTableInterface::SetSqlCondition(const string& sql)
{
  fDBProxy.SetSqlCondition(sql);
}
