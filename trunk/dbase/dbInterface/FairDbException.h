#ifndef FAIRDBEXCEPTION
#define FAIRDBEXCEPTION


#include <iosfwd>
#include <string>
#include "Rtypes.h"

class FairDbException;
class TSQLServer;
class TSQLStatement;

class ostreamx;

std::ostream& operator<<(std::ostream& s, const FairDbException& e);

class FairDbException

{

  public:
    FairDbException(const char* msg = 0, Int_t code = -1, Int_t dbType = -1 );
    FairDbException(const TSQLServer& server,Int_t dbType = -1);
    FairDbException(const TSQLStatement& statement,Int_t dbType = -1);
    FairDbException(const FairDbException& that);
    virtual ~FairDbException();

// State testing member functions

    const std::string& GetMessage() const { return fMessage; }
    Int_t GetErrorCode() const { return fErrorCode; }
    Int_t GetDbType() const { return fDbType; }

  private:


// Data members

  private:

/// The message associated with the exception.
    std::string fMessage;

/// The exception error code.
    Int_t fErrorCode;

/// The type of database that issued the exception.
    Int_t fDbType;


    ClassDef(FairDbException,0) // Object to hold a single database exception record.

};

#endif // FAIRDBEXCEPTIONLOG
