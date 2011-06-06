#ifndef FAIR_VOLUMELIST_H
#define FAIR_VOLUMELIST_H

//#include "FairVolume.h"

#include "TObject.h"
#include "TObjArray.h"
#include "TString.h"

#include <iostream>

class FairVolume;
//class TObjArray;

/**
* This Object is only used for internal book keeping!
* @author M. Al-Turany, D. Bertini
* @version 0.1
* @since 12.01.04
*/

class FairVolumeList : public TObject
{
  private:
    TObjArray* fData;
    FairVolumeList(const FairVolumeList&);
    FairVolumeList& operator=(const FairVolumeList&);

  public:
    FairVolumeList();
    virtual ~FairVolumeList();

    FairVolume* getVolume( TString* name );
    Int_t getVolumeId( TString* name );

    FairVolume* findObject( TString name );
    void addVolume( FairVolume* elem);

    Int_t getEntries () { return fData->GetEntries();}
    FairVolume* At(Int_t pos ) { return ( (FairVolume*) fData->At(pos)); }

    ClassDef(FairVolumeList,1) // Volume List
};

#endif //FAIR_VOLUMELIST_H


