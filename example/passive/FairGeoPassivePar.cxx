//*-- AUTHOR : Denis Bertini
//*-- Created : 21/06/2005

#include "FairGeoPassivePar.h"

#include "FairParamList.h"              // for FairParamList

#include "TObjArray.h"                  // for TObjArray

using namespace std;

ClassImp(FairGeoPassivePar)

FairGeoPassivePar::FairGeoPassivePar(const char* name,const char* title,const char* context)
  : FairParGenericSet(name,title,context),
    fGeoSensNodes(new TObjArray()),
    fGeoPassNodes(new TObjArray())
{
}

FairGeoPassivePar::~FairGeoPassivePar(void)
{
}

void FairGeoPassivePar::clear(void)
{
  if(fGeoSensNodes) { delete fGeoSensNodes; }
  if(fGeoPassNodes) { delete fGeoPassNodes; }
}

void FairGeoPassivePar::putParams(FairParamList* l)
{
  if (!l) { return; }
  l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
  l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t FairGeoPassivePar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }
  if (!l->fillObject("FairGeoNodes Sensitive List", fGeoSensNodes)) { return kFALSE; }
  if (!l->fillObject("FairGeoNodes Passive List", fGeoPassNodes)) { return kFALSE; }

  return kTRUE;
}
