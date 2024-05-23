/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4StraightLineFitter.h"

#include "FairRootManager.h"       // for FairRootManager
#include "FairTrackParam.h"        // for FairTrackParam
#include "FairTutorialDet4Hit.h"   // for FairTutorialDet4Hit

#include <TF1.h>            // for TF1
#include <TGraphErrors.h>   // for TGraphErrors
#include <TVector3.h>       // for TVector3
#include <fairlogger/Logger.h>
#include <set>

FairTutorialDet4StraightLineFitter::FairTutorialDet4StraightLineFitter()
    : FairTask("FairTutorialDet4StraightLineFitter")
    , fTracks(FairTrackParam::Class(), 100)
    , fVersion(2)
{
    LOG(debug) << "Default Constructor of FairTutorialDet4StraightLineFitter";
}

InitStatus FairTutorialDet4StraightLineFitter::Init()
{
    LOG(debug) << "Initilization of FairTutorialDet4StraightLineFitter";

    // Get a handle from the IO manager
    FairRootManager* ioman = FairRootManager::Instance();

    // Get a pointer to the previous already existing data level

    fHits = dynamic_cast<TClonesArray const*>(ioman->GetObject("TutorialDetHit"));
    if (!fHits) {
        LOG(error) << "No InputDataLevelName array!\n"
                   << "FairTutorialDet4StraightLineFitter will be inactive";
        return kERROR;
    }

    // Create the TClonesArray for the output data and register
    // it in the IO manager
    ioman->Register("TutorialDetTrack", "TutorialDet", &fTracks, kTRUE);

    // Do whatever else is needed at the initilization stage
    // Create histograms to be filled
    // initialize variables

    return kSUCCESS;
}

void FairTutorialDet4StraightLineFitter::Exec(Option_t* /*option*/)
{
    LOG(debug) << "Exec of FairTutorialDet4StraightLineFitter";

    if (!IsGoodEvent()) {
        return;
    }

    // Declare some variables
    /*
  Int_t detID   = 0;        // Detector ID
  Int_t trackID = 0;        // Track index
  Double_t x, y, z;         // Position
  Double_t dx = 0.1;        // Position error
  Double_t tof = 0.;        // Time of flight
*/
    TVector3 pos, dpos;   // Position and error vectors

    // Loop over TofPoints
    Int_t nHits = fHits->GetEntriesFast();
    Float_t* ZPos = new Float_t[nHits];
    Float_t* XPos = new Float_t[nHits];
    Float_t* XPosErr = new Float_t[nHits];
    Float_t* YPos = new Float_t[nHits];
    Float_t* YPosErr = new Float_t[nHits];

    for (Int_t iHit = 0; iHit < nHits; iHit++) {
        auto hit = static_cast<FairTutorialDet4Hit const*>(fHits->At(iHit));
        if (!hit) {
            continue;
        }

        XPos[iHit] = hit->GetX();
        YPos[iHit] = hit->GetY();
        ZPos[iHit] = hit->GetZ();

        XPosErr[iHit] = hit->GetDx();
        YPosErr[iHit] = hit->GetDy();
    }

    auto f1 = TF1("f1", "[0]*x + [1]");
    auto linegraphX = TGraphErrors(nHits, ZPos, XPos, nullptr, XPosErr);
    linegraphX.Fit(&f1, "Q");
    Double_t SlopeX = f1.GetParameter(0);
    Double_t OffX = f1.GetParameter(1);
    Double_t Chi2X = f1.GetChisquare();
    Double_t SlopeY = 0.;
    Double_t OffY = 0.;
    Double_t Chi2Y;

    if (2 == fVersion) {
        auto linegraphY = TGraphErrors(nHits, ZPos, YPos, nullptr, YPosErr);
        linegraphY.Fit(&f1, "Q");
        SlopeY = f1.GetParameter(0);
        OffY = f1.GetParameter(1);
        Chi2Y = f1.GetChisquare();

        LOG(debug) << XPos[0] << "," << XPos[nHits - 1] << "," << YPos[0] << "," << YPos[nHits - 1] << "," << ZPos[0]
                   << "," << ZPos[nHits - 1];
        Double_t XSlope = (XPos[nHits - 1] - XPos[0]) / (ZPos[nHits - 1] - ZPos[0]);
        Double_t YSlope = (YPos[nHits - 1] - YPos[0]) / (ZPos[nHits - 1] - ZPos[0]);

        LOG(debug) << "Slope(x,y): " << SlopeX << " ," << SlopeY;
        LOG(debug) << "Slope1(x,y): " << XSlope << " ," << YSlope;
        LOG(debug) << "Offset(x,y): " << OffX << " ," << OffY;
        LOG(debug) << "Chi2(x,y): " << Chi2X << " ," << Chi2Y;
    }

    auto track = static_cast<FairTrackParam*>(fTracks.ConstructedAt(0));
    track->SetX(OffX);
    track->SetTx(SlopeX);
    track->SetZ(0.);
    if (2 == fVersion) {
        track->SetY(OffY);
        track->SetTy(SlopeY);
    }
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
    std::set<Int_t> detIdSet;

    Int_t nHits = fHits->GetEntriesFast();
    for (Int_t iHit = 0; iHit < nHits; ++iHit) {
        auto hit = static_cast<FairTutorialDet4Hit const*>(fHits->At(iHit));
        Int_t detId = hit->GetDetectorID();
        auto it = detIdSet.find(detId);
        if (it == detIdSet.end()) {
            detIdSet.insert(detId);
        } else {
            // find hit in already used detector station
            // this is not a good event
            return kFALSE;
        }
    }
    return kTRUE;
}
