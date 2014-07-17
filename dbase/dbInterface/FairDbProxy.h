/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRDBPROXY_H
#define FAIRDBPROXY_H

#include "FairDb.h"                     // for Version

#include "Rtypes.h"                     // for UInt_t, Bool_t, etc

#include <string>                       // for string
#include <vector>                       // for vector

class FairDbConnectionPool;
class FairDbResultPool;
class FairDbTableMetaData;
class FairDbTableInterface;
class ValCondition;
class ValTimeStamp;

class FairDbProxy
{

  public:

#ifndef __CINT__
    typedef const std::vector<UInt_t> SeqList_t;
#endif

    FairDbProxy(FairDbConnectionPool& cascader,
                const std::string& tableName,
                const FairDbTableMetaData* metaData,
                const FairDbTableMetaData* metaValid,
                const FairDbTableInterface* tableProxy);
    virtual ~FairDbProxy();

    UInt_t GetNumDb() const;
    const std::string& GetTableName() const { return fTableNameUc; }
    const FairDbTableInterface* GetTableInterface() const { return fTableInterface; }
    void CreateMetaData(FairDbTableMetaData& metaData) const;
    Bool_t TableExists(Int_t selectDbNo=-1) const;
    void FindTimeLimits(const ValCondition& vc,
                        const FairDb::Version& task,
                        UInt_t dbNo,
                        ValTimeStamp earliestCreate,
                        ValTimeStamp& start,
                        ValTimeStamp& end) const;
    FairDbResultPool* QueryAllValidities(UInt_t dbNo,UInt_t seqNo=0) const;
    FairDbResultPool* QuerySeqNo(UInt_t seqNo,UInt_t dbNo) const;
#ifndef __CINT__
    FairDbResultPool* QuerySeqNos(SeqList_t& seqNos,
                                  UInt_t dbNo,
                                  const std::string& sqlData = "",
                                  const std::string& fillOpts = "") const;
#endif
    FairDbResultPool* QueryValidity(const ValCondition& vc,
                                    const FairDb::Version& task,
                                    UInt_t dbNo) const;
    FairDbResultPool* QueryValidity(const std::string& context,
                                    const FairDb::Version& task,
                                    UInt_t dbNo) const;
    FairDbResultPool* QueryValidity(UInt_t seqNo,
                                    UInt_t dbNo) const;


    Bool_t ReplaceInsertDate(const ValTimeStamp& ts,
                             UInt_t SeqNo,
                             UInt_t dbNo) const;
    Bool_t RemoveSeqNo(UInt_t seqNo,
                       UInt_t dbNo) const;
    Bool_t ReplaceSeqNo(UInt_t oldSeqNo,
                        UInt_t newSeqNo,
                        UInt_t dbNo) const;


    void SetSqlCondition(const std::string& sql) {
      fSqlCondition = sql;
    }

  private:

    Bool_t ReplaceSeqNoOracle(UInt_t oldSeqNo,
                              UInt_t newSeqNo,
                              UInt_t dbNo) const;
    FairDbProxy(const FairDbProxy&);
    FairDbProxy& operator=(const FairDbProxy&);


    FairDbConnectionPool& fConnectionPool;
    const FairDbTableMetaData* fMetaData;
    const FairDbTableMetaData* fMetaValid;
    std::string fSqlCondition;
    std::string fTableName;
    std::string fTableNameUc;
    const FairDbTableInterface* fTableInterface;
    std::string fValSuffix;

    ClassDef(FairDbProxy,0)     //  Proxy for physical database.

};

#endif  // FAIRDBPROXY_H
