/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFindHitsTask.h"

#include "FairGeoParSet.h"
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
#include <fairlogger/Logger.h>

PixelFindHitsTask::PixelFindHitsTask()
    : fGeoParSet(nullptr)
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
    // Reset();
}

PixelFindHitsTask::~PixelFindHitsTask()
{
    // Reset();
}

void PixelFindHitsTask::Reset(TClonesArray* hits)
{
    fNDigis = fNHits = 0;
    if (hits)
        hits->Delete();
}

void PixelFindHitsTask::Finish()
{
    // if (fDigis) fDigis->Delete();

    LOG(info) << "-------------------- PixelFindHitsTask : Summary ------------------------";
    LOG(info) << " Events:        " << fTNofEvents;
    LOG(info) << " Digis:         " << fTNofDigis << "    ("
              << static_cast<Double_t>(fTNofDigis) / (static_cast<Double_t>(fTNofEvents)) << " per event)";
    LOG(info) << " Hits:          " << fTNofHits << "    ("
              << static_cast<Double_t>(fTNofHits) / (static_cast<Double_t>(fTNofEvents)) << " per event)";
    LOG(info) << "---------------------------------------------------------------------";
}

void PixelFindHitsTask::Init(PixelDigiPar* digipar, FairGeoParSet* geopar)
{
    fFeCols = digipar->GetFECols();
    fFeRows = digipar->GetFERows();
    fMaxFEperCol = digipar->GetMaxFEperCol();
    fPitchX = digipar->GetXPitch();
    fPitchY = digipar->GetYPitch();
    fGeoParSet = geopar;
    LOG(info) << "PixelFindHitsTask::Init"
              << " fFeCols=" << fFeCols << " fFeRows=" << fFeRows << " fMaxFEperCol=" << fMaxFEperCol
              << " fPitchX=" << fPitchX << " fPitchY=" << fPitchX;
    LOG(info) << "geopar->printParams()";
    geopar->printParams();
    LOG(info) << "fGeoParSet->printParams()";
    fGeoParSet->printParams();
}

void PixelFindHitsTask::Exec(TClonesArray* digis, TClonesArray* hits)
{
    Reset(hits);

    LOG(info) << "PixelFindHits::Exec(TCA) EVENT " << fTNofEvents;

    fTNofEvents++;
    LOG(debug) << "PixelFindHits::Exec() ok 0 ";
    fNDigis = digis->GetEntriesFast();
    LOG(debug) << "PixelFindHits::Exec() fNDigis = " << fNDigis;
    fTNofDigis += fNDigis;
    //*
    for (Int_t iDigi = 0; iDigi < fNDigis; iDigi++) {
        PixelDigi* currentDigi = (PixelDigi*)digis->At(iDigi);

        Int_t detId = currentDigi->GetDetectorID();
        TString nodeName = Form("/cave/Pixel%d_%d", detId / 256, detId % 256);
        LOG(debug) << "PixelFindHits::Exec() ok 1 node name = " << nodeName.Data();
        fGeoParSet->GetGeometry()->cd(nodeName.Data());
        LOG(debug) << "PixelFindHits::Exec() ok 2 ";
        TGeoNode* curNode = fGeoParSet->GetGeometry()->GetCurrentNode();
        LOG(debug) << "PixelFindHits::Exec() ok 3 ";
        // TGeoMatrix* matrix = curNode->GetMatrix();

        TGeoVolume* actVolume = fGeoParSet->GetGeometry()->GetCurrentVolume();
        TGeoBBox* actBox = (TGeoBBox*)(actVolume->GetShape());

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

        new ((*hits)[fNHits]) PixelHit(detId, currentDigi->GetIndex(), pos, posErr);

        fNHits++;
    }

    fTNofHits += fNHits;
    // return fHits;
}

void PixelFindHitsTask::Exec(TList* list, TClonesArray* hits)
{
    Reset(hits);

    LOG(info) << "PixelFindHits::Exec(TList) EVENT " << fTNofEvents;

    TClonesArray* digis = (TClonesArray*)list->FindObject("PixelDigis");
    if (!digis) {
        LOG(error) << "OOOPS!!! no digis array";
        return;
    }

    fTNofEvents++;
    LOG(debug) << "PixelFindHits::Exec() ok 0 ";
    fNDigis = digis->GetEntriesFast();
    LOG(debug) << "PixelFindHits::Exec() fNDigis = " << fNDigis;
    fTNofDigis += fNDigis;
    //*
    for (Int_t iDigi = 0; iDigi < fNDigis; iDigi++) {
        PixelDigi* currentDigi = static_cast<PixelDigi*>(digis->At(iDigi));

        Int_t detId = currentDigi->GetDetectorID();
        TString nodeName = Form("/cave/Pixel%d_%d", detId / 256, detId % 256);
        LOG(debug) << "PixelFindHits::Exec() ok 1 node name = " << nodeName.Data();
        fGeoParSet->GetGeometry()->cd(nodeName.Data());
        LOG(debug) << "PixelFindHits::Exec() ok 2 ";
        TGeoNode* curNode = fGeoParSet->GetGeometry()->GetCurrentNode();
        LOG(debug) << "PixelFindHits::Exec() ok 3 ";
        //    TGeoMatrix* matrix = curNode->GetMatrix();

        TGeoVolume* actVolume = fGeoParSet->GetGeometry()->GetCurrentVolume();
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

        new ((*hits)[fNHits]) PixelHit(detId, currentDigi->GetIndex(), pos, posErr);

        fNHits++;
    }

    fTNofHits += fNHits;
    // return fHits;
}
