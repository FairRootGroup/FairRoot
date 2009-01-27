#ifndef FAIRORAINFO_H
#define FAIRORAINFO_H

#include "TObject.h"
#include "TString.h"
#include "TList.h"

class FairOraConn;

class FairOraInfo : public TObject {
private:
  FairOraConn* pConn;   // pointer to Oracle connection class
public:
  FairOraInfo(FairOraConn* p=0) {pConn=p;}
  ~FairOraInfo(void) {}
  void showSqlError(char*);
  void showRunStart(Int_t);  
  Int_t getRunId(Text_t*);
  TList* getListOfRuns(const char* ,const char* startAt="",const char* endAt="");
private:
  Bool_t getRefRunStart(const char*,TString&);
  ClassDef(FairOraInfo,0) // utility class for the interface to Oracle
};

#endif  /* !FAIRORAINFO_H */
