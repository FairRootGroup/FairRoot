//*-- AUTHOR : Ilse Koenig
//*-- Modified : 20/04/99

/////////////////////////////////////////////////////////////
// FairGeoCompositeVolume
//
//
/////////////////////////////////////////////////////////////

#include "FairGeoCompositeVolume.h"

ClassImp(FairGeoCompositeVolume)

FairGeoCompositeVolume::FairGeoCompositeVolume(Int_t nComp)
  : FairGeoVolume(),
    components(NULL)
{
  if (nComp) {
    components=new TObjArray(nComp);
    for(Int_t i=0; i<nComp; i++) { components->AddAt(new FairGeoVolume(),i); }
  }

}

FairGeoCompositeVolume::~FairGeoCompositeVolume()
{
  if (components) { components->Delete(); }
  delete components;
}

Int_t FairGeoCompositeVolume::getNumComponents()
{
  if (components) { return components->GetSize(); }
  else { return 0; }
}

FairGeoVolume* FairGeoCompositeVolume::getComponent(const Int_t n)
{
  return (FairGeoVolume*)components->At(n);
}

void FairGeoCompositeVolume::createComponents(const Int_t n)
{
  if (components) { components->Delete(); }
  components->Expand(n);
}

void FairGeoCompositeVolume::setComponent(FairGeoVolume* v,const Int_t n)
{
  if (components) { components->AddAt(v,n); }
  else { Error("FairGeoCompositeVolume::setComponent","no array of components"); }
}

void FairGeoCompositeVolume::clear()
{
  FairGeoVolume::clear();
  Int_t n=getNumComponents();
  for(Int_t i=0; i<n; i++) { ((FairGeoVolume*)components->At(i))->clear(); }
}

void FairGeoCompositeVolume::print()
{
  FairGeoVolume::print();
  FairGeoVolume* v;
  for(Int_t i=0; i<components->GetSize(); i++) {
    v=(FairGeoVolume*)components->At(i);
    if (v) { v->print(); }
  }
}
