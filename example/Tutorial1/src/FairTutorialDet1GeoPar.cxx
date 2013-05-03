#include "FairTutorialDet1GeoPar.h"

#include "FairParamList.h"              // for FairParamList

#include "TObjArray.h"                  // for TObjArray

ClassImp(FairTutorialDet1GeoPar)

FairTutorialDet1GeoPar ::FairTutorialDet1GeoPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fGeoSensNodes(new TObjArray()),
    fGeoPassNodes(new TObjArray())
{
}

FairTutorialDet1GeoPar::~FairTutorialDet1GeoPar(void)
{
}

void FairTutorialDet1GeoPar::clear(void)
{
  if(fGeoSensNodes) { delete fGeoSensNodes; }
  if(fGeoPassNodes) { delete fGeoPassNodes; }
}

void FairTutorialDet1GeoPar::putParams(FairParamList* l)
{
  if (!l) { return; }
  l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
  l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t FairTutorialDet1GeoPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }
  if (!l->fillObject("FairGeoNodes Sensitive List", fGeoSensNodes)) { return kFALSE; }
  if (!l->fillObject("FairGeoNodes Passive List", fGeoPassNodes)) { return kFALSE; }
  return kTRUE;
}
