/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the representation of a track as parabola (SD system)
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
//
// GEANE parameters (q/p, v', w', v, w) of Helix track
// The Helix can be constructed using the Helix parameter (1/p, v', w', v, w) in SC reference
// and the covariance matrix. Or using position and momentum in LAB referance.

#include "FairTrackParP.h"
#include <TGenericClassInfo.h>  // for TGenericClassInfo
#include <TMath.h>              // for Sqrt
#include <TMathBase.h>          // for Abs, Sign
#include <cmath>                // for fabs
#include <iomanip>              // for operator<<, setprecision
#include <iostream>             // for operator<<, basic_ostream, endl, cout
#include "FairGeaneUtil.h"      // for FairGeaneUtil
#include "FairTrackParH.h"      // for FairTrackParH


using std::cout;
using std::endl;

FairTrackParP::FairTrackParP()
    : FairTrackPar()
    , fU(0.)
    , fV(0.)
    , fW(0.)
    , fTV(0.)
    , fTW(0.)
    , fPx_sd(0.)
    , fPy_sd(0.)
    , fPz_sd(0.)
    , fDU(0.)
    , fDV(0.)
    , fDW(0.)
    , fDTV(0.)
    , fDTW(0.)
    , forigin(TVector3(0, 0, 0))
    , fiver(TVector3(0, 0, 0))
    , fjver(TVector3(0, 0, 0))
    , fkver(TVector3(0, 0, 0))
    , fSPU(0.)
{
    // Reset();
    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = 0;
    }
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = 0;
        }
}

// Constructor with track parameters in SD
FairTrackParP::FairTrackParP(Double_t v,
                             Double_t w,
                             Double_t Tv,
                             Double_t Tw,
                             Double_t qp,
                             Double_t CovMatrix[15],
                             TVector3 o,
                             TVector3 dj,
                             TVector3 dk)
    : FairTrackPar()
    , fU(0.)
    , fV(v)
    , fW(w)
    , fTV(Tv)
    , fTW(Tw)
    , fPx_sd(0.)
    , fPy_sd(0.)
    , fPz_sd(0.)
    , fDU(0.)
    , fDV(0.)
    , fDW(0.)
    , fDTV(0.)
    , fDTW(0.)
    , forigin(TVector3(0, 0, 0))
    , fiver(TVector3(0, 0, 0))
    , fjver(TVector3(0, 0, 0))
    , fkver(TVector3(0, 0, 0))
    , fSPU(0.)
{
    // Reset();
    SetPlane(o, dj, dk);
    // fV = v;
    // fW = w;
    //  fTV = Tv;
    //  fTW = Tw;
    fQp = qp;

    Double_t P = TMath::Abs(1 / fQp);
    // fq= int (P * fQp);
    fq = static_cast<int>(TMath::Sign(1.0, fQp));
    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = CovMatrix[i];
    }

    fPx_sd = TMath::Sqrt(P * P / (fTV * fTV + fTW * fTW + 1));
    fPy_sd = fTV * fPx_sd;
    fPz_sd = fTW * fPx_sd;

    // fU = 0.;

    FairGeaneUtil util;
    TVector3 position = util.FromSDToMARSCoord(TVector3(fU, fV, fW), forigin, fiver, fjver, fkver);
    fX = position.X();
    fY = position.Y();
    fZ = position.Z();

    fDQp = TMath::Sqrt(fabs(fCovMatrix[0]));
    fDTV = TMath::Sqrt(fabs(fCovMatrix[5]));
    fDTW = TMath::Sqrt(fabs(fCovMatrix[9]));
    fDV = TMath::Sqrt(fabs(fCovMatrix[12]));
    fDW = TMath::Sqrt(fabs(fCovMatrix[14]));

    Double_t PD[3], RD[6][6], H[3], PC[3], RC[15], SP1;
    Int_t CH;
    PC[0] = fQp;
    PC[1] = fTV;
    PC[2] = fTW;

    for (Int_t i = 0; i < 15; i++) {
        RC[i] = fCovMatrix[i];
    }

    // initialize RD
    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            RD[i][k] = 0;
        }
    }

    // retrieve field
    Double_t pnt[3];
    pnt[0] = fX;
    pnt[1] = fY;
    pnt[2] = fZ;

    GetFieldValue(pnt, H);

    CH = fq;

    TVector3 momsd = TVector3(fPx_sd, fPy_sd, fPz_sd);
    SP1 = (momsd.Dot(fjver.Cross(fkver))) / TMath::Abs(momsd.Dot(fjver.Cross(fkver)));
    fSPU = SP1;

    util.FromSDToMars(PC, RC, H, CH, SP1, fDJ, fDK, PD, RD);

    fPx = PD[0];
    fPy = PD[1];
    fPz = PD[2];

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = RD[i][j];
        }

    fDPx = TMath::Sqrt(fabs(RD[0][0]));
    fDPy = TMath::Sqrt(fabs(RD[1][1]));
    fDPz = TMath::Sqrt(fabs(RD[2][2]));
    fDX = TMath::Sqrt(fabs(RD[3][3]));
    fDY = TMath::Sqrt(fabs(RD[4][4]));
    fDZ = TMath::Sqrt(fabs(RD[5][5]));
}

