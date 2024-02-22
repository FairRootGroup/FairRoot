/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNSIM_H
#define FAIRRUNSIM_H

#include "FairGenericVMCConfig.h"
#include "FairIon.h"             // for FairIon
#include "FairMCApplication.h"   // for FairMCApplication
#include "FairParticle.h"        // for FairParticle
#include "FairRun.h"             // for FairRun

#include <Rtypes.h>      // for Bool_t, Double_t, Int_t, etc
#include <TMCtls.h>      // for multi-threading
#include <TObjArray.h>   // for TObjArray
#include <TString.h>     // for TString
#include <functional>
#include <memory>
#include <utility>

class FairField;
class FairGeoLoader;
class FairMCEventHeader;
class FairMesh;
class FairModule;
class FairPrimaryGenerator;

/**
 * \brief Configure the Simulation session
 * \ingroup base_steer fairroot_singleton
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */
class FairRunSim : public FairRun
{
  public:
    /** default ctor*/
    FairRunSim(Bool_t isMaster = kTRUE);
    /** default dtor*/
    ~FairRunSim() override;

    static FairRunSim* Instance();
    /**
     *       Add a module to the simulation (e.g. PIPE, Magnet, ..etc)
     */
    void AddModule(FairModule* Mod);
    /**
     *       Add a user defined ion to the simulation
     */
    void AddNewIon(FairIon* ion) { fIons->Add(ion); }
    /**
     *       Add a user defined ion to the simulation
     */
    void AddNewParticle(FairParticle* Particle) { fParticles->Add(Particle); }
    /**
     *       this method is used by the FAIRMCApplication
     */
    TObjArray* GetUserDefIons();
    /**
     *       this method is used by the FAIRMCApplication
     */
    TObjArray* GetUserDefParticles();

    /**
     *       Initialize the Simulation
     */
    void Init() override;
    /**
     *       run the  simulation
     */
    void Run(Int_t NEvents = 0, Int_t NotUsed = 0) override;
    /**
     *       Set the magnetic that has to be used for simulation field
     */
    void SetField(FairField* field);
    /**
     *       Set the event generator that has to be used for simulation field
     */
    void SetGenerator(FairPrimaryGenerator* Gen);

    /**
     *       Set the experiment dependent event header
     *       for each Monte Carlo Event
     */
    void SetMCEventHeader(FairMCEventHeader* McHeader) { fMCEvHead = McHeader; }

    /** Set the material file name to be used */
    void SetMaterials(const char* MatFileName);

    /**switch On/Off the track visualisation */
    void SetStoreTraj(Bool_t storeTraj = kTRUE) { fStoreTraj = storeTraj; }

    /**Return the switch for the track visualisation */
    Bool_t GetStoreTraj() const { return fStoreTraj; }

    /**switch On/Off the debug mode */
    void SetTrackingDebugMode(Bool_t set)
    {
        if (fApp) {
            fApp->SetTrackingDebugMode(set);
        }
    }

    /**Set geometry builder*/
    void SetGeoModel(const char* name);

    /**return the geometry loader used in this session*/
    TString* GetGeoModel() { return &fLoaderName; }

    /**Get the field used in simulation*/
    FairField* GetField() override { return fField; }

    /**Get the detector specific event header*/
    FairMCEventHeader* GetMCEventHeader();

    /**return the full list of modules used in simulation*/
    TObjArray* GetListOfModules() { return ListOfModules; }

    /**Get the used primary generator*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    FairPrimaryGenerator* GetPrimaryGenerator() { return fGen; }
#pragma GCC diagnostic pop

    /**switch On/Off external decayer (Pythia) */
    void SetPythiaDecayer(Bool_t decayer) { fPythiaDecayer = decayer; }

    /**switch On external decayer (Pythia). Config macro will be used */
    void SetPythiaDecayer(const TString& Config);

    /**switch On user defined decay, Config  macro will be called  */
    void SetUserDecay(const TString& Config);

    /**switch On/Off user defined decay if true gconfig/UserDecay.C macro will be called  */
    void SetUserDecay(Bool_t decay) { fUserDecay = decay; }

    /**Flag for external decayer*/
    Bool_t IsExtDecayer() { return fPythiaDecayer; }

    /**Flag for User decay*/
    Bool_t IsUserDecay() { return fUserDecay; }

    /**Switch on/off Radiation length register */
    void SetRadLenRegister(Bool_t value) { fRadLength = value; }

    void SetRadMapRegister(Bool_t value) { fRadMap = value; }

    void SetRadGridRegister(Bool_t value) { fRadGrid = value; }

    void AddMesh(FairMesh* Mesh);

    void SetUserConfig(const TString& Config) { fUserConfig = Config; }
    TString GetUserConfig() { return fUserConfig; }

    void SetUserCuts(const TString& Cuts) { fUserCuts = Cuts; }
    TString GetUserCuts() { return fUserCuts; }

