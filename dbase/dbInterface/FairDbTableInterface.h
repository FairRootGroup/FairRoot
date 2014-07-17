/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBTABLEINTERFACE_H
#define FAIRDBTABLEINTERFACE_H

#include "FairDb.h"                     // for Version
#include "FairDbProxy.h"                // for FairDbProxy
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData
#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Rtypes.h"                     // for Bool_t, UInt_t, etc

#include <string>                       // for string

class FairDbCache;
class FairDbConnectionPool;
class FairDbResult;
class FairDbValRecord;
class FairDbValRecordFactory;
class ValCondition;


class FairDbTableInterface
{

    friend class FairDbTableInterfaceStore;

  public:
    const FairDbProxy& GetDBProxy() const { return fDBProxy; }
    FairDbConnectionPool& GetConnectionPool() { return *fConnectionPool; }
    const FairDbTableMetaData& GetMetaData() const { return fMetaData; }
    const FairDbTableMetaData& GetMetaValid() const { return fMetaValid; }
    std::string GetRowName() const {
      return fObjTableMap ? fObjTableMap->ClassName() : "Unknown";
    }
    std::string GetTableName() const { return fTableName;}

    FairDbCache* GetCache() { return fCache;}
    const FairDbResult* Query(const ValCondition& vc,
                              const FairDb::Version& task,
                              Bool_t findFullTimeWindow = true);
    const FairDbResult* Query(const std::string& context,
                              const FairDb::Version& task,
                              const std::string& data,
                              const std::string& fillOpts);
    const FairDbResult* Query(UInt_t seqNo,UInt_t dbNo);
    const FairDbResult* Query(const FairDbValRecord& vrec,
                              Bool_t canReuse = kTRUE);
    ValTimeStamp QueryOverlayCreationDate(const FairDbValRecord& vrec,
                                          UInt_t dbNo);
    void RefreshMetaData();
    void SetSqlCondition(const std::string& sql);
    Bool_t TableExists() const { return fExists; }


  protected:
    FairDbTableInterface(FairDbConnectionPool* cascader,
                         const std::string& tableName,
                         const std::string& vldSuffix,
                         const FairDbObjTableMap* tableRow);
    virtual ~FairDbTableInterface();

  private:

    FairDbTableInterface(const FairDbTableInterface&);
    FairDbTableInterface& operator=(const FairDbTableInterface&);


// Level 2 (disk) cache management.
    Bool_t CanReadCache() const;
    Bool_t CanWriteCache() const;
    Bool_t RestoreFromCache(const FairDbValRecordFactory& factory);
    Bool_t SaveToCache(const std::string& name, FairDbResult& res);


    FairDbConnectionPool* fConnectionPool;
    FairDbTableMetaData fMetaData;
    FairDbTableMetaData fMetaValid;
    Bool_t fCanCache;
    FairDbCache* fCache;
    FairDbProxy fDBProxy;
    Bool_t fExists;
    std::string  fTableName;
    FairDbObjTableMap* fObjTableMap;

    ClassDef(FairDbTableInterface,0)        // Object to query a specific table.

};


#endif  // FAIRDBTABLEINTERFACE_H