// Constructor with track parameters in SD
FairTrackParP::FairTrackParP(Double_t v,
                             Double_t w,
                             Double_t Tv,
                             Double_t Tw,
                             Double_t qp,
                             Double_t CovMatrix[15],
                             TVector3 o,
                             TVector3 dj,
                             TVector3 dk,
                             Double_t spu)
    : FairTrackPar()
    , fU(0.)
    , fV(v)
    , fW(w)
    , fTV(Tv)
    , fTW(Tw)
    , fPx_sd(0.)
    , fPy_sd(0.)
    , fPz_sd(0.)
    , fDU(0.)
    , fDV(0.)
    , fDW(0.)
    , fDTV(0.)
    , fDTW(0.)
    , forigin(TVector3(0, 0, 0))
    , fiver(TVector3(0, 0, 0))
    , fjver(TVector3(0, 0, 0))
    , fkver(TVector3(0, 0, 0))
    , fSPU(spu)

{
    //  Reset();
    SetPlane(o, dj, dk);
    //  fV = v;
    //  fW = w;
    //  fTV = Tv;
    //  fTW = Tw;
    fQp = qp;
    //  fSPU = spu;
    Double_t P = 0;
    if (0 != fQp) {
        P = TMath::Abs(1 / fQp);
        fq = static_cast<int>(TMath::Sign(1.0, fQp));
        // fq= int (P * fQp);
    } else {
        fq = 1;
    }
    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = CovMatrix[i];
    }

    fPx_sd = fSPU * TMath::Sqrt(P * P / (fTV * fTV + fTW * fTW + 1));
    fPy_sd = fTV * fPx_sd;
    fPz_sd = fTW * fPx_sd;

    //  fU = 0.;

    FairGeaneUtil util;
    TVector3 position = util.FromSDToMARSCoord(TVector3(fU, fV, fW), forigin, fiver, fjver, fkver);
    fX = position.X();
    fY = position.Y();
    fZ = position.Z();

    fDQp = TMath::Sqrt(fabs(fCovMatrix[0]));
    fDTV = TMath::Sqrt(fabs(fCovMatrix[5]));
    fDTW = TMath::Sqrt(fabs(fCovMatrix[9]));
    fDV = TMath::Sqrt(fabs(fCovMatrix[12]));
    fDW = TMath::Sqrt(fabs(fCovMatrix[14]));

    Double_t PD[3], RD[6][6], H[3], PC[3], RC[15], SP1;
    Int_t CH;
    PC[0] = fQp;
    PC[1] = fTV;
    PC[2] = fTW;

    // initialize RD
    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            RD[i][k] = 0;
        }
    }

    for (Int_t i = 0; i < 15; i++) {
        RC[i] = fCovMatrix[i];
    }

    // retrieve field
    Double_t pnt[3];
    pnt[0] = fX;
    pnt[1] = fY;
    pnt[2] = fZ;

    GetFieldValue(pnt, H);

    CH = fq;

    TVector3 momsd = TVector3(fPx_sd, fPy_sd, fPz_sd);
    //  SP1 = (momsd.Dot(fjver.Cross(fkver)))/TMath::Abs(momsd.Dot(fjver.Cross(fkver)));
    SP1 = fSPU;   // correct calculation of SP1

    util.FromSDToMars(PC, RC, H, CH, SP1, fDJ, fDK, PD, RD);

    fPx = PD[0];
    fPy = PD[1];
    fPz = PD[2];

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = RD[i][j];
        }

    fDPx = TMath::Sqrt(fabs(RD[0][0]));
    fDPy = TMath::Sqrt(fabs(RD[1][1]));
    fDPz = TMath::Sqrt(fabs(RD[2][2]));
    fDX = TMath::Sqrt(fabs(RD[3][3]));
    fDY = TMath::Sqrt(fabs(RD[4][4]));
    fDZ = TMath::Sqrt(fabs(RD[5][5]));
}

