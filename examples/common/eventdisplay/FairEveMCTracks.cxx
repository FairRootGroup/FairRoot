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

#include <FairField.h>
#include <TEveManager.h>
#include <TParticlePDG.h>

FairEveMCTracks::FairEveMCTracks()
    : FairEveTracks()
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
    TEveTrackList *trList = GetTrackGroup(tr);
    Color_t color = GetEventManager()->Color(tr->GetPdgCode());
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
    FairEveTrack *track = new FairEveTrack(&p, tr->GetPdgCode(), fTrPropagator);
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

TEveTrackList *FairEveMCTracks::GetTrackGroup(void *tr)
{
    FairMCTrack *track = static_cast<FairMCTrack *>(tr);
    TString pid = Form("%i", track->GetPdgCode());
    fTrackGroup = nullptr;
    for (Int_t i = 0; i < GetTracksList()->GetEntriesFast(); i++) {
        TEveTrackList *TrListIn = static_cast<TEveTrackList *>(GetTracksList()->At(i));
        TString listName = TrListIn->GetName();
        if (listName.EqualTo(pid)) {
            fTrackGroup = TrListIn;
            break;
        }
    }
    if (fTrackGroup == nullptr) {
        fTrPropagator = new TEveTrackPropagator();
        fTrackGroup = new TEveTrackList(pid, fTrPropagator);
        fTrackGroup->SetMainColor(GetEventManager()->Color(track->GetPdgCode()));
        GetTracksList()->Add(fTrackGroup);
        gEve->AddElement(fTrackGroup, this);
        fTrackGroup->SetRnrLine(kTRUE);
    }
    return fTrackGroup;
}

void FairEveMCTracks::Repaint()
{
    Int_t nTracks = fContainer->GetEntriesFast();
    ResetGroup();
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

FairEveMCTracks::~FairEveMCTracks()
{
    // TODO Auto-generated destructor stub
}
