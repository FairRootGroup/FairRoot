/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// ------------------------------------------------------------------
// Version of June 10th
// modified to work properly in q/p variables  instead of 1/p
// ------------------------------------------------------------------
#include "FairGeaneUtil.h"
#include <TGenericClassInfo.h>  // for TGenericClassInfo
#include <TMath.h>              // for Sqrt, Cos, Sin, Power, ASin, ATan2
#include <TMathBase.h>          // for Abs, Sign
#include <TMatrixT.h>           // for TMatrixT, TMatrixT<>::kMult, operator+
#include <TMatrixTBase.h>       // for TMatrixTBase
#include <TMatrixTUtils.h>      // for TMatrixTRow
#include <string.h>             // for memset
#include <cmath>                // for sqrt, cos, pow, sin, tan


FairGeaneUtil::FairGeaneUtil()
    : TObject()
{}

FairGeaneUtil::~FairGeaneUtil() {}

void FairGeaneUtil::FromPtToSC(Double_t PC[3],
                               Double_t RC[15],
                               //     output
                               Double_t* PD,
                               Double_t* RD,
                               Int_t& IERR)
{

    // -------------------------------------------------------------
    //
    //      TRANSFORM ERROR MATRIX
    //
    //      FROM   SC   VARIABLES (q/Pt,LAMBDA,PHI,YT,ZT)
    //      FROM   SC   VARIABLES (q/P,LAMBDA,PHI,YT,ZT)
    //
    //                         INPUT
    //      CH      Charge of the paticle
    //      PC[3]   (q/Pt, Lambda, Phi, Yt, Zt)
    //      RC[15]  error matrix in upper triangular form
    //
    //                         OUTPUT
    //      PD[3]   (q/P, Lambda, Phi, Yt, Zt)
    //      RD[15]  error matrix in upper triangular form
    //      IERR    =1 when track is perp to X-axis of Master
    //
    //     Author EMC Collaboration
    //     Translated in C/Rot by A. Rotondi (June 2007)
    //
    // -------------------------------------------------------------------

    Double_t A[5][5], S[15], COSL, SINL;
    Double_t Vec[25];

    IERR = 0;
    memset(RD, 0, sizeof(*RD));

    COSL = cos(PC[1]);

    if (TMath::Abs(COSL) < 1.e-7) {
        IERR = 1;
        return;
    }

    SINL = sin(PC[1]);

    PD[0] = PC[0] * COSL;
    PD[1] = PC[1];
    PD[2] = PC[2];

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }

    // copy input in an internal vector S
    for (Int_t I = 0; I < 15; I++) {
        S[I] = RC[I];
    }

    A[0][0] = COSL;
    A[1][1] = 1.0;
    A[2][2] = 1.0;
    A[3][3] = 1.0;
    A[4][4] = 1.0;

    A[0][1] = -PC[0] * SINL;

    // transformation
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // copy the result in S in the output vector
    for (Int_t I = 0; I < 15; I++) {
        RD[I] = S[I];
    }
}

void FairGeaneUtil::FromPtToSD(Double_t PD[3],
                               Double_t RD[15],
                               Double_t H[3],
                               Int_t CH,
                               Double_t SPU,
                               Double_t DJ[3],
                               Double_t DK[3],
                               // output
                               Int_t& IERR,
                               Double_t* PC,
                               Double_t* RC)
{

    //
    // **************************************************************************
    //
    //  *** TRANSFORMS ERROR MATRIX
    //      FROM        VARIABLES (q/Pt,V',W',V,W)
    //      FROM        VARIABLES (q/P, V',W',V,W)
    //
    //                         input
    //      PD[3]   (q/P, Lambda, Phi, Yt, Zt)
    //      RD[15]  error matrix in upper triangular form
    //      H[3]    magnetic field
    //      CH        CHARGE OF PARTICLE
    //                CHARGE AND MAGNETIC FIELD ARE NEEDED
    //                FOR CORRELATION TERMS (V',YT),(V',ZT),(W',YT),(W',ZT)
    //                THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
    //                TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
    //                AND RD FOR FIXED U
    //      SPU       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM
    //                spu = sign[p·(DJ x DK)]
    //      DJ[3]     UNIT VECTOR IN V-DIRECTION
    //      DK[3]     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM
    //
    //                         output
    //      PC[3]   (q/Pt, Lambda, Phi, Yt, Zt)
    //      RC[15]  error matrix in upper triangular form
    //      IERR    =1 when track is perp to X-axis of Master
    //
    //     Author EMC Collaboration
    //     Translated in C/Rot by A. Rotondi (June 2007)
    //
    // -------------------------------------------------------------------
    //

    Double_t A[5][5], S[15], TN[3], COSL, SINL, COSL1;

    Double_t PM, HM, UN[3], VN[3], DI[3], TVW[3];
    Double_t /* UJ, */ /* UK, */ VJ, VK, HA, HAM, Q, SINZ /* , COSZ */;

    Double_t CFACT8 = 2.997925e-04;

    Double_t Vec[25];

    // ------------------------------------------------------------------

    IERR = 0;
    TVW[0] = 1. / TMath::Sqrt(1. + PD[1] * PD[1] + PD[2] * PD[2]);
    if (SPU < 0.) {
        TVW[0] = -TVW[0];
    }
    TVW[1] = PD[1] * TVW[0];
    TVW[2] = PD[2] * TVW[0];

    DI[0] = DJ[1] * DK[2] - DJ[2] * DK[1];
    DI[1] = DJ[2] * DK[0] - DJ[0] * DK[2];
    DI[2] = DJ[0] * DK[1] - DJ[1] * DK[0];

    for (Int_t I = 0; I < 3; I++) {
        TN[I] = TVW[0] * DI[I] + TVW[1] * DJ[I] + TVW[2] * DK[I];
    }

    COSL = TMath::Sqrt(TMath::Abs(1. - TN[2] * TN[2]));
    if (COSL < 1.e-30) {
        COSL = 1.e-30;
    }
    COSL1 = 1. / COSL;
    SINL = TN[2];

    PC[0] = PD[0] * COSL;
    PC[1] = PD[1];
    PC[2] = PD[2];
    PM = PC[0];

    if (TMath::Abs(TN[0]) < 1.E-30) {
        TN[0] = 1.e-30;
    }

    UN[0] = -TN[1] * COSL1;
    UN[1] = TN[0] * COSL1;
    UN[2] = 0.;

    VN[0] = -TN[2] * UN[1];
    VN[1] = TN[2] * UN[0];
    VN[2] = COSL;

    // UJ=UN[0]*DJ[0]+UN[1]*DJ[1]+UN[2]*DJ[2];
    // UK=UN[0]*DK[0]+UN[1]*DK[1]+UN[2]*DK[2];
    VJ = VN[0] * DJ[0] + VN[1] * DJ[1] + VN[2] * DJ[2];
    VK = VN[0] * DK[0] + VN[1] * DK[1] + VN[2] * DK[2];

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }

    // copy input in an internal vector S
    for (Int_t I = 0; I < 15; I++) {
        S[I] = RD[I];
    }

    if (CH != 0.) {
        HA = TMath::Sqrt(H[0] * H[0] + H[1] * H[1] + H[2] * H[2]);
        HAM = HA * PM;
        if (HAM != 0.) {
            HM = CH / HA;

            Q = -HAM * CFACT8;

            SINZ = -(H[0] * UN[0] + H[1] * UN[1] + H[2] * UN[2]) * HM;
            // COSZ= (H[0]*VN[0]+H[1]*VN[1]+H[2]*VN[2])*HM;
            A[0][3] = Q * TVW[1] * SINZ * (SINL * PD[0]);
            A[0][4] = Q * TVW[2] * SINZ * (SINL * PD[0]);
        }
    }

    A[0][0] = COSL;
    A[1][1] = 1.;
    A[2][2] = 1.;
    A[3][3] = 1.;
    A[4][4] = 1.;

    A[0][1] = -TVW[0] * VJ * (SINL * PD[0]);
    A[0][2] = -TVW[0] * VK * (SINL * PD[0]);

    // transformation
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // copy the result in S in the output vector
    for (Int_t I = 0; I < 15; I++) {
        RC[I] = S[I];
    }
}

