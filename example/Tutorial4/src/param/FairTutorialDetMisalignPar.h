#ifndef FAIRTUTORIALDETMISSALLIGNPAR_H
#define FAIRTUTORIALDETMISSALLIGNPAR_H

#include "FairParGenericSet.h"

#include "TArrayD.h"

class FairParamList;

class FairTutorialDetMisalignPar : public FairParGenericSet
{
  public:

    FairTutorialDetMisalignPar(const char* name="FairTutorialDetMissallignPar",
                               const char* title="Missalignment parameter for FairTutorialDetHitProducerIdealMissallign Parameters",
                               const char* context="TestDefaultContext");
    ~FairTutorialDetMisalignPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetShiftX() {return fShiftX;}
    TArrayD GetShiftY() {return fShiftY;}
    TArrayD GetShiftZ() {return fShiftZ;}
    TArrayD GetRotX() {return fRotX;}
    TArrayD GetRotY() {return fRotY;}
    TArrayD GetRotZ() {return fRotZ;}
    Int_t GetNrOfDetectors() {return fNrOfDetectors;}

  private:

    TArrayD fShiftX; // Array to hold the misalignment in x-direction
    TArrayD fShiftY; // Array to hold the misalignment in y-direction
    TArrayD fShiftZ; // Array to hold the misalignment in z-direction
    TArrayD fRotX; // Array to hold the rotation in x-direction
    TArrayD fRotY; // Array to hold the rotation in y-direction
    TArrayD fRotZ; // Array to hold the rotation in z-direction
    Int_t fNrOfDetectors; // Total number of detectors

    FairTutorialDetMisalignPar(const FairTutorialDetMisalignPar&);
    FairTutorialDetMisalignPar& operator=(const FairTutorialDetMisalignPar&);

    ClassDef(FairTutorialDetMisalignPar,1)
};

#endif
