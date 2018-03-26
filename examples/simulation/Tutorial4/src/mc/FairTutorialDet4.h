/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4_H
#define FAIRTUTORIALDET4_H

#include "FairDetector.h"               // for FairDetector

#include "Rtypes.h"                     // for Int_t, Bool_t, Double32_t, etc
#include "TArrayD.h"                    // for TArrayD
#include "TLorentzVector.h"             // for TLorentzVector
#include "TClonesArray.h"
#include "TVector3.h"                   // for TVector3

#include <string>                       // for string

class FairTutorialDet4Point;
class FairTutorialDet4GeoHandler;
class FairTutorialDet4MisalignPar;
class FairTutorialDet4Geo;
class FairVolume;
class TClonesArray;

class FairTutorialDet4: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairTutorialDet4(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTutorialDet4();

    /**       destructor     */
    virtual ~FairTutorialDet4();

    /**      Initialization of the detector is done here    */
    virtual void   Initialize();

    /**      Init parameter containers    */
    virtual void   InitParContainers();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( FairVolume* v=0);

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void   Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const ;

    /**      has to be called after each event to reset the containers      */
    virtual void   Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    /**      Misalign the detector geometry        */
    void ModifyGeometry();

    void SetParContainers();

    /**      This method is an example of how to add your own point
     *       of type FairTutorialDet4Point to the clones array
    */
    FairTutorialDet4Point* AddHit(Int_t trackID, Int_t detID,
                                  TVector3 pos, TVector3 mom,
                                  Double_t time, Double_t length,
                                  Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
    */

//    virtual void   CopyClones( TClonesArray* cl1,  TClonesArray* cl2 ,
//                               Int_t offset) {;}
    virtual void   SetSpecialPhysicsCuts() {;}
    virtual void   EndOfEvent();
    virtual void   FinishPrimary() {;}
    virtual void   FinishRun() {;}
    virtual void   BeginPrimary() {;}
    virtual void   PostTrack() {;}
    virtual void   PreTrack() {;}
    virtual void   BeginEvent() {;}

    void SetModifyGeometry(Bool_t val) { fModifyGeometry=val; }
    void SetGlobalCoordinates(Bool_t val) { fGlobalCoordinates=val; }

    virtual FairModule* CloneModule() const;

  private:
    void SetSensitiveVolumes();

    static FairTutorialDet4Geo* fgGeo;   //!


    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t          fTrackID;           //!  track index
    Int_t          fVolumeID;          //!  volume id
    TLorentzVector fPos;               //!  position at entrance
    TLorentzVector fMom;               //!  momentum at entrance
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss

    /** container for data points */

    TClonesArray*  fFairTutorialDet4PointCollection;

    FairTutorialDet4GeoHandler* fGeoHandler;

    FairTutorialDet4MisalignPar* fMisalignPar;

    Int_t fNrOfDetectors;
    TArrayD fShiftX;
    TArrayD fShiftY;
    TArrayD fShiftZ;
    TArrayD fRotX;
    TArrayD fRotY;
    TArrayD fRotZ;

    Bool_t fModifyGeometry;

    Bool_t fGlobalCoordinates;
    /** Method to construct the ascii geometry
     **
     **/
    void ConstructASCIIGeometry();

    Bool_t CheckIfSensitive(std::string name);

    void ModifyGeometryBySymlink();
    void ModifyGeometryByFullPath();


    FairTutorialDet4(const FairTutorialDet4&);
    FairTutorialDet4& operator=(const FairTutorialDet4&);

    ClassDef(FairTutorialDet4,2)
};

#endif //FAIRTUTORIALDET_H