void FairGeaneUtil::FromSCToPt(Double_t PC[3],
                               Double_t RC[15],
                               //  output
                               Double_t* PD,
                               Double_t* RD,
                               Int_t& IERR)
{

    // -------------------------------------------------------------
    //
    //      TRANSFORM ERROR MATRIX
    //
    //      FROM   SC   VARIABLES (q/P,LAMBDA,PHI,YT,ZT)
    //      FROM   SC   VARIABLES (q/Pt,LAMBDA,PHI,YT,ZT)
    //
    //                         INPUT
    //      PC[3]   (q/P, Lambda, Phi, Yt, Zt)
    //      RC[15]  error matrix in upper triangular form
    //
    //                         OUTPUT
    //      PD[3]   (q/Pt, Lambda, Phi, Yt, Zt)
    //      RD[15]  error matrix in upper triangular form
    //      IERR    =1 when track is perp to X-axis of Master
    //
    //     Author EMC Collaboration
    //     Translated in C/Rot by A. Rotondi (June 2007)
    //
    // -------------------------------------------------------------------

    Double_t A[5][5], S[15], COSL, COSL1;
    Double_t TANL;
    Double_t Vec[25];

    IERR = 0;
    memset(RD, 0, sizeof(*RD));

    COSL = cos(PC[1]);
    if (TMath::Abs(COSL) < 1.e-7) {
        IERR = 1;
        return;
    }
    COSL1 = 1. / COSL;
    TANL = tan(PC[1]);

    PD[0] = PC[0] * COSL1;
    PD[1] = PC[1];
    PD[2] = PC[2];

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }

    // copy input in an internal vector S
    for (Int_t I = 0; I < 15; I++) {
        S[I] = RC[I];
    }

    A[0][0] = COSL1;
    A[1][1] = 1.0;
    A[2][2] = 1.0;
    A[3][3] = 1.0;
    A[4][4] = 1.0;

    A[0][1] = PD[0] * TANL;

    // transformation
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // copy the result in S in the output vector
    for (Int_t I = 0; I < 15; I++) {
        RD[I] = S[I];
    }
}

void FairGeaneUtil::FromSCToSD(Double_t PC[3],
                               Double_t RC[15],
                               Double_t H[3],
                               Int_t CH,
                               Double_t DJ[3],
                               Double_t DK[3],
                               //    output
                               Int_t& IERR,
                               Double_t& SPU,
                               Double_t* PD,
                               Double_t* RD)
{

    // ----------------------------------------------------------------------
    //      Transform Error Matrix
    //      FROM   SC  (transverse system)  VARIABLES (q/P,LAMBDA,PHI,YT,ZT)
    //      TO     SD  (detector system)    VARIABLES (q/P,V',W',V,W)

    //      Authors: A. Haas and W. Wittek
    //      Translated in CRoot by A. Rotondi and A. Fontana June 2007

    //                                   INPUT
    //      PC(3)     q/P,LAMBDA,PHI
    //      H(3)      MAGNETIC FIELD
    //      RC(15)    ERROR MATRIX IN   SC   VARIABLES   (TRIANGLE)
    //      CH        CHARGE OF PARTICLE
    //                CHARGE AND MAGNETIC FIELD ARE NEEDED
    //                FOR CORRELATION TERMS (V',YT),(V',ZT),(W',YT),(W',ZT)
    //                THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
    //                TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
    //                AND RD FOR FIXED U
    //      DJ(3)     UNIT VECTOR IN V-DIRECTION
    //      DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM

    //                                   OUTPUT
    //      RD(15)    ERROR MATRIX IN q/P,V',W',V,W   (TRIANGLE)
    //      PD(3)     q/P,V',W'
    //      IERR  =   1       PARTICLE MOVES PERPENDICULAR TO U-AXIS
    //                       ( V',W' ARE NOT DEFINED )
    //      SPU       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM
    //                spu = sign[p·(DJ x DK)]
    //
    // ------------------------------------------------------------------------

    Double_t A[5][5], S[15], TN[3], COSL, COSP;
    Double_t UN[3], VN[3], DI[3], TVW[3];

    Double_t Vec[25];
    Double_t CFACT8 = 2.997925e-04;
    Double_t T1R, T2R, T3R, SINP, SINZ, COSZ, HA, HM, HAM;
    Double_t Q, UI, VI, UJ, UK, VJ, VK;

    IERR = 0;
    memset(RD, 0, sizeof(*RD));
    memset(PD, 0, sizeof(*PD));

    COSL = TMath::Cos(PC[1]);
    SINP = TMath::Sin(PC[2]);
    COSP = TMath::Cos(PC[2]);

    TN[0] = COSL * COSP;
    TN[1] = COSL * SINP;
    TN[2] = TMath::Sin(PC[1]);

    // DI = DJ x DK
    DI[0] = DJ[1] * DK[2] - DJ[2] * DK[1];
    DI[1] = DJ[2] * DK[0] - DJ[0] * DK[2];
    DI[2] = DJ[0] * DK[1] - DJ[1] * DK[0];

    TVW[0] = TN[0] * DI[0] + TN[1] * DI[1] + TN[2] * DI[2];
    SPU = 1.;
    if (TVW[0] < 0.) {
        SPU = -1.;
    }
    TVW[1] = TN[0] * DJ[0] + TN[1] * DJ[1] + TN[2] * DJ[2];
    TVW[2] = TN[0] * DK[0] + TN[1] * DK[1] + TN[2] * DK[2];

    // track lies in the detector plane: stop calculations
    if (TMath::Abs(TVW[0]) < 1.e-7) {
        IERR = 1;
        return;
    }

    T1R = 1. / TVW[0];
    PD[0] = PC[0];
    PD[1] = TVW[1] * T1R;
    PD[2] = TVW[2] * T1R;

    UN[0] = -SINP;
    UN[1] = COSP;
    UN[2] = 0.;

    VN[0] = -TN[2] * UN[1];
    VN[1] = TN[2] * UN[0];
    VN[2] = COSL;

    UJ = UN[0] * DJ[0] + UN[1] * DJ[1] + UN[2] * DJ[2];
    UK = UN[0] * DK[0] + UN[1] * DK[1] + UN[2] * DK[2];
    VJ = VN[0] * DJ[0] + VN[1] * DJ[1] + VN[2] * DJ[2];
    VK = VN[0] * DK[0] + VN[1] * DK[1] + VN[2] * DK[2];

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }

    // copy input in an internal vector S
    for (Int_t I = 0; I < 15; I++) {
        S[I] = RC[I];
    }

    if (CH != 0.) {
        // charged particles
        HA = TMath::Sqrt(H[0] * H[0] + H[1] * H[1] + H[2] * H[2]);
        HAM = HA * PC[0];
        if (HAM != 0.) {
            // ... in a magnetic field
            HM = CH / HA;
            Q = -HAM * CFACT8;
            SINZ = -(H[0] * UN[0] + H[1] * UN[1] + H[2] * UN[2]) * HM;
            COSZ = (H[0] * VN[0] + H[1] * VN[1] + H[2] * VN[2]) * HM;
            T3R = Q * pow(T1R, 3);
            UI = UN[0] * DI[0] + UN[1] * DI[1] + UN[2] * DI[2];
            VI = VN[0] * DI[0] + VN[1] * DI[1] + VN[2] * DI[2];
            A[1][3] = -UI * (VK * COSZ - UK * SINZ) * T3R;
            A[1][4] = -VI * (VK * COSZ - UK * SINZ) * T3R;
            A[2][3] = UI * (VJ * COSZ - UJ * SINZ) * T3R;
            A[2][4] = VI * (VJ * COSZ - UJ * SINZ) * T3R;
        }
    }

    T2R = T1R * T1R;

    // Transformation matrix from SC to SD

    A[0][0] = 1.;
    A[1][1] = -UK * T2R;
    A[1][2] = VK * COSL * T2R;
    A[2][1] = UJ * T2R;
    A[2][2] = -VJ * COSL * T2R;
    A[3][3] = VK * T1R;
    A[3][4] = -UK * T1R;
    A[4][3] = -VJ * T1R;
    A[4][4] = UJ * T1R;

    // transformation
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // copy the result in S in the output vector
    for (Int_t I = 0; I < 15; I++) {
        RD[I] = S[I];
    }
}

