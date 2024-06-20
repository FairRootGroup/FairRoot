/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMODULE_H
#define FAIRMODULE_H

#include "FairGeoInterface.h"   // for FairGeoInterface
#include "FairGeoLoader.h"      // for FairGeoLoader
#include "FairGeoNode.h"        // for FairGeoNode
#include "FairGeoSet.h"
#include "FairGeoVolume.h"
#include "FairRun.h"         // for FairRun
#include "FairRuntimeDb.h"   // for FairRuntimeDb

#include <TCollection.h>   // for TRangeDynCast
#include <TGeoMatrix.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TList.h>       // for TList (ptr only), TListIter
#include <TNamed.h>      // for TNamed
#include <TObjArray.h>   // for TObjArray
#include <TRefArray.h>   // for TRefArray
#include <TString.h>     // for TString, operator!=
#include <TVirtualMC.h>
#include <fairlogger/Logger.h>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class FairRunSim;
class FairVolumeList;
class FairVolume;

/**
 * Base class for constructing all detecors and passive volumes
 * @author M. Al-Turany, Denis Bertini
 * @version 1.0
 * @since 01.04.08 M.Al-Turany
 * Add methods to construct geometry via ROOT files
 * Add some documentation
 *
 * Changelog: 29.02.2012 [O.Merle] Fixed missing material assignment for top volume.
 *                                 ... and please - add some documentation to your code.
 */
class FairModule : public TNamed
{
  public:
    /**default ctor*/
    FairModule();
    /**Standard ctor*/
    FairModule(const char* Name, const char* title, Bool_t Active = kFALSE);
    /**default dtor*/
    ~FairModule() override;
    /**Print method should be implemented in detector or module*/
    void Print(Option_t*) const override { ; }
    /**Set the geometry file name o be used*/
    virtual void SetGeometryFileName(TString fname, TString geoVer = "0");
    /**Get the Geometry file name*/
    virtual TString GetGeometryFileName() { return fgeoName; }
    /**Get the geometry file version if used*/
    virtual TString GetGeometryFileVer() { return fgeoVer; }
    /**method called from the MC application to construct the geometry, has to be implimented by user*/
    virtual void ConstructGeometry();
    /**method called from the MC application to set optical geometry properties*/
    virtual void ConstructOpGeometry();
    /**construct geometry from root files (TGeo)*/
    virtual void ConstructRootGeometry(TGeoMatrix* shiftM = nullptr);
    /**construct geometry from standard ASSCII files (Hades Format)*/
    virtual void ConstructASCIIGeometry();
    /**
     * Modify the geometry for the simulation run using methods of the Root geometry package
     * \deprecated Deprecated pre-v18.8, will be removed in v20.
     */
    [[deprecated("Use FairAlignmentHandler instead, see Tutorial4 for examples")]] virtual void ModifyGeometry()
    {
        LOG(warn) << "This function is deprecated. Use FairAlignmentHandler instead, see Tutorial4 for examples.";
    }
    virtual void RegisterAlignmentMatrices() { ; }

    /**construct geometry from GDML files*/
    virtual void ConstructGDMLGeometry(__attribute__((unused)) TGeoMatrix* posrot);
    /** custom settings of processes and cuts for media to be forwarded to the
     ** detector simulation */
    virtual void SetSpecialPhysicsCuts() { ; }
    /** Clone this object (used in MT mode only)*/
    virtual FairModule* CloneModule() const;
    /** Init worker run (used in MT mode only) */
    virtual void BeginWorkerRun() const { ; }
    /** Finish worker run (used in MT mode only) */
    virtual void FinishWorkerRun() const { ; }

    /** @deprecated template function to construct geometry. to be used in derived classes.
     * The first and the third argument are meaningless, just pass nullptr */
    template<class T, class U>
    [[deprecated("Broken signature, use ConstructASCIIGeometry(TString) instead")]] void
        ConstructASCIIGeometry(T*, TString containerName = "", U* = nullptr);
    /** Helper function to construct geometry. */
    template<class T, class U>
    void ConstructASCIIGeometry(TString containerName = "");

