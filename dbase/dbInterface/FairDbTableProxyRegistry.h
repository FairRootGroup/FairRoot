#ifndef FAIRDBTABLEPROXYREGISTRY_H
#define FAIRDBTABLEPROXYREGISTRY_H

#include "FairDbConfigurable.h"         // for FairDbConfigurable

#include "FairDbRollbackDates.h"        // for FairDbRollbackDates
#include "FairDbSimFlagAssociation.h"   // for FairDbSimFlagAssociation

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for Bool_t, etc
#endif

#include <map>                          // for map
#include <string>                       // for string

class FairDbMultConnector;
class FairDbTableProxy;
class FairDbTableRow;

class FairDbTableProxyRegistry : public FairDbConfigurable
{

  public:

    void ShowStatistics() const;

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

    FairDbTableProxyRegistry();
    virtual ~FairDbTableProxyRegistry();

  private:
    void SetLoggingStreams();
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

    FairDbMultConnector* fMultConnector;


  private:


    FairDbTableProxyRegistry(const FairDbTableProxyRegistry&);
    FairDbTableProxyRegistry& operator=(const FairDbTableProxyRegistry&);


    void ApplySqlCondition() const;
    void ApplySqlCondition(FairDbTableProxy* proxy) const;

// Data members

    std::string fSqlCondition;

#ifndef __CINT__
    std::map<std::string,FairDbTableProxy*> fTPmap;
#endif  // __CINT__   

    FairDbRollbackDates fRollbackDates;
    FairDbSimFlagAssociation fSimFlagAss;
    TString fLogName;
    static FairDbTableProxyRegistry* fgInstance;

    ClassDef(FairDbTableProxyRegistry,0)   // Singleton register FairDbTableProxys.

};

#ifndef __CINT__
static struct FairDbTableProxyRegistry::Cleaner __dbi_cleaner;
#endif

#endif  // FAIRDBTABLEPROXYREGISTRY_H
