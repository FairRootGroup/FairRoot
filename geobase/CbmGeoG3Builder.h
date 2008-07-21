#ifndef CBMGEOG3BUILDER_H
#define CBMGEOG3BUILDER_H

#include "CbmGeoBuilder.h"
#include "TMap.h"


//class TGeoManager;
class TGeant3;
/**
 * class to create geometry in Geant3
 *
 */

class CbmG3MapedNames : public TObject {
protected:
    static TMap  fVolumeMap;
    static TMap  fMediumMap;

public:
    CbmG3MapedNames(){;}
    ~CbmG3MapedNames(){;}
    void  saveVolumeName( const char*, const char*);
    void  saveMediumName( const char*, const char*);
    static const char* getTruncVolName( const char *vname);
    static const char* getTruncMedName( const char *vname);
    static void listVolumes();
    static void listMedium();
    static const char*  getVolRealName(const char* tname);
    static const char*  getMedRealName(const char* tname);


ClassDef(CbmG3MapedNames,1) //

};


class CbmGeoG3Builder : public CbmGeoBuilder {
protected:
 TGeant3* gMC3;//!
 Int_t fDebug;//!
 Int_t fCountVolume;//!
 Int_t fCountMedium;//!
 CbmG3MapedNames* fMapedNames; //!
 char tName[4]; //!

public:
  CbmGeoG3Builder();
  CbmGeoG3Builder(const char*,const char*);
  ~CbmGeoG3Builder() {if (fMapedNames) {
                          fMapedNames->Write();
                          delete fMapedNames;
                          }
  }
  void SetVerbosity ( Int_t flag ) { fDebug = flag;}
  Bool_t createNode(CbmGeoNode*, Int_t hadFormat=0);
  Int_t createMedium(CbmGeoMedium*);
  const char* truncateName( Int_t id );
  ClassDef(CbmGeoG3Builder,0) //
private:
  CbmGeoG3Builder(const CbmGeoG3Builder &L);
  CbmGeoG3Builder& operator= (const CbmGeoG3Builder&) {return *this;}
};

#endif /* !CBMGEOG3BUILDER_H */
