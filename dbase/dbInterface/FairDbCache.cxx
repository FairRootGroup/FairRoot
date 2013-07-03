#include "FairDbCache.h"

#include "FairDbLogFormat.h"
#include "FairDbLogService.h"

#include "FairDbResult.h"               // for FairDbResult, operator<<
#include "FairDbSimFlagAssociation.h"   // for FairDbSimFlagAssociation, etc
#include "FairDbValidityRec.h"          // for operator<<, etc
#include "SimFlag.h"                    // for AsString, SimFlag_t
#include "ValContext.h"                 // for ValContext, operator<<
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


FairDbCache::FairDbCache(FairDbTableProxy& qp,const string& tableName) :
  fTableProxy(qp),
  fTableName(tableName),
  fCache(),
  fCurSize(0),
  fMaxSize(0),
  fNumAdopted(0),
  fNumReused(0)
{
  DBLOG("FairDb", FairDbLog::kVerbose) << "Creating FairDbCache" << endl;
}

FairDbCache::~FairDbCache()
{

  // Purge the AggNo == -1 cache before deleting.  For extended
  // context queries it can have FairDbResultAggs that are clients of
  // FairDbResultNonAggs in the same cache, so purging will remove clientless
  // FairDbResultAggs which should in turn make their FairDbResultNonAggs
  // clientless.
  if ( this->GetSubCache(-1) ) { this->Purge(fCache[-1]); }

  for ( CacheItr_t itr = fCache.begin(); itr != fCache.end(); ++itr) {
    ResultList_t& subCache = itr->second;
    for ( SubCacheItr_t sitr = subCache.begin();
          sitr != subCache.end();
          ++sitr) { delete *sitr; }
  }

}

void FairDbCache::Adopt(FairDbResult* res,bool registerKey)
{
  if ( ! res ) { return; }
  int aggNo = res->GetValidityRec().GetAggregateNo();

//  Prime sub-cache if necessary.
  if ( ! this->GetSubCache(aggNo) ) {
    ResultList_t emptyList;
    fCache[aggNo] = emptyList;
  }

//  Purge expired entries and add new result to cache.
  ResultList_t& subCache = fCache[aggNo];
  Purge(subCache, res);
  subCache.push_back(res);
  ++fCurSize;
  ++fNumAdopted;
  DBLOG("FairDb",FairDbLog::kInfo) << "Adopting result for " << res->TableName()
                                   << "  " <<   res->GetValidityRecGlobal()
                                   << "\nCache size now " << fCurSize << endl;
  if ( fCurSize > fMaxSize ) { fMaxSize = fCurSize; }
  // If required register key with FairDbRecord
  if ( registerKey ) {
    res->RegisterKey();
    DBLOG("FairDb",FairDbLog::kInfo) << "Caching new results: ResultKey: " <<  *res->GetKey();
  }
}

//.....................................................................

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

      DBLOG("FairDb",FairDbLog::kInfo) << "Purging " << pRes->GetValidityRec()
                                       << " from " << pRes->TableName()
                                       << " cache. Cache size now "
                                       << fCurSize-1 << endl;
      delete pRes;
//    Erasing increments iterator.
      itr = subCache.erase(itr);
      --fCurSize;

    } else {
      ++itr;
    }
  }

}

const FairDbResult* FairDbCache::Search(const FairDbValidityRec& vrec,
                                        const string& sqlQualifiers) const
{

  Int_t aggNo = vrec.GetAggregateNo();

  DBLOG("FairDb",FairDbLog::kInfo) << "Secondary cache search of table " << fTableName
                                   << " for  " << vrec
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


const FairDbResult* FairDbCache::Search(const ValContext& vc,
                                        const FairDb::Version& task ) const
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search of table " << fTableName
                                   << " for  " << vc
                                   << " with Version " << task << endl;
  const ResultList_t* subCache = this->GetSubCache(-1);
  if ( ! subCache ) {
    DBLOG("FairDb",FairDbLog::kWarning) << "Primary cache search failed - sub-cache -1 is empty" << endl;
    return 0;
  }

  // Loop over all possible SimFlag associations.

  Detector::Detector_t     det(vc.GetDetector());
  SimFlag::SimFlag_t       sim(vc.GetSimFlag());
  ValTimeStamp              ts(vc.GetTimeStamp());

  FairDbSimFlagAssociation::SimList_t simList
  = FairDbSimFlagAssociation::Instance().Get(sim);

  FairDbSimFlagAssociation::SimList_t::iterator listItr    = simList.begin();
  FairDbSimFlagAssociation::SimList_t::iterator listItrEnd = simList.end();
  while ( listItr !=  listItrEnd ) {

    SimFlag::SimFlag_t simTry = *listItr;
    ValContext vcTry(det,simTry,ts);

    DBLOG("FairDb",FairDbLog::kInfo) << "  Searching cache with SimFlag: "
                                     << SimFlag::AsString(simTry) << endl;
    for ( ConstSubCacheItr_t itr = subCache->begin();
          itr != subCache->end();
          ++itr) {
      FairDbResult* res = *itr;
      if ( res->Satisfies(vcTry,task) ) {
        fNumReused += res->GetNumAggregates();
        DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search succeeded. Result set no. of rows: "
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
      DBLOG("FairDb",FairDbLog::kInfo) << "Primary cache search succeeded Result set no. of rows: "
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
      << ifmt(fNumAdopted) << ifmt(fNumReused);
  return msg;

}
