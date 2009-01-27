#include "FairTutorialDetGeoPar.h"

#include "FairParamList.h"

#include "TObjArray.h"

#include <iostream>

ClassImp(FairTutorialDetGeoPar)

FairTutorialDetGeoPar ::FairTutorialDetGeoPar(const char* name,
					    const char* title,
					    const char* context)
  : FairParGenericSet(name,title,context) {
  
  fGeoSensNodes = new TObjArray();
  fGeoPassNodes = new TObjArray();

}

FairTutorialDetGeoPar::~FairTutorialDetGeoPar(void) {
}

void FairTutorialDetGeoPar::clear(void) {
  if(fGeoSensNodes) delete fGeoSensNodes;
  if(fGeoPassNodes) delete fGeoPassNodes;
}

void FairTutorialDetGeoPar::putParams(FairParamList* l) {
  if (!l) return;
  l->addBinary("FairGeoNodes Sensitive List", fGeoSensNodes);
  l->addBinary("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t FairTutorialDetGeoPar::getParams(FairParamList* l) {
  if (!l) return kFALSE;
  if (!l->fillBinary("FairGeoNodes Sensitive List", fGeoSensNodes)) return kFALSE;
  if (!l->fillBinary("FairGeoNodes Passive List", fGeoPassNodes)) return kFALSE;
  return kTRUE;
}
