/********************************************************************************
 * Copyright (C) 2019-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairTutPropTr.cxx
 *
 * @since 2019-09-10
 * @author R. Karabowicz
 */

#include "FairTutPropTr.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairTrackParP.h"
#include "FairTutPropPoint.h"
#include "TClonesArray.h"
#include "TDatabasePDG.h"

// -----   Default constructor   -------------------------------------------
FairTutPropTr::FairTutPropTr()
    : FairTask("FairTutPropTr")
    , fPropagatorSet(false)
    , fPointArray(0)
    , fTrackParIni(0)
    , fTrackParFinal(0)
    , fTrackParProp(0)
    , fTrackParWrong(0)
    , fPro(0)
{}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutPropTr::~FairTutPropTr()
{
    Reset();
    if (fTrackParIni) {
        fTrackParIni->Delete();
        delete fTrackParIni;
    }
    if (fTrackParProp) {
        fTrackParProp->Delete();
        delete fTrackParProp;
    }
    if (fTrackParWrong) {
        fTrackParWrong->Delete();
        delete fTrackParWrong;
    }
    if (fTrackParFinal) {
        fTrackParFinal->Delete();
        delete fTrackParFinal;
    }
}
// -------------------------------------------------------------------------

// -----   Public method Init   --------------------------------------------
InitStatus FairTutPropTr::Init()
{

    // Get RootManager
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(error) << "FairTutPropTr::Init: RootManager not instantised!";
        return kFATAL;
    }
    fTrackParIni = new TClonesArray("FairTrackParP");
    ioman->Register("PropTrackIni", "Prop", fTrackParIni, kTRUE);

    fTrackParFinal = new TClonesArray("FairTrackParP");
    ioman->Register("PropTrackFinal", "Prop", fTrackParFinal, kTRUE);

    fTrackParProp = new TClonesArray("FairTrackParP");
    ioman->Register("PropTrackPar", "Prop", fTrackParProp, kTRUE);

    fTrackParWrong = new TClonesArray("FairTrackParP");
    ioman->Register("PropTrackParWrong", "Prop", fTrackParWrong, kTRUE);

    // Get input array

    fPointArray = static_cast<TClonesArray*>(ioman->GetObject("FairTutPropPoint"));

    return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Private method InitPropagator   ---------------------------------