void FairGeaneUtil::FromSD1ToSD2(Double_t PD1[3],
                                 Double_t RD1[15],
                                 Double_t H[3],
                                 Int_t CH,
                                 Double_t SP1,
                                 Double_t DJ1[3],
                                 Double_t DK1[3],
                                 Double_t DJ2[3],
                                 Double_t DK2[3],
                                 //           output
                                 Int_t& IERR,
                                 Double_t& SP2,
                                 Double_t* PD2,
                                 Double_t* RD2)
{

    // -------------------------------------------------------------------------
    //
    //      TRANSFORMS ERROR MATRIX
    //      FROM        VARIABLES (q/P,V1',W1',V1,W1)
    //       TO         VARIABLES (q/P,V2',W2',V2,W2)
    //
    //      Authors: A. Haas and W. Wittek
    //      Translated in C/Root by A. Fontana and A. Rotondi (June 2007)
    //
    //
    //                                      INPUT
    //      PD1[3]    q/P,V1',W1'
    //      H[3]      MAGNETIC FIELD
    //      RD1(15)   ERROR MATRIX IN 1/P,V1',W1',V1,W1   (Triangular)
    //      CH        CHARGE OF PARTICLE
    //                CHARGE AND MAGNETIC FIELD ARE NEEDED
    //                FOR CORRELATION TERMS (V2',V1),(V2',W1),(W2',V1),(W2',W1)
    //                THESE CORRELATION TERMS APPEAR BECAUSE RD1 IS ASSUMED
    //                TO BE THE ERROR MATRIX FOR FIXED U1
    //                AND RD2 FOR FIXED U2
    //      SP1       SIGN OF U1-COMPONENT OF PARTICLE MOMENTUM     INPUT
    //      DJ1[3]    UNIT VECTOR IN V1-DIRECTION
    //      DK1[3]    UNIT VECTOR IN W1-DIRECTION    OF SYSTEM 1
    //      DJ2[3]    UNIT VECTOR IN V2-DIRECTION
    //      DK2[3]    UNIT VECTOR IN W2-DIRECTION    OF SYSTEM 2
    //
    //
    //                                 OUTPUT
    //      PD2[3]    q/P,V2',W2'
    //      RD2[15]   ERROR MATRIX IN 1/P,V2',W2',V2,W2   (Triangular)
    //      SP2       SIGN OF U2-COMPONENT OF PARTICLE MOMENTUM    OUTPUT
    //      IERR      = 0    TRANSFORMATION OK
    //                = 1    MOMENTUM PERPENDICULAR TO U2-DIRECTION
    //                       (V2',W2' NOT DEFINed)
    //                = 2    MOMENTUM PERPENDICULAR TO X-AXIS
    //
    // ----------------------------------------------------------------------

    Double_t A[5][5], S[15], TN[3], COSL, COSL1;
    Double_t SINZ, COSZ, UN[3], VN[3];

    Double_t Vec[25];
    Double_t PM, TR, TS, TT, HA, HM, HAM, Q;
    Double_t UJ1, UK1, UJ2, UK2, VJ1, VJ2, VK1, VK2;
    Double_t SJ1I2, SK1I2, SK2U, SK2V, SJ2U, SJ2V;
    Double_t DI1[3], DI2[3], TVW1[3], TVW2[3];
    Double_t CFACT8 = 2.997925e-04;

    IERR = 0;
    memset(PD2, 0, sizeof(*PD2));
    memset(RD2, 0, sizeof(*RD2));

    PM = PD1[0];
    TVW1[0] = 1. / sqrt(1. + PD1[1] * PD1[1] + PD1[2] * PD1[2]);
    if (SP1 < 0.) {
        TVW1[0] = -TVW1[0];
    }
    TVW1[1] = PD1[1] * TVW1[0];
    TVW1[2] = PD1[2] * TVW1[0];

    DI1[0] = DJ1[1] * DK1[2] - DJ1[2] * DK1[1];
    DI1[1] = DJ1[2] * DK1[0] - DJ1[0] * DK1[2];
    DI1[2] = DJ1[0] * DK1[1] - DJ1[1] * DK1[0];

    for (Int_t I = 0; I < 3; I++) {
        TN[I] = TVW1[0] * DI1[I] + TVW1[1] * DJ1[I] + TVW1[2] * DK1[I];
    }

    DI2[0] = DJ2[1] * DK2[2] - DJ2[2] * DK2[1];
    DI2[1] = DJ2[2] * DK2[0] - DJ2[0] * DK2[2];
    DI2[2] = DJ2[0] * DK2[1] - DJ2[1] * DK2[0];

    TVW2[0] = TN[0] * DI2[0] + TN[1] * DI2[1] + TN[2] * DI2[2];
    TVW2[1] = TN[0] * DJ2[0] + TN[1] * DJ2[1] + TN[2] * DJ2[2];
    TVW2[2] = TN[0] * DK2[0] + TN[1] * DK2[1] + TN[2] * DK2[2];

    if (TMath::Abs(TVW2[0]) < 1.e-7) {
        // track lies in the v-w plane: stop calculations
        IERR = 1;
        return;
    }
    TR = 1. / TVW2[0];
    SP2 = 1;
    if (TVW2[0] < 0.) {
        SP2 = -1;
    }
    PD2[0] = PD1[0];
    PD2[1] = TVW2[1] * TR;
    PD2[2] = TVW2[2] * TR;

    COSL = sqrt(TMath::Abs(1. - TN[2] * TN[2]));
    if (TMath::Abs(COSL) < 1.e-7) {
        //  track perp to X-axis of Master: stop calculations
        IERR = 2;
        return;
    }
    COSL1 = 1. / COSL;
    UN[0] = -TN[1] * COSL1;
    UN[1] = TN[0] * COSL1;
    UN[2] = 0.;

    VN[0] = -TN[2] * UN[1];
    VN[1] = TN[2] * UN[0];
    VN[2] = COSL;

    UJ1 = UN[0] * DJ1[0] + UN[1] * DJ1[1] + UN[2] * DJ1[2];
    UK1 = UN[0] * DK1[0] + UN[1] * DK1[1] + UN[2] * DK1[2];
    VJ1 = VN[0] * DJ1[0] + VN[1] * DJ1[1] + VN[2] * DJ1[2];
    VK1 = VN[0] * DK1[0] + VN[1] * DK1[1] + VN[2] * DK1[2];

    UJ2 = UN[0] * DJ2[0] + UN[1] * DJ2[1] + UN[2] * DJ2[2];
    UK2 = UN[0] * DK2[0] + UN[1] * DK2[1] + UN[2] * DK2[2];
    VJ2 = VN[0] * DJ2[0] + VN[1] * DJ2[1] + VN[2] * DJ2[2];
    VK2 = VN[0] * DK2[0] + VN[1] * DK2[1] + VN[2] * DK2[2];

    // reset working vectors and matrices
    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }
    for (Int_t J = 0; J < 15; J++) {
        S[J] = RD1[J];
    }

    if (CH != 0.) {
        // a charged particle
        HA = sqrt(H[0] * H[0] + H[1] * H[1] + H[2] * H[2]);
        HAM = HA * PM;
        if (HAM != 0.) {
            // ...in a magnetic field
            HM = CH / HA;
            Q = -HAM * CFACT8;
            TT = -Q * pow(TR, 3);
            SJ1I2 = DJ1[0] * DI2[0] + DJ1[1] * DI2[1] + DJ1[2] * DI2[2];
            SK1I2 = DK1[0] * DI2[0] + DK1[1] * DI2[1] + DK1[2] * DI2[2];
            SK2U = DK2[0] * UN[0] + DK2[1] * UN[1] + DK2[2] * UN[2];
            SK2V = DK2[0] * VN[0] + DK2[1] * VN[1] + DK2[2] * VN[2];
            SJ2U = DJ2[0] * UN[0] + DJ2[1] * UN[1] + DJ2[2] * UN[2];
            SJ2V = DJ2[0] * VN[0] + DJ2[1] * VN[1] + DJ2[2] * VN[2];

            SINZ = -(H[0] * UN[0] + H[1] * UN[1] + H[2] * UN[2]) * HM;
            COSZ = (H[0] * VN[0] + H[1] * VN[1] + H[2] * VN[2]) * HM;
            A[1][3] = -TT * SJ1I2 * (SK2U * SINZ - SK2V * COSZ);
            A[1][4] = -TT * SK1I2 * (SK2U * SINZ - SK2V * COSZ);
            A[2][3] = TT * SJ1I2 * (SJ2U * SINZ - SJ2V * COSZ);
            A[2][4] = TT * SK1I2 * (SJ2U * SINZ - SJ2V * COSZ);
        }
    }
    A[0][0] = 1.;
    A[3][3] = TR * (UJ1 * VK2 - VJ1 * UK2);
    A[3][4] = TR * (UK1 * VK2 - VK1 * UK2);
    A[4][3] = TR * (VJ1 * UJ2 - UJ1 * VJ2);
    A[4][4] = TR * (VK1 * UJ2 - UK1 * VJ2);

    TS = TR * TVW1[0];
    A[1][1] = A[3][3] * TS;
    A[1][2] = A[3][4] * TS;
    A[2][1] = A[4][3] * TS;
    A[2][2] = A[4][4] * TS;

    // transformation A*SA
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // final error (covariance) matrix in upper-triangular form

    //  std::cout<<"SD1toSD2: "<<PD2[0]<<","<<PD2[1]<<","<<PD2[2]<<","<<std::endl;

    for (Int_t J = 0; J < 15; J++) {
        RD2[J] = S[J];
        //  std::cout<<S[J]<<"  ";
    }
}

