//*-- AUTHOR : Ilse Koenig
//*-- Modified : 20/04/99

/////////////////////////////////////////////////////////////
// CbmGeoCompositeVolume
//
//
/////////////////////////////////////////////////////////////

#include "CbmGeoCompositeVolume.h"

ClassImp(CbmGeoCompositeVolume)

CbmGeoCompositeVolume::CbmGeoCompositeVolume(Int_t nComp)
    : CbmGeoVolume(),
	  components(0) 

{
  if (nComp) {
    components=new TObjArray(nComp);
    for(Int_t i=0;i<nComp;i++) components->AddAt(new CbmGeoVolume(),i);
  }
 
}

CbmGeoCompositeVolume::~CbmGeoCompositeVolume() {
  if (components) components->Delete();
  delete components;
}

Int_t CbmGeoCompositeVolume::getNumComponents() {
   if (components) return components->GetSize();
   else return 0;
}

CbmGeoVolume* CbmGeoCompositeVolume::getComponent(const Int_t n) {
  return (CbmGeoVolume*)components->At(n);
}

void CbmGeoCompositeVolume::createComponents(const Int_t n) {
  if (components) components->Delete();
  components->Expand(n);
}

void CbmGeoCompositeVolume::setComponent(CbmGeoVolume* v,const Int_t n) {
  if (components) components->AddAt(v,n);
  else Error("CbmGeoCompositeVolume::setComponent","no array of components");
}

void CbmGeoCompositeVolume::clear() {
  CbmGeoVolume::clear();
  Int_t n=getNumComponents();
  for(Int_t i=0;i<n;i++) ((CbmGeoVolume*)components->At(i))->clear();
}
  
void CbmGeoCompositeVolume::print() {
  CbmGeoVolume::print();
  CbmGeoVolume* v;
  for(Int_t i=0;i<components->GetSize();i++) {
    v=(CbmGeoVolume*)components->At(i);
    if (v) v->print();
  } 
} 
