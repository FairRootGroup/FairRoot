#ifndef FAIRDBCONFIGSTREAM_H
#define FAIRDBCONFIGSTREAM_H


#include <string>

#include "FairDb.h"
#include "FairDbConfigSet.h"
#include "FairDbResPtr.h"
#include "FairRegistry.h"
#include "ValContext.h"

class FairDbConfigStream;
class FairDbFieldType;
class FairRegistry;
#include <iosfwd>

ostream& operator<<(ostream& s, const FairDbConfigStream& cfStream);

class FairDbConfigStream
{


  public:

    static      ValContext fgDefaultContext;

// Constructors and destructors.
    FairDbConfigStream();
    FairDbConfigStream(const std::string& SoftwName,
                       const std::string& ConfigName="default",
                       ValContext vc = FairDbConfigStream::fgDefaultContext,
                       FairDb::Task task=0,
                       const std::string& tableName="SOFTWARE_CONFIGURATION");
    virtual ~FairDbConfigStream();

// State testing member functions
    const FairDbConfigStream& operator>>(FairRegistry* reg);
    const FairDbConfigSet* GetConfigSet() const { return fCFSet; }

// State changing member functions

    FairDbConfigStream& operator<<(const FairRegistry* reg);
    Bool_t IsEmpty() { return fCFSet == 0; }
    FairDbValidityRec& GetValidityRec() { return fVRec; }
    Bool_t Write(UInt_t dbNo = 0,
                 const std::string& logComment = "",
                 Bool_t localTest = false);

  private:

    FairDbConfigStream(const FairDbConfigStream&);  // Not implimented
    FairDbConfigStream operator=(const FairDbConfigStream&);  // Not implimented

// Data members

    ///  Pointer to the associated configuration set.  May point either
    ///  to a row of fCFSetTable (or 0) or, after operator <<, to fCFSetModified
    const FairDbConfigSet*
    fCFSet;

    /// Pointer to ConfigSet table
    FairDbResultPtr<FairDbConfigSet>
    fCFSetTable;

    /// Local FairDbConfigSet (empty until/unless filled using operator <<).
    FairDbConfigSet fCFSetModified;

    /// Associated validity rec (used when writing back to the database).
    FairDbValidityRec fVRec;

    /// Name of the configuration set
    std::string    fConfigName;

    /// Name of the software system to be configured
    std::string    fSoftwName;

    ClassDef(FairDbConfigStream,0)  // Input/output stream of configuration data

};

#endif  // DBICONFIGSTREAM_H
