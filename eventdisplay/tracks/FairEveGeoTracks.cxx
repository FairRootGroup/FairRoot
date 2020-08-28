/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairGeoTracks.cxx
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveGeoTracks.h"

#include "FairEveTrack.h"

#include <TEveManager.h>
#include <TEveSelection.h>
#include <iostream>

FairEveGeoTracks::FairEveGeoTracks()
    : FairEveTracks()
    , fContainer(nullptr)
    , fShowPrimary(kTRUE)
    , fShowSecondary(kTRUE)
    , fUsePdg(kFALSE)
    , fPdgCut(0)
    , fTMin(0)
    , fTMax(std::numeric_limits<Double_t>::max())
{
    SetElementNameTitle("FairGeoTracks", "FairGeoTracks");
}

InitStatus FairEveGeoTracks::Init()
{
    FairRootManager *mngr = FairRootManager::Instance();
    fContainer = (TClonesArray *)mngr->GetObject("GeoTracks");
    if (fContainer == nullptr)
        return kFATAL;
    return FairEveTracks::Init();
}

void FairEveGeoTracks::DrawTrack(Int_t id)
{
    TGeoTrack *tr = (TGeoTrack *)fContainer->UncheckedAt(id);
    if (!CheckCuts(tr))
        return;
    TParticle *p = (TParticle *)tr->GetParticle();
    TEveTrackList *trList = GetTrackGroup(tr);
    Color_t color = GetEventManager()->Color(p->GetPdgCode());
    FairEveTrack *track = new FairEveTrack(p, p->GetPdgCode(), fTrPropagator);
    track->SetElementTitle(Form("p={%4.3f,%4.3f,%4.3f}", p->Px(), p->Py(), p->Pz()));
    track->SetMainColor(color);
    Double_t x, y, z, t;
    tr->GetPoint(0, x, y, z, t);
    TVector3 pos(x, y, z);
    TVector3 mom(p->Px(), p->Py(), p->Pz());
    track->SetFirstPoint(mom, pos);
    for (int i = 1; i < tr->GetNpoints(); i++) {
        tr->GetPoint(i, x, y, z, t);
        pos.SetXYZ(x, y, z);
        track->SetNextPoint(pos);
    }
    track->SetRnrLine(kTRUE);
    trList->AddElement(track);
}

void FairEveGeoTracks::DrawAnimatedTrack(Int_t id)
{
    const Double_t timeScale = 1E+9;
    TGeoTrack *tr = (TGeoTrack *)fContainer->UncheckedAt(id);
    if (!CheckCuts(tr))
        return;
    if (tr->GetNpoints() < 2)
        return;   // not enought points
    if (tr->GetPoint(0)[3] * timeScale < fTMin)
        return;   // first point before tmin
    if (tr->GetPoint(0)[3] * timeScale > fTMax)
        return;   // first point after tmax
    TParticle *p = (TParticle *)tr->GetParticle();
    TEveTrackList *trList = GetTrackGroup(tr);
    Color_t color = GetEventManager()->Color(p->GetPdgCode());
    FairEveTrack *track = new FairEveTrack(p, p->GetPdgCode(), fTrPropagator);
    track->SetElementTitle(Form("p={%4.3f,%4.3f,%4.3f}", p->Px(), p->Py(), p->Pz()));
    track->SetMainColor(color);
    Double_t x, y, z, t;
    tr->GetPoint(0, x, y, z, t);
    TVector3 pos(x, y, z);
    TVector3 mom(p->Px(), p->Py(), p->Pz());
    track->SetFirstPoint(mom, pos);
    for (int i = 1; i < tr->GetNpoints(); i++) {
        tr->GetPoint(i, x, y, z, t);
        t = t * timeScale;
        if (t > fTMax) {   // outside of time limits

            Double_t xp, yp, zp, tp;
            tr->GetPoint(i - 1, xp, yp, zp, tp);
            tp = tp * timeScale;
            Double_t dT = (fTMax - tp) / (t - tp);
            Double_t dx = x - xp;
            Double_t dy = y - yp;
            Double_t dz = z - zp;
            pos.SetXYZ(xp + dx * dT, yp + dy * dT, zp + dz * dT);
            track->SetNextPoint(pos);
            break;
        } else {
            pos.SetXYZ(x, y, z);
            track->SetNextPoint(pos);
        }
    }
    track->SetRnrLine(kTRUE);
    trList->AddElement(track);
}

void FairEveGeoTracks::Repaint()
{
    Int_t nTracks = fContainer->GetEntriesFast();
    ResetGroup();
    FairEventManager::Instance()->GetTimeLimits(fTMin, fTMax);
    if (fTMin > fTMax) {   // wrong time limits draw entire tracks
        for (int i = 0; i < nTracks; i++) {
            DrawTrack(i);
        }
    } else {
        for (int i = 0; i < nTracks; i++) {
            DrawAnimatedTrack(i);
        }
    }
    gEve->Redraw3D(kFALSE);
}

TEveTrackList *FairEveGeoTracks::GetTrackGroup(void *tr)
{
    TGeoTrack *track = static_cast<TGeoTrack *>(tr);
    TParticle *P = static_cast<TParticle *>(track->GetParticle());
    fTrackGroup = nullptr;
    for (Int_t i = 0; i < GetTracksList()->GetEntriesFast(); i++) {
        TEveTrackList *TrListIn = static_cast<TEveTrackList *>(GetTracksList()->At(i));
        if (strcmp(TrListIn->GetName(), P->GetName()) == 0) {
            fTrackGroup = TrListIn;
            break;
        }
    }
    if (fTrackGroup == nullptr) {
        fTrPropagator = new TEveTrackPropagator();
        fTrackGroup = new TEveTrackList(P->GetName(), fTrPropagator);
        fTrackGroup->SetMainColor(GetEventManager()->Color(P->GetPdgCode()));
        GetTracksList()->Add(fTrackGroup);
        gEve->AddElement(fTrackGroup, this);
        fTrackGroup->SetRnrLine(kTRUE);
    }
    return fTrackGroup;
}

Bool_t FairEveGeoTracks::CheckCuts(TGeoTrack *tr)
{
    TParticle *p = (TParticle *)tr->GetParticle();
    if (UsePtCut()) {
        if (p->Pt() < GetPtMin())
            return kFALSE;
        if (p->Pt() > GetPtMax())
            return kFALSE;
    }
    if (UseEtaCut()) {
        if (p->Eta() < GetEtaMin())
            return kFALSE;
        if (p->Eta() > GetEtaMax())
            return kFALSE;
    }
    if (UseEnergyCut()) {
        if (p->Energy() < GetEnergyMin())
            return kFALSE;
        if (p->Energy() > GetEnergyMax())
            return kFALSE;
    }
    if (fUsePdg) {
        if (p->GetPdgCode() != fPdgCut)
            return kFALSE;
    }
    if (fShowPrimary && p->IsPrimary())
        return kTRUE;
    if (fShowSecondary && !p->IsPrimary())
        return kTRUE;
    return kFALSE;
}

FairEveGeoTracks::~FairEveGeoTracks() {}
