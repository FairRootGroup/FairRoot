#ifndef FAIRTUTORIALDETMISSALLIGNPAR_H
#define FAIRTUTORIALDETMISSALLIGNPAR_H

#include "FairParGenericSet.h"

#include "TArrayD.h"

class FairParamList;

class FairTutorialDetMissallignPar : public FairParGenericSet
{
  public:

    FairTutorialDetMissallignPar(const char* name="FairTutorialDetMissallignPar",
                                 const char* title="Missalignment parameter for FairTutorialDetHitProducerIdealMissallign Parameters",
                                 const char* context="TestDefaultContext");
    ~FairTutorialDetMissallignPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetShiftX() {return fShiftX;}
    TArrayD GetShiftY() {return fShiftY;}
    Int_t GetNrOfDetectors() {return fNrOfDetectors;}

  private:

    TArrayD fShiftX; // Array to hold the missallignment in x-direction
    TArrayD fShiftY; // Array to hold the missallignment in x-direction
    Int_t fNrOfDetectors; // Total number of detectors

    FairTutorialDetMissallignPar(const FairTutorialDetMissallignPar&);
    FairTutorialDetMissallignPar& operator=(const FairTutorialDetMissallignPar&);

    ClassDef(FairTutorialDetMissallignPar,1)
};

#endif
