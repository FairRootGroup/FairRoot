#ifndef CBM_VOLUMELIST_H
#define CBM_VOLUMELIST_H

//#include "CbmVolume.h"

#include "TObject.h"
#include "TObjArray.h"
#include "TString.h"

#include <iostream>

class CbmVolume;
//class TObjArray;

  /**
 * This Object is only used for internal book keeping!
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class CbmVolumeList : public TObject 
{
 private:
  TObjArray *fData;
  CbmVolumeList(const CbmVolumeList &L);
  CbmVolumeList& operator= (const CbmVolumeList&) {return *this;}

 public:
  CbmVolumeList();
  virtual ~CbmVolumeList();

  CbmVolume* getVolume( TString *name );
  Int_t getVolumeId( TString *name );

  CbmVolume* findObject( TString name );
  void addVolume( CbmVolume* elem);  
  
  Int_t getEntries () { return fData->GetEntries();}
  CbmVolume* At(Int_t pos ) { return ( (CbmVolume*) fData->At(pos)); }

    ClassDef(CbmVolumeList,1) // Volume List
};

#endif //CBM_VOLUMELIST_H
   