// Constructor with track parameters in LAB
FairTrackParP::FairTrackParP(TVector3 pos,
                             TVector3 Mom,
                             TVector3 posErr,
                             TVector3 MomErr,
                             Int_t Q,
                             TVector3 o,
                             TVector3 dj,
                             TVector3 dk)
    : FairTrackPar(pos.x(), pos.y(), pos.z(), Mom.x(), Mom.y(), Mom.z(), Q)
    , fU(0.)
    , fV(0)
    , fW(0)
    , fTV(0)
    , fTW(0)
    , fPx_sd(0.)
    , fPy_sd(0.)
    , fPz_sd(0.)
    , fDU(0.)
    , fDV(0.)
    , fDW(0.)
    , fDTV(0.)
    , fDTW(0.)
    , forigin(TVector3(0, 0, 0))
    , fiver(TVector3(0, 0, 0))
    , fjver(TVector3(0, 0, 0))
    , fkver(TVector3(0, 0, 0))
    , fSPU(0.)
{
    // Reset();
    SetPlane(o, dj, dk);

    SetPx(Mom.x());
    SetPy(Mom.y());
    SetPz(Mom.z());

    SetX(pos.x());   // x (lab)
    SetY(pos.y());   // y (lab)
    SetZ(pos.z());   // z (lab)
    Double_t P = TMath::Sqrt(fPx * fPx + fPy * fPy + fPz * fPz);
    if (Q != 0) {
        fq = Q / TMath::Abs(Q);
    }

    FairGeaneUtil util;
    TVector3 positionsd = util.FromMARSToSDCoord(TVector3(fX, fY, fZ), forigin, fiver, fjver, fkver);
    fU = positionsd.X();
    fV = positionsd.Y();
    fW = positionsd.Z();
    fQp = fq / P;

    fDPx = MomErr.x();   // dpx
    fDPy = MomErr.y();   // dpy
    fDPz = MomErr.z();   // dpz
    fDX = posErr.x();    // dpx
    fDY = posErr.y();    // dpy
    fDZ = posErr.z();    // dpz

    Double_t PD[3], RD[6][6], H[3], SP1, PC[3], RC[15];

    Int_t CH, IERR;

    PD[0] = fPx;
    PD[1] = fPy;
    PD[2] = fPz;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            RD[i][j] = 0.;
        }
    RD[0][0] = fDPx * fDPx;
    RD[1][1] = fDPy * fDPy;
    RD[2][2] = fDPz * fDPz;
    RD[3][3] = fDX * fDX;
    RD[4][4] = fDY * fDY;
    RD[5][5] = fDZ * fDZ;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = RD[i][j];
        }

    // retrieve field
    Double_t pnt[3];
    pnt[0] = fX;
    pnt[1] = fY;
    pnt[2] = fZ;

    GetFieldValue(pnt, H);

    CH = fq;

    util.FromMarsToSD(PD, RD, H, CH, fDJ, fDK, IERR, SP1, PC, RC);

    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = RC[i];
    }

    fTV = PC[1];
    fTW = PC[2];

    fDQp = TMath::Sqrt(fabs(fCovMatrix[0]));
    fDTV = TMath::Sqrt(fabs(fCovMatrix[5]));
    fDTW = TMath::Sqrt(fabs(fCovMatrix[9]));
    fDV = TMath::Sqrt(fabs(fCovMatrix[12]));
    fDW = TMath::Sqrt(fabs(fCovMatrix[14]));

    fSPU = SP1;

    fPx_sd = fSPU * TMath::Sqrt(P * P / (fTV * fTV + fTW * fTW + 1));
    fPy_sd = fTV * fPx_sd;
    fPz_sd = fTW * fPx_sd;
}

