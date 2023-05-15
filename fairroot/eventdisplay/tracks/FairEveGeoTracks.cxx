/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include "FairEveTrack.h"       // for FairEveTrack
#include "FairEventManager.h"   // for FairEventManager
#include "FairGetEventTime.h"
#include "FairRootManager.h"   // for FairRootManager
#include "FairXMLNode.h"

#include <TBranch.h>
#include <TClonesArray.h>   // for TClonesArray
#include <TEveManager.h>    // for TEveManager, gEve
#include <TEveTrack.h>      // for TEveTrackList
#include <TGeoTrack.h>      // for TGeoTrack
#include <TParticle.h>      // for TParticle
#include <TString.h>        // for Form
#include <TVector3.h>       // for TVector3
#include <iostream>
#include <limits>   // for numeric_limits

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
    FairEventManager* eveManager = FairEventManager::Instance();
    auto& mngr = eveManager->GetRootManager();
    fContainer = dynamic_cast<TClonesArray*>(mngr.GetObject("GeoTracks"));
    if (!fContainer) {
        LOG(warning) << "Geo tracks not found ! FairGeoTracksDraw will be deactivated.";
        return kERROR;
    }
    fBranch = mngr.GetInTree()->GetBranch("GeoTracks");
    FairGetEventTime::Instance().Init();
    TString xmlConfig = eveManager->GetXMLConfig();
    if (xmlConfig.Length() > 4) {
        FairXMLFile file(xmlConfig);
        FairXMLNode* root = file.GetRootNode();
        FairXMLNode* mcColors = root->GetChild("MCTracksColors");
        if (mcColors) {
            fXMLConf = FairXMLPdgColor(mcColors);
        }
    }
    return kSUCCESS;
}

void FairEveGeoTracks::DrawTrack(Int_t id)
{
    auto tr = static_cast<TGeoTrack*>(fContainer->UncheckedAt(id));
    if (!CheckCuts(tr))
        return;
    auto p = static_cast<TParticle*>(tr->GetParticle());
    Color_t color = fXMLConf.GetColor(p->GetPdgCode());
    TEveTrackList* trList = FindTrackGroup(p->GetName(), color);

    auto track = new FairEveTrack(p, p->GetPdgCode(), trList->GetPropagator());
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

void FairEveGeoTracks::DrawAnimatedTrack(TGeoTrack* tr, double t0)
{
    const Double_t timeScale = 1E+9;
    if (!CheckCuts(tr))
        return;
    if (tr->GetNpoints() < 2)
        return;   // not enought points
    if (tr->GetPoint(tr->GetNpoints() - 1)[3] * timeScale + t0 < fTMin)
        return;   // last point before tmin
    if (tr->GetPoint(0)[3] * timeScale + t0 > fTMax)
        return;   // first point after tmax
    auto p = static_cast<TParticle*>(tr->GetParticle());
    Color_t color = fXMLConf.GetColor(p->GetPdgCode());
    TEveTrackList* trList = FindTrackGroup(p->GetName(), color);
    auto track = new FairEveTrack(p, p->GetPdgCode(), trList->GetPropagator());
    track->SetElementTitle(Form("p={%4.3f,%4.3f,%4.3f}", p->Px(), p->Py(), p->Pz()));
    track->SetMainColor(color);
    Double_t x, y, z, t;                       // currentPoint
    Double_t xp = 0, yp = 0, zp = 0, tp = 0;   // previousPoint
    bool firstPoint = true;
    bool previousPoint = false;
    for (int i = 0; i < tr->GetNpoints(); i++) {
        tr->GetPoint(i, x, y, z, t);
        t = t * timeScale + t0;
        TVector3 pos(x, y, z);
        if (t < fTMin) {
            xp = x;
            yp = y;
            zp = z;
            tp = t;
            previousPoint = true;
        } else if (t > fTMin && t < fTMax) {
            if (firstPoint && previousPoint) {
                Double_t dT = (fTMin - tp) / (t - tp);
                Double_t dx = x - xp;
                Double_t dy = y - yp;
                Double_t dz = z - zp;
                pos.SetXYZ(xp + dx * dT, yp + dy * dT, zp + dz * dT);
            }
            if (firstPoint) {
                TVector3 mom(p->Px(), p->Py(), p->Pz());
                track->SetFirstPoint(mom, pos);
                firstPoint = false;
            } else {
                track->SetNextPoint(pos);
            }
            xp = x;
            yp = y;
            zp = z;
            tp = t;
        }
        if (t > fTMax) {   // outside of time limits
            Double_t dT = (fTMax - tp) / (t - tp);
            Double_t dx = x - xp;
            Double_t dy = y - yp;
            Double_t dz = z - zp;
            pos.SetXYZ(xp + dx * dT, yp + dy * dT, zp + dz * dT);
            track->SetNextPoint(pos);
            break;
        }
    }
    track->SetRnrLine(kTRUE);
    trList->AddElement(track);
}

void FairEveGeoTracks::Repaint()
{
    bool useGeoTrackHandler = false;
    if (FairRunAna::Instance()->IsTimeStamp() && fBranch != nullptr) {
        Double_t simTime = FairEventManager::Instance()->GetEvtTime();
        std::pair<int, double> evt = FairGetEventTime::Instance().GetEvent(simTime);

        if (evt.first < 0) {
            fContainer->Clear();
        } else {
            fBranch->GetEvent(evt.first);
        }
        if (FairEventManager::Instance()->GetClearHandler()) {
            fGeoTrackHandler.Reset();
        }
        if (evt.first > -1)
            fGeoTrackHandler.FillTClonesArray(fContainer, evt.first, evt.second, simTime);
        useGeoTrackHandler = true;
    }
    Int_t nTracks = 0;
    if (useGeoTrackHandler) {
        nTracks = fGeoTrackHandler.GetData().size();
    } else {
        nTracks = fContainer->GetEntriesFast();
    }
    RemoveElements();
    FairEventManager::Instance()->GetTimeLimits(fTMin, fTMax);
    if (fTMin > fTMax) {   // wrong time limits draw entire tracks
        for (int iTrack = 0; iTrack < nTracks; iTrack++) {
            DrawTrack(iTrack);
        }
    } else {
        for (int iTrack = 0; iTrack < nTracks; iTrack++) {
            TGeoTrack* track;
            double t0 = .0;
            if (useGeoTrackHandler) {
                track = fGeoTrackHandler.GetData()[iTrack].first;
                t0 = fGeoTrackHandler.GetData()[iTrack].second;
            } else {
                track = static_cast<TGeoTrack*>(fContainer->At(iTrack));
            }
            DrawAnimatedTrack(track, t0);
        }
    }
    gEve->Redraw3D(kFALSE);
}

Bool_t FairEveGeoTracks::CheckCuts(TGeoTrack* tr)
{
    auto p = static_cast<TParticle*>(tr->GetParticle());
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
