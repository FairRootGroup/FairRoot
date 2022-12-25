/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRFASTSIMEXAMPLE2
#define FAIRFASTSIMEXAMPLE2

#include "FairFastSimDetector.h"   // for FairDetector

#include <Rtypes.h>           // for Int_t, Double32_t, Double_t, etc
#include <TLorentzVector.h>   // for TLorentzVector
#include <TVector3.h>         // for TVector3

class FairTutorialDet1Point;
class TClonesArray;
class FairModule;

class FairFastSimExample2 : public FairFastSimDetector
{
  public:
    /**      Name :  Detector Name */
    FairFastSimExample2(const char* Name);

    /**      default constructor    */
    FairFastSimExample2();

    /**       destructor     */
    virtual ~FairFastSimExample2();

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const;

    /**      has to be called after each event to reset the containers      */
    virtual void Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    /**      This method is an example of how to add your own point
     *       of type FairTutorialDet1Point to the clones array
     */
    FairTutorialDet1Point*
        AddHit(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom, Double_t time, Double_t length, Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
     */
    virtual void EndOfEvent();

    virtual Bool_t IsSensitive(const std::string& name);

    virtual FairModule* CloneModule() const;

  protected:
    virtual void FastSimProcessParticle();

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
    TClonesArray* fPointsArray;

    FairFastSimExample2(const FairFastSimExample2&);
    FairFastSimExample2& operator=(const FairFastSimExample2&);

    ClassDef(FairFastSimExample2, 2);
};

#endif   // FAIRTUTORIALDET_H
