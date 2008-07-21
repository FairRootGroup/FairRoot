#ifndef CBMORACONN_H
#define CBMORACONN_H

#include "string.h"
#include "TObject.h"

class CbmOraConn : public TObject {
protected:
  char dbName[31];         // database name (may be a remote database)
  char userName[31];       // name of user
  Bool_t isConnected;      // ==kTRUE if connection is open
  Int_t actRunId;          // actual runId (can be -1 if there are no data in Oracle)
  Int_t runStart;          // start time of actual run
  char historyDate[21];    // timestamp to retrieve historic data
  Bool_t needsServerCheck; // kTRUE before first call to getRunStart
public:
  CbmOraConn();
  ~CbmOraConn();
  Bool_t open();
  Bool_t open(char*);
  Bool_t open(char*, char*);
  Bool_t isOpen() {return isConnected;}
  Bool_t reconnect();
  void close();
  void disconnect();
  void print();
  void showSqlError(const char*,const char* msg=0);
  Int_t getActRunId(void) { return actRunId; }
  Int_t getRunStart(Int_t);
  Int_t getActRunStart() { return runStart; }
  Bool_t setHistoryDate(const char*);
  const char* getHistoryDate() { return historyDate; }
  Bool_t setParamRelease(const char*);
  Bool_t setParamRelease(Int_t);
private:
  Bool_t openConnection(char*);
  char* getPassword();
  Int_t checkServerLoad();

  ClassDef(CbmOraConn,0) // Connection class to Oracle
};

#endif  /* !CBMORACONN_H */