void FairGeaneUtil::FromSDToPt(Double_t PD[3],
                               Double_t RD[15],
                               Double_t H[3],
                               Int_t CH,
                               Double_t SPU,
                               Double_t DJ[3],
                               Double_t DK[3],
                               // output
                               Int_t& IERR,
                               Double_t* PC,
                               Double_t* RC)
{
    //
    // -------------------------------------------------------------
    //
    //      TRANSFORM ERROR MATRIX
    //      FROM        VARIABLES (q/P,V',W',V,W)
    //      FROM        VARIABLES (q/Pt,V',W',V,W)
    //
    //                         input
    //      PD[3]   (q/P, Lambda, Phi, Yt, Zt)
    //      RD[15]  error matrix in upper triangular form
    //      H[3]    magnetic field
    //      CH        CHARGE OF PARTICLE
    //                CHARGE AND MAGNETIC FIELD ARE NEEDED
    //                FOR CORRELATION TERMS (V',YT),(V',ZT),(W',YT),(W',ZT)
    //                THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
    //                TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
    //                AND RD FOR FIXED U
    //      SPU       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM
    //                spu = sign[p·(DJ x DK)]
    //      DJ(3)     UNIT VECTOR IN V-DIRECTION
    //      DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM
    //
    //                         output
    //      PC[3]   (q/Pt, Lambda, Phi, Yt, Zt)
    //      RC[15]  error matrix in upper triangular form
    //      IERR    =1 when track is perp to X-axis of Master
    //
    //     Author EMC Collaboration
    //     Translated in C/Rot by A. Rotondi (June 2007)
    //
    // -------------------------------------------------------------------
    //

    //
    //

    Double_t A[5][5], S[15], TN[3], TANL, COSL, COSL1;

    Double_t PM, HM, UN[3], VN[3], DI[3], TVW[3];

    Double_t CFACT8 = 2.997925e-04;

    Double_t /* UJ, */ /* UK, */ VJ, VK, HA, HAM, Q, SINZ /* , COSZ */;
    Double_t Vec[25];

    // ------------------------------------------------------------------

    IERR = 0;

    PM = PD[0];
    TVW[0] = 1. / TMath::Sqrt(1. + PD[1] * PD[1] + PD[2] * PD[2]);
    if (SPU < 0.) {
        TVW[0] = -TVW[0];
    }
    TVW[1] = PD[1] * TVW[0];
    TVW[2] = PD[2] * TVW[0];

    DI[0] = DJ[1] * DK[2] - DJ[2] * DK[1];
    DI[1] = DJ[2] * DK[0] - DJ[0] * DK[2];
    DI[2] = DJ[0] * DK[1] - DJ[1] * DK[0];

    for (Int_t I = 0; I < 3; I++) {
        TN[I] = TVW[0] * DI[I] + TVW[1] * DJ[I] + TVW[2] * DK[I];
    }

    COSL = TMath::Sqrt(TMath::Abs(1. - TN[2] * TN[2]));
    if (COSL < 1.e-30) {
        COSL = 1.e-30;
    }
    COSL1 = 1. / COSL;
    TANL = TN[2] * COSL1;

    PC[0] = PD[0] * COSL1;
    PC[1] = PD[1];
    PC[2] = PD[2];

    if (TMath::Abs(TN[0]) < 1.e-30) {
        TN[0] = 1.e-30;
    }

    UN[0] = -TN[1] * COSL1;
    UN[1] = TN[0] * COSL1;
    UN[2] = 0.;

    VN[0] = -TN[2] * UN[1];
    VN[1] = TN[2] * UN[0];
    VN[2] = COSL;

    // UJ=UN[0]*DJ[0]+UN[1]*DJ[1]+UN[2]*DJ[2];
    // UK=UN[0]*DK[0]+UN[1]*DK[1]+UN[2]*DK[2];
    VJ = VN[0] * DJ[0] + VN[1] * DJ[1] + VN[2] * DJ[2];
    VK = VN[0] * DK[0] + VN[1] * DK[1] + VN[2] * DK[2];

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }

    // copy input in an internal vector S
    for (Int_t I = 0; I < 15; I++) {
        S[I] = RD[I];
    }

    if (CH != 0.) {
        HA = TMath::Sqrt(H[0] * H[0] + H[1] * H[1] + H[2] * H[2]);
        HAM = HA * PM;
        if (HAM != 0.) {
            HM = CH / HA;

            Q = -HAM * CFACT8;

            SINZ = -(H[0] * UN[0] + H[1] * UN[1] + H[2] * UN[2]) * HM;
            // COSZ= (H[0]*VN[0]+H[1]*VN[1]+H[2]*VN[2])*HM;
            A[0][3] = -Q * TVW[1] * SINZ * (TANL * PC[0]);
            A[0][4] = -Q * TVW[2] * SINZ * (TANL * PC[0]);
        }
    }

    A[0][0] = COSL1;
    A[1][1] = 1.;
    A[2][2] = 1.;
    A[3][3] = 1.;
    A[4][4] = 1.;

    A[0][1] = TVW[0] * VJ * (TANL * PC[0]);
    A[0][2] = TVW[0] * VK * (TANL * PC[0]);

    // transformation
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // copy the result in S in the output vector
    for (Int_t I = 0; I < 15; I++) {
        RC[I] = S[I];
    }
}

void FairGeaneUtil::FromSDToSC(Double_t PD[3],
                               Double_t RD[15],
                               Double_t H[3],
                               Int_t CH,
                               Double_t SPU,
                               Double_t DJ[3],
                               Double_t DK[3],
                               //  output
                               Int_t& IERR,
                               Double_t* PC,
                               Double_t* RC)
{

    //  ----------------------------------------------------------------------
    //
    //      Tranform error matrix
    //      FROM   SD (detector plane)     VARIABLES (q/P,V',W',V,W)
    //      TO     SC (transverse system)  VARIABLES (q/P,LAMBDA,PHI,YT,ZT)
    //
    //      Authors: A. Haas and W. Wittek
    //      Translated in C/Root by A. Rotondi and A. Fontana (June 2007)
    //
    //
    //                                 INPUT
    //      PD(3)     q/P,V',W'
    //      H(3)      MAGNETIC FIELD
    //      RD(15)    ERROR MATRIX IN 1/P,V',W',V,W      (Triangular)
    //      CH        CHARGE OF PARTICLE
    //                CHARGE AND MAGNETIC FIELD ARE NEEDED
    //                FOR CORRELATION TERMS (LAMBDA,V),(LAMBDA,W),(PHI,V),(PHI,W)
    //                THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
    //                TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
    //                AND RD FOR FIXED U
    //      SPU       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM
    //                spu = sign[p·(DJ x DK)]
    //      DJ(3)     UNIT VECTOR IN V-DIRECTION
    //      DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM
    //

    //                        OUTPUT
    //      PC(3)     q/P,LAMBDA,PHI
    //      RC(15)    ERROR MATRIX IN   SC   VARIABLES
    //      IERR              NOT USED
    //
    // ---------------------------------------------------------------------

    Double_t A[5][5], S[15], TN[3];
    Double_t SINZ, COSZ, COSL, COSL1;
    Double_t UN[3], VN[3], DI[3], TVW[3];

    Double_t Vec[25];
    Double_t CFACT8 = 2.997925e-04;
    Double_t HA, HM, HAM, Q, UJ, UK, VJ, VK;

    Double_t PM;

    IERR = 0;
    memset(RC, 0, sizeof(*RC));
    memset(PC, 0, sizeof(*PC));

    PM = PD[0];
    TVW[0] = 1. / TMath::Sqrt(1. + PD[1] * PD[1] + PD[2] * PD[2]);

    if (SPU < 0.) {
        TVW[0] = -TVW[0];
    }
    TVW[1] = PD[1] * TVW[0];
    TVW[2] = PD[2] * TVW[0];

    DI[0] = DJ[1] * DK[2] - DJ[2] * DK[1];
    DI[1] = DJ[2] * DK[0] - DJ[0] * DK[2];
    DI[2] = DJ[0] * DK[1] - DJ[1] * DK[0];

    for (Int_t I = 0; I < 3; I++) {
        TN[I] = TVW[0] * DI[I] + TVW[1] * DJ[I] + TVW[2] * DK[I];
    }

    PC[0] = PD[0];
    PC[1] = TMath::ASin(TN[2]);
    if (TMath::Abs(TN[0]) < 1.e-30) {
        TN[0] = 1.e-30;
    }

    PC[2] = TMath::ATan2(TN[1], TN[0]);

    COSL = TMath::Sqrt(TMath::Abs(1. - TN[2] * TN[2]));
    if (COSL < 1.e-30) {
        COSL = 1.e-30;
    }
    COSL1 = 1. / COSL;
    UN[0] = -TN[1] * COSL1;
    UN[1] = TN[0] * COSL1;
    UN[2] = 0.;

    VN[0] = -TN[2] * UN[1];
    VN[1] = TN[2] * UN[0];
    VN[2] = COSL;

    UJ = UN[0] * DJ[0] + UN[1] * DJ[1] + UN[2] * DJ[2];
    UK = UN[0] * DK[0] + UN[1] * DK[1] + UN[2] * DK[2];
    VJ = VN[0] * DJ[0] + VN[1] * DJ[1] + VN[2] * DJ[2];
    VK = VN[0] * DK[0] + VN[1] * DK[1] + VN[2] * DK[2];

    // prepare matrices and vectors

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 5; K++) {
            A[I][K] = 0.;
        }
    }
    for (Int_t J = 0; J < 15; J++) {
        S[J] = RD[J];
    }

    if (CH != 0.) {
        // charged particle
        HA = TMath::Sqrt(H[0] * H[0] + H[1] * H[1] + H[2] * H[2]);
        HAM = HA * PM;
        if (HAM != 0.) {
            // .... in a magnetic field
            HM = CH / HA;
            Q = -HAM * CFACT8;
            SINZ = -(H[0] * UN[0] + H[1] * UN[1] + H[2] * UN[2]) * HM;
            COSZ = (H[0] * VN[0] + H[1] * VN[1] + H[2] * VN[2]) * HM;
            A[1][3] = -Q * TVW[1] * SINZ;
            A[1][4] = -Q * TVW[2] * SINZ;
            A[2][3] = -Q * TVW[1] * COSZ * COSL1;
            A[2][4] = -Q * TVW[2] * COSZ * COSL1;
        }
    }
    A[0][0] = 1.;
    A[1][1] = TVW[0] * VJ;
    A[1][2] = TVW[0] * VK;
    A[2][1] = TVW[0] * UJ * COSL1;
    A[2][2] = TVW[0] * UK * COSL1;
    A[3][3] = UJ;
    A[3][4] = UK;
    A[4][3] = VJ;
    A[4][4] = VK;

    // transformation matrix
    FromMatToVec(A, Vec);
    SymmProd(Vec, S, S);

    // copy the result in S in the output vector
    for (Int_t I = 0; I < 15; I++) {
        RC[I] = S[I];
    }
}

