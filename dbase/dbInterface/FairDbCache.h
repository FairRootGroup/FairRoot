#ifndef FAIRDBCACHE_H
#define FAIRDBCACHE_H

#include <list>
#include <map>
#include <string>
using std::string;

#include "FairDb.h"

class ValContext;
class FairDbResult;
class FairDbTableProxyRegistry;
class FairDbTableProxy;
class FairDbValidityRec;
//class MsgStream;

class FairDbCache
{

  public:

// Typedefs

    typedef std::list<FairDbResult*> ResultList_t;

// Constructors and destructors.

    FairDbCache(FairDbTableProxy& qp,
                const string& tableName);
    virtual ~FairDbCache();


// State testing member functions
    UInt_t GetMaxSize() const { return fMaxSize; }
    UInt_t GetCurSize() const { return fCurSize; }
    UInt_t GetNumAdopted() const { return fNumAdopted; }
    UInt_t GetNumReused() const { return fNumReused; }
/// Primary searches.
    const FairDbResult* Search(const ValContext& vc,
                               const FairDb::Task& task) const;
    const FairDbResult* Search(const string& sqlQualifiers) const;

/// Secondary search.
    const FairDbResult* Search(const FairDbValidityRec& vr,
                               const string& sqlQualifiers = "") const;
//      MsgStream& ShowStatistics(MsgStream& msg) const;

// State changing member functions
    void Adopt(FairDbResult* res,bool registerKey = true);
    void Purge();
    void SetStale();

  protected:


  private:

    FairDbCache(const FairDbCache&);
    FairDbCache& operator=(const FairDbCache&);

    const ResultList_t* GetSubCache(Int_t aggNo) const;
    void Purge(ResultList_t& subCache, const FairDbResult* res=0);



    FairDbTableProxy&  fTableProxy;

    const string& fTableName;
    std::map<Int_t,ResultList_t> fCache;
    mutable UInt_t fCurSize;
    mutable UInt_t fMaxSize;
    mutable UInt_t fNumAdopted;
    mutable UInt_t fNumReused;


    ClassDef(FairDbCache,0)  //Query result cache for specific database table.

};


#endif  // FAIRDBCACHE_H
