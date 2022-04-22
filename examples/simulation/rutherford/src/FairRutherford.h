/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORD_H
#define CBMRUTHERFORD_H

#include "FairDetector.h"   // for FairDetector

#include <Rtypes.h>           // for Int_t, Double32_t, Double_t, etc
#include <TLorentzVector.h>   // for TLorentzVector
#include <TVector3.h>         // for TVector3

class FairRutherfordPoint;
class FairRutherfordGeo;
class FairVolume;
class TClonesArray;
class FairModule;

class FairRutherford : public FairDetector
{
  public:
    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
     */
    FairRutherford(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairRutherford();

    /**       destructor     */
    ~FairRutherford() override;

    /**      Initialization of the detector is done here    */
    void Initialize() override;

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
     */
    Bool_t ProcessHits(FairVolume* v = nullptr) override;

    /**       Registers the produced collections in FAIRRootManager.     */
    void Register() override;

    /** Gets the produced collections */
    TClonesArray* GetCollection(Int_t iColl) const override;

    /**      has to be called after each event to reset the containers      */
    void Reset() override;

    /**      Create the detector geometry        */
    void ConstructGeometry() override;

    /**      This method is an example of how to add your own point
     *       of type FairRutherfordPoint to the clones array
     */
    FairRutherfordPoint*
        AddHit(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom, Double_t time, Double_t length, Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
     */

    //    virtual void   CopyClones( TClonesArray* cl1,  TClonesArray* cl2 ,
    //                               Int_t offset) {;}
    void SetSpecialPhysicsCuts() override {}
    void EndOfEvent() override;
    void FinishPrimary() override {}
    void FinishRun() override {}
    void BeginPrimary() override {}
    void PostTrack() override {}
    void PreTrack() override {}
    void BeginEvent() override {}

    FairModule* CloneModule() const override;

  private:
    static FairRutherfordGeo* fgGeo;   //!

    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t fTrackID{-1};        //!  track index
    Int_t fVolumeID{-1};       //!  volume id
    TLorentzVector fPos{};     //!  position at entrance
    TLorentzVector fMom{};     //!  momentum at entrance
    Double32_t fTime{-1.};     //!  time
    Double32_t fLength{-1.};   //!  length
    Double32_t fELoss{-1};     //!  energy loss

    /** container for data points */

    TClonesArray* fFairRutherfordPointCollection;

    FairRutherford(const FairRutherford&);
    FairRutherford& operator=(const FairRutherford&);

    ClassDefOverride(FairRutherford, 1);
};

#endif   // CBMRUTHERFORD_H
