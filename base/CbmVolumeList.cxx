#include "CbmVolumeList.h"

#include "CbmVolume.h"

using std::cout;
using std::cerr;
using std::endl;

//_____________________________________________________________________________

CbmVolumeList::CbmVolumeList() 
 :fData(new TObjArray())
{
    //
   
}

//_____________________________________________________________________________
CbmVolumeList::~CbmVolumeList() {
    if (fData) {
        fData->Delete();
        delete fData;
    }
}

//_____________________________________________________________________________
CbmVolume * CbmVolumeList::getVolume(TString * name) {

    TObject * obj = findObject(* name);
    if (obj) cout << "-I CbmVolume getVolume " << name->Data() << "found" << endl;
    return (CbmVolume *) obj;
}

//_____________________________________________________________________________
Int_t CbmVolumeList::getVolumeId(TString * name) {

    TObject * obj = findObject(* name);
    if (obj) cout << "-I CbmVolume getVolume " << name->Data() << "found" << endl;
    CbmVolume * vol = (CbmVolume *) obj;
    return vol->getVolumeId();
}



//_____________________________________________________________________________
CbmVolume * CbmVolumeList::findObject(TString name) {
    CbmVolume * obj = NULL;
    for (int i = 0; i < fData->GetEntriesFast(); i++) {
            obj = (CbmVolume *) fData->At(i);
        if (obj ) {

            if (obj->getName() == name) return (CbmVolume *) obj;
        }

    }
    return NULL;
}

//_____________________________________________________________________________
void CbmVolumeList::addVolume(CbmVolume * elem) {

    CbmVolume *v= (CbmVolume *)findObject(elem->getName());

    if (v) {
    if(gDebug>0)   cerr << "-I CbmVolumeList element: " << elem->getName() <<  " VolId : " << elem->getVolumeId() << " already defined " << v->getVolumeId()<< endl;
    }else{ 	

    fData->Add(elem);
    }
}

ClassImp(CbmVolumeList)



