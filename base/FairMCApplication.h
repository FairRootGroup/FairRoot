
#ifndef FAIR_MC_APPLICATION_H
#define FAIR_MC_APPLICATION_H

#include "FairTask.h"
#include "TVirtualMCApplication.h"
#include <map>
#include "TLorentzVector.h"

class FairRootManager;
class TRefArray;
class TObjArray;
class FairGenericStack;
class FairModule;
class FairDetector;
class FairField;
class TTask;
class FairPrimaryGenerator;
class FairTrajFilter;
class TChain;
class FairVolume;
class FairRadLenManager;


/**
 * The Main Application ( Interface to MonteCarlo application )
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairMCApplication : public TVirtualMCApplication
{

  public:
    /** Standard constructor 
   *@param name      name
   *@param title     title
   *@param ModList  a TObjArray containing all detectors and modules used in this simulation
   *@param MatName  material file name 
   */
    FairMCApplication(const char * name,   const char * title, TObjArray *ModList, const char *MatName="");
   /** default constructor 
   */
    FairMCApplication();
   /** Special constructor, used for initializing G3 for Geane track propagation 
   *@param Geane    true to initialize Geane
   */
    FairMCApplication(Bool_t Geane);
    /** default destructor 
   */
    virtual ~FairMCApplication();
    /** Singelton instance 
    */
    static FairMCApplication* Instance(); 
    virtual void          AddDecayModes();  
	 /**  Add user defined particles (optional) */
    virtual void          AddParticles();                                   // MC Application
	 /** Add user defined ions (optional) */
    virtual void          AddIons();                                        // MC Application
     /** Add user defined Tasks to be executed after each event (optional) */
	void                  AddTask(TTask *fTask);
    /** Define actions at the beginning of the event */
	virtual void          BeginEvent();                                     // MC Application
	/** Define actions at the beginning of primary track */
    virtual void          BeginPrimary();                                   // MC Application
    /** Construct user geometry */
	virtual void          ConstructGeometry();                              // MC Application
    /** Define parameters for optical processes (optional) */
	virtual void          ConstructOpGeometry();                            // MC Application
	/** Calculate user field  b at point x */
    virtual void          Field(const Double_t* x, Double_t* b) const;      // MC Application
	/** Define actions at the end of event */
    virtual void          FinishEvent();                                    // MC Application
	/** Define actions at the end of primary track */
    virtual void          FinishPrimary();                                  // MC Application
	/** Define actions at the end of run */
    void                  FinishRun();
	/** Generate primary particles */
    virtual void          GeneratePrimaries();                              // MC Application
	/** Return detector by name  */
    FairDetector*          GetDetector(const char *DetName);
	/** Return Field used in simulation*/
    FairField*             GetField(){return fxField;}
	/**Return primary generator*/
    FairPrimaryGenerator*  GetGenerator();
	/**Return list of tasks*/
    TTask*                GetListOfTasks();    
    FairGenericStack*      GetStack();
    TChain*               GetChain();
	/** Initialize geometry */
    virtual void          InitGeometry();                                   // MC Application
	/** Initialize MC engine */
    void                  InitMC(const char *setup,  const char *cuts);
    void                  InitTasks();
    Bool_t 		          IsGeane(){return fGeane;}
	/**Define actions at the end of each track */
    virtual void          PostTrack();                                      // MC Application
	/** Define actions at the beginning of each track*/
    virtual void          PreTrack();                                       // MC Application
    void                  RunMC(Int_t nofEvents);
    void                  SetField(FairField *field);
    void                  SetGenerator(FairPrimaryGenerator *fxGenerator);
    void                  SetPythiaDecayer(Bool_t decayer){fPythiaDecayer=decayer;}
	void                  SetPythiaDecayerConfig(const TString decayerConf){fPythiaDecayerConfig=decayerConf;}
    void                  SetRadiationLengthReg(Bool_t RadLen);
    void                  SetTrackingDebugMode( Bool_t set ) {fDebug = set;}
    void                  SetUserDecay(Bool_t decay){fUserDecay= decay;}
    void                  SetUserDecayConfig(const TString decayerConf){fUserDecayConfig= decayerConf;}

	/** Define action at each step */
    virtual void          Stepping();                                       // MC Application
    virtual void          StopRun();                                        
	/**Define maximum radius for tracking (optional) */
    virtual Double_t      TrackingRmax() const;                             // MC Application
    /** Define maximum z for tracking (optional) */
	virtual Double_t      TrackingZmax() const;                             // MC Application
    void                  GeanePreTrack(Float_t *x,Float_t *p ,Int_t PDG);                     // PreTrack for Geane
private:
    // methods
    void RegisterStack();
    // data members
    /**Iterator for active detector list*/
    TIterator           *fActDetIter;//!
    /**List of active detector */	
    TRefArray           *fActiveDetectors;
    /**List of FairTask*/
    FairTask             *fFairTaskList;//!
    /**Iterator for detector list (Passive and Active)*/
    TIterator           *fDetIter; //!
    /**detector list (Passive and Active)*/
    TRefArray           *fDetectors;
    /**Map used for dispatcher*/
    TRefArray           *fDetMap;
    /**Flag for Geane*/
    Bool_t	         fGeane;
    /**Iterator for Module list*/
    TIterator           *fModIter; //!
    /**Module list in simulation*/
    TObjArray           *fModules; 
    /**Number of sensetive volumes in simulation session*/
    Int_t                fNoSenVolumes; //!
    /**flag for using Pythia as external decayer */
    Bool_t               fPythiaDecayer;
	/** Pythia decay config macro*/
	TString               fPythiaDecayerConfig; //!
    /** Simulation Stack  */
    FairGenericStack     *fStack; //!
    /**Pointer to thr I/O Manager */
    FairRootManager      *fRootManager; //!
    /**List of sensetive volumes in all detectors*/
    TRefArray           *fSenVolumes; //!
    /**Magnetic Field Pointer*/
    FairField            *fxField; //
    /**Primary generator*/
    FairPrimaryGenerator *fEvGen; //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t                fMcVersion;     // mc Version
    /** Track visualization manager */
    FairTrajFilter       *fTrajFilter; //!
    /**Flag for accepted tracks for visualization*/
    Bool_t               fTrajAccepted; //!
    /**Flag for using user decay*/
    Bool_t               fUserDecay;
	/**User decay config macro*/
	TString               fUserDecayConfig; //!
    /** Debug flag*/
    Bool_t               fDebug;//!
    /**dispatcher internal use */
    FairVolume 	        *fDisVol;
    /**dispatcher internal use */ 
    FairDetector         *fDisDet;
    /**dispatcher internal use */  
    std::multimap <Int_t, FairVolume* > fVolMap;//!
    /**dispatcher internal use */   
    std::multimap <Int_t, FairVolume* >::iterator fVolIter; //!
    /** Track position*/
    TLorentzVector fTrkPos; //!
    /** Flag for Radiation length register mode  */
    Bool_t   fRadLength;  //!
    
    /**Radiation length Manager*/
    FairRadLenManager  *fRadLenMan; //!

    ClassDef(FairMCApplication,1)  //Interface to MonteCarlo application
private:
   FairMCApplication(const FairMCApplication &M);
   FairMCApplication& operator= (const FairMCApplication&) {return *this;}
};

// inline functions

inline FairMCApplication* FairMCApplication::Instance()
{ return (FairMCApplication*)(TVirtualMCApplication::Instance());}

#endif
