// -------------------------------------------------------------------------
// -----                 FairVolumeList  source file                   -----
// -----          Created 12/01/04  by M. Al-Turany                    -----
// -------------------------------------------------------------------------


#include "FairVolumeList.h"
#include "FairVolume.h"

using std::cout;
using std::cerr;
using std::endl;

//_____________________________________________________________________________

FairVolumeList::FairVolumeList()
  :TObject(),
   fData(new TObjArray())
{
  //

}

//_____________________________________________________________________________
FairVolumeList::~FairVolumeList()
{
  if (fData) {
    fData->Delete();
    delete fData;
  }
}

//_____________________________________________________________________________
FairVolume* FairVolumeList::getVolume(TString* name)
{

  TObject* obj = findObject(* name);
  if (obj) { cout << "-I FairVolume getVolume " << name->Data() << "found" << endl; }
  return (FairVolume*) obj;
}

//_____________________________________________________________________________
Int_t FairVolumeList::getVolumeId(TString* name)
{

  TObject* obj = findObject(* name);
  if (obj) { cout << "-I FairVolume getVolume " << name->Data() << "found" << endl; }
  FairVolume* vol = (FairVolume*) obj;
  return vol->getVolumeId();
}



//_____________________________________________________________________________
FairVolume* FairVolumeList::findObject(TString name)
{
  FairVolume* obj = NULL;
  for (int i = 0; i < fData->GetEntriesFast(); i++) {
    obj = (FairVolume*) fData->At(i);
    if (obj ) {

      if (obj->GetName() == name) { return (FairVolume*) obj; }
    }

  }
  return NULL;
}

//_____________________________________________________________________________
void FairVolumeList::addVolume(FairVolume* elem)
{

  FairVolume* v= (FairVolume*)findObject(elem->GetName());

  if (v) {
    if(gDebug>0) { cerr << "-I FairVolumeList element: " << elem->GetName() <<  " VolId : " << elem->getVolumeId() << " already defined " << v->getVolumeId()<< endl; }
  } else {

    fData->Add(elem);
  }
}

ClassImp(FairVolumeList)



