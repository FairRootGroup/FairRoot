#ifndef CBMDETPARORAIO_H
#define CBMDETPARORAIO_H

#include "CbmDetParIo.h"

class CbmOraConn;
class CbmRtdbRun;

class CbmParOraSet : public TNamed {
public:
  Int_t contextId;         // Id of context
  Double_t versDate[2];    // Actual date range of parameters
  CbmParOraSet(const char* pName);
  ~CbmParOraSet() {}
  void clearVersDate();      
  ClassDef(CbmParOraSet,0)
};

class CbmDetParOraIo : public CbmDetParIo {
protected:
  CbmOraConn* pConn;        // pointer to Oracle connection class
  CbmRtdbRun* actContVers;  // pointer to the actual list of container versions
  Int_t actRunId;           // actual runId (can be -1 if there are no data in Oracle)
  TList* containerList;     // list of parameter containers
public:
  CbmDetParOraIo(CbmOraConn* p=0);
  virtual ~CbmDetParOraIo(void);
  void commit(void);
  void rollback(void);
  void showSqlError(const char*);
  Int_t getActRunId(void) { return actRunId; }
  Int_t getRunStart(CbmParSet* pPar=0);
  Int_t getPredefVersion(CbmParSet*);
  const char* getHistoryDate();
protected:
  void setChanged(CbmParSet*);
  CbmParOraSet* getOraSet(CbmParSet*);
  Int_t getContextId(const char*,const char*);
private:
  ClassDef(CbmDetParOraIo,0) // base class for the detector interface to Oracle
};

#endif  /* !CBMDETPARORAIO_H */
