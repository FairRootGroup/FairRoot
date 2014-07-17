/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBCACHE_H
#define FAIRDBCACHE_H

#include "FairDb.h"                     // for Version

#include "Rtypes.h"                     // for UInt_t, Int_t, etc

#include <list>                         // for list
#include <map>                          // for map
#include <string>                       // for string

class FairDbResult;
class FairDbTableInterface;
class FairDbValRecord;
class ValCondition;
class FairDbLogStream;

class FairDbCache
{

  public:

// Typedefs

    typedef std::list<FairDbResult*> ResultList_t;

    FairDbCache(FairDbTableInterface& qp,
                const std::string& tableName);
    virtual ~FairDbCache();

    UInt_t GetMaxSize() const { return fMaxSize; }
    UInt_t GetCurSize() const { return fCurSize; }
    UInt_t GetNumAccepted() const { return fNumAccepted; }
    UInt_t GetNumReused() const { return fNumReused; }

    const FairDbResult* Search(const ValCondition& vc,
                               const FairDb::Version& task) const;
    const FairDbResult* Search(const std::string& sqlQualifiers) const;


    const FairDbResult* Search(const FairDbValRecord& vr,
                               const std::string& sqlQualifiers = "") const;

    FairDbLogStream& ShowStatistics(FairDbLogStream& msg) const;


    void Accept(FairDbResult* res,bool registerKey = true);
    void Purge();
    void SetStale();
    void SetStatic(){ return SetStale();}

  protected:


  private:

    FairDbCache(const FairDbCache&);
    FairDbCache& operator=(const FairDbCache&);

    const ResultList_t* GetSubCache(Int_t aggNo) const;
    void Purge(ResultList_t& subCache, const FairDbResult* res=0);


    FairDbTableInterface&  fTableInterface;

    const std::string& fTableName;
    std::map<Int_t,ResultList_t> fCache;

    mutable UInt_t fCurSize;
    mutable UInt_t fMaxSize;
    mutable UInt_t fNumAccepted;
    mutable UInt_t fNumReused;


    ClassDef(FairDbCache,0)  //Query result cache

};


#endif  // FAIRDBCACHE_H