    /**Set the sensitivity flag for volumes, called from ConstructASCIIRootGeometry(), and has to be implimented for
     * detectors which use ConstructASCIIRootGeometry() to build the geometry */
    virtual Bool_t IsSensitive(const std::string& name);
    /**The function below is depracated, please change to the new method above */
    virtual Bool_t CheckIfSensitive(__attribute__((unused)) std::string name) __attribute__((
        deprecated("The method CheckIfSensitive is deprecated. Implement IsSensitive in the detector classes.")))
    {
        return kFALSE;
    }
    /**called from ConstructRootGeometry()*/
    virtual void ExpandNode(TGeoNode* Node);
    /**called from ConstructGDMLGeometry()*/
    virtual void ExpandNodeForGDML(__attribute__((unused)) TGeoNode* curNode);
    /**return the MC id of a volume named vname*/
    virtual Int_t getVolId(const TString&) const { return 0; }
    /**return the detector/Module id (which was set in the sim macro for the detector)*/
    Int_t GetModId() { return fModId; }
    /**Set the verbose level in this detector*/
    void SetVerboseLevel(Int_t level) { fVerboseLevel = level; }
    /**return the detector status */
    Bool_t IsActive() { return fActive; }
    /**set the detector/module id*/
    void SetModId(Int_t id) { fModId = id; }
    /** Set the name of the mother volume to which a new geometry is added.
     ** This function is needed for geometries which are defined as ROOT geometry manager.
     **/
    void SetMotherVolume(TString volName) { fMotherVolumeName = volName; }
    /**called from ConstuctASCIIGeometry*/
    void ProcessNodes(TList* aList);
    /**Set the parameter containers*/
    virtual void SetParContainers() { ; }
    /** Initialize everything which has to be done before the construction and modification
     ** of the geometry. Mostly this is needed to read data from the parameter containers.*/
    virtual void InitParContainers() { ; }
    /**return the geo parameter of this detector/module*/
    TList* GetListOfGeoPar() { return flGeoPar; }

    /**list of volumes in a simulation session*/
    static thread_local inline FairVolumeList* vList{nullptr};   //!
    /**total number of volumes in a simulaion session*/
    static thread_local inline Int_t fNbOfVolumes{0};   //!
    /**
     * For internal use only: list of all sensitive volumes in a simulaion session
     */
    static thread_local std::vector<FairVolume*> fAllSensitiveVolumes;   //!

    TString fMotherVolumeName{""};   //!
    /**
     * \deprecated Not used anywhere, will be removed in a future release
     */
    [[deprecated]] FairVolume* getFairVolume(FairGeoNode* fNode);
    void AddSensitiveVolume(TGeoVolume* v);

    /**
     * \brief For internal use: Set the current RunSim
     */
    void SetRunSim(FairRunSim* runsim) { fRunSim = runsim; }

  private:
    /// Set during FairRunSim::AddModule
    FairRunSim* fRunSim{nullptr};   //!

    /** Re-implimented from ROOT:  TGeoMatrix::SetDefaultName()  */
    void SetDefaultMatrixName(TGeoMatrix* matrix);
    void AssignMediumAtImport(TGeoVolume* v);   // O.Merle, 29.02.2012 - see impl.

    /**called from ConstructGDMLGeometry. Changes default ID created by TGDMLParse*/
    void ReAssignMediaId();
    void swap(FairModule& other) throw();

    void RegisterSensitiveVolume(FairVolume&);

  protected:
    FairModule(const FairModule&);
    FairModule& operator=(const FairModule&);
    TString fgeoVer{"Not defined"};
    TString fgeoName{"Not defined"};
    Int_t fModId{-1};
    Bool_t fActive{kFALSE};
    Int_t fNbOfSensitiveVol{0};   //!
    Int_t fVerboseLevel{0};
    TList* flGeoPar{nullptr};   //!  list of Detector Geometry parameters
    Bool_t fGeoSaved{kFALSE};   //! flag for initialisation
    TVirtualMC* fMC{nullptr};   //! cahed pointer to MC (available only after initialization)

    /**
     * \brief Get Geometry Loader
     * \note Only valid during ConstructGeometry
     */
    FairGeoLoader& GetGeometryLoader();

    ClassDefOverride(FairModule, 4);
};

template<class T, class U>
void FairModule::ConstructASCIIGeometry(TString containerName)
{
    static_assert(std::is_base_of_v<FairGeoSet, T>);
    static_assert(std::is_base_of_v<FairParSet, U>);
    FairGeoSet& MGeo = GetGeometryLoader().LoadAndCreate<T>(GetGeometryFileName());

    TList* volList = MGeo.getListOfVolumes();
    // store geo parameter
    FairRun* fRun = FairRun::Instance();
    FairRuntimeDb* rtdb = FairRun::Instance()->GetRuntimeDb();

    if ("" != containerName) {
        LOG(info) << "Add GeoNodes for " << MGeo.getDescription() << " to container " << containerName;

        //    U par=(U)(rtdb->getContainer(containerName));
        U* par = static_cast<U*>(rtdb->getContainer(containerName));
        TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
        TObjArray* fPassNodes = par->GetGeoPassiveNodes();

        FairGeoVolume* aVol = nullptr;

        for (auto node : TRangeDynCast<FairGeoNode>(volList)) {
            if (!node) {
                continue;
            }
            aVol = node;
            if (node->isSensitive()) {
                fSensNodes->AddLast(aVol);
            } else {
                fPassNodes->AddLast(aVol);
            }
        }
        ProcessNodes(volList);
        par->setChanged();
        par->setInputVersion(fRun->GetRunId(), 1);
    }
}

template<class T, class U>
void FairModule::ConstructASCIIGeometry(T*, TString containerName, U*)
{
    ConstructASCIIGeometry<T, U>(containerName);
}

#endif   // FAIRMODULE_H
