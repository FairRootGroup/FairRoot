#ifndef FAIRDBTABLEPROXYREGISTRY_H
#define FAIRDBTABLEPROXYREGISTRY_H


#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#include <map>
#include <string>
#include <cstdlib>

#include "FairDbConfigurable.h"
#include "FairDbSimFlagAssociation.h"
#include "FairDbRollbackDates.h"


class FairDbMultConnector;
class FairDbTableProxy;
class FairDbTableRow;

class FairDbTableProxyRegistry : public FairDbConfigurable
{

  public:

// State testing member functions
    void ShowStatistics() const;

// State changing member functions
    static FairDbTableProxyRegistry& Instance();
    static       Bool_t IsActive() { return fgInstance ? kTRUE: kFALSE; }

    void Config();
    void ClearRollbackDates();
    void ClearSimFlagAssociation();
    FairDbMultConnector& GetMultConnector() { return *fMultConnector; }
    FairDbTableProxy& GetTableProxy(const std::string& tableName,
                                    const FairDbTableRow* tableRow) ;
    Bool_t HasRowCounter(const std::string& tableName);
    void PurgeCaches();
    void RefreshMetaData(const std::string& tableName);
    void SetSqlCondition(const std::string& sql="");

  protected:

// Constructors (protected because singleton).
    FairDbTableProxyRegistry();
    virtual ~FairDbTableProxyRegistry();

  private:

    void SetConfigFromEnvironment();

  public:

    struct Cleaner {
      static int fgCount; // counts #includes
      Cleaner() { this->Increment(); }
      ~Cleaner() {
        if (--fgCount==0 && FairDbTableProxyRegistry::fgInstance!=0) {
          delete FairDbTableProxyRegistry::fgInstance;
          FairDbTableProxyRegistry::fgInstance = 0;
        }
      }
      void Increment() { ++fgCount; };
    };
    friend class Cleaner;


/// MultConnector
    FairDbMultConnector* fMultConnector;


  private:


    FairDbTableProxyRegistry(const FairDbTableProxyRegistry&);
    FairDbTableProxyRegistry& operator=(const FairDbTableProxyRegistry&);

// State testing member functions
    void ApplySqlCondition() const;
    void ApplySqlCondition(FairDbTableProxy* proxy) const;

// Data members


/// Default optional condition.
    std::string fSqlCondition;

#ifndef __CINT__  // Hide map from CINT; complains: missing Streamer() etc.
/// TableName::RowName -> TableProxy
    std::map<std::string,FairDbTableProxy*> fTPmap;
#endif  // __CINT__   

/// Rollback dates for each table.
    FairDbRollbackDates fRollbackDates;

/// Lists of SimFlag associations.
    FairDbSimFlagAssociation fSimFlagAss;


/// Holds only instance
    static FairDbTableProxyRegistry* fgInstance;

    ClassDef(FairDbTableProxyRegistry,0)   // Singleton register FairDbTableProxys.

};

#ifndef __CINT__
/// Count the number of #includes for this class
static struct FairDbTableProxyRegistry::Cleaner __dbi_cleaner;
#endif

#endif  // FAIRDBTABLEPROXYREGISTRY_H
