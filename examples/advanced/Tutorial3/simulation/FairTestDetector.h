/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTOR_H_
#define FAIRTESTDETECTOR_H_

#include "FairDetector.h"

#include <Rtypes.h>           // for Int_t, Double32_t, Double_t, etc
#include <TLorentzVector.h>   // for TLorentzVector
#include <TVector3.h>         // for TVector3

class FairTestDetectorPoint;
class FairVolume;
class TClonesArray;

class FairTestDetector : public FairDetector
{
  public:
    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
     */
    FairTestDetector(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTestDetector();

    /**       destructor     */
    ~FairTestDetector() override;

    /**      Initialization of the detector is done here    */
    void Initialize() override;

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
     */
    Bool_t ProcessHits(FairVolume* v = 0) override;

    /**       Registers the produced collections in FAIRRootManager.     */
    void Register() override;

    /** Gets the produced collections */
    TClonesArray* GetCollection(Int_t iColl) const override;

    /**      has to be called after each event to reset the containers      */
    void Reset() override;

    /**      Create the detector geometry        */
    void ConstructGeometry() override;

    /**      This method is an example of how to add your own point
     *       of type FairTestDetectorPoint to the clones array
     */
    FairTestDetectorPoint* AddHit(Int_t trackID,
                                  Int_t detID,
                                  TVector3 pos,
                                  TVector3 mom,
                                  TVector3 posOut,
                                  TVector3 momOut,
                                  Double_t time,
                                  Double_t length,
                                  Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
     */

    /*
    virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset)
    {
        ;
    }
*/
    void SetSpecialPhysicsCuts() override { ; }
    void EndOfEvent() override;
    void FinishPrimary() override { ; }
    void FinishRun() override { ; }
    void BeginPrimary() override { ; }
    void PostTrack() override { ; }
    void PreTrack() override { ; }
    void BeginEvent() override { ; }

  private:
    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t fTrackID;           //!  track index
    Int_t fVolumeID;          //!  volume id
    TLorentzVector fPos;      //!  position at entrance
    TLorentzVector fMom;      //!  momentum at entrance
    TLorentzVector fPosOut;   //!  position at entrance
    TLorentzVector fMomOut;   //!  momentum at entrance
    Double32_t fTime;         //!  time
    Double32_t fLength;       //!  length
    Double32_t fELoss;        //!  energy loss
    Int_t fEventNr;           //! current event number;

    /** container for data points */

    TClonesArray* fFairTestDetectorPointCollection;

    FairTestDetector(const FairTestDetector&);
    FairTestDetector& operator=(const FairTestDetector&);

    ClassDefOverride(FairTestDetector, 1);
};

#endif /* FAIRTESTDETECTOR_H_ */
