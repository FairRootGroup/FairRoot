/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFindHits.cxx
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFindHits.h"

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

#include "PixelDigi.h"
#include "PixelHit.h"
#include "PixelDigiPar.h"

#include <map>

 // 
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "FairGeoParSet.h"

using std::pair;
using std::map;



// -----   Default constructor   ------------------------------------------
PixelFindHits::PixelFindHits()
  : PixelFindHits("Pixel Hit Finder", 0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PixelFindHits::PixelFindHits(Int_t iVerbose) 
  : PixelFindHits("Pixel Hit Finder", iVerbose)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name   -----------------------------------------
PixelFindHits::PixelFindHits(const char* name, Int_t iVerbose) 
  : FairTask(name, iVerbose)
  , fDigiPar(NULL)
  , fGeoParSet(NULL)
  , fDigis(NULL)
  , fHits(NULL)
  , fNDigis(0)
  , fNHits(0)
  , fTNofEvents(0)
  , fTNofDigis(0) 
  , fTNofHits(0)
  , fFeCols(0)
  , fFeRows(0)
  , fMaxFEperCol(0)
  , fPitchX(0.)
  , fPitchY(0.)
{
  LOG(info) << "Created PixelFindHits.";
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelFindHits::~PixelFindHits() { 
  Reset();
  delete fDigiPar;
  if ( fHits ) {
    fHits->Delete();
    delete fHits;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelFindHits::Exec(Option_t* /*opt*/) {
  Reset();

  LOG(debug) << "PixelFindHits::Exec() EVENT " << fTNofEvents;

  fTNofEvents++;

  fNDigis = fDigis->GetEntriesFast();
  fTNofDigis+= fNDigis;

  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) {
    PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

    Int_t detId = currentDigi->GetDetectorID();    
    TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);
    
    gGeoManager->cd(nodeName.Data());
    TGeoNode* curNode = gGeoManager->GetCurrentNode();

//    TGeoMatrix* matrix = curNode->GetMatrix();

    TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
    TGeoBBox* actBox = static_cast<TGeoBBox*>(actVolume->GetShape());

    Int_t feId = currentDigi->GetFeID();
    Int_t col  = currentDigi->GetCol();
    Int_t row  = currentDigi->GetRow();

    Double_t locPosCalc[3];
    locPosCalc[0] = ( ((feId-1)/fMaxFEperCol)*fFeCols + col + 0.5 )*fPitchX;
    locPosCalc[1] = ( ((feId-1)%fMaxFEperCol)*fFeRows + row + 0.5 )*fPitchY;
    locPosCalc[2] = 0.;
    
    locPosCalc[0] -= actBox->GetDX();
    locPosCalc[1] -= actBox->GetDY();

    Double_t globPos[3];

    curNode->LocalToMaster(locPosCalc,globPos);

    LOG(debug) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1];
    LOG(debug) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2];

    TVector3 pos   (globPos[0],globPos[1],globPos[2]);
    TVector3 posErr(fPitchX/TMath::Sqrt(12.),fPitchY/TMath::Sqrt(12.),actBox->GetDZ());

    new ((*fHits)[fNHits]) PixelHit(detId,currentDigi->GetIndex(),pos,posErr);

    fNHits++;
  }

  fTNofHits += fNHits;
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void PixelFindHits::SetParContainers() {
  
  // Get run and runtime database
  FairRun* run = FairRun::Instance();
  if ( ! run ) LOG(fatal) << "No analysis run";

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) LOG(fatal) << "No runtime database";

  // Get GEM digitisation parameter container
  fDigiPar = static_cast<PixelDigiPar*>(db->getContainer("PixelDigiParameters"));

}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void PixelFindHits::GetParList(TList* tempList) {
  fDigiPar = new PixelDigiPar("PixelDigiParameters");
  tempList->Add(fDigiPar);
  
  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PixelFindHits::InitMQ(TList* tempList) {
  LOG(info) << "********************************************** PixelFindHits::InitMQ()";
  fDigiPar = (PixelDigiPar*)tempList->FindObject("PixelDigiParameters");

  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();

  LOG(info) << ">> fFeCols      = " << fFeCols;
  LOG(info) << ">> fFeRows      = " << fFeRows;
  LOG(info) << ">> fMaxFEperCol = " << fMaxFEperCol;
  LOG(info) << ">> fPitchX      = " << fPitchX;
  LOG(info) << ">> fPitchY      = " << fPitchY;

  fHits = new TClonesArray("PixelHit",10000);

  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PixelFindHits::ExecMQ(TList* inputList,TList* outputList) {
  //  LOG(info) << "********************************************** PixelFindHits::ExecMQ(" << inputList->GetName() << "," << outputList->GetName() << "), Event " << fTNofEvents;
  //  LOG(info) << "********************************************** PixelFindHits::ExecMQ(), Event " << fTNofEvents;
  //  LOG(info) << "h" << FairLogger::flush;
  fDigis = (TClonesArray*) inputList->FindObject("PixelDigis");
  outputList->Add(fHits);
  Exec("");
  return;
}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelFindHits::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) LOG(fatal) << "No FairRootManager";
  fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

  if ( !fDigis ) 
    LOG(warn) << "PixelFindHits::Init() No input PixelDigis array!";

  // Register output array PixelHit
  fHits = new TClonesArray("PixelHit",10000);
  ioman->Register("PixelHits", "Pixel", fHits, kTRUE);

  LOG(info) << "-I- " << fName.Data() << "::Init(). Initialization succesfull.";

  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();

  LOG(info) << "PixelFindHits::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY << "cm";
  

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelFindHits::ReInit() {

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelFindHits::Reset() {
  fNDigis = fNHits = 0;
  if ( fHits ) fHits->Clear();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelFindHits::Finish() {
  if ( fHits ) fHits->Delete();

  LOG(info) << "-------------------- " << fName.Data() << " : Summary ------------------------";
  LOG(info) << " Events:        " << fTNofEvents;
  LOG(info) << " Digis:         " << fTNofDigis  << "    ( " << static_cast<Double_t>(fTNofDigis) /(static_cast<Double_t>(fTNofEvents)) << " per event )";
  LOG(info) << " Hits:          " << fTNofHits   << "    ( " << static_cast<Double_t>(fTNofHits  )/(static_cast<Double_t>(fTNofEvents)) << " per event )";
  LOG(info) << "---------------------------------------------------------------------";
}
// -------------------------------------------------------------------------

ClassImp(PixelFindHits)

