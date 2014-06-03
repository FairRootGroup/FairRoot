/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBEXCEPTION
#define FAIRDBEXCEPTION

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string, basic_string

class FairDbException;
class TSQLServer;
class TSQLStatement;

std::ostream& operator<<(std::ostream& s, const FairDbException& e);

class FairDbException

{

  public:
    FairDbException(const char* msg = 0, Int_t code = -1, Int_t dbType = -1 );
    FairDbException(const TSQLServer& server,Int_t dbType = -1);
    FairDbException(const TSQLStatement& statement,Int_t dbType = -1);
    FairDbException(const FairDbException& that);
    virtual ~FairDbException();

    const std::string& GetMessage() const { return fMessage; }
    Int_t GetErrorCode() const { return fErrorCode; }
    Int_t GetDbType() const { return fDbType; }

  private:

    std::string fMessage;
    Int_t fErrorCode;
    Int_t fDbType;

    ClassDef(FairDbException,0) // Database exception record.

};

#endif // FAIRDBEXCEPTIONLOG
