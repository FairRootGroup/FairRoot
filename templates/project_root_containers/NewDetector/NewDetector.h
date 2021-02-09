/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef NEWDETECTOR_H
#define NEWDETECTOR_H

#include "FairDetector.h"

#include <TLorentzVector.h>
#include <TVector3.h>

class NewDetectorPoint;
class FairVolume;
class TClonesArray;

class NewDetector : public FairDetector
{

  public:
    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
     */
    NewDetector(const char* Name, Bool_t Active);

    /**      default constructor    */
    NewDetector();

    /**       destructor     */
    virtual ~NewDetector();

    /**      Initialization of the detector is done here    */
    virtual void Initialize();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
     */
    virtual void ProcessHits();

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const;

    /**      has to be called after each event to reset the containers      */
    virtual void Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    /**      This method is an example of how to add your own point
     *       of type NewDetectorPoint to the clones array
     */
    NewDetectorPoint*
        AddHit(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom, Double_t time, Double_t length, Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
     */

    virtual void SetSpecialPhysicsCuts() { ; }
    virtual void EndOfEvent();
    virtual void FinishPrimary() { ; }
    virtual void FinishRun() { ; }
    virtual void BeginPrimary() { ; }
    virtual void PostTrack() { ; }
    virtual void PreTrack() { ; }
    virtual void BeginEvent() { ; }

    virtual FairModule* CloneModule() const;

    virtual Bool_t IsSensitive(const std::string& name);

  private:
    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t fTrackID;        //!  track index
    Int_t fVolumeID;       //!  volume id
    TLorentzVector fPos;   //!  position at entrance
    TLorentzVector fMom;   //!  momentum at entrance
    Double32_t fTime;      //!  time
    Double32_t fLength;    //!  length
    Double32_t fELoss;     //!  energy loss

    /** container for data points */

    TClonesArray* fNewDetectorPointCollection;   //!

    NewDetector(const NewDetector&);
    NewDetector& operator=(const NewDetector&);

    void DefineSensitiveVolumes();

    ClassDef(NewDetector, 2);
};

#endif   // NEWDETECTOR_H