void FairTutPropTr::InitPropagator()
{
    TVector3 planePoint(0., 0., 40.);
    TVector3 planeVectJ(1., 0., 0.);
    TVector3 planeVectK(0., 1., 0.);

    fPro->SetDestinationPlane(planePoint, planeVectJ, planeVectK);

    fPropagatorSet = true;
    return;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void FairTutPropTr::Exec(Option_t*)
{
    Reset();

    if (!fPropagatorSet) {
        InitPropagator();
    }

    LOG(debug) << "FairTutPropTr::Exec";

    Int_t NoOfEntries = fPointArray->GetEntriesFast();
    LOG(debug) << "fPointArray has " << NoOfEntries << " entries";
    for (Int_t i = 0; i < NoOfEntries; i++) {
        FairTutPropPoint* point1 = static_cast<FairTutPropPoint*>(fPointArray->At(i));
        if (point1->GetZ() > 15.)
            continue;
        LOG(debug) << "first loop for " << i << "from " << NoOfEntries << " entries ";
        Int_t trId = point1->GetTrackID();
        FairTutPropPoint* point2 = 0;
        for (Int_t k = 0; k < NoOfEntries; k++) {
            point2 = static_cast<FairTutPropPoint*>(fPointArray->At(k));
            if (point2->GetZ() < 35.)
                continue;
            LOG(debug) << "second loop for " << k;
            if (point2->GetTrackID() == trId)
                break;
        }

        if (point2 == 0)
            break;

        TVector3 StartPos(point1->GetX(), point1->GetY(), point1->GetZ());
        TVector3 StartPosErr(0, 0, 0);
        TVector3 StartMom(point1->GetPx(), point1->GetPy(), point1->GetPz());
        TVector3 StartMomErr(0, 0, 0);

        TVector3 EndPos(point2->GetX(), point2->GetY(), point2->GetZ());
        TVector3 EndPosErr(0, 0, 0);
        TVector3 EndMom(point2->GetPx(), point2->GetPy(), point2->GetPz());
        TVector3 EndMomErr(0, 0, 0);

        Int_t PDGCode = -13;

        TDatabasePDG* fdbPDG = TDatabasePDG::Instance();
        TParticlePDG* fParticle = fdbPDG->GetParticle(PDGCode);
        Double_t fCharge = fParticle->Charge();

        TClonesArray& clref1 = *fTrackParIni;
        Int_t size1 = clref1.GetEntriesFast();
        FairTrackParP* fStart = new (clref1[size1]) FairTrackParP(StartPos,
                                                                  StartMom,
                                                                  StartPosErr,
                                                                  StartMomErr,
                                                                  fCharge,
                                                                  TVector3(0., 0., 10.),
                                                                  TVector3(1., 0., 0.),
                                                                  TVector3(0., 1., 0.));
        //  fStart->Print();

        TClonesArray& clref = *fTrackParProp;
        Int_t size = clref.GetEntriesFast();
        FairTrackParP* fRes = new (clref[size]) FairTrackParP();
        // fRes->Print();

        TClonesArray& clrew = *fTrackParWrong;
        Int_t sizeW = clrew.GetEntriesFast();
        FairTrackParP* fWro = new (clrew[sizeW]) FairTrackParP();
        // fRes->Print();

        TClonesArray& clref2 = *fTrackParFinal;
        Int_t size2 = clref2.GetEntriesFast();
        [[gnu::unused]] FairTrackParP* fFinal = new (clref2[size2]) FairTrackParP(EndPos,
                                                                                  EndMom,
                                                                                  EndPosErr,
                                                                                  EndMomErr,
                                                                                  fCharge,
                                                                                  TVector3(0., 0., 40.),
                                                                                  TVector3(1., 0., 0.),
                                                                                  TVector3(0., 1., 0.));

        fPro->Propagate(fStart, fRes, PDGCode);

        // use wrong pdg code
        fPro->Propagate(fStart, fWro, -PDGCode);

        /*
        LOG(info) << "SetPCAPropagation from " << fFinal->GetX() << ", " << fFinal->GetY() << ", " << fFinal->GetZ()
                  << " / " << fFinal->GetPx() << ", " << fFinal->GetPy() << ", " << fFinal->GetPz();
        fPro->SetPCAPropagation(1,-1,fFinal);
        LOG(info) << "FindPCA";
        PCAOutputStruct pcaToPoint = fPro->FindPCA(1, PDGCode, TVector3(2.5,0.5,15.), TVector3(0.,0.,0.),
        TVector3(0.,0.,0.), 15.); LOG(info) << "findpca = " << pcaToPoint.PCAStatusFlag << " with distance " <<
        pcaToPoint.Distance
                  << ", closest point at (" << pcaToPoint.OnTrackPCA.X() << "," << pcaToPoint.OnTrackPCA.Y() << "," <<
        pcaToPoint.OnTrackPCA.Z() << ")";

        PCAOutputStruct pcaToWire = fPro->FindPCA(2, PDGCode, TVector3(0.,0.,0.), TVector3(-10.,-10.,15.),
        TVector3(10.,10.,15.), 15.); LOG(info) << "findpca = " << pcaToWire.PCAStatusFlag << " with distance " <<
        pcaToWire.Distance
                  << ", closest point at (" << pcaToWire.OnTrackPCA.X() << "," << pcaToWire.OnTrackPCA.Y() << "," <<
        pcaToWire.OnTrackPCA.Z() << ")"
                  << ", on the wire (" << pcaToWire.OnWirePCA.X() << "," << pcaToWire.OnWirePCA.Y() << "," <<
        pcaToWire.OnWirePCA.Z() << ")";
        */
    }
}

// -----   Private method Reset   ------------------------------------------
void FairTutPropTr::Reset()
{
    if (fTrackParIni)
        fTrackParIni->Clear();
    if (fTrackParProp)
        fTrackParProp->Clear();
    if (fTrackParWrong)
        fTrackParWrong->Clear();
    if (fTrackParFinal)
        fTrackParFinal->Clear();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void FairTutPropTr::Finish()
{
    if (fTrackParIni)
        fTrackParIni->Delete();
    if (fTrackParProp)
        fTrackParProp->Delete();
    if (fTrackParWrong)
        fTrackParWrong->Delete();
    if (fTrackParFinal)
        fTrackParFinal->Delete();
}