void FairGeaneUtil::FromVec15ToMat25(Double_t V[15], fiveMat& A)
{
    //
    //   ------------------------------------------------------
    //   Passage from a 15-dim vector to a symmetric 5x5 matrix
    //   following the upper triangular convention
    //
    //      Author   A. Rotondi June 2007
    //
    //   ------------------------------------------------------

    A[0][0] = V[0];
    A[0][1] = V[1];
    A[0][2] = V[2];
    A[0][3] = V[3];
    A[0][4] = V[4];

    A[1][1] = V[5];
    A[1][2] = V[6];
    A[1][3] = V[7];
    A[1][4] = V[8];

    A[2][2] = V[9];
    A[2][3] = V[10];
    A[2][4] = V[11];

    A[3][3] = V[12];
    A[3][4] = V[13];

    A[4][4] = V[14];

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t k = I; k < 5; k++) {
            A[k][I] = A[I][k];
        }
    }
}
void FairGeaneUtil::FromVecToMat(fiveMat& A, Double_t V[25])
{
    //
    //   ------------------------------------------------------
    //   Passage from 25-dim vector to a symmetric 5x5 matrix
    //   (FoRTRAN column convention)
    //
    //      Author   A. Rotondi June 2007
    //
    //   ------------------------------------------------------

    A[0][0] = V[0];
    A[1][0] = V[1];
    A[2][0] = V[2];
    A[3][0] = V[3];
    A[4][0] = V[4];

    A[0][1] = V[5];
    ;
    A[1][1] = V[6];
    ;
    A[2][1] = V[7];
    ;
    A[3][1] = V[8];
    ;
    A[4][1] = V[9];
    ;

    A[0][2] = V[10];
    A[1][2] = V[11];
    A[2][2] = V[12];
    A[3][2] = V[13];
    A[4][2] = V[14];

    A[0][3] = V[15];
    A[1][3] = V[16];
    A[2][3] = V[17];
    A[3][3] = V[18];
    A[4][3] = V[19];

    A[0][4] = V[20];
    A[1][4] = V[21];
    A[2][4] = V[22];
    A[3][4] = V[23];
    A[4][4] = V[24];
}

void FairGeaneUtil::FromMarsToSC(Double_t PD[3],
                                 Double_t RD[6][6],
                                 Double_t H[3],
                                 Int_t CH,
                                 //  output
                                 Double_t* PC,
                                 Double_t* RC)
{
    //  ----------------------------------------------------------------------
    //
    //      Tranform error matrix
    //      FROM   MASTER                  VARIABLES (px, py,pz, x, y, z)
    //      TO     SC (transverse system)  VARIABLES (q/p, lambda, phi, yt, zt)
    //                                   momentum along x axis (GEANE convention)
    //
    //      Method: the matrix in MARS is transformed in a detctor SD system
    //              with the detector plane coincident with the SC transverse plane.
    //              Then, the SD to SC routine is used.
    //              In this way the track length s is not modified by the transformation.
    //
    //      Authors: A. Rotondi and A. Fontana (June 2007)
    //               rewritten by A. Rotondi and Lia Lavezzi  (may 2008)
    //
    //                                 INPUT
    //      PD(3)     px, py, pz
    //      RD(6,6)   ERROR MATRIX  from MASTER Reference System
    //                covariances of (px, py, pz, x, y, z)
    //
    //      CH        CHARGE OF PARTICLE
    //      H(3)      MAGNETIC FIELD components
    //
    //                                 OUTPUT
    //      PC(3)     q/p, lambda, phi
    //      RC(15)    ERROR MATRIX IN   SC   VARIABLES
    //
    //
    // ---------------------------------------------------------------------

    //  Double_t PDD[3], RDD[15];

    Double_t SPU, DJ[3], DK[3], PM /* , PM3 */ /* , PT */;
    Int_t IERR;
    Double_t clam, slam, cphi, sphi, PC1[3], RC1[15];
    // ------------------------------------------------------------------

    // reset

    IERR = 0;
    memset(RC, 0, sizeof(*RC));
    memset(PC, 0, sizeof(*PC));

    PM = TMath::Sqrt(PD[0] * PD[0] + PD[1] * PD[1] + PD[2] * PD[2]);
    // PM3 = TMath::Power(PM,3);
    // PT  = TMath::Sqrt(PD[0]*PD[0]+PD[1]*PD[1]);

    // prepare the director cosines of a virtual dtector system
    // lying on the SC transverse plane

    slam = PD[2] / PM;
    clam = TMath::Sqrt(1. - slam * slam);

    if (TMath::Abs(clam) < 1.e-10) {
        clam = 0.;
        slam = 1.;
        cphi = 0.;
        sphi = -1.;
    } else {
        cphi = PD[0] / (clam * PM);
        sphi = PD[1] / (clam * PM);
    }

    DJ[0] = -sphi;
    DJ[1] = cphi;
    DJ[2] = 0.;

    DK[0] = -slam * cphi;
    DK[1] = -slam * sphi;
    DK[2] = clam;

    FromMarsToSD(PD, RD, H, CH, DJ, DK, IERR, SPU, PC1, RC1);

    // from SD to SC

    FromSDToSC(PC1, RC1, H, CH, SPU, DJ, DK, IERR, PC, RC);
}

