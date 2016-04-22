/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4StraightLineFitter.h"

#include "FairLogger.h"                 // for FairLogger, etc
#include "FairRootManager.h"            // for FairRootManager
#include "FairTrackParam.h"             // for FairTrackParam
#include "FairTutorialDet4Hit.h"        // for FairTutorialDet4Hit

#include "TClonesArray.h"               // for TClonesArray
#include "TF1.h"                        // for TF1
#include "TGraphErrors.h"               // for TGraphErrors
#include "TVector3.h"                   // for TVector3

#include <stddef.h>                     // for NULL
#include <set>                          // for set, set<>::iterator, etc

// ---- Default constructor -------------------------------------------
FairTutorialDet4StraightLineFitter::FairTutorialDet4StraightLineFitter()
  :FairTask("FairTutorialDet4StraightLineFitter"),
   fHits(NULL),
   fTracks(NULL),
   fVersion(2)
{
  LOG(DEBUG) << "Default Constructor of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;
}

// ---- Destructor ----------------------------------------------------
FairTutorialDet4StraightLineFitter::~FairTutorialDet4StraightLineFitter()
{
  LOG(DEBUG) << "Destructor of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;
  if (fTracks) {
    fTracks->Delete();
    delete fTracks;
  }
}

// ----  Initialisation  ----------------------------------------------
void FairTutorialDet4StraightLineFitter::SetParContainers()
{
  LOG(DEBUG) << "SetParContainers of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;
  // Load all necessary parameter containers from the runtime data base
  /*
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  <FairTutorialDet4StraightLineFitterDataMember> = (<ClassPointer>*)
    (rtdb->getContainer("<ContainerName>"));
  */
}

// ---- Init ----------------------------------------------------------
InitStatus FairTutorialDet4StraightLineFitter::Init()
{
  LOG(DEBUG) << "Initilization of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();

  // Get a pointer to the previous already existing data level

  fHits = static_cast<TClonesArray*>(ioman->GetObject("TutorialDetHit"));
  if ( ! fHits ) {
    LOG(ERROR)<<"No InputDataLevelName array!\n"
              << "FairTutorialDet4StraightLineFitter will be inactive"<<FairLogger::endl;
    return kERROR;
  }

  // Create the TClonesArray for the output data and register
  // it in the IO manager
  fTracks = new TClonesArray("FairTrackParam", 100);
  ioman->Register("TutorialDetTrack","TutorialDet",fTracks,kTRUE);


  // Do whatever else is needed at the initilization stage
  // Create histograms to be filled
  // initialize variables

  return kSUCCESS;

}

