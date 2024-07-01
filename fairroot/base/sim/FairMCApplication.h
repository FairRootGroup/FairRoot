/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairMCApplication header file                   -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#ifndef FAIR_MC_APPLICATION_H
#define FAIR_MC_APPLICATION_H

#include "FairRadGridManager.h"
#include "FairRunInfo.h"   // for FairRunInfo

#include <Rtypes.h>                  // for Int_t, Bool_t, Double_t, etc
#include <TLorentzVector.h>          // for TLorentzVector
#include <TRefArray.h>               //
#include <TString.h>                 // for TString
#include <TVirtualMC.h>              // for TVirtualMC
#include <TVirtualMCApplication.h>   // for TVirtualMCApplication
#include <list>                      // for list
#include <map>                       // for map, multimap, etc
#include <memory>                    // for std::unique_ptr
#include <vector>                    // for std::vector

class FairDetector;
class FairEventHeader;
class FairField;
class FairGenericStack;
class FairModule;
class FairMCEventHeader;
class FairPrimaryGenerator;
class FairRadLenManager;
class FairRadMapManager;
class FairRootManager;
class FairTask;
class FairTrajFilter;
class FairVolume;
class FairRunSim;
class TChain;
class TTask;

enum class FairMCApplicationState
{
    kUnknownState,
    kConstructGeometry,
    kInitGeometry
};

