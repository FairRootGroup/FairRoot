/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----   FairTutorialDet4HitProducerIdealMissallign source file       -----
// -----                  Created 11.02.13  by F. Uhlig                -----
// -------------------------------------------------------------------------
#include "FairTutorialDet4HitProducerIdealMisalign.h"

#include "FairLogger.h"                 // for FairLogger, etc
#include "FairRootManager.h"            // for FairRootManager
#include "FairRunAna.h"                 // for FairRunAna
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairTutorialDet4GeoHandler.h"  // for FairTutorialDet4GeoHandler
#include "FairTutorialDet4Hit.h"        // for FairTutorialDet4Hit
#include "FairTutorialDet4MisalignPar.h"
#include "FairTutorialDet4GeoPar.h"
#include "FairTutorialDet4Point.h"      // for FairTutorialDet4Point

#include "TClonesArray.h"               // for TClonesArray
#include "TMath.h"                      // for Cos, Sin
#include "TMathBase.h"                  // for Abs
#include "TRandom.h"                    // for TRandom, gRandom
#include "TVector3.h"                   // for TVector3

#include <stddef.h>                     // for NULL

// -----   Default constructor   -------------------------------------------
FairTutorialDet4HitProducerIdealMisalign::FairTutorialDet4HitProducerIdealMisalign()
  : FairTask("Missallign Hit Producer for the TutorialDet"),
    fPointArray(NULL),
    fHitArray(NULL),
    fShiftX(),
    fShiftY(),
    fShiftZ(),
    fRotX(),
    fRotY(),
    fRotZ(),
    fDigiPar(NULL),
    fGeoHandler(new FairTutorialDet4GeoHandler),
    fGeoPar(NULL),
    fDoMisalignment(kFALSE)
{
}

// -----   Destructor   ----------------------------------------------------
FairTutorialDet4HitProducerIdealMisalign::~FairTutorialDet4HitProducerIdealMisalign() { }

// --------------------------------------------------
void FairTutorialDet4HitProducerIdealMisalign::SetParContainers()
{

  LOG(INFO)<< "Set tutdet missallign parameters"<<FairLogger::endl;
  // Get Base Container
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = static_cast<FairTutorialDet4MisalignPar*>
             (rtdb->getContainer("FairTutorialDet4MissallignPar"));

  fGeoPar = static_cast<FairTutorialDet4GeoPar*>
             (rtdb->getContainer("FairTutorialDet4GeoPar"));

}
// --------------------------------------------------------------------
InitStatus FairTutorialDet4HitProducerIdealMisalign::ReInit()
{

  // Get Base Container
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = static_cast<FairTutorialDet4MisalignPar*>
             (rtdb->getContainer("FairTutorialDet4MissallignPar"));

  fShiftX=fDigiPar->GetShiftX();
  fShiftY=fDigiPar->GetShiftY();
  fShiftZ=fDigiPar->GetShiftZ();
  fRotX=fDigiPar->GetRotX();
  fRotY=fDigiPar->GetRotY();
  fRotZ=fDigiPar->GetRotZ();

  return kSUCCESS;
}

