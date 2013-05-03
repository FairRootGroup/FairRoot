#ifndef FAIRDBTABLEPROXY_H
#define FAIRDBTABLEPROXY_H

#include "FairDb.h"                     // for Version
#include "FairDbProxy.h"                // for FairDbProxy
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData
#include "FairDbTableRow.h"             // for FairDbTableRow
#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Rtypes.h"                     // for Bool_t, UInt_t, etc

#include <string>                       // for string

class FairDbCache;
class FairDbMultConnector;
class FairDbResult;
class FairDbValidityRec;
class FairDbValidityRecBuilder;
class ValContext;


class FairDbTableProxy
{

    friend class FairDbTableProxyRegistry;

  public:

// State testing member functions
    const FairDbProxy& GetDBProxy() const { return fDBProxy; }
    FairDbMultConnector& GetMultConnector() { return *fMultConnector; }
    const FairDbTableMetaData& GetMetaData() const { return fMetaData; }
    const FairDbTableMetaData& GetMetaValid() const { return fMetaValid; }
    std::string GetRowName() const {
      return fTableRow ? fTableRow->ClassName() : "Unknown";
    }
    std::string GetTableName() const { return fTableName;}
// State changing member functions
    FairDbCache* GetCache() { return fCache;}
    const FairDbResult* Query(const ValContext& vc,
                              const FairDb::Version& task,
                              Bool_t findFullTimeWindow = true);
    const FairDbResult* Query(const std::string& context,
                              const FairDb::Version& task,
                              const std::string& data,
                              const std::string& fillOpts);
    const FairDbResult* Query(UInt_t seqNo,UInt_t dbNo);
    const FairDbResult* Query(const FairDbValidityRec& vrec,
                              Bool_t canReuse = kTRUE);
    ValTimeStamp QueryOverlayCreationDate(const FairDbValidityRec& vrec,
                                          UInt_t dbNo);
    void RefreshMetaData();
    void SetSqlCondition(const std::string& sql);
    Bool_t TableExists() const { return fExists; }

  protected:

// Constructors (protected because created and owned by FairDbTableProxyRegistry).
    FairDbTableProxy(FairDbMultConnector* cascader,
                     const std::string& tableName,
                     const std::string& vldSuffix,
                     const FairDbTableRow* tableRow);
    virtual ~FairDbTableProxy();

  private:


    FairDbTableProxy(const FairDbTableProxy&);
    FairDbTableProxy& operator=(const FairDbTableProxy&);


// Level 2 (disk) cache management.
    Bool_t CanReadL2Cache() const;
    Bool_t CanWriteL2Cache() const;
    Bool_t RestoreFromL2Cache(const FairDbValidityRecBuilder& builder);
    Bool_t SaveToL2Cache(const std::string& name, FairDbResult& res);


    FairDbMultConnector* fMultConnector;
    FairDbTableMetaData fMetaData;
    FairDbTableMetaData fMetaValid;
    Bool_t fCanL2Cache;
    FairDbCache* fCache;
    FairDbProxy fDBProxy;
    Bool_t fExists;
    std::string  fTableName;
    FairDbTableRow* fTableRow;

    ClassDef(FairDbTableProxy,0)        // Object to query a specific table.

};


#endif  // FAIRDBTABLEPROXY_H
