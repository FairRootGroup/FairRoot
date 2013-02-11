#include "FairTutorialDetMissallignPar.h"

#include "FairParamList.h"

//#include <iostream>

ClassImp(FairTutorialDetMissallignPar)

FairTutorialDetMissallignPar ::FairTutorialDetMissallignPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fShiftX(),
    fShiftY(),
    fNrOfDetectors(0)
{
}

FairTutorialDetMissallignPar::~FairTutorialDetMissallignPar(void)
{
}

void FairTutorialDetMissallignPar::clear(void)
{
}

void FairTutorialDetMissallignPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("NrOfDetectors", fNrOfDetectors);
  l->add("ShiftX", fShiftX);
  l->add("ShiftY", fShiftY);

}

Bool_t FairTutorialDetMissallignPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("NrOfDetectors", &fNrOfDetectors) ) { return kFALSE; }

  fShiftX.Set(fNrOfDetectors);
  if ( ! l->fill("ShiftX", &fShiftX )) { return kFALSE; }

  fShiftY.Set(fNrOfDetectors);
  if ( ! l->fill("ShiftY", &fShiftY )) { return kFALSE; }

  return kTRUE;
}
