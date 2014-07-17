/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBEXCEPTIONLOG
#define FAIRDBEXCEPTIONLOG

#include "FairDbException.h"            // for FairDbException

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string
#include <vector>                       // for vector

class TSQLServer;
class TSQLStatement;


class FairDbExceptionLog

{

  public:
    FairDbExceptionLog(const FairDbException* e = 0);
    virtual ~FairDbExceptionLog();

    Bool_t IsEmpty() const { return fEntries.size() == 0; }
    const std::vector<FairDbException>& GetEntries() const { return fEntries; }
    void Print() const;
    UInt_t Size() const { return fEntries.size(); }
    void Copy(FairDbExceptionLog& that, UInt_t start=0) const;

    void AddLog(const FairDbExceptionLog& el);
    void AddEntry(const FairDbException& e) { fEntries.push_back(e); }
    void AddEntry(const char* errMsg, Int_t code = -1, Int_t dbType = -1) {
      this->AddEntry(FairDbException(errMsg,code,dbType));
    }
    void AddEntry(const std::string& errMsg, Int_t code = -1, Int_t dbType = -1) {
      this->AddEntry(FairDbException(errMsg.c_str(),code,dbType));
    }
    void AddEntry(const TSQLServer& server, Int_t dbType = -1) {
      this->AddEntry(FairDbException(server,dbType));
    }
    void AddEntry(const TSQLStatement& statement, Int_t dbType = -1) {
      this->AddEntry(FairDbException(statement,dbType));
    }
    void Clear() { fEntries.clear(); }

    static FairDbExceptionLog& GetGELog() { return fgGELog;}
    static FairDbExceptionLog& GetGlobalErrorLog() { return fgGELog;}

  private:

    std::vector<FairDbException> fEntries;
    static FairDbExceptionLog fgGELog;

    ClassDef(FairDbExceptionLog,0) // Object to hold database exceptions

};

std::ostream& operator<<(std::ostream& s, const FairDbExceptionLog& el);

#endif // FAIRDBEXCEPTIONLOG

