/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "Pixel.h"

#include "PixelPoint.h"
#include "PixelGeo.h"
#include "PixelGeoPar.h"



#include "FairDetectorList.h"           // for DetectorId::kTutDet
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairGeoVolume.h"              // for FairGeoVolume
#include "FairRootManager.h"            // for FairRootManager
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairStack.h"                  // for FairStack
#include "FairVolume.h"                 // for FairVolume
#include "FairLogger.h"                 // for logging



#include <iosfwd>                       // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TList.h"                      // for TListIter, TList (ptr only)
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString
#include "TVirtualMC.h"                 // for TVirtualMC
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include "TGeoPhysicalNode.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"

#include <stddef.h>                     // for NULL


#include <iostream>
using std::cout;
using std::endl;

Pixel::Pixel()
  : FairDetector("Pixel", kTRUE, kPixel),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fMisalignDetector(kFALSE),
    fPixelPointCollection(new TClonesArray("PixelPoint"))
{
}

Pixel::Pixel(const char* name, Bool_t active)
  : FairDetector(name, active, kPixel),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fMisalignDetector(kFALSE),
    fPixelPointCollection(new TClonesArray("PixelPoint"))
{
}

Pixel::~Pixel()
{
  if (fPixelPointCollection) {
    fPixelPointCollection->Delete();
    delete fPixelPointCollection;
  }
}

void Pixel::Initialize()
{
  FairDetector::Initialize();
}

Bool_t  Pixel::ProcessHits(FairVolume* vol)
{

  /** This method is called from the MC stepping */
  //Set parameters at entrance of volume. Reset ELoss.
  if ( TVirtualMC::GetMC()->IsTrackEntering() ) {
    fELoss  = 0.;
    fTime   = TVirtualMC::GetMC()->TrackTime() * 1.0e09;
    fLength = TVirtualMC::GetMC()->TrackLength();
    TVirtualMC::GetMC()->TrackPosition(fPos);
    TVirtualMC::GetMC()->TrackMomentum(fMom);
  }

  // Sum energy loss for all steps in the active volume
  fELoss += TVirtualMC::GetMC()->Edep();

  // Create PixelPoint at exit of active volume
  if ( TVirtualMC::GetMC()->IsTrackExiting()    ||
       TVirtualMC::GetMC()->IsTrackStop()       ||
       TVirtualMC::GetMC()->IsTrackDisappeared()   ) {
    fTrackID  = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();


    if (fELoss == 0. ) { return kFALSE; }

    // Taking stationNr and sectorNr from string is almost effortless.
    // Simulation of 100k events with 5 pions without magnetic field takes:
    // - Real time 142.366 s, CPU time 140.32s WITH USING VolPath TO GET fVolumeID
    // - Real time 142.407 s, CPU time 140.64s WITHOUT THE FOLLOWING TString OPERATIONS
    {
      TString detPath = TVirtualMC::GetMC()->CurrentVolPath();
      detPath.Remove (0,detPath.Last('/')+1);
      detPath.Remove (0,detPath.First("Pixel")+5);
      Int_t stationNr = detPath.Atoi();
      detPath.Remove (0,detPath.First("_")+1);
      Int_t sectorNr  = detPath.Atoi();
      fVolumeID = stationNr*256+sectorNr;
    }

    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of Pixel det points in TParticle
    FairStack* stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
    stack->AddPoint(kPixel);
  }

  return kTRUE;
}

void Pixel::EndOfEvent()
{

  fPixelPointCollection->Clear();

}



void Pixel::Register()
{

  /** This will create a branch in the output tree called
      PixelPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  FairRootManager::Instance()->Register("PixelPoint", "Pixel",
                                        fPixelPointCollection, kTRUE);

}


TClonesArray* Pixel::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fPixelPointCollection; }
  else { return NULL; }
}

void Pixel::Reset()
{
  fPixelPointCollection->Clear();
}

void Pixel::ConstructGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

    PixelGeo*  Geo  = new PixelGeo();
    ConstructASCIIGeometry<PixelGeo, PixelGeoPar>(Geo, "PixelGeoPar");
}

void Pixel::ModifyGeometry() {  
  if ( !fMisalignDetector ) {
    return;
  }
  if(0==gGeoManager) {
    std::cout<<" -E- No gGeoManager in PndGemDetector::Initialize()!"<<std::endl;
    return;
  }

  TString tName = Form("/cave/Pixel1_1");
  cout << tName.Data() << endl;	
  TGeoPhysicalNode* tgpn = gGeoManager->MakePhysicalNode(tName.Data());
  if ( !tgpn ) {cout << "no thpn" << endl; return;} 
  cout << "got TGPN" << endl;
  TGeoHMatrix* tghm = static_cast<TGeoHMatrix*>(tgpn->GetOriginalMatrix());
  if ( !tghm ) {cout << "no tghm" << endl; return;}
  cout << "got TGHM" << endl;
  cout << " * * *  o r i g  * * *  o r i g  * * *  o r i g  * * *  o r i g  * * * " << endl;
  tghm->Print();
  tghm->RotateX(0.);
  tghm->RotateY(0.);
  tghm->RotateZ(0.);//gRandom->Gaus(0.,.1));
  Double_t* trans = tghm->GetTranslation();
  cout << "trans = " << trans[0] << " " << trans[1] << " " << trans[2] << endl;
  cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
  for ( Int_t ic = 0 ; ic < 3 ; ic++ ) 
    trans[ic] += 3.-ic;//gRandom->Gaus(0.,.03);
  tghm->SetTranslation(trans);
  cout << " * * * m o v e d * * * m o v e d * * * m o v e d * * * m o v e d * * * " << endl;
  tghm->Print();
  cout << " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
  tgpn->Align(tghm);
}

PixelPoint* Pixel::AddHit(Int_t trackID, Int_t detID,
                                      TVector3 pos, TVector3 mom,
                                      Double_t time, Double_t length,
                                      Double_t eLoss)
{
  TClonesArray& clref = *fPixelPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) PixelPoint(trackID, detID, pos, mom,
         time, length, eLoss);
}

ClassImp(Pixel)
