#include "FairBaseParSet.h"

#include "FairPrimaryGenerator.h"

#include "FairParamList.h"

#include "TObjArray.h"


ClassImp(FairBaseParSet)

FairBaseParSet::FairBaseParSet(const char* name,const char* title,const char* context)
: FairParGenericSet(name,title,context),
  fDetList(0),
  fGeoNodes(new TObjArray()),
  fPriGen(0)
{
  
			
}


FairBaseParSet::~FairBaseParSet(void) {
}

void FairBaseParSet::clear(void) {
  if(fPriGen) delete fPriGen;
  if(fDetList) delete fDetList;
  if(fGeoNodes) delete fGeoNodes;

  }

void FairBaseParSet::putParams(FairParamList* l) {
  if (!l) return;
  l->addBinary("Detector List", fDetList);
  l->addBinary("Event Generator", fPriGen);
  l->addBinary("FairGeoNodes List", fGeoNodes);
  
}

Bool_t FairBaseParSet::getParams(FairParamList* l) {
  if (!l) return kFALSE;
  if (!l->fillBinary("Detector List", fDetList)) return kFALSE;
  if (!l->fillBinary("Event Generator", fPriGen))return kFALSE;
  if (!l->fillBinary("FairGeoNodes List", fGeoNodes)) return kFALSE;
  return kTRUE;
}


