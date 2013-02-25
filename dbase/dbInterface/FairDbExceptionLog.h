#ifndef FAIRDBEXCEPTIONLOG
#define FAIRDBEXCEPTIONLOG


#include <iosfwd>
#include <string>
#include <vector>

#include "Rtypes.h"

#include "FairDbException.h"

class TSQLServer;
class TSQLStatement;
class FairDbExceptionLog;

std::ostream& operator<<(std::ostream& s, const FairDbExceptionLog& el);

class FairDbExceptionLog

{

  public:
    FairDbExceptionLog(const FairDbException* e = 0);
    virtual ~FairDbExceptionLog();

// State testing member functions

    Bool_t IsEmpty() const { return fEntries.size() == 0; }
    const std::vector<FairDbException>&
    GetEntries() const { return fEntries; }
    void Print() const;
    UInt_t Size() const { return fEntries.size(); }
    void Copy(FairDbExceptionLog& that, UInt_t start=0) const;

// State changing member functions

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

// The Global Exception Log
    static FairDbExceptionLog& GetGELog() { return fgGELog;}

  private:


// Data members

  private:

/// The exception entries.
    std::vector<FairDbException> fEntries;

/// Global Exception Log
    static FairDbExceptionLog fgGELog;

    ClassDef(FairDbExceptionLog,0) // Object to hold database exceptions

};

#endif // FAIRDBEXCEPTIONLOG

