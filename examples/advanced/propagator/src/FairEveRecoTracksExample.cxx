/*
 * FairEveRecoTracksExample.cxx
 *
 *  Created on: 16 cze 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveRecoTracksExample.h"

#include "FairEveRecoTrack.h"
#include "FairEveRecoTrackList.h"
#include "FairEveTrack.h"
#include "FairTutPropHit.h"

#include <FairField.h>
#include <TEveManager.h>
#include <TParticle.h>
#include <TParticlePDG.h>

FairEveRecoTracksExample::FairEveRecoTracksExample()
    : FairEveTracks()
    , fContainerReco(nullptr)
    , fContainerSim(nullptr)
    , fHits1(nullptr)
    , fHits2(nullptr)
    , fShowPrimary(kTRUE)
    , fShowSecondary(kTRUE)
    , fDrawMC(kTRUE)
    , fUsePdg(kFALSE)
    , fPdgCut(0)
    , fRK(nullptr)
    , fPDG(nullptr)
{
    SetElementNameTitle("FairEveRecoTracksExample", "FairEveRecoTracksExample");
}

Bool_t FairEveRecoTracksExample::CheckCuts(FairTutPropTrack *tr)
{
    FairTrackParP par = tr->GetParamFirst();
    TVector3 mom(par.GetPx(), par.GetPy(), par.GetPz());
    if (UsePtCut()) {
        if (mom.Pt() < GetPtMin())
            return kFALSE;
        if (mom.Pt() > GetPtMax())
            return kFALSE;
    }
    if (UseEtaCut()) {
        if (mom.Eta() < GetEtaMin())
            return kFALSE;
        if (mom.Eta() > GetEtaMax())
            return kFALSE;
    }
    // assume pion mass
    Double_t energy = TMath::Sqrt(mom.Mag2() + 0.139 * 0.139);
    if (UseEnergyCut()) {
        if (energy < GetEnergyMin())
            return kFALSE;
        if (energy > GetEnergyMax())
            return kFALSE;
    }
    return kTRUE;
}

void FairEveRecoTracksExample::DrawTrack(Int_t id)
{
    FairTutPropTrack *tr = static_cast<FairTutPropTrack *>(fContainerReco->UncheckedAt(id));
    FairMCTrack *mc = nullptr;   // TODO add MC stuff
    if (!CheckCuts(tr))
        return;
    TEveTrackList *trList = GetTrackGroup(tr);
    FairTrackParP par = tr->GetParamFirst();
    Color_t col = kYellow;
    Int_t dummy_pid = 111;
    if (par.GetQ() < 0) {
        col = kBlue;
        dummy_pid = -211;
    } else if (par.GetQ() > 0) {
        col = kRed;
        dummy_pid = 211;
    }
    TParticle p(
        dummy_pid, 0, 0, 0, 0, 0, par.GetPx(), par.GetPy(), par.GetPz(), 0, par.GetX(), par.GetY(), par.GetZ(), 0);
    FairEveRecoTrack *track = new FairEveRecoTrack(&p, par.GetQ(), fTrPropagator);
    track->SetElementTitle(Form("p={%4.3f,%4.3f,%4.3f}", p.Px(), p.Py(), p.Pz()));
    track->SetMainColor(col);
    TVector3 pos(p.Vx(), p.Vy(), p.Vz());
    TVector3 mom(p.Px(), p.Py(), p.Pz());
    track->GetRecoTrack()->SetFirstPoint(mom, pos);
    Double_t charge = par.GetQ();
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
        track->GetRecoTrack()->SetNextPoint(pos);
    }
    for (int i = 0; i < tr->GetNofHits(); i++) {
        std::pair<int, int> hitid = tr->GetHitIndex(i);
        switch (hitid.first) {
            case 1: {
                FairTutPropHit *hit = static_cast<FairTutPropHit *>(fHits1->UncheckedAt(hitid.second));
                track->AddHit(TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
            } break;
            case 2: {
                FairTutPropHit *hit = static_cast<FairTutPropHit *>(fHits2->UncheckedAt(hitid.second));
                track->AddHit(TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
            } break;
            default:
                break;
        }
    }
    if (fDrawMC && tr->GetMCTrackIndex() >= 0) {
        mc = (FairMCTrack *)fContainerSim->UncheckedAt(tr->GetMCTrackIndex());
        TParticle p_mc(mc->GetPdgCode(),
                       0,
                       0,
                       0,
                       0,
                       0,
                       mc->GetPx(),
                       mc->GetPy(),
                       mc->GetPz(),
                       mc->GetEnergy(),
                       mc->GetStartX(),
                       mc->GetStartY(),
                       mc->GetStartZ(),
                       mc->GetStartT());
        track->InitMCTrack(&p_mc);
        vecRKIn[0] = mc->GetStartX();
        vecRKIn[1] = mc->GetStartY();
        vecRKIn[2] = mc->GetStartZ();
        P = 1.0 / TMath::Sqrt(mc->GetPx() * mc->GetPx() + mc->GetPy() * mc->GetPy() + mc->GetPz() * mc->GetPz());
        vecRKIn[3] = mc->GetPx() * P;
        vecRKIn[4] = mc->GetPy() * P;
        vecRKIn[5] = mc->GetPz() * P;
        vecRKIn[6] = 1.0 / P;
        for (double z = mc->GetStartZ(); z < 100; z++) {
            vec3[2] = z;
            fRK->PropagateToPlane(charge, vecRKIn, vec1, vec2, vec3, vecOut);
            pos.SetXYZ(vecOut[0], vecOut[1], vecOut[2]);
            track->GetMCTrack()->SetNextPoint(pos);
        }
    }
    track->CloseCompound();
    track->GetRecoTrack()->SetRnrLine(kTRUE);
    trList->AddElement(track);
}

TEveTrackList *FairEveRecoTracksExample::GetTrackGroup(void *tr)
{
    FairTutPropTrack *track = static_cast<FairTutPropTrack *>(tr);
    Color_t col = kYellow;
    TString pid = "neutral";
    Int_t q = track->GetParamFirst().GetQ();
    if (q < 0) {
        pid = "neg";
        col = kBlue;
    } else if (q > 0) {
        pid = "pos";
        col = kRed;
    }

    fTrackGroup = nullptr;
    for (Int_t i = 0; i < GetTracksList()->GetEntriesFast(); i++) {
        FairEveRecoTrackList *TrListIn = static_cast<FairEveRecoTrackList *>(GetTracksList()->At(i));
        TString listName = TrListIn->GetName();
        if (listName.EqualTo(pid)) {
            fTrackGroup = TrListIn;
            break;
        }
    }
    if (fTrackGroup == nullptr) {
        fTrPropagator = new TEveTrackPropagator();
        fTrackGroup = new FairEveRecoTrackList(pid, fTrPropagator);
        fTrackGroup->SetMainColor(col);
        GetTracksList()->Add(fTrackGroup);
        gEve->AddElement(fTrackGroup, this);
        fTrackGroup->SetRnrLine(kTRUE);
    }
    return fTrackGroup;
}

void FairEveRecoTracksExample::Repaint()
{
    Int_t nTracks = fContainerReco->GetEntriesFast();
    ResetGroup();
    for (int i = 0; i < nTracks; i++) {
        DrawTrack(i);
    }
    gEve->Redraw3D(kFALSE);
}

InitStatus FairEveRecoTracksExample::Init()
{
    FairRootManager *mngr = FairRootManager::Instance();
    fContainerReco = (TClonesArray *)mngr->GetObject("FairTutPropTracks");
    if (fContainerReco == nullptr) {
        LOG(ERROR) << "Reco traks not found";
        return kFATAL;
    }
    fHits1 = (TClonesArray *)mngr->GetObject("FairTutPropHits");
    fHits2 = (TClonesArray *)mngr->GetObject("FairTutPropHits2");
    if (fHits1 == nullptr || fHits2 == nullptr) {
        LOG(ERROR) << "Hits not found";
        return kFATAL;
    }
    fContainerSim = (TClonesArray *)mngr->GetObject("MCTrack");
    if (fContainerSim == nullptr) {
        LOG(WARNING) << "No branch with MC tracks";
    }
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

void FairEveRecoTracksExample::SetDrawMC(Bool_t draw)
{
    if (fContainerSim) {
        fDrawMC = draw;
    }
}

void FairEveRecoTracksExample::SwapTracks()
{
    for (int i = 0; i < GetTracksList()->GetEntriesFast(); i++) {
        TEveTrackList *eveList = (TEveTrackList *)GetTracksList()->UncheckedAt(i);
        for (TEveElement::List_i iter = eveList->BeginChildren(); iter != eveList->EndChildren(); ++iter) {
            FairEveRecoTrack *el = dynamic_cast<FairEveRecoTrack *>((*iter));
            if (el->GetRnrSelf()) {
                el->SetRnrSelfChildren(kFALSE, kFALSE);
            } else {
                el->SetRnrSelfChildren(kTRUE, kTRUE);
            }
        }
    }
    gEve->Redraw3D(kFALSE);
}

FairEveRecoTracksExample::~FairEveRecoTracksExample()
{
    // TODO Auto-generated destructor stub
}
