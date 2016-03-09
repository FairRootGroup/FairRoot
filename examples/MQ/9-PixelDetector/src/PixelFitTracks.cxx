/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFitTracks.cxx
 *
 *  Created on: 25.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFitTracks.h"

// Includes from base
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLink.h"
#include "FairLogger.h"

// Includes from ROOT
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TGeoManager.h"
#include "TGeoNode.h"
#include "TGeoVolume.h"
#include "TGeoBBox.h"

#include "PixelDigiPar.h"
#include "PixelHit.h"
#include "PixelTrack.h"

#include <map>

using std::pair;
using std::map;

// -----   Default constructor   ------------------------------------------
PixelFitTracks::PixelFitTracks()
  : PixelFitTracks("Pixel Track Fitter", 0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PixelFitTracks::PixelFitTracks(Int_t iVerbose) 
  : PixelFitTracks("Pixel Track Fitter", iVerbose)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name   -----------------------------------------
PixelFitTracks::PixelFitTracks(const char* name, Int_t iVerbose) 
  : FairTask(name, iVerbose)
  , fDigiPar(NULL)
  , fHits(NULL)
  , fTracks(NULL)
  , fFitTracks(NULL)
  , fTNofEvents(0)
  , fNHits(0)
  , fNTracks(0)
  , fTNofTracks(0)
  , fNFitTracks(0)
  , fTNofFitTracks(0)
{
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelFitTracks::~PixelFitTracks() { 
  Reset();
  if ( fDigiPar)   delete fDigiPar;
  if ( fFitTracks ) {
    fFitTracks->Delete();
    delete fFitTracks;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelFitTracks::Exec(Option_t* /*opt*/) {

  Reset();

  fNHits   = fHits  ->GetEntriesFast();
  fNTracks = fTracks->GetEntriesFast();

  LOG(DEBUG) << "PixelFitTracks::Exec() EVENT " << fTNofEvents << " with " << fNTracks << " TRACKS" << FairLogger::endl;

  Double_t hitXPos[3];
  Double_t hitYPos[3];
  Double_t hitZPos[3];

  for ( Int_t itrack = 0 ; itrack < fNTracks ; itrack++ ) {
    PixelTrack* curTrack = static_cast<PixelTrack*>(fTracks->At(itrack));

    for ( Int_t ihit = 0 ; ihit < curTrack->GetNofHits() ; ihit++ ) {
      PixelHit* curHit = static_cast<PixelHit*>(fHits->At(curTrack->GetHitIndex(ihit)));
      
      //      LOG(INFO) << " HIT[" << curTrack->GetHitIndex(ihit) << "] = ( " << curHit->GetX() << " , " << curHit->GetY() << " , " << curHit->GetZ() << " )" << FairLogger::endl;
      hitXPos[ihit] = curHit->GetX();
      hitYPos[ihit] = curHit->GetY();
      hitZPos[ihit] = curHit->GetZ();
    }

    Double_t valX0 = 0., errX0 = 0., valAX = 0., errAX = 0.;
    Double_t valY0 = 0., errY0 = 0., valAY = 0., errAY = 0.;
    
    LinearRegression(curTrack->GetNofHits(),hitZPos,hitXPos,valX0,errX0,valAX,errAX);
    LinearRegression(curTrack->GetNofHits(),hitZPos,hitYPos,valY0,errY0,valAY,errAY);
    
    PixelTrack* fitTrack = new ((*fFitTracks)[fNFitTracks]) PixelTrack(valX0,valAX,valY0,valAY,
								       errX0,errAX,errY0,errAY);
    for ( Int_t ihit = 0 ; ihit < curTrack->GetNofHits() ; ihit++ ) {
      fitTrack->AddHitIndex(curTrack->GetHitIndex(ihit));
    }

    fNFitTracks += 1;

    LOG(DEBUG) << "Track params:  "
	       << " AX = " << curTrack->GetAX() << " += " << curTrack->GetAXErr() 
	       << " X0 = " << curTrack->GetX0() << " += " << curTrack->GetX0Err() << FairLogger::endl
	       << "                         "
	       << " AY = " << curTrack->GetAY() << " += " << curTrack->GetAYErr() 
	       << " Y0 = " << curTrack->GetY0() << " += " << curTrack->GetY0Err() << FairLogger::endl;
    LOG(DEBUG) << "Fitted params: " 
	       << " AX = " << valAX << " += " << errAX
	       << " X0 = " << valX0 << " += " << errX0 << FairLogger::endl
	       << "                         "
	       << " AY = " << valAY << " += " << errAY 
	       << " Y0 = " << valY0 << " += " << errY0 << FairLogger::endl;
  }

  fTNofEvents    += 1;
  fTNofTracks    += fNTracks;
  fTNofFitTracks += fNFitTracks;
}
// -------------------------------------------------------------------------

// -----   Private method LinearRegression   -------------------------------
Double_t PixelFitTracks::LinearRegression(Int_t nval, Double_t xval[], Double_t yval[], 
					  Double_t& valA0, Double_t& errA0,
					  Double_t& valA1, Double_t& errA1 ) {
  Double_t valN  = static_cast<Double_t>(nval);
  Double_t sumXY = 0.;
  Double_t sumX  = 0.;
  Double_t sumY  = 0.;
  Double_t sumXX = 0.;
  for ( Int_t ival = 0 ; ival < nval ; ival++ ) {
    sumXY += xval[ival]*yval[ival];
    sumX  += xval[ival];
    sumY  += yval[ival];
    sumXX += xval[ival]*xval[ival];
  }
  valA1  = (valN*sumXY-sumX*sumY)/(valN*sumXX-sumX*sumX);
  valA0  = (sumY-valA1*sumX)/valN;
  Double_t sumEE = 0.;
  for ( Int_t ival = 0 ; ival < nval ; ival++ ) {
    sumEE += (yval[ival]-valA0-valA1*xval[ival])*(yval[ival]-valA0-valA1*xval[ival]);
  }
  Double_t valS = TMath::Sqrt(sumEE/(valN-2.));
  errA1 = valS*TMath::Sqrt(valN/(valN*sumXX-sumX*sumX));
  errA0 = valS*TMath::Sqrt(sumXX/(valN*sumXX-sumX*sumX));
  // cout << "A0 = " << valA0 << " +- " << errA0 << " / A1 = " << valA1 << " +- " << errA1 << " / S = " << valS << endl;
  return valS;
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void PixelFitTracks::SetParContainers() {
  
  // Get run and runtime database
  FairRun* run = FairRun::Instance();
  if ( ! run ) Fatal("SetParContainers", "No analysis run");

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) Fatal("SetParContainers", "No runtime database");

  // Get GEM digitisation parameter container
  fDigiPar = static_cast<PixelDigiPar*>(db->getContainer("PixelDigiParameters"));

}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelFitTracks::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) Fatal("Init", "No FairRootManager");

  fHits =  static_cast<TClonesArray*>(ioman->GetObject("PixelHits"));
  if ( !fHits ) 
    LOG(WARNING) << "PixelFitTracks::Init() No input PixelHit array!" << FairLogger::endl;
  fTracks =  static_cast<TClonesArray*>(ioman->GetObject("PixelTracks"));
  if ( !fTracks ) 
    LOG(WARNING) << "PixelFitTracks::Init() No input PixelTrack array!" << FairLogger::endl;
  
  // Register output array PixelHit
  fFitTracks = new TClonesArray("PixelTrack",10000);
  ioman->Register("PixelFitTracks", "Pixel", fFitTracks, kTRUE);

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelFitTracks::ReInit() {

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelFitTracks::Reset() {
  fNFitTracks = fNTracks = fNHits = 0;
  if ( fFitTracks ) fFitTracks->Delete();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelFitTracks::Finish() {
  if ( fFitTracks ) fFitTracks->Delete();

  LOG(INFO) << "-------------------- " << fName.Data() << " : Summary ------------------------" << FairLogger::endl;
  LOG(INFO) << " Events:        " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << " Tracks:        " << fTNofTracks   << "    ( " << static_cast<Double_t>(fTNofTracks  )/(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << " Fitted Tracks: " << fTNofFitTracks << "    ( " << static_cast<Double_t>(fTNofFitTracks)/(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << "---------------------------------------------------------------------" << FairLogger::endl; 
}
// -------------------------------------------------------------------------



ClassImp(PixelFitTracks)

