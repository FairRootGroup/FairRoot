#include "CbmTutorialDetGeoPar.h"

#include "CbmParamList.h"

#include "TObjArray.h"

#include <iostream>

ClassImp(CbmTutorialDetGeoPar)

CbmTutorialDetGeoPar ::CbmTutorialDetGeoPar(const char* name,
					    const char* title,
					    const char* context)
  : CbmParGenericSet(name,title,context) {
  
  fGeoSensNodes = new TObjArray();
  fGeoPassNodes = new TObjArray();

}

CbmTutorialDetGeoPar::~CbmTutorialDetGeoPar(void) {
}

void CbmTutorialDetGeoPar::clear(void) {
  if(fGeoSensNodes) delete fGeoSensNodes;
  if(fGeoPassNodes) delete fGeoPassNodes;
}

void CbmTutorialDetGeoPar::putParams(CbmParamList* l) {
  if (!l) return;
  l->addBinary("CbmGeoNodes Sensitive List", fGeoSensNodes);
  l->addBinary("CbmGeoNodes Passive List", fGeoPassNodes);
}

Bool_t CbmTutorialDetGeoPar::getParams(CbmParamList* l) {
  if (!l) return kFALSE;
  if (!l->fillBinary("CbmGeoNodes Sensitive List", fGeoSensNodes)) return kFALSE;
  if (!l->fillBinary("CbmGeoNodes Passive List", fGeoPassNodes)) return kFALSE;
  return kTRUE;
}
