// -------------------------------------------------------------------------
// -----   FairTutorialDetHitProducerIdealMissallign source file       -----
// -----                  Created 11.02.13  by F. Uhlig                -----
// -------------------------------------------------------------------------
#include "FairTutorialDetHitProducerIdealMisalign.h"

#include "FairTutorialDetHit.h"
#include "FairTutorialDetPoint.h"
#include "FairTutorialDetMisalignPar.h"

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "TClonesArray.h"
#include "TRandom.h"
#include "TGeoMatrix.h"
#include "TMath.h"
//#include "TGeoCombiTrans.h"

// -----   Default constructor   -------------------------------------------
FairTutorialDetHitProducerIdealMisalign::FairTutorialDetHitProducerIdealMisalign()
  : FairTask("Missallign Hit Producer for the TutorialDet"),
    fPointArray(NULL),
    fHitArray(NULL),
    fShiftX(),
    fShiftY(),
    fShiftZ(),
    fRotX(),
    fRotY(),
    fRotZ(),
    fDigiPar(NULL)
{
}

// -----   Destructor   ----------------------------------------------------
FairTutorialDetHitProducerIdealMisalign::~FairTutorialDetHitProducerIdealMisalign() { }

// --------------------------------------------------
void FairTutorialDetHitProducerIdealMisalign::SetParContainers()
{

  LOG(INFO)<< "Set tutdet missallign parameters"<<FairLogger::endl;
  // Get Base Container
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = (FairTutorialDetMisalignPar*)
             (rtdb->getContainer("FairTutorialDetMissallignPar"));

}
// --------------------------------------------------------------------
InitStatus FairTutorialDetHitProducerIdealMisalign::ReInit()
{

  // Get Base Container
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = (FairTutorialDetMisalignPar*)
             (rtdb->getContainer("FairTutorialDetMissallignPar"));

  fShiftX=fDigiPar->GetShiftX();
  fShiftY=fDigiPar->GetShiftY();
  fShiftZ=fDigiPar->GetShiftZ();
  fRotX=fDigiPar->GetRotX();
  fRotY=fDigiPar->GetRotY();
  fRotZ=fDigiPar->GetRotZ();
}

// -----   Public method Init   --------------------------------------------
InitStatus FairTutorialDetHitProducerIdealMisalign::Init()
{

  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) {
    LOG(FATAL) << "RootManager not instantised!" << FairLogger::endl;
    return kFATAL;
  }

  // Get input array
  fPointArray = (TClonesArray*) ioman->GetObject("TutorialDetPoint");
  if ( ! fPointArray ) {
    LOG(FATAL)<<"No TutorialDetPoint array!" << FairLogger::endl;
    return kFATAL;
  }

  // Create and register output array
  fHitArray = new TClonesArray("FairTutorialDetHit");
  ioman->Register("TutorialDetHit", "TutorialDet", fHitArray, kTRUE);

  LOG(INFO)<< "HitProducerIdealMissallign: Initialisation successfull"
           << FairLogger::endl;


  fShiftX=fDigiPar->GetShiftX();
  fShiftY=fDigiPar->GetShiftY();
  fShiftZ=fDigiPar->GetShiftZ();
  fRotX=fDigiPar->GetRotX();
  fRotY=fDigiPar->GetRotY();
  fRotZ=fDigiPar->GetRotZ();
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
void FairTutorialDetHitProducerIdealMisalign::Exec(Option_t* opt)
{

  // Reset output array
  if ( ! fHitArray ) { LOG(FATAL)<<"No TutorialDetHitArray"<<FairLogger::endl; }

  fHitArray->Clear();

  // Declare some variables
  FairTutorialDetPoint* point = NULL;
  Int_t detID   = 0;        // Detector ID
  Int_t trackID = 0;        // Track index
  Double_t x, y, z;         // Position
  Double_t dx = 0.1;        // Position error
  Double_t tof = 0.;        // Time of flight
  TVector3 pos, dpos;       // Position and error vectors

  // Loop over TofPoints
  Int_t nHits = 0;
  Int_t nPoints = fPointArray->GetEntriesFast();
  for (Int_t iPoint=0; iPoint<nPoints; iPoint++) {
    point = (FairTutorialDetPoint*) fPointArray->At(iPoint);
    if ( ! point) { continue; }

    // Detector ID
    detID = point->GetDetectorID();

    // MCTrack ID
    trackID = point->GetTrackID();

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
    tof = point->GetTime();

    // Create new hit
    pos.SetXYZ(x,y,z);
    dpos.SetXYZ(dx, dx, 0.);
    new ((*fHitArray)[nHits]) FairTutorialDetHit(detID, iPoint, pos, dpos);
    nHits++;
  }   // Loop over MCPoints

  // Event summary
  LOG(DEBUG)<< "Create " << nHits << " TutorialDetHits out of "
            << nPoints << " TutorilaDetPoints created." << FairLogger::endl;

}
// -------------------------------------------------------------------------

Double_t FairTutorialDetHitProducerIdealMisalign::GetHitErr(Double_t sigma)
{
  Double_t err = gRandom->Gaus(0, sigma);
  return (TMath::Abs(err) < 3 * sigma) ? err : (err > 0) ? 3 * sigma : -3 * sigma;
}



ClassImp(FairTutorialDetHitProducerIdealMisalign)
