/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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
  LOG(INFO) << "Created PixelFindHits." << FairLogger::endl;
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
void PixelFindHits::Exec(Option_t* /*opt*/) {
  Reset();

  LOG(DEBUG) << "PixelFindHits::Exec() EVENT " << fTNofEvents << FairLogger::endl;

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

    LOG(DEBUG) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1] << FairLogger::endl;
    LOG(DEBUG) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2] << FairLogger::endl;

    TVector3 pos   (globPos[0],globPos[1],globPos[2]);
    TVector3 posErr(fPitchX/TMath::Sqrt(12.),fPitchY/TMath::Sqrt(12.),actBox->GetDZ());

    new ((*fHits)[fNHits]) PixelHit(detId,currentDigi->GetIndex(),pos,posErr);

    fNHits++;
  }

  fTNofHits += fNHits;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelFindHits::ExecMQ(Option_t* /*opt*/) {

  Reset();

  LOG(DEBUG) << "PixelFindHits::Exec() EVENT " << fTNofEvents << FairLogger::endl;

  fTNofEvents++;

  fNDigis = fDigis->GetEntriesFast();
  fTNofDigis+= fNDigis;

  TGeoHMatrix* rtMat[3][4];
  for ( Int_t istat = 0 ; istat < 3 ; istat++ ) {
    for ( Int_t isens = 0 ; isens < 4 ; isens++ ) {
      rtMat[istat][isens] = new TGeoHMatrix();
    }
    Double_t rotMat[9] = {1.,0.,0., 0.,1.,0., 0.,0.,1.};
    rtMat[istat][0]->SetRotation(rotMat);
    rotMat[0] =  0.;    rotMat[1] = -1.;    rotMat[3] =  1.;    rotMat[4] =  0.;
    rtMat[istat][1]->SetRotation(rotMat);
    rotMat[0] = -1.;    rotMat[1] =  0.;    rotMat[3] =  0.;    rotMat[4] = -1.;
    rtMat[istat][2]->SetRotation(rotMat);
    rotMat[0] =  0.;    rotMat[1] =  1.;    rotMat[3] = -1.;    rotMat[4] =  0.;
    rtMat[istat][3]->SetRotation(rotMat);
  }
  rtMat[0][0]->SetDx( 1.50); rtMat[0][0]->SetDy( 1.00); rtMat[0][0]->SetDz(5.);
  rtMat[0][1]->SetDx(-1.00); rtMat[0][1]->SetDy( 1.50); rtMat[0][1]->SetDz(5.);
  rtMat[0][2]->SetDx(-1.50); rtMat[0][2]->SetDy(-1.00); rtMat[0][2]->SetDz(5.);
  rtMat[0][3]->SetDx( 1.00); rtMat[0][3]->SetDy(-1.50); rtMat[0][3]->SetDz(5.);
  rtMat[1][0]->SetDx( 2.75); rtMat[1][0]->SetDy( 2.25); rtMat[1][0]->SetDz(10.);
  rtMat[1][1]->SetDx(-2.25); rtMat[1][1]->SetDy( 2.75); rtMat[1][1]->SetDz(10.);
  rtMat[1][2]->SetDx(-2.75); rtMat[1][2]->SetDy(-2.25); rtMat[1][2]->SetDz(10.);
  rtMat[1][3]->SetDx( 2.25); rtMat[1][3]->SetDy(-2.75); rtMat[1][3]->SetDz(10.);
  rtMat[2][0]->SetDx( 5.50); rtMat[2][0]->SetDy( 4.50); rtMat[2][0]->SetDz(20.);
  rtMat[2][1]->SetDx(-4.50); rtMat[2][1]->SetDy( 5.50); rtMat[2][1]->SetDz(20.);
  rtMat[2][2]->SetDx(-5.50); rtMat[2][2]->SetDy(-4.50); rtMat[2][2]->SetDz(20.);
  rtMat[2][3]->SetDx( 4.50); rtMat[2][3]->SetDy(-5.50); rtMat[2][3]->SetDz(20.);
  fFeCols = 110;
  fFeRows = 116;
  fMaxFEperCol = 64;
  fPitchX = 0.01;
  fPitchY = 0.01;
  Double_t sensorSize[3][2] = {{1.,1.5},{2.25,2.75},{4.5,5.5}};
  Double_t zerr = 0.0075;

  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) {
    PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

    Int_t detId = currentDigi->GetDetectorID();    
    Int_t istat = detId/256-1;
    Int_t isens = detId%256-1;

    Int_t feId = currentDigi->GetFeID();
    Int_t col  = currentDigi->GetCol();
    Int_t row  = currentDigi->GetRow();

    Double_t locPosCalc[3];
    locPosCalc[0] = ( ((feId-1)/fMaxFEperCol)*fFeCols + col + 0.5 )*fPitchX;
    locPosCalc[1] = ( ((feId-1)%fMaxFEperCol)*fFeRows + row + 0.5 )*fPitchY;
    locPosCalc[2] = 0.;

    LOG(DEBUG) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1] << FairLogger::endl;
    
    locPosCalc[0] -= sensorSize[istat][0];
    locPosCalc[1] -= sensorSize[istat][1];
    
    Double_t globPos[3];

    rtMat[istat][isens]->LocalToMaster(locPosCalc,globPos);

    LOG(DEBUG) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2] << FairLogger::endl;

    TVector3 pos   (globPos[0],globPos[1],globPos[2]);
    TVector3 posErr(fPitchX/TMath::Sqrt(12.),fPitchY/TMath::Sqrt(12.),zerr);

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
  if ( ! run ) LOG(FATAL) << "No analysis run" << FairLogger::endl;

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) LOG(FATAL) << "No runtime database" << FairLogger::endl;

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
  LOG(INFO) << "********************************************** PixelFindHits::InitMQ()" << FairLogger::endl;
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
void   PixelFindHits::ExecMQ(TList* inputList,TList* outputList) {
  //  LOG(INFO) << "********************************************** PixelFindHits::ExecMQ(" << inputList->GetName() << "," << outputList->GetName() << "), Event " << fTNofEvents << FairLogger::endl;
  //  LOG(INFO) << "********************************************** PixelFindHits::ExecMQ(), Event " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << "h" << FairLogger::flush;
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

  if ( ! ioman ) LOG(FATAL) << "No FairRootManager" << FairLogger::endl;
  fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

  if ( !fDigis ) 
    LOG(WARNING) << "PixelFindHits::Init() No input PixelDigis array!" << FairLogger::endl;

  // Register output array PixelHit
  fHits = new TClonesArray("PixelHit",10000);
  ioman->Register("PixelHits", "Pixel", fHits, kTRUE);

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
  if ( fHits ) fHits->Delete();

  LOG(INFO) << "-------------------- " << fName.Data() << " : Summary ------------------------" << FairLogger::endl;
  LOG(INFO) << " Events:        " << fTNofEvents << FairLogger::endl;
  LOG(INFO) << " Digis:         " << fTNofDigis  << "    ( " << static_cast<Double_t>(fTNofDigis) /(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << " Hits:          " << fTNofHits   << "    ( " << static_cast<Double_t>(fTNofHits  )/(static_cast<Double_t>(fTNofEvents)) << " per event )" << FairLogger::endl;
  LOG(INFO) << "---------------------------------------------------------------------" << FairLogger::endl; 
}
// -------------------------------------------------------------------------



// MQ

void PixelFindHits::InitMQ(const std::string& root_file, const std::string& ascii_file) 
{
  fHits = new TClonesArray("PixelHits",10000);
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
  fGeoParSet = static_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
  fDigiPar = static_cast<PixelDigiPar*>(fRtdb->getContainer("PixelDigiParameters"));
  
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

  LOG(DEBUG) << "PixelFindHits::Exec() EVENT " << fTNofEvents << FairLogger::endl;

  fTNofEvents++;

  fNDigis = fDigis->GetEntriesFast();
  fTNofDigis+= fNDigis;
//*
  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) 
  {
    PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

    Int_t detId = currentDigi->GetDetectorID();    
    TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);

    fGeoParSet->GetGeometry()->cd(nodeName.Data());

    TGeoNode* curNode = fGeoParSet->GetGeometry()->GetCurrentNode();

//    TGeoMatrix* matrix = curNode->GetMatrix();

    TGeoVolume* actVolume = fGeoParSet->GetGeometry()->GetCurrentVolume();
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

    LOG(DEBUG) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1] << FairLogger::endl;
    LOG(DEBUG) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2] << FairLogger::endl;

    TVector3 pos   (globPos[0],globPos[1],globPos[2]);
    TVector3 posErr(fPitchX/TMath::Sqrt(12.),fPitchY/TMath::Sqrt(12.),actBox->GetDZ());

    new ((*fHits)[fNHits]) PixelHit(detId,currentDigi->GetIndex(),pos,posErr);

    fNHits++;
  }


  fTNofHits += fNHits;
  return fHits;
}



ClassImp(PixelFindHits)