/**
 * The Main Application ( Interface to MonteCarlo application )
 * \ingroup base_sim fairroot_singleton
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
    FairMCApplication(const char* name, const char* title, TObjArray* ModList, const char* MatName);
    /** default constructor
     */
    FairMCApplication();

    FairMCApplication(const FairMCApplication&) = delete;
    FairMCApplication& operator=(const FairMCApplication&) = delete;
    FairMCApplication(FairMCApplication&&) = delete;
    FairMCApplication& operator=(FairMCApplication&&) = delete;

    /** default destructor
     */
    ~FairMCApplication() override;

    static FairMCApplication* Instance();
    virtual void AddDecayModes();
    /**  Add user defined particles (optional) */
    void AddParticles() override;   // MC Application
    /** Add user defined ions (optional)
        Called by TVirtualMC.
        TGeant3 calls AddIons() first, then InitGeometry().
        TGeant4 calls InitGeometry() first, then AddIons().*/
    void AddIons() override;   // MC Application
    /**
     *Add user defined Tasks to be executed after each event (optional)
     * @param fTask: Task that has to be excuted during simulation
     */
    void AddTask(TTask* fTask);
    /** Define actions at the beginning of the event */
    void BeginEvent() override;   // MC Application
    /** Define actions at the beginning of primary track */
    void BeginPrimary() override;   // MC Application
    /** Construct user geometry */
    void ConstructGeometry() override;   // MC Application
    /** Align or misalign geometry before actual run       */
    Bool_t MisalignGeometry() override;
    /** Define parameters for optical processes (optional) */
    void ConstructOpGeometry() override;   // MC Application
    /** Define actions at the end of event */
    void FinishEvent() override;   // MC Application
    /** Define actions at the end of primary track */
    void FinishPrimary() override;   // MC Application
    /** Define actions at the end of run */
    void FinishRun();
    /** Generate primary particles */
    void GeneratePrimaries() override;   // MC Application
    /** Return detector by name  */
    FairDetector* GetDetector(const char* DetName);
    /** Return Field used in simulation*/
    FairField* GetField() { return fxField; }
    /**Return primary generator*/
    FairPrimaryGenerator* GetGenerator();
    /**Return list of tasks*/
    TTask* GetListOfTasks();
    FairGenericStack* GetStack();
    TChain* GetChain();
    /** Initialize geometry
        Called by TVirtualMC.
        TGeant3 calls AddIons() first, then InitGeometry().
        TGeant4 calls InitGeometry() first, then AddIons().*/
    void InitGeometry() override;   // MC Application
    /** Initialize MC engine */
    void InitMC(const char* setup, const char* cuts);
    /** Initialize Tasks if any*/
    void InitTasks();
    /**Define actions at the end of each track */
    void PostTrack() override;   // MC Application
    /** Define actions at the beginning of each track*/
    void PreTrack() override;   // MC Application

    /** Clone for worker (used in MT mode only) */
    TVirtualMCApplication* CloneForWorker() const override;

    /** Init application on worker (used in MT mode only) */
    void InitOnWorker() override;

    /** Finish run on worker (used in MT mode only) */
    void FinishRunOnWorker() override;

    /** Run the MC engine
     * @param nofEvents : number of events to simulate
     */
    void RunMC(Int_t nofEvents);
    /**
     * Set the magnetic field for simulation
     * @param field: magnetic field
     */
    void SetField(FairField* field);
    /**
     * Set the event generator  for simulation
     * @param fxGenerator: Event generator(s)
     */
    void SetGenerator(FairPrimaryGenerator* fxGenerator);
    /**
     * Set the parameter containers needed by Tasks(if any)
     */
    void SetParTask();
    /**
     * Switch for using Pythia as external decayer
     * @param decayer: if TRUE pythia will decay particles specifid in the Decay Config macro (see
     * SetPythiaDecayerConfig)
     */
    void SetPythiaDecayer(Bool_t decayer) { fPythiaDecayer = decayer; }
    /**
     * set the decay configuration macro to be used by Pythia
     */
    void SetPythiaDecayerConfig(const TString decayerConf) { fPythiaDecayerConfig = decayerConf; }
    /**
     * Switch for using the radiation length manager
     */
    void SetRadiationLengthReg(Bool_t RadLen);
    /**
     * Switch for using the radiation map manager
     */
    void SetRadiationMapReg(Bool_t RadMap);
    /**
     * Switch for debuging the tracking
     */
    void SetTrackingDebugMode(Bool_t set) { fDebug = set; }
    /**
     * Switch for using 2 or 3 body phase-space decay
     * @param  decay: if TRUE 2/3 body phase space decay will be used for particle specified in the User Decay Config
     * macro (see SetUserDecayConfig)
     */
    void SetUserDecay(Bool_t decay) { fUserDecay = decay; }
    /**
     * set the decay configuration macro to be used by user decay
     */
    void SetUserDecayConfig(const TString decayerConf) { fUserDecayConfig = decayerConf; }
    /** Define action at each step, dispatch the action to the corresponding detectors */
    void Stepping() override;   // MC Application
    /** Stop the run*/
    virtual void StopRun();
    /** Stop the run*/
    virtual void StopMCRun();
    /**Define maximum radius for tracking (optional) */
    Double_t TrackingRmax() const override;   // MC Application
    /** Define maximum z for tracking (optional) */
    Double_t TrackingZmax() const override;   // MC Application

    void AddMeshList(TObjArray* meshList);

    /**
     * Set if the current event should be written to the output file.
     * The default value which is set back after each event is to store
     * the event.
     */
    void SetSaveCurrentEvent(Bool_t set) { fSaveCurrentEvent = set; }

    /**
     * Get the current application state.
     */
    FairMCApplicationState GetState() const { return fState; }

    /**
     * Return non-owning pointer to FairRadGridManager
     */
    auto GetRadGridMan() { return fRadGridMan.get(); }

    /**
     * Return the MT state of TVirtualMC
     */
    auto GetIsMT() { return fMC ? fMC->IsMT() : false; }

    void ls(Option_t* option = "") const override;

  private:
    // methods
    Int_t GetIonPdg(Int_t z, Int_t a) const;

    /** Register output */
    void RegisterOutput();
    /** Finalize the init stage:
        initialize event generator,
        initialize tasks,
        write output folder.*/
    void InitFinalizer();

    void UndoGeometryModifications();

    /** Simulation Stack  */
    std::unique_ptr<FairGenericStack> fStack;   //!

  protected:
    // data members
    /**
     * \brief Main instance
     *
     * Only set for instances created by \ref CloneForWorker
     * and points to the instance from which the clone was
     * created
     */
    const FairMCApplication* fParent{nullptr};   //!
    /**List of active detector */
    TRefArray fActiveDetectors;
    /**List of FairTask*/
    FairTask* fFairTaskList;   //!
    /**Module list in simulation*/
    TObjArray* fModules;
    /**flag for using Pythia as external decayer */
    Bool_t fPythiaDecayer;
    /** Pythia decay config macro*/
    TString fPythiaDecayerConfig;   //!
    /**Pointer to thr I/O Manager */
    FairRootManager* fRootManager;   //!
    /**Magnetic Field Pointer*/
    FairField* fxField;   //
    /**Primary generator*/
    FairPrimaryGenerator* fEvGen;   //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t fMcVersion;   // mc Version
    /** Track visualization manager */
    std::unique_ptr<FairTrajFilter> fTrajFilter;   //!
    /**Flag for accepted tracks for visualization*/
    bool fTrajAccepted{false};   //!
    /**Flag for using user decay*/
    Bool_t fUserDecay;
    /**User decay config macro*/
    TString fUserDecayConfig;   //!
    /** Debug flag*/
    Bool_t fDebug;   //!
    /**dispatcher internal use */
    std::multimap<Int_t, FairVolume*> fVolMap;   //!
    /** Track position*/
    /**dispatcher internal use RadLeng*/
    std::map<Int_t, Int_t> fModVolMap;   //!
    TLorentzVector fTrkPos;              //!
    /** Flag for Radiation length register mode  */
    bool fRadLength{false};   //!

    /**Radiation length Manager*/
    std::unique_ptr<FairRadLenManager> fRadLenMan;   //!
    /** Flag for Radiation map register mode  */
    bool fRadMap{false};   //!
    /**Radiation Map Manager*/
    std::unique_ptr<FairRadMapManager> fRadMapMan;   //!
    /**Radiation map Grid Manager*/
    std::unique_ptr<FairRadGridManager> fRadGridMan{};   //!

    FairEventHeader* fEventHeader;   //!

    FairMCEventHeader* fMCEventHeader;   //!
    /** list of senstive detectors used in the simuation session*/
    std::list<FairDetector*> listActiveDetectors;   //!
    /** list of all detectors used in the simuation session*/
    std::list<FairDetector*> listDetectors;   //!
    /** Pointer to the current MC engine //!
     */
    TVirtualMC* fMC;

    FairRunSim* fRun{nullptr};   //!

    /** Flag if the current event should be saved */
    Bool_t fSaveCurrentEvent;

    /** Current state */
    FairMCApplicationState fState;   //!

    ClassDefOverride(FairMCApplication, 5);

  private:
    /** Private special copy constructor, needed for CloneForWorker */
    FairMCApplication(const FairMCApplication&, std::unique_ptr<FairRunSim>);

    FairRunInfo fRunInfo;   //!
    Bool_t fGeometryIsInitialized;

    /**
     * List of modules, mirrors fModules
     */
    std::vector<FairModule*> fListModules{};   //!

    /**
     * Owned Modules (inside the worker)
     */
    std::vector<std::unique_ptr<FairModule>> fOwnedModules;   //!

    /**
     * Clean up the FairRunSim created in CloneForWorker
     */
    std::unique_ptr<FairRunSim> fWorkerRunSim;   //!
};

// inline functions

inline FairMCApplication* FairMCApplication::Instance()
{
    return static_cast<FairMCApplication*>(TVirtualMCApplication::Instance());
}

#endif
