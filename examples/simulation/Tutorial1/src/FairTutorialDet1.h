/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1_H
#define FAIRTUTORIALDET1_H

#include "FairDetector.h"   // for FairDetector

#include <Rtypes.h>           // for Int_t, Double32_t, Double_t, etc
#include <TClonesArray.h>     // for TClonesArray
#include <TLorentzVector.h>   // for TLorentzVector
#include <TVector3.h>         // for TVector3
#include <memory>             // for std::unique_ptr

class FairTutorialDet1Point;
class FairTutorialDet1Geo;
class FairVolume;
class FairModule;

class FairTutorialDet1 : public FairDetector
{
  public:
    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
     */
    FairTutorialDet1(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTutorialDet1();

    /**       destructor     */
    ~FairTutorialDet1() override;

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
     *       of type FairTutorialDet1Point to the clones array
     */
    FairTutorialDet1Point*
        AddHit(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom, Double_t time, Double_t length, Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
     */

    //    virtual void   CopyClones( TClonesArray* cl1,  TClonesArray* cl2 ,
    //                               Int_t offset) {;}
    void SetSpecialPhysicsCuts() override { ; }
    void EndOfEvent() override;
    void FinishPrimary() override { ; }
    void FinishRun() override { ; }
    void BeginPrimary() override { ; }
    void PostTrack() override { ; }
    void PreTrack() override { ; }
    void BeginEvent() override { ; }

    FairModule* CloneModule() const override;

    Bool_t IsSensitive(const std::string& name) override;

  private:
    /** Track information to be stored until the track leaves the
    active volume.
    */
    TLorentzVector fPos{};     //!  position at entrance
    TLorentzVector fMom{};     //!  momentum at entrance
    Double32_t fTime{-1.};     //!  time
    Double32_t fLength{-1.};   //!  length
    Double32_t fELoss{-1};     //!  energy loss

    bool fIsInitialised{false};   //!  prevent double initilization

    /** container for data points */

    std::unique_ptr<TClonesArray> fFairTutorialDet1PointCollection{new TClonesArray("FairTutorialDet1Point")};   //!

    FairTutorialDet1(const FairTutorialDet1&);
    FairTutorialDet1& operator=(const FairTutorialDet1&);

    ClassDefOverride(FairTutorialDet1, 1);
};

#endif   // FAIRTUTORIALDET_H
