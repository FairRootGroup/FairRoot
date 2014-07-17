/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbCache.h"

#include "FairDbLogFormat.h"
#include "FairDbLogService.h"

#include "FairDbResult.h"               // for FairDbResult, operator<<
#include "FairDbDataTypeUnion.h"         // for FairDbDataTypeUnion, etc
#include "FairDbValRecord.h"          // for operator<<, etc
#include "DataType.h"                    // for AsString, DataType_t
#include "ValCondition.h"                 // for ValCondition, operator<<
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector, etc

#include "Riosfwd.h"                    // for ostream

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <utility>                      // for pair

using std::cout;
using std::endl;
using std::map;
using std::string;

ClassImp(FairDbCache)


typedef FairDbCache::ResultList_t ResultList_t;
typedef map<Int_t,ResultList_t>::const_iterator ConstCacheItr_t;
typedef map<Int_t,ResultList_t>::iterator CacheItr_t;
typedef ResultList_t::const_iterator ConstSubCacheItr_t;
typedef ResultList_t::iterator SubCacheItr_t;


FairDbCache::FairDbCache(FairDbTableInterface& qp,const string& tableName) :
  fTableInterface(qp),
  fTableName(tableName),
  fCache(),
  fCurSize(0),
  fMaxSize(0),
  fNumAccepted(0),
  fNumReused(0)
{
  DBLOG("FairDb", FairDbLog::kVerbose) << "Creating FairDbCache" << endl;
}

FairDbCache::~FairDbCache()
{

  if ( this->GetSubCache(-1) ) { this->Purge(fCache[-1]); }

  for ( CacheItr_t itr = fCache.begin(); itr != fCache.end(); ++itr) {
    ResultList_t& subCache = itr->second;
    for ( SubCacheItr_t sitr = subCache.begin();
          sitr != subCache.end();
          ++sitr) { delete *sitr; }
  }

}

void FairDbCache::Accept(FairDbResult* res,bool registerKey)
{
  if ( ! res ) { return; }
  int aggNo = res->GetValidityRec().GetAggregateNo();

  if ( ! this->GetSubCache(aggNo) ) {
    ResultList_t emptyList;
    fCache[aggNo] = emptyList;
  }

  ResultList_t& subCache = fCache[aggNo];
  Purge(subCache, res);
  subCache.push_back(res);
  ++fCurSize;
  ++fNumAccepted;
  DBLOG("FairDb",FairDbLog::kInfo) << "Registering result for: " << res->TableName()
                                   << "  " <<   res->GetValidityRecGlobal()
                                   << "\nCache size updated: " << fCurSize << endl;
  if ( fCurSize > fMaxSize ) { fMaxSize = fCurSize; }

  if ( registerKey ) {
    res->RegisterKey();
    DBLOG("FairDb",FairDbLog::kInfo) << "Caching results @ <ResKey># " <<  *res->GetKey();
  }
}


const ResultList_t* FairDbCache::GetSubCache(Int_t aggNo) const
{
  ConstCacheItr_t itr = fCache.find(aggNo);
  return ( itr == fCache.end() ) ? 0 : &itr->second;

}

void FairDbCache::Purge()
{

  for ( CacheItr_t itr = fCache.begin(); itr != fCache.end(); ++itr
      ) { Purge(itr->second); }

}

void FairDbCache::Purge(ResultList_t& subCache, const FairDbResult* res)
{

  for ( SubCacheItr_t itr = subCache.begin(); itr != subCache.end(); ) {
    FairDbResult* pRes = *itr;

    if (      pRes->GetNumClients() == 0
              && (    ! res
                      || pRes->CanDelete(res)  ) ) {

      DBLOG("FairDb",FairDbLog::kInfo) << "Purging: " << pRes->GetValidityRec()
                                       << " from: " << pRes->TableName()
                                       << " cache. Cache size updated: "
                                       << fCurSize-1 << endl;
      delete pRes;
      // Erase Iterators
      itr = subCache.erase(itr);
      --fCurSize;

    } else {
      ++itr;
    }
  }

}

