#ifndef CBM_VOLUME_H
#define CBM_VOLUME_H

#include "TNamed.h"

//#include "TObject.h"
//#include "TObjArray.h"

#include <iostream>

class CbmGeoNode;
class CbmModule;
/**
 * This Object is only used for internal book keeping!
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */
   

class CbmVolume : public TNamed{ 

public:

  CbmVolume();
  CbmVolume(TString name, Int_t id=0, Int_t detid=0,CbmModule *fMod=0);
  virtual ~CbmVolume();

   const char*  GetName() { return fName.Data();}
   TString getName() { return fName;}

   void setRealName( TString name ) { fRealName = name;}
   const char* getRealName() { return fRealName.Data();}
   Int_t getVolumeId() { return fVolumeId;}
   Int_t getModId() { return  fModId;}
   void  setModId(Int_t id) { fModId=id;}
   void  setCopyNo(Int_t id){ fCopyNo=id;}
   void  setVolumeId ( Int_t id ) {fVolumeId= id;}
   void  setGeoNode(CbmGeoNode *d){fNode=d;}
   void  setMotherId(Int_t fM){fMotherId=fM;}
   void  setMotherCopyNo(Int_t CopyNo){fMotherCopyNo=CopyNo;}

   CbmModule *GetModule(){return fModule;}
   void SetModule(CbmModule *mod){fModule=mod;}
   
   Int_t getMCid(){return fMCid;}
   Int_t getCopyNo(){ return fCopyNo;}
   void  setMCid(Int_t id){fMCid=id;}
   CbmGeoNode *getGeoNode(){return fNode;}
   Int_t getMotherId(){ return fMotherId;}
   Int_t getMotherCopyNo(){return fMotherCopyNo;}

    
private:
   CbmVolume(const CbmVolume &V);
   CbmVolume& operator= (const CbmVolume&) {return *this;}

   TString fName; 	/**Volume Name in MC*/
   TString fRealName;	/**Volume Name in ASCII file*/
   Int_t fVolumeId;       /**Volume Id in GeoManager*/
   Int_t fModId;          /**Module Id in which this volume exist*/
   Int_t fMCid;		/**Volume Id in MC*/
   Int_t fCopyNo;         /**Volume Copy No*/
   Int_t fMotherId;	/**Mother Volume Id*/
   Int_t fMotherCopyNo;   /**Mother Volume Copy No*/
   CbmModule *fModule;	/**The Module (detector) which will proccess the hits for this volume*/
   CbmGeoNode *fNode;     /**Node corresponding to this volume*/

   ClassDef(CbmVolume,2) // Volume Definition
        
};

#endif //
