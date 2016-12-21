/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelAltFindHits.cxx
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelAltFindHits.h"

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
PixelAltFindHits::PixelAltFindHits()
  : PixelAltFindHits("Pixel Hit Finder", 0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PixelAltFindHits::PixelAltFindHits(Int_t iVerbose) 
  : PixelAltFindHits("Pixel Hit Finder", iVerbose)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name   -----------------------------------------
PixelAltFindHits::PixelAltFindHits(const char* name, Int_t iVerbose) 
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
  LOG(INFO) << "Created PixelAltFindHits." << FairLogger::endl;
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelAltFindHits::~PixelAltFindHits() { 
  Reset();
  if ( fDigiPar)   delete fDigiPar;
  if ( fHits ) {
    fHits->Delete();
    delete fHits;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelAltFindHits::Exec(Option_t* /*opt*/) {
  Reset();

  LOG(DEBUG) << "PixelAltFindHits::Exec() EVENT " << fTNofEvents << FairLogger::endl;

  fTNofEvents++;

  fNDigis = fDigis->GetEntriesFast();
  fTNofDigis+= fNDigis;

  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) {
    PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

    Int_t detId     = currentDigi->GetDetectorID();
    
    Double_t posX, posY, posZ;
    Double_t errX, errY, errZ;
    Int_t hitIndex = FindHit(detId,currentDigi->GetFeID(),currentDigi->GetCol(),currentDigi->GetRow(),currentDigi->GetIndex(),
			     posX,posY,posZ,errX,errY,errZ);

    TVector3 pos   (posX,posY,posZ);
    TVector3 posErr(errX,errY,errZ);

    if ( hitIndex == -666 ) continue; // hit not found

    new ((*fHits)[fNHits]) PixelHit(detId,hitIndex,pos,posErr);
    
    fNHits++;
  }
  
  fTNofHits += fNHits;
}
// -------------------------------------------------------------------------

// -----   Private method FindHit   ----------------------------------------
// should return -666 if hit not found
Int_t PixelAltFindHits::FindHit(Int_t detId, Int_t feId, Int_t col, Int_t row, Int_t index,
			     Double_t& posX, Double_t& posY, Double_t& posZ, 
			     Double_t& errX, Double_t& errY, Double_t& errZ) {
  TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);
  
  gGeoManager->cd(nodeName.Data());
  TGeoNode*   curNode   = gGeoManager->GetCurrentNode();
  TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
  TGeoBBox* actBox = static_cast<TGeoBBox*>(actVolume->GetShape());

  Double_t locPosCalc[3];
  locPosCalc[0] = ( ((feId-1)/fMaxFEperCol)*fFeCols + col + 0.5 )*fPitchX;
  locPosCalc[1] = ( ((feId-1)%fMaxFEperCol)*fFeRows + row + 0.5 )*fPitchY;
  locPosCalc[2] = 0.;
  
  locPosCalc[0] -= actBox->GetDX();
  locPosCalc[1] -= actBox->GetDY();
  
  Double_t globPos[3];
  
  curNode->LocalToMaster(locPosCalc,globPos);
  
  LOG(DEBUG) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1] << FairLogger::endl;
  LOG(DEBUG) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2] << FairLogger::endl;

  posX = globPos[0];
  posY = globPos[1];
  posZ = globPos[2];
  errX = fPitchX/TMath::Sqrt(12.);
  errY = fPitchY/TMath::Sqrt(12.);
  errZ = actBox->GetDZ();

