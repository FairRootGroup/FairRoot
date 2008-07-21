#ifndef CBMDETECTOR_H
#define CBMDETECTOR_H

#include "CbmModule.h"

class CbmVolume;
class TClonesArray;

/**
 * Base class for constructing detecors
 * @author M. Al-Turany, Denis Bertini
 * @version 0.1
 * @since 12.01.04 
 */
class CbmDetector : public CbmModule{


public:
  
    /**
      constructor
      Name :  Detector Name
      Active: kTRUE for active detectors  (ProcessHits() will be called)
              kFALSE for inactive detectors
    */
    CbmDetector(const char * Name, Bool_t Active, Int_t DetId=0);
    /**
      default constructor
    */
    CbmDetector();
    /**
      destructor
    */
    virtual ~CbmDetector();
    /**
      Initialization of the detector is done here
    */
    virtual void   Initialize();
    /**
      this method is called for each step during simulation (see CbmMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( CbmVolume *v=0)=0;
    /**
      this is called at the end of an event
    */ 
    virtual void   EndOfEvent(){;}
    /**
      Registers the produced collections in CBMRootManager.
    */
    virtual void   Register()=0;

    /** Gets the produced collections **/
    virtual TClonesArray* GetCollection(Int_t iColl) const = 0;

    /**
      has to be called after each event to reset the containers    
    */
    virtual void   Reset()=0;
    
    virtual void   CopyClones( TClonesArray *cl1,  TClonesArray *cl2 , Int_t offset) {;}
    
    virtual void   FinishPrimary(){;}                               
    virtual void   FinishRun(){;}
    virtual void   BeginPrimary(){;}   
    virtual void   PostTrack(){;}                                     
    virtual void   PreTrack(){;}                                      
    virtual void   BeginEvent(){;}
    virtual void   SetSpecialPhysicsCuts(){;} 
    void SaveGeoParams();
    Int_t  GetDetId() {return fDetId;}

private:
   CbmDetector(const CbmDetector &M);
   CbmDetector& operator= (const CbmDetector&) {return *this;}


 protected:

    Int_t fDetId; // Detector Id has to be set from ctr.

    ClassDef(CbmDetector,1)

};
#endif //CBMDETECTOR_H
