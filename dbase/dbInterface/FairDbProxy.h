
#ifndef FAIRDBPROXY_H
#define FAIRDBPROXY_H


#include <string>
using std::string;
#include <list>
#include <vector>

#include "FairDb.h"

class FairDbMultConnector;
class FairDbResultSet;
class FairDbTableMetaData;
class FairDbTableProxy;
class ValContext;
class ValTimeStamp;

class FairDbProxy
{

  public:

#ifndef __CINT__
    typedef const std::vector<UInt_t> SeqList_t;
#endif

// Constructors.
    FairDbProxy(FairDbMultConnector& cascader,
                const string& tableName,
                const FairDbTableMetaData* metaData,
                const FairDbTableMetaData* metaValid,
                const FairDbTableProxy* tableProxy);
    virtual ~FairDbProxy();
    UInt_t GetNumDb() const;
    const string& GetTableName() const { return fTableNameUc; }
    const FairDbTableProxy* GetTableProxy() const { return fTableProxy; }
    void StoreMetaData(FairDbTableMetaData& metaData) const;
    Bool_t TableExists(Int_t selectDbNo=-1) const;
    void FindTimeBoundaries(const ValContext& vc,
                            const FairDb::Task& task,
                            UInt_t dbNo,
                            ValTimeStamp earliestCreate,
                            ValTimeStamp& start,
                            ValTimeStamp& end) const;
    FairDbResultSet* QueryAllValidities(UInt_t dbNo,UInt_t seqNo=0) const;
    FairDbResultSet* QuerySeqNo(UInt_t seqNo,UInt_t dbNo) const;
#ifndef __CINT__
    /// Secondary query for aggregate and extended context queries.
    FairDbResultSet* QuerySeqNos(SeqList_t& seqNos,
                                 UInt_t dbNo,
                                 const string& sqlData = "",
                                 const string& fillOpts = "") const;
#endif
    FairDbResultSet* QueryValidity(const ValContext& vc,
                                   const FairDb::Task& task,
                                   UInt_t dbNo) const;
    FairDbResultSet* QueryValidity(const string& context,
                                   const FairDb::Task& task,
                                   UInt_t dbNo) const;
    FairDbResultSet* QueryValidity(UInt_t seqNo,
                                   UInt_t dbNo) const;

    // Store (output) member functions
    Bool_t ReplaceInsertDate(const ValTimeStamp& ts,
                             UInt_t SeqNo,
                             UInt_t dbNo) const;
    Bool_t RemoveSeqNo(UInt_t seqNo,
                       UInt_t dbNo) const;
    Bool_t ReplaceSeqNo(UInt_t oldSeqNo,
                        UInt_t newSeqNo,
                        UInt_t dbNo) const;

    // State changing member functions
    void SetSqlCondition(const string& sql) {
      fSqlCondition = sql;
    }

  private:

    Bool_t ReplaceSeqNoOracle(UInt_t oldSeqNo,
                              UInt_t newSeqNo,
                              UInt_t dbNo) const;
    FairDbProxy(const FairDbProxy&);
    FairDbProxy& operator=(const FairDbProxy&);


    FairDbMultConnector& fMultConnector;
    const FairDbTableMetaData* fMetaData;
    const FairDbTableMetaData* fMetaValid;
    string fSqlCondition;
    string fTableName;
    string fTableNameUc;
    const FairDbTableProxy* fTableProxy;
    string fValSuffix;

    ClassDef(FairDbProxy,0)     //  Proxy for physical database.

};

#endif  // FAIRDBPROXY_H
