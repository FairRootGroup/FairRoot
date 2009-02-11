#ifndef FAIRGENERICPARORAIO_H
#define FAIRGENERICPARORAIO_H

#include "FairDetParOraIo.h"

class FairOraConn;
class FairParSet;
class FairParGenericSet;
class FairParamObj;

class FairGenericParOraIo : public FairDetParOraIo {
private:
public:
  FairGenericParOraIo(FairOraConn* p=0);
  ~FairGenericParOraIo() {;}
  Bool_t init(FairParSet*,Int_t*);
  Int_t write(FairParSet*);
  Bool_t read(FairParGenericSet*);
  Int_t writeSet(FairParGenericSet*);
  Bool_t readFromLoadingTable(FairParGenericSet*,Int_t);
private:
  Bool_t readBlob(FairParamObj*,Int_t,Bool_t);
  Int_t createParamVers(FairParGenericSet*);
  Int_t storeBlob(UChar_t*,Int_t,Bool_t);
  Bool_t readLoadBlob(FairParamObj*,Int_t,Bool_t);
  ClassDef(FairGenericParOraIo,0) // I/O from Oracle for gemeric parameter containers
};

#endif  /* !FAIRGENERICPARORAIO_H */

