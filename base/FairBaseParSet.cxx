#include "FairBaseParSet.h"

#include "FairPrimaryGenerator.h"

#include "FairParamList.h"

#include "TObjArray.h"


ClassImp(FairBaseParSet)

FairBaseParSet::FairBaseParSet(const char* name,const char* title,const char* context)
: FairParGenericSet(name,title,context),
  fDetList(0),
  fGeoNodes(new TObjArray()),
  fPriGen(0),
  fBeamMom(15)
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
  l->addObject("Detector List", fDetList);
  l->addObject("Event Generator", fPriGen);
  l->addObject("FairGeoNodes List", fGeoNodes);
  l->add("Beam Momentum Gev/c", fBeamMom);
}

Bool_t FairBaseParSet::getParams(FairParamList* l) {
  if (!l) return kFALSE;
  if (!l->fillObject("Detector List", fDetList)) return kFALSE;
  if (!l->fillObject("Event Generator", fPriGen))return kFALSE;
  if (!l->fillObject("FairGeoNodes List", fGeoNodes)) return kFALSE;
  if (!l->fill("Beam Momentum Gev/c", &fBeamMom)) return kFALSE;
  return kTRUE;
}