void FairGeaneUtil::FromSCToMars(Double_t PC[3],
                                 Double_t RC[15],
                                 Double_t H[3],
                                 Int_t CH,
                                 //  output
                                 Double_t* PD,
                                 sixMat& RD)
{
    //  ------------------------------------------------------------------------
    //
    //      Transform error matrix
    //
    //      FROM  SC (transverse system)         (q/P,LAMBDA,PHI,YT,ZT)
    //      TO    MASTER Reference System (MARS) (px, py, pz, z, y, z)
    //
    //      Method: the SC system is transformed in a SD system with the
    //              detector plane coincident with the transverse one.
    //              Then, the SD to MARS routine is used.
    //
    //      Authors: A. Rotondi and A. Fontana (June 2007)
    //               rewritten by A. Rotondi and Lia Lavezzi (may 2008)
    //               In this way the track length s is not modified by the transformation.
    //
    //                                 INPUT
    //      PC(3)     q/p lambda phi
    //      RC(15)    ERROR MATRIX IN   SC   VARIABLES
    //                covariances of (px, py, pz, x, y, z)
    //      H(3)      Magnetic field components
    //      CH        CHARGE OF PARTICLE
    //
    //                                 OUTPUT
    //      PD(3)     px, py, pz
    //      RD(6,6)    ERROR MATRIX in MASTER Reference System
    //
    //
    // ---------------------------------------------------------------------------

    //  Double_t M65[6][5], M65T[5][6], AJ[5][6];
    // Double_t DJ[3], DK[3], RCM[5][5];
    Double_t DJ[3], DK[3];
    Double_t PDD[3], RDD[15];

    Int_t IERR;
    // Double_t SPU, PM, PM2, PM3, PVW, PVW3;
    Double_t SPU;
    Double_t clam, slam, cphi, sphi;
    // -------------------------------------------------------------------------

    IERR = 0;
    memset(PD, 0, sizeof(*PD));

    // reset matrices
    for (Int_t I = 0; I < 6; I++) {
        for (Int_t K = 0; K < 6; K++) {
            RD[I][K] = 0.;
        }
    }

    // go from SC to SD with the same plane
    // prepare the director cosines of a virtual dtector system
    // lying on the SC transverse plane

    clam = TMath::Cos(PC[1]);
    slam = TMath::Sin(PC[1]);
    cphi = TMath::Cos(PC[2]);
    sphi = TMath::Sin(PC[2]);

    // momentum is perpendicular to the x-y plane
    if (TMath::Abs(clam) < 1.e-15) {
        clam = 0.;
        slam = 1.;
        cphi = 0.;
        sphi = -1.;
    }

    // GEANE routines to go on SD

    DJ[0] = -sphi;
    DJ[1] = cphi;
    DJ[2] = 0.;

    DK[0] = -slam * cphi;
    DK[1] = -slam * sphi;
    DK[2] = clam;

    FromSCToSD(PC, RC, H, CH, DJ, DK, IERR, SPU, PDD, RDD);

    if (IERR != 1) {

        FromSDToMars(PDD, RDD, H, CH, SPU, DJ, DK, PD, RD);
    }
}

void FairGeaneUtil::FromMarsToSD(Double_t PD[3],
                                 Double_t RD[6][6],
                                 Double_t[3] /*H[3]*/,
                                 Int_t CH,
                                 Double_t DJ1[3],
                                 Double_t DK1[3],
                                 //  output
                                 Int_t& IERR,
                                 Double_t& SP1,
                                 Double_t* PC,
                                 Double_t* RC)
{

    //  ----------------------------------------------------------------------
    //
    //      Tranform error matrix
    //      FROM   MASTER                  VARIABLES (px, py,pz, x, y, z)
    //      TO     SD (transverse or local system)
    //                                     VARIABLES (q/p, v', w', v, w)
    //
    //      Method: the MARS system is rotated to a local cartesia system
    //              with the x-y plane on the v-w one of SD.   Hence eq (79) of the
    //              report CMS 2006/001 is used to go from canonical to SD variables.
    //              In this way the track length variation and the magnetic field
    //              effects are correctly taken into account.
    //
    //      Authors: A. Rotondi and A. Fontana (July 2007)
    //               Rewritten by A. Rotondi and Lia Lavezzi (may 2008)
    //               corrected for the q/p variable by A. Rotondi (10 june 2007)
    //
    //                                 INPUT
    //      PD(3)     px, py, pz  in MARS
    //      RD(6,6)   ERROR MATRIX  from MASTER Reference System
    //                covariances of (px, py, pz, x, y, z)
    //
    //      CH        CHARGE OF PARTICLE
    //      H(3)      MAGNETIC FIELD components
    //      DJ1(3)    Director cosines of axis v in MARS
    //      DK1(3)    Director cosines of axis w in MARS
    //
    //                                 OUTPUt
    //      IERR      = 0    TRANSFORMATION OK
    //                = 1    MOMENTUM LIES IN THE DETECTOR PLANE
    //
    //      PC(3)     q/p, v', w'
    //      RC(15)    ERROR MATRIX IN   SD   VARIABLES
    //      SP1       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM
    //                SP1 = sign[p.(DJ x DK)]
    //
    //
    // ---------------------------------------------------------------------

    //  Double_t PDD[3], RDD[15];
    Double_t PDD[3];
    Double_t M56[5][6], M56T[6][5], AJ[5][5], AJT[6][5];
    Double_t R6[6][6], RLC[6][6];
    //  Double_t SPU, PM, PM3, PT;
    Double_t PM, PM3 /* , PT */;
    Double_t Rot[3][3], Rmat[6][6], Rtra[6][6];
    // ------------------------------------------------------------------

    // reset

    IERR = 0;
    memset(RC, 0, sizeof(*RC));
    memset(PC, 0, sizeof(*PC));

    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 6; K++) {
            AJT[K][I] = 0.;
            M56[I][K] = 0.;
            M56T[K][I] = 0.;
            if (K != 5) {
                AJ[I][K] = 0.;
            }
        }
    }

    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            R6[i][k] = 0.;
            RLC[i][k] = 0;
            Rmat[i][k] = 0.;
            Rtra[i][k] = 0.;
        }
    }

    // to local cartesian frame

    TVector3 MI(1., 0., 0.);
    TVector3 MJ(0., 1., 0.);
    TVector3 MK(0., 0., 1.);
    // local cartesian
    TVector3 DI(DJ1[0], DJ1[1], DJ1[2]);
    TVector3 DJ(DK1[0], DK1[1], DK1[2]);
    TVector3 DK = DI.Cross(DJ);

    // rotation: D.. final versors, M.. initial
    // vectors are  column matrices

    Rot[0][0] = DI.Dot(MI);
    Rot[0][1] = DI.Dot(MJ);
    Rot[0][2] = DI.Dot(MK);
    Rot[1][0] = DJ.Dot(MI);
    Rot[1][1] = DJ.Dot(MJ);
    Rot[1][2] = DJ.Dot(MK);
    Rot[2][0] = DK.Dot(MI);
    Rot[2][1] = DK.Dot(MJ);
    Rot[2][2] = DK.Dot(MK);

    TMatrixT<double> PD1(3, 1);
    PD1[0][0] = PD[0];
    PD1[1][0] = PD[1];
    PD1[2][0] = PD[2];

    TMatrixT<double> Rot1(3, 3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            Rot1[i][j] = Rot[i][j];
        }

    // momentum components in the lcl cartesian frame
    // with the x-y plane on the detectorr one

    TMatrixT<double> Rot1xPD1(Rot1, TMatrixT<double>::kMult, PD1);
    PDD[0] = Rot1xPD1[0][0];
    PDD[1] = Rot1xPD1[1][0];
    PDD[2] = Rot1xPD1[2][0];

    // jacobian for error matrix in MARS

    Rmat[0][0] = Rot[0][0];
    Rmat[0][1] = Rot[0][1];
    Rmat[0][2] = Rot[0][2];
    Rmat[1][0] = Rot[1][0];
    Rmat[1][1] = Rot[1][1];
    Rmat[1][2] = Rot[1][2];
    Rmat[2][0] = Rot[2][0];
    Rmat[2][1] = Rot[2][1];
    Rmat[2][2] = Rot[2][2];

    Rmat[3][3] = Rot[0][0];
    Rmat[3][4] = Rot[0][1];
    Rmat[3][5] = Rot[0][2];
    Rmat[4][3] = Rot[1][0];
    Rmat[4][4] = Rot[1][1];
    Rmat[4][5] = Rot[1][2];
    Rmat[5][3] = Rot[2][0];
    Rmat[5][4] = Rot[2][1];
    Rmat[5][5] = Rot[2][2];

    // transposed of the jacobian

    for (Int_t I = 0; I < 6; I++) {
        for (Int_t K = 0; K < 6; K++) {
            Rtra[K][I] = Rmat[I][K];
        }
    }

    // product (J)(RD)(J+)

    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            for (Int_t l = 0; l < 6; l++) {
                R6[i][k] += RD[i][l] * Rtra[l][k];
            }
        }
    }

    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            for (Int_t l = 0; l < 6; l++) {
                RLC[i][k] += Rmat[i][l] * R6[l][k];
            }
        }
    }
    // go from local cartesian to the detector system SD
    // x-y of local are v and w of SD.
    // use of eq. (79) of the CMS report 2006/001 (Strandlie and Wittek)
    //

    PM = TMath::Sqrt(PDD[0] * PDD[0] + PDD[1] * PDD[1] + PDD[2] * PDD[2]);
    PM3 = TMath::Power(PM, 3);
    // PT  = TMath::Sqrt(PDD[0]*PDD[0]+PDD[1]*PDD[1]);

    //
    // check if track lies in the x-y plane of the local cartesian frame
    // if so, IERR=1 and exit
    //

    if (TMath::Abs(PDD[2]) < 1.e-08) {
        IERR = 1;
    }

    else {

        // output q/p, v' and w'  in SD

        PC[0] = CH / PM;
        PC[1] = PDD[0] / PDD[2];
        PC[2] = PDD[1] / PDD[2];
        ;

        // Jacobian  Mars --> SD parallel to  Mars x-y plane
        //  eq (79) of CMS note 2006/001 (Strandle and Wittek)

        M56[0][0] = -CH * PDD[0] / PM3;
        M56[0][1] = -CH * PDD[1] / PM3;
        M56[0][2] = -CH * PDD[2] / PM3;

        M56[1][0] = 1. / PDD[2];
        M56[1][1] = 0.;
        M56[1][2] = -PDD[0] / (PDD[2] * PDD[2]);

        M56[2][0] = 0.;
        M56[2][1] = 1. / PDD[2];
        M56[2][2] = -PDD[1] / (PDD[2] * PDD[2]);

        M56[3][3] = 1.;
        M56[4][4] = 1.;

        // matrix multiplication with  the Jacobian

        for (Int_t k = 0; k < 5; k++) {
            for (Int_t l = 0; l < 6; l++) {
                M56T[l][k] = M56[k][l];
            }
        }

        for (Int_t i = 0; i < 6; i++) {
            for (Int_t k = 0; k < 5; k++) {
                for (Int_t l = 0; l < 6; l++) {
                    AJT[i][k] += RLC[i][l] * M56T[l][k];
                }
            }
        }

        for (Int_t i = 0; i < 5; i++) {
            for (Int_t k = 0; k < 5; k++) {
                for (Int_t l = 0; l < 6; l++) {
                    AJ[i][k] += M56[i][l] * AJT[l][k];
                }
            }
        }

        //  SD  format output erro matrix RC(15)
        FromMat25ToVec15(AJ, RC);

        SP1 = TMath::Sign(1.,
                          PD[0] * (DJ1[1] * DK1[2] - DJ1[2] * DK1[1]) + PD[1] * (DJ1[2] * DK1[0] - DJ1[0] * DK1[2])
                              + PD[2] * (DJ1[0] * DK1[1] - DJ1[1] * DK1[0]));
    }
}

