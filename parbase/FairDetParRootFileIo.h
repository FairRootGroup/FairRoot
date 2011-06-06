#ifndef FAIRDETPARROOTFILEIO_H
#define FAIRDETPARROOTFILEIO_H

#include "FairDetParIo.h"

class FairParRootFile;
class FairParSet;

class FairDetParRootFileIo : public FairDetParIo
{
  protected:
    FairParRootFile* pFile;    // pointer to parameter ROOT file
  public:
    FairDetParRootFileIo(FairParRootFile* f);
    virtual ~FairDetParRootFileIo() {}
    virtual Bool_t read(FairParSet*);
    Int_t write(FairParSet*);
//  Bool_t read(HDetGeomPar*,Int_t*);
  protected:
    Int_t findInputVersion(Text_t* contName);
    Int_t getMaxVersion(Text_t* contName);
    TObject* findContainer(Text_t* contName, Int_t version);
  private:
    FairDetParRootFileIo(const FairDetParRootFileIo&);
    FairDetParRootFileIo& operator= (const FairDetParRootFileIo&);

    ClassDef(FairDetParRootFileIo,0) // detector base class for parameter I/O from ROOT file
};

#endif  /* !FAIRDETPARROOTFILEIO_H */

