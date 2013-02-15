#include "FairTutorialDetMisalignPar.h"

#include "FairParamList.h"

//#include <iostream>

ClassImp(FairTutorialDetMisalignPar)

FairTutorialDetMisalignPar ::FairTutorialDetMisalignPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fShiftX(),
    fShiftY(),
    fNrOfDetectors(0)
{
}

FairTutorialDetMisalignPar::~FairTutorialDetMisalignPar(void)
{
}

void FairTutorialDetMisalignPar::clear(void)
{
}

void FairTutorialDetMisalignPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("NrOfDetectors", fNrOfDetectors);
  l->add("ShiftX", fShiftX);
  l->add("ShiftY", fShiftY);

}

Bool_t FairTutorialDetMisalignPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("NrOfDetectors", &fNrOfDetectors) ) { return kFALSE; }

  fShiftX.Set(fNrOfDetectors);
  if ( ! l->fill("ShiftX", &fShiftX )) { return kFALSE; }

  fShiftY.Set(fNrOfDetectors);
  if ( ! l->fill("ShiftY", &fShiftY )) { return kFALSE; }

  return kTRUE;
}
