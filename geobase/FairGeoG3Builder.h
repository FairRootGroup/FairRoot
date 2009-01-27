#ifndef CBMGEOG3BUILDER_H
#define CBMGEOG3BUILDER_H

#include "FairGeoBuilder.h"
#include "TMap.h"


//class TGeoManager;
class TGeant3;
/**
 * class to create geometry in Geant3
 *
 */

class FairG3MapedNames : public TObject {
protected:
    static TMap  fVolumeMap;
    static TMap  fMediumMap;

public:
    FairG3MapedNames(){;}
    ~FairG3MapedNames(){;}
    void  saveVolumeName( const char*, const char*);
    void  saveMediumName( const char*, const char*);
    static const char* getTruncVolName( const char *vname);
    static const char* getTruncMedName( const char *vname);
    static void listVolumes();
    static void listMedium();
    static const char*  getVolRealName(const char* tname);
    static const char*  getMedRealName(const char* tname);


ClassDef(FairG3MapedNames,1) //

};


class FairGeoG3Builder : public FairGeoBuilder {
protected:
 TGeant3* gMC3;//!
 Int_t fDebug;//!
 Int_t fCountVolume;//!
 Int_t fCountMedium;//!
 FairG3MapedNames* fMapedNames; //!
 char tName[4]; //!

public:
  FairGeoG3Builder();
  FairGeoG3Builder(const char*,const char*);
  ~FairGeoG3Builder() {if (fMapedNames) {
                          fMapedNames->Write();
                          delete fMapedNames;
                          }
  }
  void SetVerbosity ( Int_t flag ) { fDebug = flag;}
  Bool_t createNode(FairGeoNode*, Int_t hadFormat=0);
  Int_t createMedium(FairGeoMedium*);
  const char* truncateName( Int_t id );
  ClassDef(FairGeoG3Builder,0) //
private:
  FairGeoG3Builder(const FairGeoG3Builder &L);
  FairGeoG3Builder& operator= (const FairGeoG3Builder&) {return *this;}
};

#endif /* !CBMGEOG3BUILDER_H */
