/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 16.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelDigitize.h"

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
#include "PixelPoint.h"
#include "PixelDigiPar.h"

#include <map>

using std::pair;
using std::map;



// -----   Default constructor   ------------------------------------------
PixelDigitize::PixelDigitize()
  : PixelDigitize("Pixel Digitizer", 0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PixelDigitize::PixelDigitize(Int_t iVerbose) 
  : PixelDigitize("Pixel Digitizer", iVerbose)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name   -----------------------------------------
PixelDigitize::PixelDigitize(const char* name, Int_t iVerbose) 
  : FairTask(name, iVerbose)
  , fDigiPar(NULL)
  , fPoints(NULL)
  , fDigis(NULL)
  , fNPoints(0)
  , fNDigis(0)
  , fTNofEvents(0)
  , fTNofPoints(0)
  , fTNofDigis(0) 
  , fFeCols(0)
  , fFeRows(0)
  , fMaxFEperCol(0)
  , fPitchX(0.)
  , fPitchY(0.)
{
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelDigitize::~PixelDigitize() { 
  Reset();
  if ( fDigiPar)   delete fDigiPar;
  if ( fDigis ) {
    fDigis->Delete();
    delete fDigis;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelDigitize::Exec(Option_t* opt) {

  Reset();

  LOG(DEBUG) << "PixelDigitize::Exec() EVENT " << fTNofEvents << FairLogger::endl;

  fTNofEvents++;

  fNPoints = fPoints->GetEntriesFast();
  fTNofPoints+= fNPoints;

  for ( Int_t iPoint = 0 ; iPoint < fNPoints ; iPoint++ ) {
    PixelPoint* currentPixelPoint = (PixelPoint*)fPoints->At(iPoint);

    Double_t posIn[3] = {currentPixelPoint->GetX(),
			 currentPixelPoint->GetY(),
 			 currentPixelPoint->GetZ()};

    Int_t detId = currentPixelPoint->GetDetectorID();    
    TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);


    gGeoManager->cd(nodeName.Data());
    TGeoNode* curNode = gGeoManager->GetCurrentNode();

    if ( !curNode ) LOG(WARNING) << "PixelDigitize::Exec() node \"" << nodeName.Data() << "\" unknown!" << FairLogger::endl;

    Double_t locPosIn[4];

    curNode->MasterToLocal(posIn,locPosIn);

    // The local coordinate system has the origin set to the center of the volume.
    // To calculate the pixel number, it is necessary to move the origin to the bottom left corner.
    TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
    TGeoBBox* actBox = (TGeoBBox*)(actVolume->GetShape());
    Double_t sensorWidth  = 2.*actBox->GetDX();
    Double_t sensorHeight = 2.*actBox->GetDY();
    locPosIn[0] += actBox->GetDX();
    locPosIn[1] += actBox->GetDY();

    LOG(DEBUG) << "GLOB PNT " << detId << " POSITION:  " << posIn[0] << " / " << posIn[1] << " / " << posIn[2] << FairLogger::endl;
    LOG(DEBUG) << "POINT ON " << detId << " POSITION:  " << locPosIn[0] << " / " << locPosIn[1] << FairLogger::endl;

    Int_t col  = (Int_t)(locPosIn[0]/fPitchX);
    Int_t ocol = col;
    Int_t row  = (Int_t)(locPosIn[1]/fPitchY);
    Int_t orow = row;
    Int_t feCol = col/fFeCols;
    col = col%fFeCols;
    Int_t feRow = row/fFeRows;
    row = row%fFeRows;
    Int_t feId = 1+feCol*fMaxFEperCol+feRow;

    LOG(DEBUG) << "COL = " << feCol << " FE + " << col << " ( " << ocol << " ) /// " 
	       << "ROW = " << feRow << " FE + " << row << " ( " << orow << " ) /// " 
	       << " /// PIXEL = " << feId << FairLogger::endl;

    ActivatePixel(iPoint,detId,feId,col,row,1.,0.);
  }

  fTNofDigis += fNDigis;
}
// -------------------------------------------------------------------------

// -----   Private method ActivatePixel   ----------------------------------
void PixelDigitize::ActivatePixel(Int_t index, Int_t detId, Int_t feId, Int_t col, Int_t row, Double_t charge, Double_t timestamp) {

  Bool_t pixelAlreadyFired = kFALSE;
  PixelDigi* tempPixel = NULL;
  for ( Int_t ipixel = 0 ; ipixel < fNDigis ; ipixel++ ) {  
    tempPixel = (PixelDigi*)fDigis->At(ipixel);
    if ( tempPixel->GetDetectorID() == detId &&
   	 tempPixel->GetFeID()       == feId  &&
   	 tempPixel->GetCol()        == col   &&
   	 tempPixel->GetRow()        == row ) {
      pixelAlreadyFired = kTRUE;
      tempPixel->SetCharge(tempPixel->GetCharge()+charge);
    }
  }
  // TODO: order the PixelDigi in the output array by station, not by track...
  if ( !pixelAlreadyFired ) {
    new ((*fDigis)[fNDigis]) PixelDigi(index,detId,feId,col,row,charge,timestamp);
    fNDigis++;
  }
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void PixelDigitize::SetParContainers() {
  
  // Get run and runtime database
  FairRun* run = FairRun::Instance();
  if ( ! run ) Fatal("SetParContainers", "No analysis run");

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) Fatal("SetParContainers", "No runtime database");

  // Get GEM digitisation parameter container
  fDigiPar = (PixelDigiPar*)(db->getContainer("PixelDigiParameters"));

}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelDigitize::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) Fatal("Init", "No FairRootManager");
  fPoints = (TClonesArray*) ioman->GetObject("PixelPoint");

  // Register output array StsDigi
  fDigis = new TClonesArray("PixelDigi",10000);
  ioman->Register("PixelDigis", "Pixel", fDigis, kTRUE);

  LOG(INFO) << "-I- " << fName.Data() << "::Init(). Initialization succesfull." << FairLogger::endl;

  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();

  LOG(INFO) << "PixelDigitize::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY << "cm" << FairLogger::endl;
  

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelDigitize::ReInit() {

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelDigitize::Reset() {
  fNPoints = fNDigis = 0;
  if ( fDigis ) fDigis->Delete();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelDigitize::Finish() {
  if ( fDigis ) fDigis->Delete();

  LOG(INFO) << "-------------------- " << fName.Data() << " : Summary ------------------------" << FairLogger::endl;
  LOG(INFO) << " Events:        " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << " MC Points:     " << fTNofPoints << "    ( " << (Double_t)fTNofPoints/((Double_t)fTNofEvents) << " per event )" << FairLogger::endl;
  LOG(INFO) << " Digis:         " << fTNofDigis  << "    ( " << (Double_t)fTNofDigis /((Double_t)fTNofEvents) << " per event )" << FairLogger::endl;
  LOG(INFO) << "---------------------------------------------------------------------" << FairLogger::endl; 
}
// -------------------------------------------------------------------------



ClassImp(PixelDigitize)

