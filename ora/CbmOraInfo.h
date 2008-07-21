#ifndef CBMORAINFO_H
#define CBMORAINFO_H

#include "TObject.h"
#include "TString.h"
#include "TList.h"

class CbmOraConn;

class CbmOraInfo : public TObject {
private:
  CbmOraConn* pConn;   // pointer to Oracle connection class
public:
  CbmOraInfo(CbmOraConn* p=0) {pConn=p;}
  ~CbmOraInfo(void) {}
  void showSqlError(char*);
  void showRunStart(Int_t);  
  Int_t getRunId(Text_t*);
  TList* getListOfRuns(const char* ,const char* startAt="",const char* endAt="");
private:
  Bool_t getRefRunStart(const char*,TString&);
  ClassDef(CbmOraInfo,0) // utility class for the interface to Oracle
};

#endif  /* !CBMORAINFO_H */
