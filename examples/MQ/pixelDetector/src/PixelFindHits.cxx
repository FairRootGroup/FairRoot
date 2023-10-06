/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "PixelDigi.h"
#include "PixelDigiPar.h"
#include "PixelHit.h"

#include <TClonesArray.h>
#include <TGeoBBox.h>
#include <TGeoManager.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TList.h>
#include <TMath.h>
#include <TString.h>
#include <TVector3.h>

PixelFindHits::PixelFindHits()
    : PixelFindHits("Pixel Hit Finder", 0)
{}

PixelFindHits::PixelFindHits(Int_t iVerbose)
    : PixelFindHits("Pixel Hit Finder", iVerbose)
{}

PixelFindHits::PixelFindHits(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fDigiPar(nullptr)
    , fGeoParSet(nullptr)
    , fDigis(nullptr)
    , fHits(nullptr)
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

PixelFindHits::~PixelFindHits()
{
    Reset();
    delete fDigiPar;
    if (fHits) {
        fHits->Delete();
        delete fHits;
    }
}

void PixelFindHits::Exec(Option_t* /*opt*/)
{
    Reset();

    LOG(debug) << "PixelFindHits::Exec() EVENT " << fTNofEvents;

    fTNofEvents++;

    fNDigis = fDigis->GetEntriesFast();
    fTNofDigis += fNDigis;

    for (Int_t iDigi = 0; iDigi < fNDigis; iDigi++) {
        PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

        Int_t detId = currentDigi->GetDetectorID();
        TString nodeName = Form("/cave/Pixel%d_%d", detId / 256, detId % 256);

        gGeoManager->cd(nodeName.Data());
        TGeoNode* curNode = gGeoManager->GetCurrentNode();

        // TGeoMatrix* matrix = curNode->GetMatrix();

        TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
        TGeoBBox* actBox = static_cast<TGeoBBox*>(actVolume->GetShape());

        Int_t feId = currentDigi->GetFeID();
        Int_t col = currentDigi->GetCol();
        Int_t row = currentDigi->GetRow();

        Double_t locPosCalc[3];
        locPosCalc[0] = (((feId - 1) / fMaxFEperCol) * fFeCols + col + 0.5) * fPitchX;
        locPosCalc[1] = (((feId - 1) % fMaxFEperCol) * fFeRows + row + 0.5) * fPitchY;
        locPosCalc[2] = 0.;

        locPosCalc[0] -= actBox->GetDX();
        locPosCalc[1] -= actBox->GetDY();

        Double_t globPos[3];

        curNode->LocalToMaster(locPosCalc, globPos);

        LOG(debug) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1];
        LOG(debug) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / "
                   << globPos[2];

        TVector3 pos(globPos[0], globPos[1], globPos[2]);
        TVector3 posErr(fPitchX / TMath::Sqrt(12.), fPitchY / TMath::Sqrt(12.), actBox->GetDZ());

        new ((*fHits)[fNHits]) PixelHit(detId, currentDigi->GetIndex(), pos, posErr);

        fNHits++;
    }

    fTNofHits += fNHits;
}

void PixelFindHits::SetParContainers()
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

void PixelFindHits::GetParList(TList* tempList)
{
    fDigiPar = new PixelDigiPar("PixelDigiParameters");
    tempList->Add(fDigiPar);
}

void PixelFindHits::InitMQ(TList* tempList)
{
    LOG(info) << "********************************************** PixelFindHits::InitMQ()";
    fDigiPar = dynamic_cast<PixelDigiPar*>(tempList->FindObject("PixelDigiParameters"));
    if (!fDigiPar) {
        throw std::runtime_error("no PixelDigiParameters");
    }

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

    fHits = new TClonesArray("PixelHit", 10000);
}

void PixelFindHits::ExecMQ(TList* inputList, TList* outputList)
{
    //  LOG(info) << "********************************************** PixelFindHits::ExecMQ(" << inputList->GetName() <<
    //  "," << outputList->GetName() << "), Event " << fTNofEvents; LOG(info) <<
    //  "********************************************** PixelFindHits::ExecMQ(), Event " << fTNofEvents; LOG(info) <<
    //  "h" << FairLogger::flush;
    fDigis = dynamic_cast<TClonesArray*>(inputList->FindObject("PixelDigis"));
    if (!fDigis) {
        throw std::runtime_error("no PixelDigis");
    }
    if (!fDigis->GetClass()->InheritsFrom(PixelDigi::Class())) {
        throw std::runtime_error("wrong type in PixelDigis TCA");
    }
    outputList->Add(fHits);
    Exec("");
}

InitStatus PixelFindHits::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    if (!ioman)
        LOG(fatal) << "No FairRootManager";
    fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

    if (!fDigis)
        LOG(warn) << "PixelFindHits::Init() No input PixelDigis array!";

    // Register output array PixelHit
    fHits = new TClonesArray("PixelHit", 10000);
    ioman->Register("PixelHits", "Pixel", fHits, kTRUE);

    LOG(info) << "-I- " << fName.Data() << "::Init(). Initialization succesfull.";

    fFeCols = fDigiPar->GetFECols();
    fFeRows = fDigiPar->GetFERows();
    fMaxFEperCol = fDigiPar->GetMaxFEperCol();
    fPitchX = fDigiPar->GetXPitch();
    fPitchY = fDigiPar->GetYPitch();

    LOG(info) << "PixelFindHits::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY
              << "cm";

    return kSUCCESS;
}

InitStatus PixelFindHits::ReInit() { return kSUCCESS; }

void PixelFindHits::Reset()
{
    fNDigis = fNHits = 0;
    if (fHits)
        fHits->Clear();
}

void PixelFindHits::Finish()
{
    if (fHits)
        fHits->Delete();

    LOG(info) << "-------------------- " << fName.Data() << " : Summary ------------------------";
    LOG(info) << " Events:        " << fTNofEvents;
    LOG(info) << " Digis:         " << fTNofDigis << "    ("
              << static_cast<Double_t>(fTNofDigis) / (static_cast<Double_t>(fTNofEvents)) << " per event)";
    LOG(info) << " Hits:          " << fTNofHits << "    ("
              << static_cast<Double_t>(fTNofHits) / (static_cast<Double_t>(fTNofEvents)) << " per event)";
    LOG(info) << "---------------------------------------------------------------------";
}
