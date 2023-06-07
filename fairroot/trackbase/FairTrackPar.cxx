/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
//      Created by M. Al-Turany  06.02.2007
// -------------------------------------------------------------------------

#include "FairTrackPar.h"
#include <TGenericClassInfo.h>  // for TGenericClassInfo
#include <TMath.h>              // for Sqrt
#include <fairlogger/Logger.h>  // for Logger, LOG
#include "FairField.h"          // for FairField
#include "FairRunAna.h"         // for FairRunAna

FairTrackPar::FairTrackPar()
    : TObject()
    , fX(0.)
    , fY(0.)
    , fZ(0.)
    , fDX(0.)
    , fDY(0.)
    , fDZ(0.)
    , fPx(0.)
    , fPy(0.)
    , fPz(0.)
    , fDPx(0.)
    , fDPy(0.)
    , fDPz(0.)
    , fQp(0.)
    , fDQp(0.)
    , fq(1)
{}

FairTrackPar::FairTrackPar(Double_t x, Double_t y, Double_t z, Double_t px, Double_t py, Double_t pz, Int_t q)

    : TObject()
    , fX(x)
    , fY(y)
    , fZ(z)
    , fDX(x)
    , fDY(y)
    , fDZ(z)
    , fPx(px)
    , fPy(py)
    , fPz(pz)
    , fDPx(px)
    , fDPy(py)
    , fDPz(pz)
    , fQp(0.)
    , fDQp(0.)
    , fq(q)
{

    Double_t p = TMath::Sqrt(fPx * fPx + fPy * fPy + fPz * fPz);
    if (p != 0) {
        fQp = q / p;
    }
}

FairTrackPar::FairTrackPar(Double_t x,
                           Double_t y,
                           Double_t z,
                           Double_t dx,
                           Double_t dy,
                           Double_t dz,
                           Double_t px,
                           Double_t py,
                           Double_t pz,
                           Double_t dpx,
                           Double_t dpy,
                           Double_t dpz,
                           Int_t q)
    : TObject()
    , fX(x)
    , fY(y)
    , fZ(z)
    , fDX(dx)
    , fDY(dy)
    , fDZ(dz)
    , fPx(px)
    , fPy(py)
    , fPz(pz)
    , fDPx(dpx)
    , fDPy(dpy)
    , fDPz(dpz)
    , fQp(0.)
    , fDQp(0.)
    , fq(q)
{
    Double_t p = TMath::Sqrt(fPx * fPx + fPy * fPy + fPz * fPz);
    if (p != 0) {
        fQp = q / p;
    }
}

FairTrackPar::~FairTrackPar() {}

void FairTrackPar::Print(Option_t* /*option*/) const
{
    LOG(info) << "Position :(" << fX << "," << fY << "," << fZ << ")";
    LOG(info) << "Momentum :(" << fPx << "," << fPy << "," << fPz << ")";
}

void FairTrackPar::GetFieldValue(const Double_t point[3], Double_t* bField)
{
    FairRunAna* fRun = FairRunAna::Instance();
    if (fRun->GetField() != 0)
        fRun->GetField()->GetFieldValue(point, bField);
    else {
        bField[0] = .0;
        bField[1] = .0;
        bField[2] = .0;
    }
}
