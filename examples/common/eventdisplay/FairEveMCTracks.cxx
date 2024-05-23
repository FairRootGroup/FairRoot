/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include "FairEveTrack.h"       // for FairEveTrack
#include "FairEventManager.h"   // for FairEventManager
#include "FairField.h"          // for FairField
#include "FairMCTrack.h"        // for FairMCTrack
#include "FairRKPropagator.h"   // for FairRKPropagator
#include "FairRootManager.h"    // for FairRootManager
#include "FairRunAna.h"         // for FairRunAna

#include <TClonesArray.h>        // for TClonesArray
#include <TDatabasePDG.h>        // for TDatabasePDG
#include <TEveManager.h>         // for TEveManager, gEve
#include <TEveTrack.h>           // for TEveTrackList
#include <TLorentzVector.h>      // for TLorentzVector
#include <TParticle.h>           // for TParticle
#include <TParticlePDG.h>        // for TParticlePDG
#include <TString.h>             // for Form
#include <TVector3.h>            // for TVector3
#include <fairlogger/Logger.h>   // for LOG

FairEveMCTracks::FairEveMCTracks()
    : FairEveTracks(kFALSE)
    , fShowPrimary(kTRUE)
    , fShowSecondary(kTRUE)
    , fUsePdg(kFALSE)
    , fPdgCut(0)
{
    SetElementNameTitle("FairMCTracks", "FairMCTracks");
}

Bool_t FairEveMCTracks::CheckCuts(FairMCTrack* tr)
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
    if (!fRK)
        return;

    auto tr = static_cast<FairMCTrack*>(fContainer->UncheckedAt(id));
    if (!CheckCuts(tr))
        return;
    Color_t color = GetEventManager()->Color(tr->GetPdgCode());
    TEveTrackList* trList = FindTrackGroup(Form("%i", tr->GetPdgCode()), color);
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
    auto track = new FairEveTrack(&p, tr->GetPdgCode(), trList->GetPropagator());
    track->SetElementTitle(Form("p={%4.3f,%4.3f,%4.3f}", p.Px(), p.Py(), p.Pz()));
    track->SetMainColor(color);
    TVector3 pos(p.Vx(), p.Vy(), p.Vz());
    TVector3 mom(p.Px(), p.Py(), p.Pz());
    track->SetFirstPoint(mom, pos);

    TParticlePDG* part = fPDG->GetParticle(tr->GetPdgCode());

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
    auto status = FairEveTracks::Init();
    if (status != kSUCCESS)
        return status;
    FairEventManager* eveManager = GetEventManager();
    FairRootManager* mngr = &(eveManager->GetRootManager());
    fContainer = dynamic_cast<TClonesArray*>(mngr->GetObject("MCTrack"));
    if (!fContainer) {
        LOG(warning) << "MCTrack branch not found ! FairMCTrackDraw will be deactivated.";
        return kERROR;
    }
    TClass* classTrack = fContainer->GetClass();
    if (classTrack && !classTrack->InheritsFrom("FairMCTrack")) {
        LOG(warning)
            << "MCTrack branch found but does not contain FairMCTrack objects! FairMCTrackDraw will be deactivated.";
        return kERROR;
    }
    FairRunAna* ana = FairRunAna::Instance();
    FairField* field = ana->GetField();
    if (field == nullptr) {
        LOG(warning) << "Lack of magnetic field map!";
    }
    fRK = std::make_unique<FairRKPropagator>(field);
    fPDG = TDatabasePDG::Instance();
    return kSUCCESS;
}

FairEveMCTracks::~FairEveMCTracks() = default;
