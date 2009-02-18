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
  void showSqlError(Char_t*);
  void showRunStart(Int_t);  
  Int_t getRunId(Text_t*);
  TList* getListOfRuns(const Char_t* ,const Char_t* startAt="",const Char_t* endAt="");
private:
  TList* getListOfSimRefRuns(const Char_t* ,const Char_t*,const Char_t*);
  Bool_t getRunStart(const Char_t*,TString&);
  Bool_t getSimRefRunStart(const Char_t*,TString&);
  ClassDef(FairOraInfo,0) // utility class for the interface to Oracle
};

#endif  /* !FAIRORAINFO_H */