// should return -666 if hit not found
  return index;
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void PixelAltFindHits::SetParContainers() {
  
  // Get run and runtime database
  FairRun* run = FairRun::Instance();
  if ( ! run ) LOG(FATAL) << "No analysis run" << FairLogger::endl;

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) LOG(FATAL) << "No runtime database" << FairLogger::endl;

  // Get GEM digitisation parameter container
  fDigiPar = static_cast<PixelDigiPar*>(db->getContainer("PixelDigiParameters"));

}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void PixelAltFindHits::GetParList(TList* tempList) {
  fDigiPar = new PixelDigiPar("PixelDigiParameters");
  tempList->Add(fDigiPar);
  
  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PixelAltFindHits::InitMQ(TList* tempList) {
  LOG(INFO) << "********************************************** PixelAltFindHits::InitMQ()" << FairLogger::endl;
  fDigiPar = (PixelDigiPar*)tempList->FindObject("PixelDigiParameters");

  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();

  LOG(INFO) << ">> fFeCols      = " << fFeCols << FairLogger::endl;
  LOG(INFO) << ">> fFeRows      = " << fFeRows << FairLogger::endl;
  LOG(INFO) << ">> fMaxFEperCol = " << fMaxFEperCol << FairLogger::endl;
  LOG(INFO) << ">> fPitchX      = " << fPitchX << FairLogger::endl;
  LOG(INFO) << ">> fPitchY      = " << fPitchY << FairLogger::endl;

  fHits = new TClonesArray("PixelHit",10000);

  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PixelAltFindHits::ExecMQ(TList* inputList,TList* outputList) {
  //  LOG(INFO) << "********************************************** PixelAltFindHits::ExecMQ(" << inputList->GetName() << "," << outputList->GetName() << "), Event " << fTNofEvents << FairLogger::endl;
  //  LOG(INFO) << "********************************************** PixelAltFindHits::ExecMQ(), Event " << fTNofEvents << FairLogger::endl;
  //  LOG(INFO) << "h" << FairLogger::flush;
  fDigis = (TClonesArray*) inputList->FindObject("PixelDigis");
  outputList->Add(fHits);
  Exec("");
  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void PixelAltFindHits::ExecMQ(PixelPayload::Digi *digiPalVector,
                              int                 nofDigis,
                              PixelPayload::Hit  *hitPalVector,
                              int                &nofHits) {
  for ( int idigi = 0 ; idigi < nofDigis ; idigi++ ) {
    FindHit(digiPalVector[idigi].fDetectorID,
	    digiPalVector[idigi].fFeID,
	    digiPalVector[idigi].fCol,
	    digiPalVector[idigi].fRow,
	    idigi,
	    hitPalVector[idigi].posX,
	    hitPalVector[idigi].posY,
	    hitPalVector[idigi].posZ,
	    hitPalVector[idigi].dposX,
	    hitPalVector[idigi].dposY,
	    hitPalVector[idigi].dposZ);
    hitPalVector[idigi].fDetectorID = digiPalVector[idigi].fDetectorID;
    nofHits++;
  }
  return;
}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelAltFindHits::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) LOG(FATAL) << "No FairRootManager" << FairLogger::endl;
  fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

  if ( !fDigis ) 
    LOG(WARNING) << "PixelAltFindHits::Init() No input PixelDigis array!" << FairLogger::endl;

  // Register output array PixelHit
  fHits = new TClonesArray("PixelHit",10000);
  ioman->Register("PixelHits", "Pixel", fHits, kTRUE);

  LOG(INFO) << "-I- " << fName.Data() << "::Init(). Initialization succesfull." << FairLogger::endl;

  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();

  LOG(INFO) << "PixelAltFindHits::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY << "cm" << FairLogger::endl;
  

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelAltFindHits::ReInit() {

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelAltFindHits::Reset() {
  fNDigis = fNHits = 0;
  if ( fHits ) fHits->Clear();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelAltFindHits::Finish() {
  if ( fHits ) fHits->Delete();

  LOG(INFO) << "-------------------- " << fName.Data() << " : Summary ------------------------" << FairLogger::endl;
  LOG(INFO) << " Events:        " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << " Digis:         " << fTNofDigis  << "    ( " << static_cast<Double_t>(fTNofDigis) /(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << " Hits:          " << fTNofHits   << "    ( " << static_cast<Double_t>(fTNofHits  )/(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << "---------------------------------------------------------------------" << FairLogger::endl; 
}
// -------------------------------------------------------------------------

ClassImp(PixelAltFindHits)

