/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairRadMapManager source file                   -----
// -------------------------------------------------------------------------

#include "FairRadMapManager.h"

#include "FairRadMapPoint.h"            // for FairRadMapPoint
#include "FairRootManager.h"            // for FairRootManager

#include "Riosfwd.h"                    // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TGeoVolume.h"                 // for TGeoVolume
#include "TLorentzVector.h"             // for TLorentzVector
#include "TMap.h"                       // for TMap
#include "TObjArray.h"                  // for TObjArray
#include "TObject.h"                    // for TObject
#include "TVector3.h"                   // for TVector3
#include "TVectorDfwd.h"                // for TVectorD
#include "TVectorT.h"                   // for TVectorT
#include "TVirtualMC.h"                 // for TVirtualMC, gMC
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include <stdio.h>                      // for NULL, printf
#include <iostream>                     // for operator<<, basic_ostream, etc

using namespace std;


ClassImp(FairRadMapManager)

FairRadMapManager* FairRadMapManager::fgInstance = NULL;

FairRadMapManager* FairRadMapManager::Instance()
{
  /**singelton instance*/
  return fgInstance;
}

FairRadMapManager::FairRadMapManager()
  : fPointCollection(new TClonesArray("FairRadMapPoint")),
    fTrackID(0),
    fVolumeID(0),
    fPdg(0),
    fPosIn(TLorentzVector(0,0,0,0)),
    fPosOut(TLorentzVector(0,0,0,0)),
    fMomIn(TLorentzVector(0,0,0,0)),
    fMomOut(TLorentzVector(0,0,0,0)),
    fTime(0),
    fLength(0),
    fStep(0),
    fELoss(0),
    fDose(0),
    fDoseSL(0),
    fA(0),
    fZmat(0),
    fRadl(0),
    fDensity(0),
    fAbsl(0),
    fActVol(0),
    fActMass(0),
    fMassMap(NULL)
{
  /** radiation length default ctor */
  if(NULL == fgInstance) {
    fgInstance = this;
    //    fPointCollection=new TClonesArray("FairRadMapPoint");
  }

}


FairRadMapManager::~FairRadMapManager()
{
  /** radiation length default dtor */
  fgInstance = NULL;
  fPointCollection->Delete();
  delete fPointCollection;
  delete fMassMap;
}

void FairRadMapManager::Init()
{
  /**create the branch for output */
  FairRootManager::Instance()->Register("RadMap","RadMapPoint", fPointCollection, kTRUE);
  cout << "RadMapMan initialized" << endl;

  // compute once the masses of the volumes in this simulation and store them in a TMap object

  Int_t volumeiterator=0,lastvolume=0;
  Double_t vmass;
  TObjArray* volumelist;
  TGeoVolume* myvolume;
  const char* volumename;
  fMassMap = new TMap(lastvolume+1,0);

  volumelist = gGeoManager->GetListOfVolumes();

  lastvolume = volumelist->GetLast();

  volumeiterator=0;

  cout << "RadMapMan: calculating the masses for " << lastvolume << " volumes in this simulation" << endl;

  while ( volumeiterator<=lastvolume ) {
    volumename = volumelist->At(volumeiterator)->GetName();
    myvolume = gGeoManager->GetVolume(volumename);
    vmass = myvolume->WeightA(); // calculate weight analytically
    TVectorD* vomass= new TVectorD(1,1,vmass,"END"); // 1-dim vector

    fMassMap->Add(myvolume,vomass);

    cout <<  myvolume->GetName() << " has " << vmass << " kg" << endl;

    volumeiterator++;
  }

}

void FairRadMapManager::Reset()
{
  /**We have to free the momeory, Clear() is faster but not enough! */
  fPointCollection->Delete();
  printf(" FairRadMapManager::Reset() ------------------------------------------------\n");
}

void FairRadMapManager::AddPoint(Int_t&)
{
  /**Add a point to the collection*/
  if ( gMC->IsTrackEntering() ) {
    fELoss  = 0.;
    fStep = 0.;
    fDose = 0.;
    fDoseSL = 0.;
    fPdg = 0;
    fActVol = 0.;
    fActMass = 0.;
    Int_t copyNo;
    fVolumeID = gMC->CurrentVolID(copyNo);
    fTime   = gMC->TrackTime() * 1.0e09;
    fLength = gMC->TrackLength();
    gMC->TrackPosition(fPosIn);
    gMC->TrackMomentum(fMomIn);
    //    Int_t MatId=  gMC->CurrentMaterial(fA, fZmat, fDensity, fRadl, fAbsl);
    gMC->CurrentMaterial(fA, fZmat, fDensity, fRadl, fAbsl);

    //    if (!gGeoManager) { GetGeoManager(); }
    //    TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
    TGeoVolume* actVolume = gGeoManager->GetVolume(fVolumeID);

    TVectorD* ActMass = static_cast<TVectorD*>(fMassMap->GetValue(actVolume));

    fActMass = ActMass->Min(); // read from TVectorD

    //    cout << actVolume->GetName() << " has " << fActMass << " kg" << endl;

  }
  /** Sum energy loss for all steps in the active volume */
  fELoss += gMC->Edep();
  fStep  += gMC->TrackStep();

  fPdg = gMC->TrackPid();

  // calculate the energy dose
  // exclude fragments with PDG code >= 10000

  if (fPdg<10000 && fStep>0 && fActMass>0 ) {
    //       fDose = fELoss*1.602e-10/(fDensity*actvol*0.001); // per mass/kg
    fDose = fELoss*1.602e-10/(fActMass); // per mass/kg
  } else {
    fDose = -.00001;
  }

  // exclude very high, probably wrong, energy doses
  if ( fDose>0.02 ) {
    fDose = -.00001;
  }

  /**  Create a point at exit of the volume */
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {

//    FairRadMapPoint* p=0;
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    Int_t copyNo;
    Int_t fVolID = gMC->CurrentVolID(copyNo); // CAVEAT: fVolID is NOT an unique identifier!!
    gMC->TrackPosition(fPosOut);
    gMC->TrackMomentum(fMomOut);

    TClonesArray& clref = *fPointCollection;
    Int_t tsize = clref.GetEntriesFast();

//    p=new(clref[tsize]) FairRadMapPoint(fTrackID, fVolID,
    new(clref[tsize]) FairRadMapPoint(fTrackID, fVolID,
                                        TVector3(fPosIn.X(),fPosIn.Y(),fPosIn.Z()),
                                        TVector3(fMomIn.X(),fMomIn.Y(),fMomIn.Z()),
                                        fTime, fLength, fELoss,
                                        TVector3(fPosOut.X(),fPosOut.Y(),fPosOut.Z()),
                                        TVector3(fMomOut.X(),fMomOut.Y(),fMomOut.Z()),
                                        fA, fZmat, fDensity, fActMass, fStep, fDose, fDoseSL, fPdg);

  }

}


