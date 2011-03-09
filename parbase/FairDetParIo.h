#ifndef FAIRDETPARIO_H
#define FAIRDETPARIO_H


//#include "Rtypes.h"
#include "TNamed.h"

class FairParSet;

class FairDetParIo : public TNamed
{
  protected:
    Int_t inputNumber; // input number (first or second input in runtime database)
  public:
    FairDetParIo();
    virtual ~FairDetParIo() {;}

    // sets the input number
    void setInputNumber(Int_t n) {inputNumber=n;}

    // returns the input number
    Int_t getInputNumber() {return inputNumber;}

    // initializes parameter container
    virtual Bool_t init(FairParSet*) {return kFALSE;}

    // writes parameter container to output
    virtual Int_t write(FairParSet*) {return kFALSE;}

    ClassDef(FairDetParIo,0)  // Base class for detector parameter IO
};

#endif  /* !HDETPARIO_H */







