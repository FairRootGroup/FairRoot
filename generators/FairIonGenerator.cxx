/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairIonGenerator source file                 -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairIonGenerator.h"

#include "FairIon.h"                // for FairIon
#include "FairLogger.h"             // for logging
#include "FairParticle.h"           // for FairParticle
#include "FairPrimaryGenerator.h"   // for FairPrimaryGenerator
#include "FairRunSim.h"             // for FairRunSim

#include <TDatabasePDG.h>   // for TDatabasePDG
#include <TObjArray.h>      // for TObjArray
#include <TParticle.h>      // for TParticle
#include <TParticlePDG.h>   // for TParticlePDG
#include <cstdio>           // for sprintf

Int_t FairIonGenerator::fgNIon = 0;

FairIonGenerator::FairIonGenerator()
    : FairBaseMCGenerator()
    , fPx(0)
    , fPy(0)
    , fPz(0)
    , fIon(nullptr)
    , fQ(0)
{
    // LOG(warn) << "FairIonGenerator: Please do not use the default constructor!";
}

FairIonGenerator::FairIonGenerator(const Char_t* ionName,
                                   Int_t mult,
                                   Double_t px,
                                   Double_t py,
                                   Double_t pz,
                                   Double_t vx,
                                   Double_t vy,
                                   Double_t vz)
    : FairBaseMCGenerator()
    , fPx(px)
    , fPy(py)
    , fPz(pz)
    , fIon(nullptr)
    , fQ(0)
{
    SetVertex(vx, vy, vz);
    SetMultiplicity(mult);
    FairRunSim* fRun = FairRunSim::Instance();
    TObjArray* UserIons = fRun->GetUserDefIons();
    TObjArray* UserParticles = fRun->GetUserDefParticles();
    FairParticle* part = 0;
    fIon = static_cast<FairIon*>(UserIons->FindObject(ionName));
    if (fIon) {
        fgNIon++;
        fPx = Double_t(fIon->GetA()) * px;
        fPy = Double_t(fIon->GetA()) * py;
        fPz = Double_t(fIon->GetA()) * pz;
    } else {
        part = static_cast<FairParticle*>(UserParticles->FindObject(ionName));
        if (part) {
            fgNIon++;
            TParticle* particle = part->GetParticle();
            fPx = Double_t(particle->GetMass() / 0.92827231) * px;
            fPy = Double_t(particle->GetMass() / 0.92827231) * py;
            fPz = Double_t(particle->GetMass() / 0.92827231) * pz;
        }
    }
    if (fIon == 0 && part == 0) {
        LOG(fatal) << "Ion or Particle is not defined !";
    }
}

FairIonGenerator::FairIonGenerator(Int_t z,
                                   Int_t a,
                                   Int_t q,
                                   Int_t mult,
                                   Double_t px,
                                   Double_t py,
                                   Double_t pz,
                                   Double_t vx,
                                   Double_t vy,
                                   Double_t vz)
    : FairBaseMCGenerator()
    , fPx(Double_t(a) * px)
    , fPy(Double_t(a) * py)
    , fPz(Double_t(a) * pz)
    , fIon(nullptr)
    , fQ(0)
{
    fgNIon++;
    SetVertex(vx, vy, vz);
    SetMultiplicity(mult);
    /*
  fMult = mult;
  fPx   = Double_t(a) * px;
  fPy   = Double_t(a) * py;
  fPz   = Double_t(a) * pz;
  fVx   = vx;
  fVy   = vy;
  fVz   = vz;
  */
    char buffer[20];
    sprintf(buffer, "FairIon%d", fgNIon);
    fIon = new FairIon(buffer, z, a, q);
    FairRunSim* run = FairRunSim::Instance();
    if (!run) {
        LOG(error) << "No FairRun instantised!";
    } else {
        run->AddNewIon(fIon);
    }
}

FairIonGenerator::FairIonGenerator(const FairIonGenerator& rhs)
    : FairBaseMCGenerator(rhs)
    , fPx(rhs.fPx)
    , fPy(rhs.fPy)
    , fPz(rhs.fPz)
    , fIon(rhs.fIon)
    ,   // CHECK
    fQ(0)
{
    // fIon= new FairIon(buffer, z, a, q);
    FairRunSim* run = FairRunSim::Instance();
    if (!run) {
        LOG(error) << "No FairRun instantised!";
    } else {
        run->AddNewIon(fIon);
    }
}

FairIonGenerator::~FairIonGenerator()
{
    // if (fIon) delete fIon;
}

void FairIonGenerator::SetExcitationEnergy(Double_t eExc) { fIon->SetExcEnergy(eExc); }

void FairIonGenerator::SetMass(Double_t mass) { fIon->SetMass(mass); }

Bool_t FairIonGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
    // if ( ! fIon ) {
    //   LOG(warn) << "FairIonGenerator: No ion defined! ";
    //   return kFALSE;
    // }
    GenerateEventParameters();
    TParticlePDG* thisPart = TDatabasePDG::Instance()->GetParticle(fIon->GetName());
    if (!thisPart) {
        LOG(warn) << "FairIonGenerator: Ion " << fIon->GetName() << " not found in database!";
        return kFALSE;
    }

    int pdgType = thisPart->PdgCode();

    for (Int_t i = 0; i < GetMultiplicity(); i++) {
        LOG(debug) << "FairIonGenerator: Generating ion " << fIon->GetName()
                   << Form(" p=(%.2f, %.2f, %.2f) GeV,", fPx, fPy, fPz);
        primGen->AddTrack(pdgType, fPx, fPy, fPz, fX, fY, fZ);
    }

    return kTRUE;
}

FairGenerator* FairIonGenerator::CloneGenerator() const
{
    // Clone for worker (used in MT mode only)

    return new FairIonGenerator(*this);
}

ClassImp(FairIonGenerator);
