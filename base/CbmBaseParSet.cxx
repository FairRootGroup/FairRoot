#include "CbmBaseParSet.h"

#include "CbmPrimaryGenerator.h"

#include "CbmParamList.h"

#include "TObjArray.h"


ClassImp(CbmBaseParSet)

CbmBaseParSet::CbmBaseParSet(const char* name,const char* title,const char* context)
: CbmParGenericSet(name,title,context),
  fDetList(0),
  fGeoNodes(new TObjArray()),
  fPriGen(0)
{
  
			
}


CbmBaseParSet::~CbmBaseParSet(void) {
}

void CbmBaseParSet::clear(void) {
  if(fPriGen) delete fPriGen;
  if(fDetList) delete fDetList;
  if(fGeoNodes) delete fGeoNodes;

  }

void CbmBaseParSet::putParams(CbmParamList* l) {
  if (!l) return;
  l->addBinary("Detector List", fDetList);
  l->addBinary("Event Generator", fPriGen);
  l->addBinary("CbmGeoNodes List", fGeoNodes);
  
}

Bool_t CbmBaseParSet::getParams(CbmParamList* l) {
  if (!l) return kFALSE;
  if (!l->fillBinary("Detector List", fDetList)) return kFALSE;
  if (!l->fillBinary("Event Generator", fPriGen))return kFALSE;
  if (!l->fillBinary("CbmGeoNodes List", fGeoNodes)) return kFALSE;
  return kTRUE;
}


