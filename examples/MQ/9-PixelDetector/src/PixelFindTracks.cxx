/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFindTracks.cxx
 *
 *  Created on: 23.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFindTracks.h"

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

#include "TH2F.h"

#include "PixelDigiPar.h"
#include "PixelHit.h"
#include "PixelTrack.h"

#include <map>

using std::pair;
using std::map;

// -----   Default constructor   ------------------------------------------
PixelFindTracks::PixelFindTracks()
  : PixelFindTracks("Pixel Track Finder", 0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PixelFindTracks::PixelFindTracks(Int_t iVerbose) 
  : PixelFindTracks("Pixel Track Finder", iVerbose)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name   -----------------------------------------
PixelFindTracks::PixelFindTracks(const char* name, Int_t iVerbose) 
  : FairTask(name, iVerbose)
  , fDigiPar(NULL)
  , fHits(NULL)
  , fTracks(NULL)
  , fTNofEvents(0)
  , fNHits(0)
  , fTNofHits(0)
  , fNTracks(0)
  , fTNofTracks(0)
  , fhDist2D(NULL)
{
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelFindTracks::~PixelFindTracks() { 
  Reset();
  if ( fDigiPar)   delete fDigiPar;
  if ( fTracks ) {
    fTracks->Delete();
    delete fTracks;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelFindTracks::Exec(Option_t* /*opt*/) {

  Reset();

  fNHits = fHits->GetEntriesFast();

  LOG(DEBUG) << "PixelFindTracks::Exec() EVENT " << fTNofEvents << " with " << fNHits << " HITS" << FairLogger::endl;

  PixelHit* curHit1;
  PixelHit* curHit2;
  PixelHit* curHit3;

  Double_t parX0 = 0.;
  Double_t parY0 = 0.;
  Double_t parAX = 0.;
  Double_t parAY = 0.;
  Double_t expX  = 0.;
  Double_t expY  = 0.;

  for ( Int_t ihit1 = 0 ; ihit1 < fNHits ; ihit1++ ) {
    curHit1 = static_cast<PixelHit*>(fHits->At(ihit1));
    LOG(DEBUG) << "hit1 at " << curHit1->GetX() << " , " << curHit1->GetY() << " , " << curHit1->GetZ() << " / " << curHit1->GetDetectorID() << FairLogger::endl;
    if ( (curHit1->GetDetectorID())/256 != 1 ) continue;
    for ( Int_t ihit2 = 0 ; ihit2 < fNHits ; ihit2++ ) {
      curHit2 = static_cast<PixelHit*>(fHits->At(ihit2));
      LOG(DEBUG) << "hit2 at " << curHit2->GetX() << " , " << curHit2->GetY() << " , " << curHit2->GetZ() << " / " << curHit2->GetDetectorID() << FairLogger::endl;
      if ( (curHit2->GetDetectorID())/256 != 2 ) continue;
      
      parAX = (curHit2->GetX()-curHit1->GetX())/(curHit2->GetZ()-curHit1->GetZ());
      parAY = (curHit2->GetY()-curHit1->GetY())/(curHit2->GetZ()-curHit1->GetZ());
      parX0 = curHit1->GetX()-parAX*curHit1->GetZ();
      parY0 = curHit1->GetY()-parAY*curHit1->GetZ();
      
      for ( Int_t ihit3 = 0 ; ihit3 < fNHits ; ihit3++ ) {
	curHit3 = static_cast<PixelHit*>(fHits->At(ihit3));
	LOG(DEBUG) << "hit3 at " << curHit3->GetX() << " , " << curHit3->GetY() << " , " << curHit3->GetZ() << " / " << curHit3->GetDetectorID() << FairLogger::endl;
	if ( (curHit3->GetDetectorID())/256 != 3 ) continue;
	expX = parX0+parAX*curHit3->GetZ();
	expY = parY0+parAY*curHit3->GetZ();

	fhDist2D->Fill(expX-curHit3->GetX(),expY-curHit3->GetY());

	if ( TMath::Abs(expX-curHit3->GetX()) < 0.03 &&
	     TMath::Abs(expY-curHit3->GetY()) < 0.03 ) {
	  LOG(DEBUG) << "should create track..." << FairLogger::endl;
	  PixelTrack* tempTrack = new ((*fTracks)[fNTracks]) PixelTrack(parX0,parAX,parY0,parAY,0.,0.,0.,0.);
	  tempTrack->AddHitIndex(ihit1);
	  tempTrack->AddHitIndex(ihit2);
	  tempTrack->AddHitIndex(ihit3);
	  LOG(DEBUG) << "--> " << fNTracks << FairLogger::endl;
	  fNTracks++;
	}
	// LOG(DEBUG) << ">>>>>> " << curHit3->GetX() << "  /  " << curHit3->GetY() << FairLogger::endl;
	// LOG(DEBUG) << "       " << expX << "  /  " << expY << FairLogger::endl;

      }
    }
  }

  fTNofEvents += 1;
  fTNofHits   += fNHits;
  fTNofTracks += fNTracks;
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void PixelFindTracks::SetParContainers() {
  
  // Get run and runtime database
  FairRun* run = FairRun::Instance();
  if ( ! run ) Fatal("SetParContainers", "No analysis run");

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) Fatal("SetParContainers", "No runtime database");

  // Get GEM digitisation parameter container
  fDigiPar = static_cast<PixelDigiPar*>(db->getContainer("PixelDigiParameters"));

}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void PixelFindTracks::GetParList(TList* tempList) {
  fDigiPar = new PixelDigiPar("PixelDigiParameters");
  tempList->Add(fDigiPar);
  
  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PixelFindTracks::InitMQ(TList* tempList) {
  LOG(INFO) << "********************************************** PixelFindTracks::InitMQ()" << FairLogger::endl;
  fDigiPar = (PixelDigiPar*)tempList->FindObject("PixelDigiParameters");

  fTracks = new TClonesArray("PixelTrack",10000);
  fhDist2D = new TH2F("fhDist2D","Distance between hit and expected track",400,-1.,1.,400,-1.,1.);

  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PixelFindTracks::ExecMQ(TList* inputList,TList* outputList) {
  //  LOG(INFO) << "********************************************** PixelFindTracks::ExecMQ(" << inputList->GetName() << "," << outputList->GetName() << "), Event " << fTNofEvents << FairLogger::endl;
  //  LOG(INFO) << "********************************************** PixelFindTracks::ExecMQ(), Event " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << "t" << FairLogger::flush;
  fHits = (TClonesArray*) inputList->FindObject("PixelHits");
  outputList->Add(fTracks);
  Exec("");
  return;
}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelFindTracks::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) Fatal("Init", "No FairRootManager");
  fHits = static_cast<TClonesArray*>(ioman->GetObject("PixelHits"));

  if ( !fHits ) 
    LOG(WARNING) << "PixelFindTracks::Init() No input PixelHit array!" << FairLogger::endl;

  // Register output array PixelHit
  fTracks = new TClonesArray("PixelTrack",10000);
  ioman->Register("PixelTracks", "Pixel", fTracks, kTRUE);

  fhDist2D = new TH2F("fhDist2D","Distance between hit and expected track",400,-1.,1.,400,-1.,1.);

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelFindTracks::ReInit() {

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelFindTracks::Reset() {
  fNTracks = fNHits = 0;
  if ( fTracks ) fTracks->Delete();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelFindTracks::Finish() {
  if ( fTracks ) fTracks->Delete();

  fhDist2D->Draw("colz");

  LOG(INFO) << "-------------------- " << fName.Data() << " : Summary ------------------------" << FairLogger::endl;
  LOG(INFO) << " Events:        " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << " Hits:          " << fTNofHits   << "    ( " << static_cast<Double_t>(fTNofHits  )/(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << " Tracks:        " << fTNofTracks << "    ( " << static_cast<Double_t>(fTNofTracks)/(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << "---------------------------------------------------------------------" << FairLogger::endl; 
}
// -------------------------------------------------------------------------



ClassImp(PixelFindTracks)

