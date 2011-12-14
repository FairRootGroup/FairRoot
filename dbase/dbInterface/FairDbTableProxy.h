#ifndef FAIRDBTABLEPROXY_H
#define FAIRDBTABLEPROXY_H

#include <string>
#include <sstream>
using std::string;

#include "FairDb.h"
#include "FairDbProxy.h"
#include "FairDbTableMetaData.h"
#include "FairDbValidityRec.h"
#include "ValContext.h"
#include "ValTimeStamp.h"

class FairDbCache;
class FairDbMultConnector;
class FairDbResult;
class FairDbTableProxyRegistry;
class FairDbTableRow;
class FairDbValidityRec;
class FairDbValidityRecBuilder;

class FairDbTableProxy
{

    friend class FairDbTableProxyRegistry;

  public:

// State testing member functions
    const FairDbProxy& GetDBProxy() const { return fDBProxy; }
    FairDbMultConnector& GetMultConnector() { return *fMultConnector; }
    const FairDbTableMetaData& GetMetaData() const { return fMetaData; }
    const FairDbTableMetaData& GetMetaValid() const { return fMetaValid; }
    string GetRowName() const {
      return fTableRow ? fTableRow->ClassName() : "Unknown";
    }
    string GetTableName() const { return fTableName;}
// State changing member functions
    FairDbCache* GetCache() { return fCache;}
    const FairDbResult* Query(const ValContext& vc,
                              const FairDb::Task& task,
                              Bool_t findFullTimeWindow = true);
    const FairDbResult* Query(const string& context,
                              const FairDb::Task& task,
                              const string& data,
                              const string& fillOpts);
    const FairDbResult* Query(UInt_t seqNo,UInt_t dbNo);
    const FairDbResult* Query(const FairDbValidityRec& vrec,
                              Bool_t canReuse = kTRUE);
    ValTimeStamp QueryOverlayCreationDate(const FairDbValidityRec& vrec,
                                          UInt_t dbNo);
    void RefreshMetaData();
    void SetSqlCondition(const string& sql);
    Bool_t TableExists() const { return fExists; }

  protected:

// Constructors (protected because created and owned by FairDbTableProxyRegistry).
    FairDbTableProxy(FairDbMultConnector* cascader,
                     const string& tableName,
                     const string& vldSuffix,
                     const FairDbTableRow* tableRow);
    virtual ~FairDbTableProxy();

  private:


    FairDbTableProxy(const FairDbTableProxy&);
    FairDbTableProxy& operator=(const FairDbTableProxy&);


// Level 2 (disk) cache management.
    Bool_t CanReadL2Cache() const;
    Bool_t CanWriteL2Cache() const;
    Bool_t RestoreFromL2Cache(const FairDbValidityRecBuilder& builder);
    Bool_t SaveToL2Cache(const string& name, FairDbResult& res);


    FairDbMultConnector* fMultConnector;
    FairDbTableMetaData fMetaData;
    FairDbTableMetaData fMetaValid;
    Bool_t fCanL2Cache;
    FairDbCache* fCache;
    FairDbProxy fDBProxy;
    Bool_t fExists;
    string  fTableName;
    FairDbTableRow* fTableRow;

    ClassDef(FairDbTableProxy,0)        // Object to query a specific table.

};


#endif  // FAIRDBTABLEPROXY_H
