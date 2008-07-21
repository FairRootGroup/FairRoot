#ifndef CBMDETPARIO_H
#define CBMDETPARIO_H


//#include "Rtypes.h"
#include "TNamed.h"

class CbmParSet;

class CbmDetParIo : public TNamed {
protected:
  Int_t inputNumber; // input number (first or second input in runtime database)
public:
  CbmDetParIo() {}
  virtual ~CbmDetParIo() {}

  // sets the input number
  void setInputNumber(Int_t n) {inputNumber=n;}

  // returns the input number
  Int_t getInputNumber() {return inputNumber;}

  // initializes parameter container
  virtual Bool_t init(CbmParSet*) {return kFALSE;}

  // writes parameter container to output
  virtual Int_t write(CbmParSet*) {return kFALSE;}

  ClassDef(CbmDetParIo,0)  // Base class for detector parameter IO
};

#endif  /* !HDETPARIO_H */







