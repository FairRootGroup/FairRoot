#ifndef FAIRDBCONFIGSTREAM_H
#define FAIRDBCONFIGSTREAM_H

#include "FairDb.h"                     // for Version
#include "FairDbConfigSet.h"            // for FairDbConfigSet
#include "FairDbResPtr.h"               // for FairDbResultPtr
#include "FairDbValidityRec.h"          // for FairDbValidityRec
#include "ValContext.h"                 // for ValContext

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Bool_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string

class FairRegistry;

class FairDbConfigStream
{


  public:

    static      ValContext fgDefaultContext;

    FairDbConfigStream();
    FairDbConfigStream(const std::string& SoftwName,
                       const std::string& ConfigName="default",
                       ValContext vc = FairDbConfigStream::fgDefaultContext,
                       FairDb::Version task=0,
                       const std::string& tableName="SOFTWARE_CONFIGURATION");
    virtual ~FairDbConfigStream();

    const FairDbConfigStream& operator>>(FairRegistry* reg);
    const FairDbConfigSet* GetConfigSet() const { return fCFSet; }


    FairDbConfigStream& operator<<(const FairRegistry* reg);
    Bool_t IsEmpty() { return fCFSet == 0; }
    FairDbValidityRec& GetValidityRec() { return fVRec; }
    Bool_t Write(UInt_t dbNo = 0,
                 const std::string& logComment = "",
                 Bool_t localTest = false);

  private:

    FairDbConfigStream(const FairDbConfigStream&);
    FairDbConfigStream operator=(const FairDbConfigStream&);


    const FairDbConfigSet*
    fCFSet;
    FairDbResultPtr<FairDbConfigSet> fCFSetTable;
    FairDbConfigSet fCFSetModified;
    FairDbValidityRec fVRec;
    std::string    fConfigName;
    std::string    fSoftwName;

    ClassDef(FairDbConfigStream,0)

};

ostream& operator<<(ostream& s, const FairDbConfigStream& cfStream);

#endif  // FAIRDBCONFIGSTREAM_H