// Constructor with track parameters in LAB (with complete covariance matrix in MARS)
FairTrackParP::FairTrackParP(TVector3 pos,
                             TVector3 Mom,
                             Double_t covMARS[6][6],
                             Int_t Q,
                             TVector3 o,
                             TVector3 dj,
                             TVector3 dk)
    : FairTrackPar(pos.x(), pos.y(), pos.z(), Mom.x(), Mom.y(), Mom.z(), Q)
    , fU(0.)
    , fV(0)
    , fW(0)
    , fTV(0)
    , fTW(0)
    , fPx_sd(0.)
    , fPy_sd(0.)
    , fPz_sd(0.)
    , fDU(0.)
    , fDV(0.)
    , fDW(0.)
    , fDTV(0.)
    , fDTW(0.)
    , forigin(TVector3(0, 0, 0))
    , fiver(TVector3(0, 0, 0))
    , fjver(TVector3(0, 0, 0))
    , fkver(TVector3(0, 0, 0))
    , fSPU(0.)
{
    //  Reset();
    SetPlane(o, dj, dk);

    SetPx(Mom.x());
    SetPy(Mom.y());
    SetPz(Mom.z());

    SetX(pos.x());   // x (lab)
    SetY(pos.y());   // y (lab)
    SetZ(pos.z());   // z (lab)
    Double_t P = TMath::Sqrt(fPx * fPx + fPy * fPy + fPz * fPz);
    if (Q != 0) {
        fq = Q / TMath::Abs(Q);
    }

    FairGeaneUtil util;
    TVector3 positionsd = util.FromMARSToSDCoord(TVector3(fX, fY, fZ), forigin, fiver, fjver, fkver);
    fU = positionsd.X();
    fV = positionsd.Y();
    fW = positionsd.Z();
    fQp = fq / P;

    fDPx = TMath::Sqrt(fabs(covMARS[0][0]));   // dpx
    fDPy = TMath::Sqrt(fabs(covMARS[1][1]));   // dpy
    fDPz = TMath::Sqrt(fabs(covMARS[2][2]));   // dpz
    fDX = TMath::Sqrt(fabs(covMARS[3][3]));    // dpx
    fDY = TMath::Sqrt(fabs(covMARS[4][4]));    // dpy
    fDZ = TMath::Sqrt(fabs(covMARS[5][5]));    // dpz

    Double_t PD[3], RD[6][6], H[3], SP1, PC[3], RC[15];
    Int_t IERR, CH;

    PD[0] = fPx;
    PD[1] = fPy;
    PD[2] = fPz;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            RD[i][j] = covMARS[i][j];
        }
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = RD[i][j];
        }

    // retrieve field
    Double_t pnt[3];
    pnt[0] = fX;
    pnt[1] = fY;
    pnt[2] = fZ;

    GetFieldValue(pnt, H);

    CH = fq;

    util.FromMarsToSD(PD, RD, H, CH, fDJ, fDK, IERR, SP1, PC, RC);

    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = RC[i];
    }

    fTV = PC[1];
    fTW = PC[2];

    fDQp = TMath::Sqrt(fabs(fCovMatrix[0]));
    fDTV = TMath::Sqrt(fabs(fCovMatrix[5]));
    fDTW = TMath::Sqrt(fabs(fCovMatrix[9]));
    fDV = TMath::Sqrt(fabs(fCovMatrix[12]));
    fDW = TMath::Sqrt(fabs(fCovMatrix[14]));

    fSPU = SP1;

    fPx_sd = fSPU * TMath::Sqrt(P * P / (fTV * fTV + fTW * fTW + 1));
    fPy_sd = fTV * fPx_sd;
    fPz_sd = fTW * fPx_sd;
}