// ---- ReInit  -------------------------------------------------------
InitStatus FairTutorialDet4StraightLineFitter::ReInit()
{
  LOG(DEBUG) << "Initilization of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;
  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void FairTutorialDet4StraightLineFitter::Exec(Option_t* /*option*/)
{
  LOG(DEBUG) << "Exec of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;

  if (!IsGoodEvent()) { return; }

  // Declare some variables
  FairTutorialDet4Hit* hit = NULL;
/*
  Int_t detID   = 0;        // Detector ID
  Int_t trackID = 0;        // Track index
  Double_t x, y, z;         // Position
  Double_t dx = 0.1;        // Position error
  Double_t tof = 0.;        // Time of flight
*/
  TVector3 pos, dpos;       // Position and error vectors

  // Loop over TofPoints
  Int_t nHits = fHits->GetEntriesFast();
  Float_t* ZPos = new Float_t[nHits];
  Float_t* XPos = new Float_t[nHits];
  Float_t* XPosErr = new Float_t[nHits];
  Float_t* YPos = new Float_t[nHits];
  Float_t* YPosErr = new Float_t[nHits];

  for (Int_t iHit=0; iHit<nHits; iHit++) {
    hit = static_cast<FairTutorialDet4Hit*>(fHits->At(iHit));
    if ( ! hit) { continue; }

    XPos[iHit] = hit->GetX();
    YPos[iHit] = hit->GetY();
    ZPos[iHit] = hit->GetZ();

    XPosErr[iHit] = hit->GetDx();
    YPosErr[iHit] = hit->GetDy();
  }

  TF1* f1 = new TF1("f1", "[0]*x + [1]");
  TGraphErrors* LineGraph;

  LineGraph = new TGraphErrors(nHits, ZPos, XPos, 0, XPosErr);
  LineGraph->Fit("f1", "Q");
  Double_t SlopeX = f1->GetParameter(0);
  Double_t OffX = f1->GetParameter(1);
  Double_t Chi2X = f1->GetChisquare();
  Double_t SlopeY;
  Double_t OffY;
  Double_t Chi2Y;

  if ( 2 == fVersion ) {
    LineGraph = new TGraphErrors(nHits, ZPos, YPos, 0, YPosErr);
    LineGraph->Fit("f1", "Q");
    SlopeY = f1->GetParameter(0);
    OffY = f1->GetParameter(1);
    Chi2Y = f1->GetChisquare();

    LOG(DEBUG)<<XPos[0]<<","<<XPos[nHits-1]<<","<<YPos[0]<<","<<YPos[nHits-1]<<","<<ZPos[0]<<","<<ZPos[nHits-1]<<FairLogger::endl;
    Double_t XSlope = (XPos[nHits-1]-XPos[0])/(ZPos[nHits-1]-ZPos[0]);
    Double_t YSlope = (YPos[nHits-1]-YPos[0])/(ZPos[nHits-1]-ZPos[0]);

    LOG(DEBUG)<<"Slope(x,y): "<<SlopeX<<" ,"<<SlopeY<<FairLogger::endl;
    LOG(DEBUG)<<"Slope1(x,y): "<<XSlope<<" ,"<<YSlope<<FairLogger::endl;
    LOG(DEBUG)<<"Offset(x,y): "<<OffX<<" ,"<<OffY<<FairLogger::endl;
    LOG(DEBUG)<<"Chi2(x,y): "<<Chi2X<<" ,"<<Chi2Y<<FairLogger::endl;

  }

  FairTrackParam* track = new FairTrackParam();
  track->SetX(OffX);
  track->SetTx(SlopeX);
  track->SetZ(0.);
  if ( 2 == fVersion ) {
    track->SetY(OffY);
    track->SetTy(SlopeY);
  }
  new ((*fTracks)[0]) FairTrackParam(*track);
  //  const TMatrixFSym matrix;
  //  Double_t Z = 0.;
  //  new ((*fTracks)[0]) FairTrackParam(OffX, OffY, Z, SlopeX, SlopeY, matrix);

  delete[] ZPos;
  delete[] XPos;
  delete[] XPosErr;
  delete[] YPos;
  delete[] YPosErr;
}

Bool_t FairTutorialDet4StraightLineFitter::IsGoodEvent()
{
  // Check if each for the event there is maximum 1 hit per detector
  // station. In the moment we create tracks with all hits in the
  // event, so we have to check for this.
  // In the end the algorithm should be able to work also with
  // missing hits in some stations
  FairTutorialDet4Hit* hit;
  std::set<Int_t> detIdSet;
  std::set<Int_t>::iterator it;

  Int_t nHits = fHits->GetEntriesFast();
  for (Int_t iHit=0; iHit<nHits; ++iHit) {
    hit = static_cast<FairTutorialDet4Hit*>(fHits->At(iHit));
    Int_t detId = hit->GetDetectorID();
    it = detIdSet.find(detId);
    if ( it == detIdSet.end() ) {
      detIdSet.insert(detId);
    } else {
      // find hit in already used detector station
      // this is not a good event
      return kFALSE;
    }
  }
  return kTRUE;
}

// ---- Finish --------------------------------------------------------
void FairTutorialDet4StraightLineFitter::Finish()
{
  LOG(DEBUG) << "Finish of FairTutorialDet4StraightLineFitter"
	     << FairLogger::endl;
}

ClassImp(FairTutorialDet4StraightLineFitter)
