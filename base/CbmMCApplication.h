
#ifndef CBM_MC_APPLICATION_H
#define CBM_MC_APPLICATION_H

#include "CbmTask.h"
#include "TVirtualMCApplication.h"
#include <map>
#include "TLorentzVector.h"

class CbmRootManager;
class TRefArray;
class TObjArray;
class CbmGenericStack;
class CbmModule;
class CbmDetector;
class CbmField;
class TTask;
class CbmPrimaryGenerator;
class CbmTrajFilter;
class TChain;
class CbmVolume;
class CbmRadLenManager;


/**
 * The Main Application ( Interface to MonteCarlo application )
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class CbmMCApplication : public TVirtualMCApplication
{

  public:
    /** Standard constructor 
   *@param name      name
   *@param title     title
   *@param ModList  a TObjArray containing all detectors and modules used in this simulation
   *@param MatName  material file name 
   */
    CbmMCApplication(const char * name,   const char * title, TObjArray *ModList, const char *MatName);
   /** default constructor 
   */
    CbmMCApplication();
   /** Special constructor, used for initializing G3 for Geane track propagation 
   *@param Geane    true to initialize Geane
   */
    CbmMCApplication(Bool_t Geane);
    /** default destructor 
   */
    virtual ~CbmMCApplication();
    /** Singelton instance 
    */
    static CbmMCApplication* Instance(); 
    virtual void        AddDecayModes();  
    virtual void        AddParticles();                                   // MC Application
    virtual void        AddIons();                                        // MC Application
    void                  AddTask(TTask *fTask);
    virtual void        BeginEvent();                                     // MC Application
    virtual void        BeginPrimary();                                   // MC Application
    virtual void        ConstructGeometry();                              // MC Application
    virtual void        ConstructOpGeometry();                            // MC Application
    virtual void        Field(const Double_t* x, Double_t* b) const;      // MC Application
    virtual void        FinishEvent();                                    // MC Application
    virtual void        FinishPrimary();                                  // MC Application
    void                  FinishRun();
    virtual void        GeneratePrimaries();                              // MC Application
    CbmDetector*          GetDetector(const char *DetName);
    CbmField*             GetField(){return fxField;}
    CbmPrimaryGenerator*  GetGenerator();
    TTask*                GetListOfTasks();    
    CbmGenericStack*      GetStack();
    TChain*               GetChain();
    virtual void        InitGeometry();                                   // MC Application
    void                  InitMC(const char *setup);
    void                  InitTasks();
    Bool_t 		  IsGeane(){return fGeane;}
    virtual void        PostTrack();                                      // MC Application
    virtual void        PreTrack();                                       // MC Application
    void                  RunMC(Int_t nofEvents);
    void                  SetField(CbmField *field);
    void                  SetGenerator(CbmPrimaryGenerator *fxGenerator);
    void                  SetPythiaDecayer(Bool_t decayer){fPythiaDecayer=decayer;}
    void                  SetRadiationLengthReg(Bool_t RadLen);
    void                  SetTrackingDebugMode( Bool_t set ) {fDebug = set;}
    void                  SetUserDecay(Bool_t decay){fUserDecay= decay;}
    virtual void        Stepping();                                       // MC Application
    virtual void        StopRun();                                        // MC Application
    virtual Double_t    TrackingRmax() const;                             // MC Application
    virtual Double_t    TrackingZmax() const;                             // MC Application
    void                GeanePreTrack(Float_t *x,Float_t *p ,Int_t PDG);                     // PreTrack for Geane
private:
    // methods
    void RegisterStack();
    // data members
    /**Iterator for active detector list*/
    TIterator           *fActDetIter;//!
    /**List of active detector */	
    TRefArray           *fActiveDetectors;
    /**List of CbmTask*/
    CbmTask             *fCbmTaskList;//!
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
    /** Simulation Stack  */
    CbmGenericStack     *fStack; //!
    /**Pointer to thr I/O Manager */
    CbmRootManager      *fRootManager; //!
    /**List of sensetive volumes in all detectors*/
    TRefArray           *fSenVolumes; //!
    /**Magnetic Field Pointer*/
    CbmField            *fxField; //
    /**Primary generator*/
    CbmPrimaryGenerator *fEvGen; //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t                fMcVersion;     // mc Version
    /** Track visualization manager */
    CbmTrajFilter       *fTrajFilter; //!
    /**Flag for accepted tracks for visualization*/
    Bool_t               fTrajAccepted; //!
    /**Flag for using user decay*/
    Bool_t               fUserDecay;
    /** Debug flag*/
    Bool_t               fDebug;//!
    /**dispatcher internal use */
    CbmVolume 	        *fDisVol;
    /**dispatcher internal use */ 
    CbmDetector         *fDisDet;
    /**dispatcher internal use */  
    std::multimap <Int_t, CbmVolume* > fVolMap;//!
    /**dispatcher internal use */   
    std::multimap <Int_t, CbmVolume* >::iterator fVolIter; //!
    /** Track position*/
    TLorentzVector fTrkPos; //!
    /** Flag for Radiation length register mode  */
    Bool_t   fRadLength;  //!
    
    /**Radiation length Manager*/
    CbmRadLenManager  *fRadLenMan; //!

    ClassDef(CbmMCApplication,1)  //Interface to MonteCarlo application
private:
   CbmMCApplication(const CbmMCApplication &M);
   CbmMCApplication& operator= (const CbmMCApplication&) {return *this;}
};

// inline functions

inline CbmMCApplication* CbmMCApplication::Instance()
{ return (CbmMCApplication*)(TVirtualMCApplication::Instance());}

#endif

