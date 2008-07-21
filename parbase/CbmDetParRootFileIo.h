#ifndef CBMDETPARROOTFILEIO_H
#define CBMDETPARROOTFILEIO_H

#include "CbmDetParIo.h"
//#include "TFile.h"
//#include "TArrayI.h"

class CbmParRootFile;
class CbmParSet;

class CbmDetParRootFileIo : public CbmDetParIo {
protected:
  CbmParRootFile* pFile;    // pointer to parameter ROOT file
public:
  CbmDetParRootFileIo(CbmParRootFile* f);
  virtual ~CbmDetParRootFileIo() {}
  virtual Bool_t read(CbmParSet*);
  Int_t write(CbmParSet*);
//  Bool_t read(HDetGeomPar*,Int_t*);
protected:
  Int_t findInputVersion(Text_t* contName);
  Int_t getMaxVersion(Text_t* contName);
  TObject* findContainer(Text_t* contName, Int_t version);
  ClassDef(CbmDetParRootFileIo,0) // detector base class for parameter I/O from ROOT file
};

#endif  /* !CBMDETPARROOTFILEIO_H */

