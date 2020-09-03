/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCTracks.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairEveMCTracks.h"

#include "FairEveTrack.h"
#include "FairEventManager.h"
#include "FairField.h"
#include "FairMCTrack.h"
#include "FairRKPropagator.h"
#include "FairRootManager.h"
#include "FairRunAna.h"

#include <TClonesArray.h>
#include <TDatabasePDG.h>
#include <TEveManager.h>
#include <TEvePointSet.h>
#include <TEveTrack.h>
#include <TEveTrackPropagator.h>
#include <TLorentzVector.h>
#include <TObjArray.h>
#include <TParticle.h>
#include <TParticlePDG.h>
#include <TString.h>
#include <TVector3.h>

FairEveMCTracks::FairEveMCTracks()
    : FairEveTracks(kFALSE)
    , fContainer(nullptr)
    , fShowPrimary(kTRUE)
    , fShowSecondary(kTRUE)
    , fUsePdg(kFALSE)
    , fPdgCut(0)
    , fRK(nullptr)
    , fPDG(nullptr)
{
    SetElementNameTitle("FairMCTracks", "FairMCTracks");
}

Bool_t FairEveMCTracks::CheckCuts(FairMCTrack *tr)
{
    TLorentzVector mom;
    tr->Get4Momentum(mom);
    if (UsePtCut()) {
        if (tr->GetPt() < GetPtMin())
            return kFALSE;
        if (tr->GetPt() > GetPtMax())
            return kFALSE;
    }
    if (UseEtaCut()) {
        if (mom.Eta() < GetEtaMin())
            return kFALSE;
        if (mom.Eta() > GetEtaMax())
            return kFALSE;
    }
    if (UseEnergyCut()) {
        if (mom.Energy() < GetEnergyMin())
            return kFALSE;
        if (mom.Energy() > GetEnergyMax())
            return kFALSE;
    }
    if (fUsePdg) {
        if (tr->GetPdgCode() != fPdgCut)
            return kFALSE;
    }
    Bool_t primary = kTRUE;
    if (tr->GetMotherId() != -1)
        primary = kFALSE;
    if (fShowPrimary && primary)
        return kTRUE;
    if (fShowSecondary && !primary)
        return kTRUE;
    return kFALSE;
}

void FairEveMCTracks::DrawTrack(Int_t id)
{
    FairMCTrack *tr = (FairMCTrack *)fContainer->UncheckedAt(id);
    if (!CheckCuts(tr))
        return;
    Color_t color = GetEventManager()->Color(tr->GetPdgCode());
    TEveTrackList *trList = FindTrackGroup(Form("%i", tr->GetPdgCode()), color);
    TParticle p(tr->GetPdgCode(),
                0,
                0,
                0,
                0,
                0,
                tr->GetPx(),
                tr->GetPy(),
                tr->GetPz(),
                tr->GetEnergy(),
                tr->GetStartX(),
                tr->GetStartY(),
                tr->GetStartZ(),
                tr->GetStartT());
    FairEveTrack *track = new FairEveTrack(&p, tr->GetPdgCode(), trList->GetPropagator());
    track->SetElementTitle(Form("p={%4.3f,%4.3f,%4.3f}", p.Px(), p.Py(), p.Pz()));
    track->SetMainColor(color);
    TVector3 pos(p.Vx(), p.Vy(), p.Vz());
    TVector3 mom(p.Px(), p.Py(), p.Pz());
    track->SetFirstPoint(mom, pos);

    TParticlePDG *part = fPDG->GetParticle(tr->GetPdgCode());

    Double_t charge = 0;
    if (part) {
        charge = part->Charge() / 3.0;
    }
    Double_t P = 1.0 / mom.Mag();
    Double_t vecRKIn[7] = {pos.X(), pos.Y(), pos.Z(), mom.Px() * P, mom.Py() * P, mom.Pz() * P, 1.0 / P};
    Double_t vec1[3] = {0, 1, 0};
    Double_t vec2[3] = {1, 0, 0};
    Double_t vec3[3] = {0, 0, 0};
    Double_t vecOut[7];
    for (int i = 0; i < 100; i++) {
        vec3[2] = 10. * i;
        fRK->PropagateToPlane(charge, vecRKIn, vec1, vec2, vec3, vecOut);
        pos.SetXYZ(vecOut[0], vecOut[1], vecOut[2]);
        track->SetNextPoint(pos);
    }
    track->SetRnrLine(kTRUE);
    trList->AddElement(track);
}

void FairEveMCTracks::Repaint()
{
    Int_t nTracks = fContainer->GetEntriesFast();
    RemoveElements();
    for (int i = 0; i < nTracks; i++) {
        DrawTrack(i);
    }
    gEve->Redraw3D(kFALSE);
}

InitStatus FairEveMCTracks::Init()
{
    FairRootManager *mngr = FairRootManager::Instance();
    fContainer = (TClonesArray *)mngr->GetObject("MCTrack");
    if (fContainer == nullptr)
        return kFATAL;
    FairRunAna *ana = FairRunAna::Instance();
    FairField *field = ana->GetField();
    if (field == nullptr) {
        LOG(ERROR) << "Lack of magnetic field map!";
        field = new FairField();
    }
    fRK = new FairRKPropagator(field);
    fPDG = TDatabasePDG::Instance();
    return FairEveTracks::Init();
}

FairEveMCTracks::~FairEveMCTracks() {}