    /** Set Beam energy in GeV/c */
    void SetBeamMom(Double_t BeamMom)
    {
        fBeamMom = BeamMom;
        fUseBeamMom = kTRUE;
    }

    /** Get the Beam energy */
    Double_t GetBeamMom() { return fBeamMom; }

    /**Get beam energy flag */
    Bool_t UseBeamMom() { return fUseBeamMom; }
    void SetFieldContainer();

    void SetSimSetup(std::function<void()> f)
    {
        fSimSetup = f;
        fUseSimSetupFunction = true;
    }
    void SetSimSetupPostInit(std::function<void()> f)
    {
        fSimSetupPostInit = f;
        fUseSimSetupPostInitFunction = true;
    }

    void SetSimulationConfig(std::unique_ptr<FairGenericVMCConfig> tconf) { fSimulationConfig = std::move(tconf); }
    /**
     * Get non-owning pointer
     */
    FairGenericVMCConfig* GetSimulationConfig() { return fSimulationConfig.get(); }

    /**
     * Set the MultiThreaded mode, available only for Geant4
     */
    void SetIsMT(bool isMT) { fIsMT = isMT; }
    /**
     * Read the MultiThreaded mode
     */
    bool IsMT() const { return fIsMT; }
    /**
     * Read the used transport MultiThreaded mode
     */
    bool WasMT() const { return fWasMT; }

    void SetImportTGeoToVMC(Bool_t v) { fImportTGeoToVMC = v; }
    Bool_t IsImportTGeoToVMC() const { return fImportTGeoToVMC; }

    void StopMCRun() { fApp->StopMCRun(); }

    /**
     * Get non-owning pointer to FairMCApplication
     */
    auto GetMCApplication() { return fApp; }

    void ls(Option_t* option = "") const override;

  private:
    FairRunSim(const FairRunSim& M);
    FairRunSim& operator=(const FairRunSim&) { return *this; }
    void SetMCConfig();
    void CheckFlukaExec();

    bool fWasMT{false};   //!                              /** Actual MT mode used */

    std::unique_ptr<FairGeoLoader> fGeoLoader;   //!

  protected:
    Int_t count{0};                     //!< Internal counter
    FairMCApplication* fApp{nullptr};   //!< Main VMC application
    Double_t fBeamMom{0};               //!< Beam Energy in GeV/c
    Bool_t fUseBeamMom{kFALSE};         //!< flag for use Beam Energy
    /**
     * Primary Event Generator
     *
     * \deprecated Use \ref GetPrimaryGenerator() / \ref SetGenerator()
     * \deprecated Deprecated in v18.8, will be removed in v19.2.
     */
    [[deprecated("Use Setter/Getter")]] FairPrimaryGenerator* fGen{nullptr};   //!

    FairMCEventHeader* fMCEvHead;                   //!                          /** MC Event Header */
    static TMCThreadLocal FairRunSim* fginstance;   //!              /** Singleton Instance */
    FairField* fField;                              /** Magnetic Field */
    TObjArray* fIons;                               //!                              /** Array of user defined ions */
    TObjArray* fParticles;                          //!                         /** Array of user defined particles*/
    TObjArray* ListOfModules;                       //!                       /** Array of used modules */
    TString MatFname;                               //!                           /** Material file name */
    bool fStoreTraj{false};                         //!< Trajectory store flags
    TString fLoaderName{"TGeo"};                    //!< Geometry Model (TGeo or G3)
    Bool_t fPythiaDecayer;                          //!                    /** flag for using Pythia decayer*/
    TString fPythiaDecayerConfig;                   //!               /** Macro for Pythia decay configuration*/
    Bool_t fUserDecay;                              /** flag for setting user decay */
    TString fUserDecayConfig;                       //!                   /** Macro for decay configuration*/
    Bool_t fRadLength;                              //!                       /** flag for registring radiation length*/
    Bool_t fRadMap;                                 //!                            /** flag for RadiationMapManager
    Bool_t fRadGrid;                                //!
    TObjArray* fMeshList;                           //!                          /** radiation grid scoring
    TString fUserConfig;                            //!                        /** Macro for geant configuration*/
    TString fUserCuts;                              //!                          /** Macro for geant cuts*/
    bool fIsMT{false};                              //!                              /** MT mode option (Geant4 only)*/
    Bool_t fImportTGeoToVMC;                        //!                   /** Allow importing TGeometry to VMC */
    std::function<void()> fSimSetup;   //!                          /** A user provided function to do sim setup /
                                       //!                          instead of using macros **/
    bool fUseSimSetupFunction = false;
    std::function<void()> fSimSetupPostInit;   //!                          /** A user provided function to do sim setup
                                               //!                          / instead of using macros **/
    bool fUseSimSetupPostInitFunction = false;
    std::unique_ptr<FairGenericVMCConfig> fSimulationConfig{};   //!                 /** Simulation configuration */

    ClassDefOverride(FairRunSim, 2);
};

#endif   // FAIRRUNSIM_H
