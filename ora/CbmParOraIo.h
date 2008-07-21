#ifndef CBMPARORAIO_H
#define CBMPARORAIO_H

#include "string.h"
#include "CbmParIo.h"
#include "CbmOraConn.h"

class CbmOraInfo;

class CbmParOraIo : public CbmParIo {
private:
  CbmOraConn* pConn;    // pointer to the connection class
  CbmOraInfo* pInfo;    // pointer to the utility class
  Bool_t isConnected;   // ==kTRUE if connection is open
public:
  CbmParOraIo();
  ~CbmParOraIo();
  Bool_t open();
  Bool_t open(char *userName);
  Bool_t open(char *dbName, char *userName);
  Bool_t reconnect();
  void close();
  void disconnect();
  Bool_t check() {return isConnected;}  // kTRUE if connection is open
  void print();
  void setDetParIo(Text_t*);
  CbmOraInfo* getOraInfo() {return pInfo;}
  Bool_t setHistoryDate(const char*);
  Bool_t setParamRelease(const char*);
  TList* getListOfRuns(const char*,const char* startAt="",const char* endAt="");
private:
  Bool_t activateDetIo();
  ClassDef(CbmParOraIo,0) // Class for parameter I/O from Oracle
};

#endif  /* !CBMPARORAIO_H */

