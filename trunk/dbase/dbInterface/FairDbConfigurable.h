#ifndef FAIRDBCONFIGURABLE_H
#define FAIRDBCONFIGURABLE_H
#ifndef REGISTRY_H
# include "FairRegistry.h"
#endif

class FairDbConfDialog;

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif

class FairDbConfigurable
{

  public:

    FairDbConfigurable();
    virtual ~FairDbConfigurable();

    // Subclass should implement this method:
    virtual void            Config() = 0;

    // Access default and main configuration
    virtual const FairRegistry& DefaultConfig() const;
    FairRegistry&               GetConfig();
    const FairRegistry&         GetConfig() const;

    // Call anytime.  Triggers Config() only iff it has been modifed
    // since last calling.
    int  Update();

    // Set config via interactive dialog
    void Set(FairDbConfDialog* d=0);

    // Set config via string
    void Set(const char* s);

  protected:
    virtual void CommitDefaultConfig(const FairRegistry& r);

  private:
    FairRegistry fDefConfig, fConfig;


    ClassDef(FairDbConfigurable,1)
};

#endif // FAIRDBCONFIGURABLE_H
