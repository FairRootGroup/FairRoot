/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

// Includes from ROOT
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

PixelAltFindHits::PixelAltFindHits()
    : PixelAltFindHits("Pixel Hit Finder", 0)
{}

PixelAltFindHits::PixelAltFindHits(Int_t iVerbose)
    : PixelAltFindHits("Pixel Hit Finder", iVerbose)
{}

PixelAltFindHits::PixelAltFindHits(const char* name, Int_t iVerbose)
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
    LOG(info) << "Created PixelAltFindHits.";
    Reset();
}

PixelAltFindHits::~PixelAltFindHits()
{
    Reset();
    delete fDigiPar;
    if (fHits) {
        fHits->Delete();
        delete fHits;
    }
}

void PixelAltFindHits::Exec(Option_t* /*opt*/)
{
    Reset();

    LOG(debug) << "PixelAltFindHits::Exec() EVENT " << fTNofEvents;

    fTNofEvents++;

    fNDigis = fDigis->GetEntriesFast();
    fTNofDigis += fNDigis;

    for (Int_t iDigi = 0; iDigi < fNDigis; iDigi++) {
        PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

        Int_t detId = currentDigi->GetDetectorID();

        Double_t posX, posY, posZ;
        Double_t errX, errY, errZ;
        Int_t hitIndex = FindHit(detId,
                                 currentDigi->GetFeID(),
                                 currentDigi->GetCol(),
                                 currentDigi->GetRow(),
                                 currentDigi->GetIndex(),
                                 posX,
                                 posY,
                                 posZ,
                                 errX,
                                 errY,
                                 errZ);

        TVector3 pos(posX, posY, posZ);
        TVector3 posErr(errX, errY, errZ);

        if (hitIndex == -666)
            continue;   // hit not found

        new ((*fHits)[fNHits]) PixelHit(detId, hitIndex, pos, posErr);

        fNHits++;
    }

    fTNofHits += fNHits;
}

// should return -666 if hit not found
Int_t PixelAltFindHits::FindHit(Int_t detId,
                                Int_t feId,
                                Int_t col,
                                Int_t row,
                                Int_t index,
                                Double_t& posX,
                                Double_t& posY,
                                Double_t& posZ,
                                Double_t& errX,
                                Double_t& errY,
                                Double_t& errZ)
{
    TString nodeName = Form("/cave/Pixel%d_%d", detId / 256, detId % 256);

    gGeoManager->cd(nodeName.Data());
    TGeoNode* curNode = gGeoManager->GetCurrentNode();
    TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
    TGeoBBox* actBox = static_cast<TGeoBBox*>(actVolume->GetShape());

    Double_t locPosCalc[3];
    locPosCalc[0] = (((feId - 1) / fMaxFEperCol) * fFeCols + col + 0.5) * fPitchX;
    locPosCalc[1] = (((feId - 1) % fMaxFEperCol) * fFeRows + row + 0.5) * fPitchY;
    locPosCalc[2] = 0.;

    locPosCalc[0] -= actBox->GetDX();
    locPosCalc[1] -= actBox->GetDY();

    Double_t globPos[3];

    curNode->LocalToMaster(locPosCalc, globPos);

    LOG(debug) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1];
    LOG(debug) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2];

    posX = globPos[0];
    posY = globPos[1];
    posZ = globPos[2];
    errX = fPitchX / TMath::Sqrt(12.);
    errY = fPitchY / TMath::Sqrt(12.);
    errZ = actBox->GetDZ();

    // should return -666 if hit not found
    return index;
}

void PixelAltFindHits::SetParContainers()
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

void PixelAltFindHits::GetParList(TList* tempList)
{
    fDigiPar = new PixelDigiPar("PixelDigiParameters");
    tempList->Add(fDigiPar);

    return;
}

void PixelAltFindHits::InitMQ(TList* tempList)
{
    LOG(info) << "********************************************** PixelAltFindHits::InitMQ()";
    fDigiPar = (PixelDigiPar*)tempList->FindObject("PixelDigiParameters");

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

    return;
}

void PixelAltFindHits::ExecMQ(TList* inputList, TList* outputList)
{
    //  LOG(info) << "********************************************** PixelAltFindHits::ExecMQ(" << inputList->GetName()
    //  << "," << outputList->GetName() << "), Event " << fTNofEvents; LOG(info) <<
    //  "********************************************** PixelAltFindHits::ExecMQ(), Event " << fTNofEvents; LOG(info) <<
    //  "h" << FairLogger::flush;
    fDigis = (TClonesArray*)inputList->FindObject("PixelDigis");
    outputList->Add(fHits);
    Exec("");
    return;
}

void PixelAltFindHits::ExecMQ(PixelPayload::Digi* digiPalVector,
                              int nofDigis,
                              PixelPayload::Hit* hitPalVector,
                              int& nofHits)
{
    for (int idigi = 0; idigi < nofDigis; idigi++) {
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

InitStatus PixelAltFindHits::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    if (!ioman)
        LOG(fatal) << "No FairRootManager";
    fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

    if (!fDigis)
        LOG(warn) << "PixelAltFindHits::Init() No input PixelDigis array!";

    // Register output array PixelHit
    fHits = new TClonesArray("PixelHit", 10000);
    ioman->Register("PixelHits", "Pixel", fHits, kTRUE);

    LOG(info) << "-I- " << fName.Data() << "::Init(). Initialization succesfull.";

    fFeCols = fDigiPar->GetFECols();
    fFeRows = fDigiPar->GetFERows();
    fMaxFEperCol = fDigiPar->GetMaxFEperCol();
    fPitchX = fDigiPar->GetXPitch();
    fPitchY = fDigiPar->GetYPitch();

    LOG(info) << "PixelAltFindHits::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY
              << "cm";

    return kSUCCESS;
}

InitStatus PixelAltFindHits::ReInit() { return kSUCCESS; }

void PixelAltFindHits::Reset()
{
    fNDigis = fNHits = 0;
    if (fHits)
        fHits->Clear();
}

void PixelAltFindHits::Finish()
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
