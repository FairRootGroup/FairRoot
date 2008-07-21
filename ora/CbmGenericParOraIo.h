#ifndef CBMGENERICPARORAIO_H
#define CBMGENERICPARORAIO_H

#include "CbmDetParOraIo.h"

class CbmOraConn;
class CbmParSet;
class CbmParGenericSet;
class CbmParamBinObj;

class CbmGenericParOraIo : public CbmDetParOraIo {
private:
  class CbmParOraBlob : public TObject {
    public:
      CbmParamBinObj* binaryParam;   // Pointer to object in parameter list
      Int_t           blobId;        // Id of BinaryLargeObject
      CbmParOraBlob(CbmParamBinObj* o=0,Int_t id=0) { binaryParam=o; blobId=id; }
      ~CbmParOraBlob() {}
  };
public:
  CbmGenericParOraIo(CbmOraConn* p=0);
  ~CbmGenericParOraIo() {;}
  Bool_t init(CbmParSet*,Int_t*);
  Int_t write(CbmParSet*);
  Bool_t read(CbmParGenericSet*);
  Int_t writeSet(CbmParGenericSet*);
  Bool_t readFromLoadingTable(CbmParGenericSet*,Int_t);
private:
  Bool_t readBlob(CbmParamBinObj* obj,Int_t lobId);
  Int_t createParamVers(CbmParGenericSet*);
  Int_t storeBlob(UChar_t*, Int_t);
  Bool_t readLoadBlob(CbmParamBinObj*,Int_t);
  ClassDef(CbmGenericParOraIo,0) // I/O from Oracle for gemeric parameter containers
};

#endif  /* !CBMGENERICPARORAIO_H */

