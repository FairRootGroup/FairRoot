/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 16.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelDigitize.h"

#include "PixelDigi.h"
#include "PixelDigiPar.h"
#include "PixelPoint.h"

// Includes from base
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

// Includes from ROOT
#include <TClonesArray.h>
#include <TGeoBBox.h>
#include <TGeoManager.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TList.h>
#include <TString.h>

PixelDigitize::PixelDigitize()
    : PixelDigitize("Pixel Digitizer", 0)
{}

PixelDigitize::PixelDigitize(Int_t iVerbose)
    : PixelDigitize("Pixel Digitizer", iVerbose)
{}

PixelDigitize::PixelDigitize(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fDigiPar(nullptr)
    , fPoints(nullptr)
    , fDigis(nullptr)
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

PixelDigitize::~PixelDigitize()
{
    Reset();
    delete fDigiPar;
    if (fDigis) {
        fDigis->Delete();
        delete fDigis;
    }
}

void PixelDigitize::Exec(Option_t* /*opt*/)
{
    Reset();

    LOG(debug) << "PixelDigitize::Exec() EVENT " << fTNofEvents;

    fTNofEvents++;

    fNPoints = fPoints->GetEntriesFast();
    fTNofPoints += fNPoints;

    for (Int_t iPoint = 0; iPoint < fNPoints; iPoint++) {
        PixelPoint* currentPixelPoint = static_cast<PixelPoint*>(fPoints->At(iPoint));

        Double_t posIn[3] = {currentPixelPoint->GetX(), currentPixelPoint->GetY(), currentPixelPoint->GetZ()};

        Int_t detId = currentPixelPoint->GetDetectorID();
        TString nodeName = Form("/cave/Pixel%d_%d", detId / 256, detId % 256);

        gGeoManager->cd(nodeName.Data());
        TGeoNode* curNode = gGeoManager->GetCurrentNode();

        if (!curNode)
            LOG(fatal) << "PixelDigitize::Exec() node \"" << nodeName.Data() << "\" unknown!";

        Double_t locPosIn[3];

        curNode->MasterToLocal(posIn, locPosIn);

        // The local coordinate system has the origin set to the center of the volume.
        // To calculate the pixel number, it is necessary to move the origin to the bottom left corner.
        TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
        TGeoBBox* actBox = static_cast<TGeoBBox*>(actVolume->GetShape());
        // Double_t sensorWidth  = 2.*actBox->GetDX();
        // Double_t sensorHeight = 2.*actBox->GetDY();
        locPosIn[0] += actBox->GetDX();
        locPosIn[1] += actBox->GetDY();

        LOG(debug) << "GLOB PNT " << detId << " POSITION:  " << posIn[0] << " / " << posIn[1] << " / " << posIn[2];
        LOG(debug) << "POINT ON " << detId << " POSITION:  " << locPosIn[0] << " / " << locPosIn[1];

        Int_t col = static_cast<Int_t>(locPosIn[0] / fPitchX);
        Int_t ocol = col;
        Int_t row = static_cast<Int_t>(locPosIn[1] / fPitchY);
        Int_t orow = row;
        Int_t feCol = col / fFeCols;
        col = col % fFeCols;
        Int_t feRow = row / fFeRows;
        row = row % fFeRows;
        Int_t feId = 1 + feCol * fMaxFEperCol + feRow;

        LOG(debug) << "COL = " << feCol << " FE + " << col << " ( " << ocol << " ) /// "
                   << "ROW = " << feRow << " FE + " << row << " ( " << orow << " ) /// "
                   << " /// PIXEL = " << feId;

        ActivatePixel(iPoint, detId, feId, col, row, 1., 0.);
    }

    fTNofDigis += fNDigis;
}

void PixelDigitize::ActivatePixel(Int_t index,
                                  Int_t detId,
                                  Int_t feId,
                                  Int_t col,
                                  Int_t row,
                                  Double_t charge,
                                  Double_t timestamp)
{
    Bool_t pixelAlreadyFired = kFALSE;
    PixelDigi* tempPixel = nullptr;
    for (Int_t ipixel = 0; ipixel < fNDigis; ipixel++) {
        tempPixel = static_cast<PixelDigi*>(fDigis->At(ipixel));
        if (tempPixel->GetDetectorID() == detId && tempPixel->GetFeID() == feId && tempPixel->GetCol() == col
            && tempPixel->GetRow() == row) {
            pixelAlreadyFired = kTRUE;
            tempPixel->SetCharge(tempPixel->GetCharge() + charge);
        }
    }
    // TODO: order the PixelDigi in the output array by station, not by track...
    if (!pixelAlreadyFired) {
        new ((*fDigis)[fNDigis]) PixelDigi(index, detId, feId, col, row, charge, timestamp);
        fNDigis++;
    }
}

void PixelDigitize::SetParContainers()
{
    // Get run and runtime database
    FairRun* run = FairRun::Instance();
    if (!run) {
        LOG(fatal) << "No analysis run";

    } else {
        FairRuntimeDb* db = run->GetRuntimeDb();
        if (!db) {
            LOG(fatal) << "No runtime database";
        } else {
            // Get GEM digitisation parameter container
            fDigiPar = static_cast<PixelDigiPar*>(db->getContainer("PixelDigiParameters"));
        }
    }
}

void PixelDigitize::GetParList(TList* tempList)
{
    fDigiPar = new PixelDigiPar("PixelDigiParameters");
    tempList->Add(fDigiPar);

    return;
}

void PixelDigitize::InitMQ(TList* tempList)
{
    LOG(info) << "********************************************** PixelDigitize::InitMQ()";
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

    fDigis = new TClonesArray("PixelDigi", 10000);

    return;
}

void PixelDigitize::ExecMQ(TList* inputList, TList* outputList)
{
    //  LOG(info) << "********************************************** PixelDigitize::ExecMQ(" << inputList->GetName() <<
    //  "," << outputList->GetName() << "), Event " << fTNofEvents; LOG(info) <<
    //  "********************************************** PixelDigitize::ExecMQ(), Event " << fTNofEvents;
    fPoints = (TClonesArray*)inputList->FindObject("PixelPoint");
    outputList->Add(fDigis);
    Exec("");
    return;
}

InitStatus PixelDigitize::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    if (!ioman)
        LOG(fatal) << "No FairRootManager";
    fPoints = static_cast<TClonesArray*>(ioman->GetObject("PixelPoint"));

    // Register output array StsDigi
    fDigis = new TClonesArray("PixelDigi", 10000);
    ioman->Register("PixelDigis", "Pixel", fDigis, kTRUE);

    LOG(info) << "-I- " << fName.Data() << "::Init(). Initialization succesfull.";

    fFeCols = fDigiPar->GetFECols();
    fFeRows = fDigiPar->GetFERows();
    fMaxFEperCol = fDigiPar->GetMaxFEperCol();
    fPitchX = fDigiPar->GetXPitch();
    fPitchY = fDigiPar->GetYPitch();

    LOG(info) << "PixelDigitize::SetParContainers() Pixel detector with pitch size " << fPitchX << "cm x" << fPitchY
              << "cm";

    return kSUCCESS;
}

InitStatus PixelDigitize::ReInit() { return kSUCCESS; }

void PixelDigitize::Reset()
{
    fNPoints = fNDigis = 0;
    if (fDigis)
        fDigis->Clear();
}

void PixelDigitize::Finish()
{
    if (fDigis)
        fDigis->Delete();

    LOG(info) << "-------------------- " << fName.Data() << " : Summary ------------------------";
    LOG(info) << " Events:        " << fTNofEvents;
    LOG(info) << " MC Points:     " << fTNofPoints << "    ( "
              << static_cast<Double_t>(fTNofPoints) / (static_cast<Double_t>(fTNofEvents)) << " per event )";
    LOG(info) << " Digis:         " << fTNofDigis << "    ( "
              << static_cast<Double_t>(fTNofDigis) / (static_cast<Double_t>(fTNofEvents)) << " per event )";
    LOG(info) << "---------------------------------------------------------------------";
}
