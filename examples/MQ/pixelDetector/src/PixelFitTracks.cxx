/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFitTracks.cxx
 *
 *  Created on: 25.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFitTracks.h"

#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "PixelDigiPar.h"
#include "PixelHit.h"
#include "PixelTrack.h"

#include <TMath.h>
#include <fairlogger/Logger.h>

PixelFitTracks::PixelFitTracks()
    : PixelFitTracks("Pixel Track Fitter", 0)
{}

PixelFitTracks::PixelFitTracks(Int_t iVerbose)
    : PixelFitTracks("Pixel Track Fitter", iVerbose)
{}

PixelFitTracks::PixelFitTracks(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fDigiPar(nullptr)
    , fHits(nullptr)
    , fTracks(nullptr)
    , fFitTracks(nullptr)
    , fTNofEvents(0)
    , fNHits(0)
    , fNTracks(0)
    , fTNofTracks(0)
    , fNFitTracks(0)
    , fTNofFitTracks(0)
{}

PixelFitTracks::~PixelFitTracks()
{
    delete fDigiPar;
    if (fFitTracks) {
        fFitTracks->Delete();
        delete fFitTracks;
    }
}

void PixelFitTracks::Exec(Option_t* /*opt*/)
{
    fNFitTracks = 0;
    if (fFitTracks)
        fFitTracks->Clear();

    fNHits = fHits->GetEntriesFast();
    fNTracks = fTracks->GetEntriesFast();

    LOG(debug) << "PixelFitTracks::Exec() EVENT " << fTNofEvents << " with " << fNTracks << " TRACKS";

    for (Int_t itrack = 0; itrack < fNTracks; itrack++) {
        PixelTrack* curTrack = static_cast<PixelTrack*>(fTracks->At(itrack));

        const Int_t nofHits = curTrack->GetNofHits();
        // Default initialize the arrays
        Double_t* hitXPos = new Double_t[nofHits]();
        Double_t* hitYPos = new Double_t[nofHits]();
        Double_t* hitZPos = new Double_t[nofHits]();

        for (Int_t ihit = 0; ihit < nofHits; ihit++) {
            PixelHit* curHit = static_cast<PixelHit*>(fHits->At(curTrack->GetHitIndex(ihit)));

            // LOG(info) << " HIT[" << curTrack->GetHitIndex(ihit) << "] = (" << curHit->GetX() << " , " <<
            // curHit->GetY() << " , " << curHit->GetZ() << ")";
            hitXPos[ihit] = curHit->GetX();
            hitYPos[ihit] = curHit->GetY();
            hitZPos[ihit] = curHit->GetZ();
        }

        Double_t valX0 = 0., errX0 = 0., valAX = 0., errAX = 0.;
        Double_t valY0 = 0., errY0 = 0., valAY = 0., errAY = 0.;

        LinearRegression(nofHits, hitZPos, hitXPos, valX0, errX0, valAX, errAX);
        LinearRegression(nofHits, hitZPos, hitYPos, valY0, errY0, valAY, errAY);

        PixelTrack* fitTrack =
            new ((*fFitTracks)[fNFitTracks]) PixelTrack(valX0, valAX, valY0, valAY, errX0, errAX, errY0, errAY);
        for (Int_t ihit = 0; ihit < nofHits; ihit++) {
            fitTrack->AddHitIndex(curTrack->GetHitIndex(ihit));
        }

        fNFitTracks += 1;

        LOG(debug) << "Track params:  "
                   << " AX = " << curTrack->GetAX() << " += " << curTrack->GetAXErr() << " X0 = " << curTrack->GetX0()
                   << " += " << curTrack->GetX0Err() << "                         "
                   << " AY = " << curTrack->GetAY() << " += " << curTrack->GetAYErr() << " Y0 = " << curTrack->GetY0()
                   << " += " << curTrack->GetY0Err();
        LOG(debug) << "Fitted params: "
                   << " AX = " << valAX << " += " << errAX << " X0 = " << valX0 << " += " << errX0
                   << "                         "
                   << " AY = " << valAY << " += " << errAY << " Y0 = " << valY0 << " += " << errY0;

        delete[] hitXPos;
        delete[] hitYPos;
        delete[] hitZPos;
    }

    fTNofEvents += 1;
    fTNofTracks += fNTracks;
    fTNofFitTracks += fNFitTracks;
}

Double_t PixelFitTracks::LinearRegression(Int_t nval,
                                          Double_t xval[],
                                          Double_t yval[],
                                          Double_t& valA0,
                                          Double_t& errA0,
                                          Double_t& valA1,
                                          Double_t& errA1)
{
    Double_t valN = static_cast<Double_t>(nval);
    Double_t sumXY = 0.;
    Double_t sumX = 0.;
    Double_t sumY = 0.;
    Double_t sumXX = 0.;

    for (Int_t ival = 0; ival < nval; ival++) {
        sumXY += xval[ival] * yval[ival];
        sumX += xval[ival];
        sumY += yval[ival];
        sumXX += xval[ival] * xval[ival];
    }
    valA1 = (valN * sumXY - sumX * sumY) / (valN * sumXX - sumX * sumX);
    valA0 = (sumY - valA1 * sumX) / valN;
    Double_t sumEE = 0.;
    for (Int_t ival = 0; ival < nval; ival++) {
        sumEE += (yval[ival] - valA0 - valA1 * xval[ival]) * (yval[ival] - valA0 - valA1 * xval[ival]);
    }
    Double_t valS = TMath::Sqrt(sumEE / (valN - 2.));
    errA1 = valS * TMath::Sqrt(valN / (valN * sumXX - sumX * sumX));
    errA0 = valS * TMath::Sqrt(sumXX / (valN * sumXX - sumX * sumX));
    // cout << "A0 = " << valA0 << " +- " << errA0 << " / A1 = " << valA1 << " +- " << errA1 << " / S = " << valS <<
    // endl;
    return valS;
}

void PixelFitTracks::SetParContainers()
{
    // Get run and runtime database
    FairRun* run = FairRun::Instance();
    if (!run)
        LOG(fatal) << "No analysis run";

    FairRuntimeDb* db = run->GetRuntimeDb();
    if (!db)
        LOG(fatal) << "No runtime database";

    // Get GEM digitisation parameter container
    fDigiPar = static_cast<PixelDigiPar*>(db->getContainer("PixelDigiParameters"));
}

void PixelFitTracks::GetParList(TList* tempList)
{
    fDigiPar = new PixelDigiPar("PixelDigiParameters");
    tempList->Add(fDigiPar);
}

void PixelFitTracks::InitMQ(TList* tempList)
{
    LOG(info) << "********************************************** PixelFitTracks::InitMQ()";
    fDigiPar = (PixelDigiPar*)tempList->FindObject("PixelDigiParameters");

    fFitTracks = new TClonesArray("PixelTrack", 10000);
    fFitTracks->SetName("PixelFitTracks");
}

void PixelFitTracks::ExecMQ(TList* inputList, TList* outputList)
{
    //  LOG(info) << "********************************************** PixelFitTracks::ExecMQ(" << inputList->GetName() <<
    //  "," << outputList->GetName() << "), Event " << fTNofEvents; LOG(info) <<
    //  "********************************************** PixelFitTracks::ExecMQ(), Event " << fTNofEvents; LOG(info) <<
    //  "f" << FairLogger::flush;
    fHits = (TClonesArray*)inputList->FindObject("PixelHits");
    fTracks = (TClonesArray*)inputList->FindObject("PixelTracks");
    outputList->Add(fFitTracks);
    Exec("");
}

InitStatus PixelFitTracks::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman)
        LOG(fatal) << "No FairRootManager";

    fHits = static_cast<TClonesArray*>(ioman->GetObject("PixelHits"));
    if (!fHits)
        LOG(warn) << "PixelFitTracks::Init() No input PixelHit array!";
    fTracks = static_cast<TClonesArray*>(ioman->GetObject("PixelTracks"));
    if (!fTracks)
        LOG(warn) << "PixelFitTracks::Init() No input PixelTrack array!";

    // Register output array PixelHit
    fFitTracks = new TClonesArray("PixelTrack", 10000);
    ioman->Register("PixelFitTracks", "Pixel", fFitTracks, kTRUE);

    return kSUCCESS;
}

void PixelFitTracks::Finish()
{
    if (fFitTracks)
        fFitTracks->Delete();

    LOG(info) << "-------------------- " << fName.Data() << " : Summary ------------------------";
    LOG(info) << " Events:        " << fTNofEvents;
    LOG(info) << " Tracks:        " << fTNofTracks << "    ("
              << static_cast<Double_t>(fTNofTracks) / (static_cast<Double_t>(fTNofEvents)) << " per event)";
    LOG(info) << " Fitted Tracks: " << fTNofFitTracks << "    ("
              << static_cast<Double_t>(fTNofFitTracks) / (static_cast<Double_t>(fTNofEvents)) << " per event)";
    LOG(info) << "---------------------------------------------------------------------";
}