void FairGeaneUtil::FromSDToMars(Double_t PC[3],
                                 Double_t RC[15],
                                 Double_t[3] /*H[3]*/,
                                 Int_t CH,
                                 Double_t SP1,
                                 Double_t DJ1[3],
                                 Double_t DK1[3],
                                 //  output
                                 Double_t* PD,
                                 sixMat& RD)
{
    //  ------------------------------------------------------------------------
    //
    //      Transform error matrix
    //
    //      FROM  SD (detector system system)    (q/P,v'.w'.v.w)
    //      TO    MASTER Reference System (MARS) (px, py, pz, z, y, z)
    //
    //      Method:  eq (80) of the report CMS 2006/001 is used
    //              to go from SD to the local cartesian  frame.
    //              Then the error matrix in MARS is obtained through the jacobian
    //              between  the local cartesian frame and MARS.
    //
    //      Authors: A. Rotondi and A. Fontana (June 2007)
    //               Rewritten by A. Rotondi and Lia Lavezzi (may 2008)
    //               corrected for the q/p variable by A. Rotondi (10 june 2007)
    //
    //                                 INPUT
    //      PC(3)     q/p v' w'
    //      RC(15)    ERROR MATRIX IN   SD   VARIABLES
    //                covariances of (px, py, pz, x, y, z)
    //      H(3)      Magnetic field components
    //      CH        CHARGE OF PARTICLE
    //      DJ1(3)    Director cosines of axis v in MARS
    //      DK1(3)    Director cosines of axis w in MARS
    //      SP1       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM
    //                spu = sign[p·(DJ1 x DK1)]
    //
    //                                 OUTPUT
    //      PD(3)     px, py, pz
    //      RD(6,6)   ERROR (Covariance) MATRIX in MASTER Reference System
    //
    //
    // ---------------------------------------------------------------------------

    Double_t M65[6][5], M65T[5][6], AJ[5][6];
    Double_t RCM[5][5];
    Double_t PDD[3];
    Double_t Rot[3][3];

    //    TVector3 PD1, PD2;
    TVector3 PD2;

    Double_t RD1[6][6], Rmat[6][6], AJJ[6][6], Rtra[6][6];

    Double_t SPU, PM, PM2, PVW, PVW3;

    // -------------------------------------------------------------------------

    memset(PD, 0, sizeof(*PD));

    // reset matrices
    for (Int_t I = 0; I < 5; I++) {
        for (Int_t K = 0; K < 6; K++) {
            AJ[I][K] = 0.;
            M65[K][I] = 0.;
            M65T[I][K] = 0.;
            RD[I][K] = 0.;
            RD1[I][K] = 0.;
            Rmat[I][K] = 0.;
            Rtra[I][K] = 0.;
            AJJ[I][K] = 0.;
            if (K < 5)
                RCM[I][K] = 0.;
        }
    }
    for (Int_t I = 0; I < 6; I++) {
        RD[5][I] = 0.;
        RD1[5][I] = 0.;
        Rmat[5][I] = 0.;
        Rtra[5][I] = 0.;
        AJJ[5][I] = 0.;
    }

    SPU = SP1;

    // jacobian from SD to local cartesian

    PM = 1.e+30;
    if (PC[0] != 0.) {
        PM = CH / PC[0];
    }
    PM2 = PM * PM;
    PVW = TMath::Sqrt(1. + PC[1] * PC[1] + PC[2] * PC[2]);
    PVW3 = TMath::Power(PVW, 3);

    // output px, py, pz (cartesian)

    PDD[0] = SPU * PM * PC[1] / PVW;
    PDD[1] = SPU * PM * PC[2] / PVW;
    PDD[2] = SPU * PM / PVW;

    // Jacobian SD -->  Mars
    //  eq (80) of CMS note 2006/001 (Strandlie and Wittek)

    M65[0][0] = -SPU * PM2 * PC[1] / (CH * PVW);
    M65[1][0] = -SPU * PM2 * PC[2] / (CH * PVW);
    M65[2][0] = -SPU * PM2 / (CH * PVW);

    M65[0][1] = SPU * PM * (1. + PC[2] * PC[2]) / PVW3;
    M65[1][1] = -SPU * PM * PC[1] * PC[2] / PVW3;
    M65[2][1] = -SPU * PM * PC[1] / PVW3;

    M65[0][2] = -SPU * PM * PC[1] * PC[2] / PVW3;
    M65[1][2] = SPU * PM * (1. + PC[1] * PC[1]) / PVW3;
    M65[2][2] = -SPU * PM * PC[2] / PVW3;

    M65[3][3] = 1.;
    M65[4][4] = 1.;

    FromVec15ToMat25(RC, RCM);

    // transposed of the jacobian

    for (Int_t I = 0; I < 6; I++) {
        for (Int_t K = 0; K < 5; K++) {
            M65T[K][I] = M65[I][K];
        }
    }

    // product (J)(RCM)(J+)

    for (Int_t i = 0; i < 5; i++) {
        for (Int_t k = 0; k < 6; k++) {
            for (Int_t l = 0; l < 5; l++) {
                AJ[i][k] += RCM[i][l] * M65T[l][k];
            }
        }
    }

    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            for (Int_t l = 0; l < 5; l++) {
                RD1[i][k] += M65[i][l] * AJ[l][k];
            }
        }
    }

    // now go from the local cartesian to MARS

    // MARS
    TVector3 MI(1., 0., 0.);
    TVector3 MJ(0., 1., 0.);
    TVector3 MK(0., 0., 1.);
    // local cartesian
    TVector3 DI(DJ1[0], DJ1[1], DJ1[2]);
    TVector3 DJ(DK1[0], DK1[1], DK1[2]);
    TVector3 DK = DI.Cross(DJ);

    // rotation: M.. final  versors, D.. initial
    // vectors are  column matrices

    Rot[0][0] = MI.Dot(DI);
    Rot[0][1] = MI.Dot(DJ);
    Rot[0][2] = MI.Dot(DK);
    Rot[1][0] = MJ.Dot(DI);
    Rot[1][1] = MJ.Dot(DJ);
    Rot[1][2] = MJ.Dot(DK);
    Rot[2][0] = MK.Dot(DI);
    Rot[2][1] = MK.Dot(DJ);
    Rot[2][2] = MK.Dot(DK);

    TMatrixT<double> PD1(3, 1);
    PD1[0][0] = PDD[0];
    PD1[1][0] = PDD[1];
    PD1[2][0] = PDD[2];

    TMatrixT<double> Rot1(3, 3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            Rot1[i][j] = Rot[i][j];
        }

    TMatrixT<double> Rot1xPD1(Rot1, TMatrixT<double>::kMult, PD1);
    PD[0] = Rot1xPD1[0][0];
    PD[1] = Rot1xPD1[1][0];
    PD[2] = Rot1xPD1[2][0];

    // jacobian for error matrix in MARS

    Rmat[0][0] = Rot[0][0];
    Rmat[0][1] = Rot[0][1];
    Rmat[0][2] = Rot[0][2];
    Rmat[1][0] = Rot[1][0];
    Rmat[1][1] = Rot[1][1];
    Rmat[1][2] = Rot[1][2];
    Rmat[2][0] = Rot[2][0];
    Rmat[2][1] = Rot[2][1];
    Rmat[2][2] = Rot[2][2];

    Rmat[3][3] = Rot[0][0];
    Rmat[3][4] = Rot[0][1];
    Rmat[3][5] = Rot[0][2];
    Rmat[4][3] = Rot[1][0];
    Rmat[4][4] = Rot[1][1];
    Rmat[4][5] = Rot[1][2];
    Rmat[5][3] = Rot[2][0];
    Rmat[5][4] = Rot[2][1];
    Rmat[5][5] = Rot[2][2];

    // transposed of the jacobian

    for (Int_t I = 0; I < 6; I++) {
        for (Int_t K = 0; K < 6; K++) {
            Rtra[K][I] = Rmat[I][K];
        }
    }

    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            for (Int_t l = 0; l < 6; l++) {
                AJJ[i][k] += RD1[i][l] * Rtra[l][k];
            }
        }
    }

    for (Int_t i = 0; i < 6; i++) {
        for (Int_t k = 0; k < 6; k++) {
            for (Int_t l = 0; l < 6; l++) {
                RD[i][k] += Rmat[i][l] * AJJ[l][k];
            }
        }
    }
}