// ctor from helix to parabola ---------------------------------------------------------------
// -- WARNING -- please pay attention to choose a plane which DOES NOT CONTAIN the TRACK, i.e.
// the plane normal axis u MUST NOT BE ORTHOGONAL to the particle momentum. If this happens
// you will get an error flag:
// IERR = 1 [when the particle moves perpendicular to u-axis (i.e. ON the CHOSEN PLANE)
//          ==> v', w' are not definded.]
FairTrackParP::FairTrackParP(FairTrackParH* helix, TVector3 dj, TVector3 dk, Int_t& ierr)
    : FairTrackPar()
    , fU(0.)
    , fV(0)
    , fW(0)
    , fTV(0)
    , fTW(0)
    , fPx_sd(0.)
    , fPy_sd(0.)
    , fPz_sd(0.)
    , fDU(0.)
    , fDV(0.)
    , fDW(0.)
    , fDTV(0.)
    , fDTW(0.)
    , forigin(TVector3(0, 0, 0))
    , fiver(TVector3(0, 0, 0))
    , fjver(TVector3(0, 0, 0))
    , fkver(TVector3(0, 0, 0))
    , fSPU(0.)
{

    // q/p, lambda, phi --> q/p, v', w'
    Double_t PC[3] = {helix->GetQp(), helix->GetLambda(), helix->GetPhi()};
    Double_t RC[15];
    helix->GetCov(RC);
    // retrieve field
    TVector3 xyz(helix->GetX(), helix->GetY(), helix->GetZ());
    Double_t H[3], pnt[3];
    pnt[0] = xyz.X();
    pnt[1] = xyz.Y();
    pnt[2] = xyz.Z();

    GetFieldValue(pnt, H);

    Int_t CH = helix->GetQ();

    Double_t DJ[3] = {dj.X(), dj.Y(), dj.Z()};
    Double_t DK[3] = {dk.X(), dk.Y(), dk.Z()};

    Int_t IERR = 0;
    Double_t SPU = 0;
    Double_t PD[3], RD[15];

    FairGeaneUtil util;
    util.FromSCToSD(PC, RC, H, CH, DJ, DK, IERR, SPU, PD, RD);

    ierr = IERR;

    // MARS coordinates
    TVector3 o(xyz.X(), xyz.Y(), xyz.Z());
    TVector3 di = dj.Cross(dk);
    TVector3 uvm = util.FromMARSToSDCoord(xyz, o, di, dj, dk);

    if (ierr == 0)
        SetTrackPar(uvm.Y(), uvm.Z(), PD[1], PD[2], PD[0], RD, o, di, dj, dk, SPU);
    else {
        cout << "FairTrackParP(FairTrackParH *) contructor ERROR: CANNOT convert helix to parabola" << endl;
    }
}

// define track in LAB
void FairTrackParP::SetTrackPar(Double_t X,
                                Double_t Y,
                                Double_t Z,
                                Double_t Px,
                                Double_t Py,
                                Double_t Pz,
                                Int_t Q,
                                Double_t CovMatrix[15],
                                TVector3 o,
                                TVector3 /*di*/,
                                TVector3 dj,
                                TVector3 dk)
{
    Reset();
    SetPlane(o, dj, dk);

    Double_t P = TMath::Sqrt(Px * Px + Py * Py + Pz * Pz);

    if (Q != 0) {
        fq = TMath::Abs(Q) / Q;
    }
    fQp = fq / P;

    SetX(X);
    SetY(Y);
    SetZ(Z);

    SetPx(Px);
    SetPy(Py);
    SetPz(Pz);

    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = CovMatrix[i];
    }

    FairGeaneUtil util;

    TVector3 positionsd = util.FromMARSToSDCoord(TVector3(fX, fY, fZ), forigin, fiver, fjver, fkver);
    fU = positionsd.X();
    fV = positionsd.Y();
    fW = positionsd.Z();
    fQp = fq / P;

    Double_t PD[3], RD[6][6], H[3], SP1, PC[3], RC[15];
    Int_t IERR, CH;
    PD[0] = Px;
    PD[1] = Py;
    PD[2] = Pz;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            RD[i][j] = 0.;
        }
    // retrieve field
    Double_t pnt[3];
    pnt[0] = fX;
    pnt[1] = fY;
    pnt[2] = fZ;

    GetFieldValue(pnt, H);

    CH = fq;
    util.FromMarsToSD(PD, RD, H, CH, fDJ, fDK, IERR, SP1, PC, RC);
    fTV = PC[1];
    fTW = PC[2];

    fDQp = TMath::Sqrt(fabs(fCovMatrix[0]));
    fDTV = TMath::Sqrt(fabs(fCovMatrix[5]));
    fDTW = TMath::Sqrt(fabs(fCovMatrix[9]));
    fDV = TMath::Sqrt(fabs(fCovMatrix[12]));
    fDW = TMath::Sqrt(fabs(fCovMatrix[14]));

    for (Int_t i = 0; i < 15; i++) {
        RC[i] = fCovMatrix[i];
    }

    util.FromSDToMars(PC, RC, H, CH, SP1, fDJ, fDK, PD, RD);

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = RD[i][j];
        }

    fDPx = TMath::Sqrt(fabs(RD[0][0]));
    fDPy = TMath::Sqrt(fabs(RD[1][1]));
    fDPz = TMath::Sqrt(fabs(RD[2][2]));
    fDX = TMath::Sqrt(fabs(RD[3][3]));
    fDY = TMath::Sqrt(fabs(RD[4][4]));
    fDZ = TMath::Sqrt(fabs(RD[5][5]));

    fSPU = SP1;
}

