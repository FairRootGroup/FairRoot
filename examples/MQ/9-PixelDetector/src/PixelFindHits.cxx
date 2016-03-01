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
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelFindHits::~PixelFindHits() { 
  Reset();
  if ( fDigiPar)   delete fDigiPar;
  if ( fHits ) {
    fHits->Delete();
    delete fHits;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelFindHits::Exec(Option_t* opt) {

  Reset();

  LOG(INFO) << "PixelFindHits::Exec() EVENT " << fTNofEvents << FairLogger::endl;

  fTNofEvents++;

  fNDigis = fDigis->GetEntriesFast();
  fTNofDigis+= fNDigis;

  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) {
    PixelDigi* currentDigi = (PixelDigi*)fDigis->At(iDigi);

    Int_t detId = currentDigi->GetDetectorID();    
    TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);
    
    gGeoManager->cd(nodeName.Data());
    TGeoNode* curNode = gGeoManager->GetCurrentNode();

    TGeoMatrix* matrix = curNode->GetMatrix();

    TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
    TGeoBBox* actBox = (TGeoBBox*)(actVolume->GetShape());

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

    LOG(INFO) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1] << FairLogger::endl;
    LOG(INFO) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2] << FairLogger::endl;

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
  if ( ! run ) Fatal("SetParContainers", "No analysis run");

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) Fatal("SetParContainers", "No runtime database");

  // Get GEM digitisation parameter container
  fDigiPar = (PixelDigiPar*)(db->getContainer("PixelDigiParameters"));

}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelFindHits::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) Fatal("Init", "No FairRootManager");
  fDigis = (TClonesArray*) ioman->GetObject("PixelDigis");

  if ( !fDigis ) 
    LOG(WARNING) << "PixelFindHits::Init() No input PixelDigis array!" << FairLogger::endl;

  // Register output array PixelHit
  fHits = new TClonesArray("PixelHit",10000);
  ioman->Register("PixelHit", "Pixel", fHits, kTRUE);

  LOG(INFO) << "-I- " << fName.Data() << "::Init(). Initialization succesfull." << FairLogger::endl;

  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();

  LOG(INFO) << "PixelFindHits::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY << "cm" << FairLogger::endl;
  

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
  if ( fHits ) fHits->Delete();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelFindHits::Finish() {
  if ( fDigis ) fDigis->Delete();

  LOG(INFO) << "-------------------- " << fName.Data() << " : Summary ------------------------" << FairLogger::endl;
  LOG(INFO) << " Events:        " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << " Digis:         " << fTNofDigis  << "    ( " << (Double_t)fTNofDigis /((Double_t)fTNofEvents) << " per event )" << FairLogger::endl;
  LOG(INFO) << " Hits:          " << fTNofHits   << "    ( " << (Double_t)fTNofHits  /((Double_t)fTNofEvents) << " per event )" << FairLogger::endl;
  LOG(INFO) << "---------------------------------------------------------------------" << FairLogger::endl; 
}
// -------------------------------------------------------------------------



// MQ

void PixelFindHits::InitMQ(const std::string& root_file, const std::string& ascii_file) 
{
  fHits = new TClonesArray("PixelHit",10000);
//*
  // init parameters below
  std::cout << "creating fRtdb" << std::endl;
  FairRuntimeDb* fRtdb = FairRuntimeDb::instance();

  std::cout << "setting root input file" << std::endl;
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  //parInput1->open("pixel_TGeant3.params.root");
  parInput1->open(root_file.c_str());

  std::cout << "setting ascii input file" << std::endl;
  FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
  //parIo1->open("/Users/karabowi/fairroot/pixel9/FairRoot/examples/MQ/9-PixelDetector/param/pixel_digi.par","in");
  parIo1->open(ascii_file.c_str(),"in");

  fRtdb->setFirstInput(parInput1);
  fRtdb->setSecondInput(parIo1);

  std::cout << "get GeoParSet and BaseParSet" << std::endl;
  fRtdb->getContainer("FairGeoParSet");
  //  FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));

  //  if ( par ) cout << " already got par" << endl;

  //  fRtdb->print();

  //PixelDigiPar* fDigiPar = (PixelDigiPar*)(fRtdb->getContainer("PixelDigiParameters"));
  fGeoParSet = (FairGeoParSet*)(fRtdb->getContainer("FairGeoParSet"));
  fDigiPar = (PixelDigiPar*)(fRtdb->getContainer("PixelDigiParameters"));
  
  Int_t runId = 1456147577;
  std::cout << "trying to initContainers with runId = " << runId << std::endl;
  fRtdb->initContainers(runId);

  std::cout << "-> GREAT, for example xpitch = " << fDigiPar->GetXPitch() << std::endl;
  fFeCols = fDigiPar->GetFECols();
  fFeRows = fDigiPar->GetFERows();
  fMaxFEperCol = fDigiPar->GetMaxFEperCol();
  fPitchX = fDigiPar->GetXPitch();
  fPitchY = fDigiPar->GetYPitch();
// */

}

void PixelFindHits::UpdateParameter(PixelDigiPar* digipar, FairGeoParSet* geopar)
{
  fFeCols = digipar->GetFECols();
  fFeRows = digipar->GetFERows();
  fMaxFEperCol = digipar->GetMaxFEperCol();
  fPitchX = digipar->GetXPitch();
  fPitchY = digipar->GetYPitch();
  fGeoParSet=geopar;
}


TClonesArray* PixelFindHits::ExecMQ(TClonesArray* digis) 
{

  Reset();
  fDigis=digis;// RootDeserializer has ownership

  LOG(INFO) << "PixelFindHits::Exec() EVENT " << fTNofEvents << FairLogger::endl;

  fTNofEvents++;

  fNDigis = fDigis->GetEntriesFast();
  fTNofDigis+= fNDigis;
//*
  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) 
  {
    PixelDigi* currentDigi = (PixelDigi*)fDigis->At(iDigi);

    Int_t detId = currentDigi->GetDetectorID();    
    TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);

    fGeoParSet->GetGeometry()->cd(nodeName.Data());

    TGeoNode* curNode = fGeoParSet->GetGeometry()->GetCurrentNode();

    TGeoMatrix* matrix = curNode->GetMatrix();

    TGeoVolume* actVolume = fGeoParSet->GetGeometry()->GetCurrentVolume();
    TGeoBBox* actBox = (TGeoBBox*)(actVolume->GetShape());

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

    LOG(INFO) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1] << FairLogger::endl;
    LOG(INFO) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2] << FairLogger::endl;

    TVector3 pos   (globPos[0],globPos[1],globPos[2]);
    TVector3 posErr(fPitchX/TMath::Sqrt(12.),fPitchY/TMath::Sqrt(12.),actBox->GetDZ());

    new ((*fHits)[fNHits]) PixelHit(detId,currentDigi->GetIndex(),pos,posErr);

    fNHits++;
  }


  fTNofHits += fNHits;
  return fHits;
}



ClassImp(PixelFindHits)