void FairGeaneUtil::FromMat25ToVec15(Double_t A[5][5], Double_t* V)
{
    //
    //   ------------------------------------------------------
    //   Passage from a symmetric 5x5 matrix to a 15-dim vector
    //   following the upper triangular convention
    //
    //      Author   A. Rotondi June 2007
    //
    //   ------------------------------------------------------

    V[0] = A[0][0];
    V[1] = A[0][1];
    V[2] = A[0][2];
    V[3] = A[0][3];
    V[4] = A[0][4];

    V[5] = A[1][1];
    V[6] = A[1][2];
    V[7] = A[1][3];
    V[8] = A[1][4];

    V[9] = A[2][2];
    V[10] = A[2][3];
    V[11] = A[2][4];

    V[12] = A[3][3];
    V[13] = A[3][4];

    V[14] = A[4][4];
}

void FairGeaneUtil::FromMatToVec(Double_t A[5][5], Double_t* V)
{
    //
    //   ------------------------------------------------------
    //   Passage from a 5x5 matrix to a 25-dim vector
    //
    //      Author   A. Rotondi June 2007
    //
    //   ------------------------------------------------------

    V[0] = A[0][0];
    V[1] = A[1][0];
    V[2] = A[2][0];
    V[3] = A[3][0];
    V[4] = A[4][0];

    V[5] = A[0][1];
    V[6] = A[1][1];
    V[7] = A[2][1];
    V[8] = A[3][1];
    V[9] = A[4][1];

    V[10] = A[0][2];
    V[11] = A[1][2];
    V[12] = A[2][2];
    V[13] = A[3][2];
    V[14] = A[4][2];

    V[15] = A[0][3];
    V[16] = A[1][3];
    V[17] = A[2][3];
    V[18] = A[3][3];
    V[19] = A[4][3];

    V[20] = A[0][4];
    V[21] = A[1][4];
    V[22] = A[2][4];
    V[23] = A[3][4];
    V[24] = A[4][4];
}

void FairGeaneUtil::SymmProd(Double_t A[25], Double_t S[15], Double_t* R)
{
    //
    //  ---------------------------------------------------------
    //  TRANSFORMATION OF SYMMETRIC 5X5 MATRIX S:
    //                      A*S*AT -> R.
    //  A is a 25-dim vector corresonding to the 5x5 transformation
    //  matrix
    //  S and R ARE SYMMETRIC ERROR (COVARIANCE) MATRICES STORED
    //  IN TRIANGULAR FORM.
    //
    //                     INPUT
    //    A[25] transformation matrix 5x5
    //    S[15] error matrix in triangular form
    //
    //                     OUTPUT
    //    R[15] error matrix in triangular form
    //
    //  NB: S AND R MAY WELL BE THE SAME MATRIX.
    //
    //         Author: A. Haas (Freiburg University) 5/7/81
    //         transported with modifications
    //         in C/Root  by A. Rotondi (June 2007)
    //
    // * ------------------------------------------------------

    Double_t Q[15], T1, T2, T3, T4, T5;

    for (Int_t i = 0; i < 15; i++) {
        Q[i] = S[i];
    }

    Int_t K = 0;
    for (Int_t J = 0; J < 5; J++) {
        T1 = A[J];
        T2 = A[J + 5];
        T3 = A[J + 10];
        T4 = A[J + 15];
        T5 = A[J + 20];
        for (Int_t I = J; I < 5; I++) {
            R[K] = A[I] * (Q[0] * T1 + Q[1] * T2 + Q[2] * T3 + Q[3] * T4 + Q[4] * T5)
                   + A[I + 5] * (Q[1] * T1 + Q[5] * T2 + Q[6] * T3 + Q[7] * T4 + Q[8] * T5)
                   + A[I + 10] * (Q[2] * T1 + Q[6] * T2 + Q[9] * T3 + Q[10] * T4 + Q[11] * T5)
                   + A[I + 15] * (Q[3] * T1 + Q[7] * T2 + Q[10] * T3 + Q[12] * T4 + Q[13] * T5)
                   + A[I + 20] * (Q[4] * T1 + Q[8] * T2 + Q[11] * T3 + Q[13] * T4 + Q[14] * T5);
            K++;
        }
    }
}

// ------------------------- modifiche 27 jul 2007 --------------------------

TVector3 FairGeaneUtil::FromMARSToSDCoord(TVector3 xyz, TVector3 o, TVector3 di, TVector3 dj, TVector3 dk)
{

    TMatrixT<double> matrix(3, 3);
    // rotation matrix (u,v,w) = (fmatrix) * (x,y,z)
    matrix[0][0] = di[0];
    matrix[0][1] = di[1];
    matrix[0][2] = di[2];
    matrix[1][0] = dj[0];
    matrix[1][1] = dj[1];
    matrix[1][2] = dj[2];
    matrix[2][0] = dk[0];
    matrix[2][1] = dk[1];
    matrix[2][2] = dk[2];

    TMatrixT<double> xyzvec(3, 1);
    xyzvec[0][0] = xyz.X();
    xyzvec[1][0] = xyz.Y();
    xyzvec[2][0] = xyz.Z();

    TMatrixT<double> origin(3, 1);
    origin[0][0] = o.X();
    origin[1][0] = o.Y();
    origin[2][0] = o.Z();

    xyzvec -= origin;

    TMatrixT<double> uvwvec(matrix, TMatrixT<double>::kMult, xyzvec);

    TVector3 uvw = TVector3(uvwvec[0][0], uvwvec[1][0], uvwvec[2][0]);
    return uvw;
}

TVector3 FairGeaneUtil::FromSDToMARSCoord(TVector3 uvw, TVector3 o, TVector3 di, TVector3 dj, TVector3 dk)
{
    TMatrixT<double> matrix(3, 3);
    matrix[0][0] = di[0];
    matrix[0][1] = di[1];
    matrix[0][2] = di[2];
    matrix[1][0] = dj[0];
    matrix[1][1] = dj[1];
    matrix[1][2] = dj[2];
    matrix[2][0] = dk[0];
    matrix[2][1] = dk[1];
    matrix[2][2] = dk[2];

    TMatrixT<double> uvwvec(3, 1);
    uvwvec[0][0] = uvw.X();
    uvwvec[1][0] = uvw.Y();
    uvwvec[2][0] = uvw.Z();

    TMatrixT<double> uvwrot(matrix, TMatrixT<double>::kTransposeMult, uvwvec);

    TMatrixT<double> origin(3, 1);
    origin[0][0] = o.X();
    origin[1][0] = o.Y();
    origin[2][0] = o.Z();

    TMatrixT<double> xyzvec(3, 1);
    xyzvec = uvwrot + origin;

    TVector3 xyz = TVector3(xyzvec[0][0], xyzvec[1][0], xyzvec[2][0]);

    return xyz;
}
