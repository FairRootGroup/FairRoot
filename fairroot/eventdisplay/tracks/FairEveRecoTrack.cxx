/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveRecoTrack.cxx
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

 #include "FairEveRecoTrack.h"
 #include <TEvePointSet.h>      // for TEvePointSet
 #include <TGeoTrack.h>         // for TGeoTrack
 #include <TMathBase.h>         // for Abs
 #include <TParticle.h>         // for TParticle
 #include "FairEveTrack.h"      // for FairEveTrack
 #include "FairEventManager.h"  // for FairEventManager

FairEveRecoTrack::FairEveRecoTrack()
    : TEveCompound()
    , fHits(nullptr)
    , fNPoints(0)
    , fRecoTrack(nullptr)
    , fMCTrack(nullptr)
{}

FairEveRecoTrack::FairEveRecoTrack(TParticle *t, Int_t label, TEveTrackPropagator *prop)
    : TEveCompound()
    , fHits(nullptr)
    , fNPoints(0)
    , fRecoTrack(new FairEveTrack(t, label, prop))
    , fMCTrack(nullptr)
{
    OpenCompound();
    AddElement(fRecoTrack);
}

void FairEveRecoTrack::AddHit(TVector3 hit)
{
    TVector3 world = FairEventManager::Instance()->GetWorldSize();
    if (TMath::Abs(hit.X()) > world.X())
        return;
    if (TMath::Abs(hit.Y()) > world.Y())
        return;
    if (TMath::Abs(hit.Z()) > world.Z())
        return;
    if (fHits == nullptr) {
        fHits = new TEvePointSet();
        fHits->SetCompound(this);
        fHits->SetMainColor(GetMainColor());
        AddElement(fHits);
    }
    fHits->SetNextPoint(hit.X(), hit.Y(), hit.Z());
}

void FairEveRecoTrack::MakeMCTrack(const TGeoTrack *geo)
{
    if (fMCTrack != nullptr)
        return;
    TParticle *p = static_cast<TParticle *>(geo->GetParticle());
    fMCTrack = new FairEveTrack(p, fRecoTrack->GetLabel(), fRecoTrack->GetPropagator());
    fMCTrack->SetLineColor(fRecoTrack->GetLineColor());
    TVector3 mom(p->Px(), p->Py(), p->Pz());
    const Double_t *posV = geo->GetFirstPoint();
    TVector3 pos(posV[0], posV[1], posV[2]);
    fMCTrack->SetFirstPoint(mom, pos);
    for (int i = 1; i < geo->GetNpoints(); i++) {
        const Double_t *xyz = geo->GetPoint(i);
        pos.SetXYZ(xyz[0], xyz[1], xyz[2]);
        fMCTrack->SetNextPoint(pos);
    }
    fMCTrack->SetLineStyle(10);
    AddElement(fMCTrack);
    CloseCompound();
}

void FairEveRecoTrack::InitMCTrack(const TParticle *p)
{
    if (fMCTrack != nullptr)
        return;
    TParticle *P = new TParticle(*p);
    fMCTrack = new FairEveTrack(P, fRecoTrack->GetLabel(), fRecoTrack->GetPropagator());
    fMCTrack->SetLineColor(fRecoTrack->GetLineColor());
    TVector3 mom(p->Px(), p->Py(), p->Pz());
    TVector3 pos(P->Vx(), P->Vy(), P->Vz());
    fMCTrack->SetFirstPoint(mom, pos);
    fMCTrack->SetLineStyle(10);
    AddElement(fMCTrack);
}

void FairEveRecoTrack::SetMainColor(Color_t color)
{
    TEveCompound::SetMainColor(color);
    if (fRecoTrack)
        fRecoTrack->SetMainColor(color);
    if (fHits)
        fHits->SetMainColor(color);
    if (fMCTrack)
        fMCTrack->SetMainColor(color);
}

FairEveRecoTrack::~FairEveRecoTrack() {}
