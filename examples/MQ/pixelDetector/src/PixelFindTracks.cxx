/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFindTracks.cxx
 *
 *  Created on: 23.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFindTracks.h"

#include "PixelDigiPar.h"
#include "PixelHit.h"
#include "PixelTrack.h"

// Includes from base
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRun.h"   // for FairRun
#include "FairRuntimeDb.h"

// Includes from ROOT
#include <TClonesArray.h>
#include <TH2.h>         // for TH2F
#include <TList.h>       // for TList
#include <TMathBase.h>   // for Abs

PixelFindTracks::PixelFindTracks()
    : PixelFindTracks("Pixel Track Finder", 0)
{}

PixelFindTracks::PixelFindTracks(Int_t iVerbose)
    : PixelFindTracks("Pixel Track Finder", iVerbose)
{}

PixelFindTracks::PixelFindTracks(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fDigiPar(nullptr)
    , fHits(nullptr)
    , fTracks(nullptr)
    , fTNofEvents(0)
    , fNHits(0)
    , fTNofHits(0)
    , fNTracks(0)
    , fTNofTracks(0)
    , fhDist2D(nullptr)
{
    Reset();
}

PixelFindTracks::~PixelFindTracks()
{
    Reset();
    delete fDigiPar;
    if (fTracks) {
        fTracks->Delete();
        delete fTracks;
    }
}

void PixelFindTracks::Exec(Option_t* /*opt*/)
{
    Reset();

    fNHits = fHits->GetEntriesFast();

    LOG(debug) << "PixelFindTracks::Exec() EVENT " << fTNofEvents << " with " << fNHits << " HITS";

    PixelHit* curHit1;
    PixelHit* curHit2;
    PixelHit* curHit3;

    Double_t parX0 = 0.;
    Double_t parY0 = 0.;
    Double_t parAX = 0.;
    Double_t parAY = 0.;
    Double_t expX = 0.;
    Double_t expY = 0.;

    for (Int_t ihit1 = 0; ihit1 < fNHits; ihit1++) {
        curHit1 = static_cast<PixelHit*>(fHits->At(ihit1));
        LOG(debug) << "hit1 at " << curHit1->GetX() << " , " << curHit1->GetY() << " , " << curHit1->GetZ() << " / "
                   << curHit1->GetDetectorID();
        if ((curHit1->GetDetectorID()) / 256 != 1)
            continue;
        for (Int_t ihit2 = 0; ihit2 < fNHits; ihit2++) {
            curHit2 = static_cast<PixelHit*>(fHits->At(ihit2));
            LOG(debug) << "hit2 at " << curHit2->GetX() << " , " << curHit2->GetY() << " , " << curHit2->GetZ() << " / "
                       << curHit2->GetDetectorID();
            if ((curHit2->GetDetectorID()) / 256 != 2)
                continue;

            parAX = (curHit2->GetX() - curHit1->GetX()) / (curHit2->GetZ() - curHit1->GetZ());
            parAY = (curHit2->GetY() - curHit1->GetY()) / (curHit2->GetZ() - curHit1->GetZ());
            parX0 = curHit1->GetX() - parAX * curHit1->GetZ();
            parY0 = curHit1->GetY() - parAY * curHit1->GetZ();

            for (Int_t ihit3 = 0; ihit3 < fNHits; ihit3++) {
                curHit3 = static_cast<PixelHit*>(fHits->At(ihit3));
                LOG(debug) << "hit3 at " << curHit3->GetX() << " , " << curHit3->GetY() << " , " << curHit3->GetZ()
                           << " / " << curHit3->GetDetectorID();
                if ((curHit3->GetDetectorID()) / 256 != 3)
                    continue;
                expX = parX0 + parAX * curHit3->GetZ();
                expY = parY0 + parAY * curHit3->GetZ();

                fhDist2D->Fill(expX - curHit3->GetX(), expY - curHit3->GetY());

                if (TMath::Abs(expX - curHit3->GetX()) < 0.03 && TMath::Abs(expY - curHit3->GetY()) < 0.03) {
                    LOG(debug) << "should create track...";
                    PixelTrack* tempTrack =
                        new ((*fTracks)[fNTracks]) PixelTrack(parX0, parAX, parY0, parAY, 0., 0., 0., 0.);
                    tempTrack->AddHitIndex(ihit1);
                    tempTrack->AddHitIndex(ihit2);
                    tempTrack->AddHitIndex(ihit3);
                    LOG(debug) << "--> " << fNTracks;
                    fNTracks++;
                }
                // LOG(debug) << ">>>>>> " << curHit3->GetX() << "  /  " << curHit3->GetY();
                // LOG(debug) << "       " << expX << "  /  " << expY;
            }
        }
    }

    fTNofEvents += 1;
    fTNofHits += fNHits;
    fTNofTracks += fNTracks;
}

void PixelFindTracks::SetParContainers()
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

void PixelFindTracks::GetParList(TList* tempList)
{
    fDigiPar = new PixelDigiPar("PixelDigiParameters");
    tempList->Add(fDigiPar);

    return;
}

void PixelFindTracks::InitMQ(TList* tempList)
{
    LOG(info) << "********************************************** PixelFindTracks::InitMQ()";
    fDigiPar = (PixelDigiPar*)tempList->FindObject("PixelDigiParameters");

    fTracks = new TClonesArray("PixelTrack", 10000);
    fhDist2D = new TH2F("fhDist2D", "Distance between hit and expected track", 400, -1., 1., 400, -1., 1.);

    return;
}

void PixelFindTracks::ExecMQ(TList* inputList, TList* outputList)
{
    //  LOG(info) << "********************************************** PixelFindTracks::ExecMQ(" << inputList->GetName()
    //  << "," << outputList->GetName() << "), Event " << fTNofEvents; LOG(info) <<
    //  "********************************************** PixelFindTracks::ExecMQ(), Event " << fTNofEvents; LOG(info) <<
    //  "t" << FairLogger::flush;
    fHits = (TClonesArray*)inputList->FindObject("PixelHits");
    outputList->Add(fTracks);
    Exec("");
    return;
}

InitStatus PixelFindTracks::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    if (!ioman)
        LOG(fatal) << "No FairRootManager";
    fHits = static_cast<TClonesArray*>(ioman->GetObject("PixelHits"));

    if (!fHits)
        LOG(warn) << "PixelFindTracks::Init() No input PixelHit array!";

    // Register output array PixelHit
    fTracks = new TClonesArray("PixelTrack", 10000);
    ioman->Register("PixelTracks", "Pixel", fTracks, kTRUE);

    fhDist2D = new TH2F("fhDist2D", "Distance between hit and expected track", 400, -1., 1., 400, -1., 1.);

    return kSUCCESS;
}

InitStatus PixelFindTracks::ReInit() { return kSUCCESS; }

void PixelFindTracks::Reset()
{
    fNTracks = fNHits = 0;
    if (fTracks)
        fTracks->Clear();
}

void PixelFindTracks::Finish()
{
    if (fTracks)
        fTracks->Delete();

    fhDist2D->Draw("colz");

    LOG(info) << "-------------------- " << fName.Data() << " : Summary ------------------------";
    LOG(info) << " Events:        " << fTNofEvents;
    LOG(info) << " Hits:          " << fTNofHits << "    ( "
              << static_cast<Double_t>(fTNofHits) / (static_cast<Double_t>(fTNofEvents)) << " per event )";
    LOG(info) << " Tracks:        " << fTNofTracks << "    ( "
              << static_cast<Double_t>(fTNofTracks) / (static_cast<Double_t>(fTNofEvents)) << " per event )";
    LOG(info) << "---------------------------------------------------------------------";
}
