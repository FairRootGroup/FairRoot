/*
 * FairYPtGenerator.cxx
 *
 *  Created on: 6 mar 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairYPtGenerator.h"

#include "FairLogger.h"
#include "FairPrimaryGenerator.h"

#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TParticlePDG.h>
#include <TRandom.h>

FairYPtGenerator::FairYPtGenerator()
    : FairBaseMCGenerator()
    , fYPt()
{}

FairYPtGenerator::FairYPtGenerator(const FairYPtGenerator &base)
    : FairBaseMCGenerator(base)
{
    base.fYPt.Copy(this->fYPt);
    fYPt.SetDirectory(nullptr);
}

FairYPtGenerator &FairYPtGenerator::operator=(const FairYPtGenerator &rhs)
{
    if (&rhs == this)
        return *this;
    FairBaseMCGenerator::operator=(rhs);
    rhs.fYPt.Copy(fYPt);
    fYPt.SetDirectory(nullptr);
    return *this;
}

void FairYPtGenerator::SetYPt(const TH2D &yPt)
{
    yPt.Copy(fYPt);
    fYPt.SetDirectory(nullptr);
}

Bool_t FairYPtGenerator::Init()
{
    if (!FairBaseMCGenerator::Init())
        return kFALSE;
    fYPt.ResetStats();
    for (int i = 1; i <= fYPt.GetNbinsX(); i++) {
        for (int j = 1; j < fYPt.GetNbinsY(); j++) {
            if (fYPt.GetBinContent(i, j) < 0) {
                LOG(fatal) << "FairYPtGenerator negative entries !";
            }
        }
    }
    if (fYPt.GetEntries() == 0) {
        LOG(fatal) << "FairYPtGenerator lack  entries !";
    }
    return kTRUE;
}

Bool_t FairYPtGenerator::ReadEvent(FairPrimaryGenerator *primGen)
{
    Double_t pt, y;
    GenerateEventParameters();
    for (int i = 0; i < GetMultiplicity(); i++) {
        GetYPt(y, pt);
        Double_t e = TMath::Sqrt(pt * pt + GetMass2());
        Double_t phi = gRandom->Uniform(-TMath::Pi(), TMath::Pi());
        Double_t pz = TMath::Sign(e * 0.5, y) * TMath::Exp(-y) * (TMath::Exp(2.0 * y) - 1.0);
        Double_t px = pt * TMath::Cos(phi);
        Double_t py = pt * TMath::Sin(phi);
        LOG(debug) << "FairYPtGenerator:  " << Form("PDG %i p=(%.2f, %.2f, %.2f) GeV,", GetPDGType(), px, py, pz);
        primGen->AddTrack(GetPDGType(), px, py, pz, fX, fY, fZ);
    }
    return kTRUE;
}

FairGenerator *FairYPtGenerator::CloneGenerator() const { return new FairYPtGenerator(*this); }

void FairYPtGenerator::GetYPt(Double_t &y, Double_t &pt) { fYPt.GetRandom2(y, pt); }

FairYPtGenerator::~FairYPtGenerator() {}