// -----   Public method Init   --------------------------------------------
InitStatus FairTutorialDet4HitProducerIdealMisalign::Init()
{

  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) {
    LOG(FATAL) << "RootManager not instantised!" << FairLogger::endl;
    return kFATAL;
  }

  // Get input array
  fPointArray = static_cast<TClonesArray*>(ioman->GetObject("TutorialDetPoint"));
  if ( ! fPointArray ) {
    LOG(FATAL)<<"No TutorialDetPoint array!" << FairLogger::endl;
    return kFATAL;
  }

  // Create and register output array
  fHitArray = new TClonesArray("FairTutorialDet4Hit");
  ioman->Register("TutorialDetHit", "TutorialDet", fHitArray, kTRUE);

  LOG(INFO)<< "HitProducerIdealMissallign: Initialisation successfull"
           << FairLogger::endl;


  fShiftX=fDigiPar->GetShiftX();
  fShiftY=fDigiPar->GetShiftY();
  fShiftZ=fDigiPar->GetShiftZ();
  fRotX=fDigiPar->GetRotX();
  fRotY=fDigiPar->GetRotY();
  fRotZ=fDigiPar->GetRotZ();

  Bool_t isGlobalCoordinateSystem=fGeoPar->IsGlobalCoordinateSystem();
  if (isGlobalCoordinateSystem) {
    LOG(FATAL) << "Task can only work with local coordinates."
	       << FairLogger::endl;
  }
  /*
    Int_t num = fDigiPar->GetNrOfDetectors();
    Int_t size = fShiftX.GetSize();
    LOG(INFO)<<"Array has a size of "<< size << "elements"<<FairLogger::endl;
    for (Int_t i=0; i< num; ++i) {
      LOG(INFO)<< i <<": "<<fShiftX.At(i)<<FairLogger::endl;
    }
  */
  return kSUCCESS;

}
// -----   Public method Exec   --------------------------------------------
void FairTutorialDet4HitProducerIdealMisalign::Exec(Option_t* /*opt*/)
{

  fHitArray->Clear();

  // Declare some variables
  FairTutorialDet4Point* point = NULL;
  Int_t detID   = 0;        // Detector ID
//  Int_t trackID = 0;        // Track index
  Double_t x, y, z;         // Position
  Double_t dx = 0.1;        // Position error
//  Double_t tof = 0.;        // Time of flight
  TVector3 pos, dpos;       // Position and error vectors

  // Loop over TofPoints
  Int_t nHits = 0;
  Int_t nPoints = fPointArray->GetEntriesFast();
  for (Int_t iPoint=0; iPoint<nPoints; iPoint++) {
    point = static_cast<FairTutorialDet4Point*>(fPointArray->At(iPoint));
    if ( ! point) { continue; }

    // Detector ID
    detID = point->GetDetectorID();

    // MCTrack ID
//    trackID = point->GetTrackID();

    if(fDoMisalignment) {

      Float_t cosAlpha = TMath::Cos(fRotZ.At(detID));
      Float_t sinAlpha = TMath::Sin(fRotZ.At(detID));

      // Determine hit position
      x  = (point->GetX()*cosAlpha + point->GetY()*sinAlpha)-fShiftX.At(detID);
      y  = (-point->GetX()*sinAlpha + point->GetY()*cosAlpha)-fShiftY.At(detID);
      z  = point->GetZ();

      LOG(DEBUG)<<"Pos before misalignment: "<< point->GetX() <<", "
                << point->GetY() <<", "<< point->GetZ() <<FairLogger::endl;
      LOG(DEBUG)<<"Pos after misalignment: "<< x <<", "
                << y <<", "<< z <<FairLogger::endl;

      x = x + GetHitErr(0.1);
      y = y + GetHitErr(0.1);

      LOG(DEBUG2)<<"Missallign hit by "<<fShiftX.At(detID)<<" cm in x- and "
                 << fShiftY.At(detID)<<" cm in y-direction."<<FairLogger::endl;

      // Time of flight
//      tof = point->GetTime();

      // Create new hit
      pos.SetXYZ(x,y,z);
      dpos.SetXYZ(dx, dx, 0.);
      new ((*fHitArray)[nHits]) FairTutorialDet4Hit(detID, iPoint, pos, dpos);
      nHits++;
    }  else {

      // Determine hit position
      x  = point->GetX();
      y  = point->GetY();
      z  = point->GetZ();

      LOG(INFO)<<"Position: "<<x<<", "<<y<<", "<<z<<FairLogger::endl;

      Double_t local[3] = {x, y, z};
      Double_t global[3];

      fGeoHandler->LocalToGlobal(local, global, detID);

      x = global[0] + GetHitErr(0.1);
      y = global[1] + GetHitErr(0.1);
      z = global[2];

      LOG(INFO)<<"Position: "<<x<<", "<<y<<", "<<z<<FairLogger::endl;
      LOG(INFO)<<"****"<<FairLogger::endl;
      // Time of flight
      //tof = point->GetTime();

      // Create new hit
      pos.SetXYZ(x,y,z);
      dpos.SetXYZ(dx, dx, 0.);
      new ((*fHitArray)[nHits]) FairTutorialDet4Hit(detID, iPoint, pos, dpos);
      nHits++;

    }
  }
  // Event summary
  LOG(DEBUG)<< "Create " << nHits << " TutorialDetHits out of "
            << nPoints << " TutorilaDetPoints created." << FairLogger::endl;

}
// -------------------------------------------------------------------------

Double_t FairTutorialDet4HitProducerIdealMisalign::GetHitErr(Double_t sigma)
{
  Double_t err = gRandom->Gaus(0, sigma);
  return (TMath::Abs(err) < 3 * sigma) ? err : (err > 0) ? 3 * sigma : -3 * sigma;
}



ClassImp(FairTutorialDet4HitProducerIdealMisalign)