const FairDbResult* FairDbCache::Search(const FairDbValRecord& vrec,
                                        const string& sqlQualifiers) const
{

  Int_t aggNo = vrec.GetAggregateNo();

  DBLOG("FairDb",FairDbLog::kInfo) << "Secondary cache search of table: " << fTableName
                                   << " for:  " << vrec
                                   << (sqlQualifiers != "" ? sqlQualifiers : "" ) << endl;
  const ResultList_t* subCache = this->GetSubCache(aggNo);
  if ( ! subCache ) {
    DBLOG("FairDb",FairDbLog::kInfo) << "Secondary cache search failed." << endl;
    return 0;
  }

  ConstSubCacheItr_t itrEnd = subCache->end();
  for ( ConstSubCacheItr_t itr = subCache->begin();
        itr != itrEnd;
        ++itr) {
    FairDbResult* res = *itr;
    if ( res->Satisfies(vrec,sqlQualifiers) ) {
      fNumReused += res->GetNumAggregates();
      DBLOG("FairDb",FairDbLog::kInfo) << "Secondary cache search succeeded.  Result set no. of rows: "
                                       << res->GetNumRows() << endl;
      return res;
    }
  }

  DBLOG("FairDb",FairDbLog::kWarning) << "Secondary cache search failed." << endl;
  return 0;
}


const FairDbResult* FairDbCache::Search(const ValCondition& vc,
                                        const FairDb::Version& task ) const
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search of table: " << fTableName
                                   << " for:  " << vc
                                   << " with Version: " << task << endl;
  const ResultList_t* subCache = this->GetSubCache(-1);
  if ( ! subCache ) {
    DBLOG("FairDb",FairDbLog::kWarning) << "Primary cache search failed :: (derived-cache-1) is empty" << endl;
    return 0;
  }

  // Loop over all possible DataType associations.

  Detector::Detector_t     det(vc.GetDetector());
  DataType::DataType_t       sim(vc.GetDataType());
  ValTimeStamp              ts(vc.GetTimeStamp());

  FairDbDataTypeUnion::SimList_t simList
  = FairDbDataTypeUnion::Instance().Get(sim);

  FairDbDataTypeUnion::SimList_t::iterator listItr    = simList.begin();
  FairDbDataTypeUnion::SimList_t::iterator listItrEnd = simList.end();
  while ( listItr !=  listItrEnd ) {

    DataType::DataType_t simTry = *listItr;
    ValCondition vcTry(det,simTry,ts);

    DBLOG("FairDb",FairDbLog::kInfo) << "  Searching cache with DataType: "
                                     << DataType::AsString(simTry) << endl;
    for ( ConstSubCacheItr_t itr = subCache->begin();
          itr != subCache->end();
          ++itr) {
      FairDbResult* res = *itr;
      if ( res->Satisfies(vcTry,task) ) {
        fNumReused += res->GetNumAggregates();
        DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search succeeded. Result set nb# of rows: "
                                         << res->GetNumRows() << endl;
        return res;
      }
    }

    DBLOG("FairDb",FairDbLog::kWarning) << "Primary cache search failed." << endl;
    ++listItr;
  }

  return 0;
}

const FairDbResult* FairDbCache::Search(const string& sqlQualifiers) const
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search of table " << fTableName
                                   << " for  SQL " << sqlQualifiers << endl;
  const ResultList_t* subCache = this->GetSubCache(-1);
  if ( ! subCache ) {
    DBLOG("FairDb",FairDbLog::kWarning) << "Primary cache search failed" << endl;
    return 0;
  }
  for ( ConstSubCacheItr_t itr = subCache->begin();
        itr != subCache->end();
        ++itr) {
    FairDbResult* res = *itr;
    if ( res->Satisfies(sqlQualifiers) ) {
      fNumReused += res->GetNumAggregates();
      DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search succeeded Result set nb# of rows: "
                                       << res->GetNumRows() << endl;
      return res;
    }
  }
  DBLOG("FairDb",FairDbLog::kWarning) << "Primary cache search failed" << endl;
  return 0;
}

void FairDbCache::SetStale()
{

  for ( CacheItr_t cacheItr = fCache.begin();
        cacheItr != fCache.end();
        ++cacheItr
      ) {
    ResultList_t& subcache = cacheItr->second;

    for ( SubCacheItr_t subcacheItr = subcache.begin();
          subcacheItr != subcache.end();
          ++subcacheItr ) { (*subcacheItr)->SetCanReuse(kFALSE); }
  }

}


FairDbLogStream& FairDbCache::ShowStatistics(FairDbLogStream& msg) const
{

  FairDbLogFormat ifmt("%10i");

  msg << ifmt(fCurSize) << ifmt(fMaxSize)
      << ifmt(fNumAccepted) << ifmt(fNumReused);
  return msg;

}