// define track in SD
void FairTrackParP::SetTrackPar(Double_t v,
                                Double_t w,
                                Double_t Tv,
                                Double_t Tw,
                                Double_t qp,
                                Double_t CovMatrix[15],
                                TVector3 o,
                                TVector3 /*di*/,
                                TVector3 dj,
                                TVector3 dk,
                                Double_t spu)
{
    Reset();
    SetPlane(o, dj, dk);
    fU = 0;
    fV = v;
    fW = w;
    fTV = Tv;
    fTW = Tw;
    fQp = qp;
    fSPU = spu;

    Double_t P = TMath::Abs(1 / fQp);
    // fq= int (P * fQp);
    fq = static_cast<int>(TMath::Sign(1.0, fQp));
    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = CovMatrix[i];
    }

    fPx_sd = fSPU * TMath::Sqrt(P * P / (fTV * fTV + fTW * fTW + 1));
    fPy_sd = fTV * fPx_sd;
    fPz_sd = fTW * fPx_sd;

    FairGeaneUtil util;
    TVector3 position = util.FromSDToMARSCoord(TVector3(fU, fV, fW), forigin, fiver, fjver, fkver);
    fX = position.X();
    fY = position.Y();
    fZ = position.Z();

    fDQp = TMath::Sqrt(fabs(fCovMatrix[0]));
    fDTV = TMath::Sqrt(fabs(fCovMatrix[5]));
    fDTW = TMath::Sqrt(fabs(fCovMatrix[9]));
    fDV = TMath::Sqrt(fabs(fCovMatrix[12]));
    fDW = TMath::Sqrt(fabs(fCovMatrix[14]));

    Double_t PD[3], RD[6][6], H[3], PC[3], RC[15], SP1;
    Int_t CH;
    PC[0] = fQp;
    PC[1] = fTV;
    PC[2] = fTW;

    for (Int_t i = 0; i < 15; i++) {
        RC[i] = fCovMatrix[i];
    }

    // initialize RD
    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            RD[i][k] = 0;
        }
    }

    // retrieve field
    Double_t pnt[3];
    pnt[0] = fX;
    pnt[1] = fY;
    pnt[2] = fZ;

    GetFieldValue(pnt, H);

    CH = fq;

    TVector3 momsd = TVector3(fPx_sd, fPy_sd, fPz_sd);
    // SP1 = (momsd.Dot(fjver.Cross(fkver)))/TMath::Abs(momsd.Dot(fjver.Cross(fkver)));
    SP1 = fSPU;

    util.FromSDToMars(PC, RC, H, CH, SP1, fDJ, fDK, PD, RD);

    fPx = PD[0];
    fPy = PD[1];
    fPz = PD[2];

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            fCovMatrix66[i][j] = RD[i][j];
        }

    fDPx = TMath::Sqrt(fabs(RD[0][0]));
    fDPy = TMath::Sqrt(fabs(RD[1][1]));
    fDPz = TMath::Sqrt(fabs(RD[2][2]));
    fDX = TMath::Sqrt(fabs(RD[3][3]));
    fDY = TMath::Sqrt(fabs(RD[4][4]));
    fDZ = TMath::Sqrt(fabs(RD[5][5]));
}

void FairTrackParP::CalCov()
{
    // not needed
}

FairTrackParP::~FairTrackParP() {}

