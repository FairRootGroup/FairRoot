#ifndef FAIRDETECTOR_H
#define FAIRDETECTOR_H

#include "FairModule.h"

class FairVolume;
class TClonesArray;

/**
 * Base class for constructing detecors
 * @author M. Al-Turany, Denis Bertini
 * @version 0.1
 * @since 12.01.04 
 */
class FairDetector : public FairModule{


public:
  
    /**
     * constructor
     * @param Name :  Detector Name
	 * @param Active: kTRUE for active detectors  (ProcessHits() will be called)
					  kFALSE for inactive detectors
    */
    FairDetector(const char * Name, Bool_t Active, Int_t DetId=0);
    /**
	 * default constructor
     */
    FairDetector();
    /**
     *Destructor
    */
    virtual ~FairDetector();
    /**
     *Initialization of the detector is done here
    */
    virtual void   Initialize();
    /**
	 *This method is called for each step during simulation (see FairMCApplication::Stepping())
	 *Has to be implimented in specific detector class
	 * @param FairVolume: current volume in stepping 
    */
    virtual Bool_t ProcessHits( FairVolume *v=0)=0;
    /**
     *this is called at the end of an event
    */ 
    virtual void   EndOfEvent(){;}
    /**
     * Registers the produced collections in FairRootManager.
	 * Has to be implimented in specific detector class
    */
    virtual void   Register()=0;

    /** Gets the produced collections 
	 * Has to be implimented in specific detector class
	*/
    virtual TClonesArray* GetCollection(Int_t iColl) const = 0;

    /**
     * called after each event to reset the containers
	 * Has to be implimented in specific detector class
    */
    virtual void   Reset()=0;
    
    virtual void   CopyClones( TClonesArray *cl1,  TClonesArray *cl2 , Int_t offset) {;}
    /** Action can be taken after each primary here*/
    virtual void   FinishPrimary(){;}                
	/** Action can be taken at end of a run here*/
    virtual void   FinishRun(){;}
	/** Action can be taken before each primary here*/
    virtual void   BeginPrimary(){;}
	/** Action can be taken after each track here*/
    virtual void   PostTrack(){;}           
	/** Action can be taken before each primary here*/
    virtual void   PreTrack(){;}  
	/** Action can be taken before each event here*/
    virtual void   BeginEvent(){;}
	/** User can impliment this method to set special cuts/process for the detector media
	 *  setting in this method will overwrite the global setting in g3/4Config.C and SetCuts.C
	 */
    virtual void   SetSpecialPhysicsCuts(){;} 
    /**Save the geometry parameters to the rtdb*/
	void SaveGeoParams();
	
	/**Return the Detector unique ID */
    Int_t  GetDetId() {return fDetId;}

private:
   FairDetector(const FairDetector &M);
   FairDetector& operator= (const FairDetector&) {return *this;}


 protected:

    Int_t fDetId; /** Detector Id has to be set from ctr.*/

    ClassDef(FairDetector,1)

};
#endif //FAIRDETECTOR_H