void FairTrackParP::Print(Option_t* /*option*/) const
{
    cout << "Position : (";
    cout << std::setprecision(2) << fX << ", " << fY << ", " << fZ << ")" << endl;
    cout << std::setprecision(2) << "Slopes : dx/dz = " << fTV << ", dy/dz = " << fTW << endl;
    cout << std::setprecision(2) << "q/p = " << fQp << endl;
}

/*Double_t FairTrackParP::GetDX()
{ return fDX; }
Double_t FairTrackParP::GetDY()
{ return fDY; }
Double_t FairTrackParP::GetDZ()
{ return fDZ; }
*/

Double_t FairTrackParP::GetV() { return fV; }

Double_t FairTrackParP::GetW() { return fW; }

Double_t FairTrackParP::GetTV() { return fTV; }

Double_t FairTrackParP::GetTW() { return fTW; }

Double_t FairTrackParP::GetDV() { return fDV; }

Double_t FairTrackParP::GetDW() { return fDW; }

Double_t FairTrackParP::GetDTV() { return fDTV; }

Double_t FairTrackParP::GetDTW() { return fDTW; }
/*
Double_t FairTrackParP::GetX()
{
  return fX;
}
Double_t FairTrackParP::GetY()
{
  return fY;
}

Double_t FairTrackParP::GetZ()
{
  return fZ;
}

Double_t FairTrackParP::GetDPx()
{
  return fDPx;
}

Double_t FairTrackParP::GetDPy()
{
  return fDPy;
}

Double_t FairTrackParP::GetDPz()
{
  return fDPz;
}

Double_t FairTrackParP::GetDQp()
{
  return fDQp;
}
*/
TVector3 FairTrackParP::GetOrigin() { return forigin; }

TVector3 FairTrackParP::GetIVer() { return fiver; }

TVector3 FairTrackParP::GetJVer() { return fjver; }

TVector3 FairTrackParP::GetKVer() { return fkver; }

void FairTrackParP::Reset()
{
    fU = 0.;
    fV = 0.;
    fW = 0.;
    fTV = 0.;
    fTW = 0.;
    fDV = 0.;
    fDW = 0.;
    fDTV = 0.;
    fDTW = 0.;
    for (Int_t i = 0; i < 15; i++) {
        fCovMatrix[i] = 0.;
    }
    fPx_sd = 0.;
    fPy_sd = 0.;
    fPz_sd = 0.;

    // base class members
    fX = fY = fZ = 0.;
    fDX = fDY = fDZ = 0.;
    fPx = fPy = fPz = 0.;
    fDPx = fDPy = fDPz = 0.;
    fQp = fDQp = fq = 0;
}

void FairTrackParP::SetPlane(TVector3 o, TVector3 j, TVector3 k)
{
    // origin
    forigin = TVector3(o.X(), o.Y(), o.Z());

    // check unity
    j.SetMag(1.);
    k.SetMag(1.);
    // check orthogonality
    if (j * k != 0) {

        k = (j.Cross(k)).Cross(j);
    }

    // plane
    // i
    TVector3 i = j.Cross(k);
    i.SetMag(1.);
    fDI[0] = i.X();
    fDI[1] = i.Y();
    fDI[2] = i.Z();
    fiver = TVector3(fDI[0], fDI[1], fDI[2]);
    // j
    fDJ[0] = j.X();
    fDJ[1] = j.Y();
    fDJ[2] = j.Z();
    fjver = TVector3(fDJ[0], fDJ[1], fDJ[2]);
    // k
    fDK[0] = k.X();
    fDK[1] = k.Y();
    fDK[2] = k.Z();
    fkver = TVector3(fDK[0], fDK[1], fDK[2]);
}

void FairTrackParP::SetTransportMatrix(Double_t mat[][5])
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            ftrmat[i][j] = mat[i][j];
        }
}

void FairTrackParP::GetTransportMatrix(Double_t mat[][5])
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            mat[i][j] = ftrmat[i][j];
        }
}

void FairTrackParP::GetCovQ(Double_t* CovQ)
{
    // return error matrix in 1/p instead of q/p

    for (int i = 0; i < 15; i++) {
        CovQ[i] = fCovMatrix[i];
        if (fq != 0) {
            if (i == 0) {
                CovQ[i] = CovQ[i] / (fq * fq);
            }
            if (i > 0 && i < 5) {
                CovQ[i] = CovQ[i] / fq;
            }
        }
    }
}
