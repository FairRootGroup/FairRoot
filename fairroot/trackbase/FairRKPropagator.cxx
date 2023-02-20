/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRKPropagator.h"

#include "FairField.h"       // for FairField
#include "FairTrackParH.h"   // for FairTrackParH
#include "FairTrackParP.h"   // for FairTrackParP
#include "TDatabasePDG.h"    // for TDatabasePDG
#include "TMath.h"           // for Sqrt
#include "TMathBase.h"       // for Abs
#include "TVector3.h"        // for TVector3, operator-, operator*

#include <TGenericClassInfo.h>   // for TGenericClassInfo
#include <TParticlePDG.h>        // for TParticlePDG
#include <array>                 // for std::array
#include <fairlogger/Logger.h>   // for LOG
#include <math.h>                // for sqrt
#include <stdio.h>               // for printf
#include <stdlib.h>              // for abs

ClassImp(FairRKPropagator);

//______________________________________________________________________________
FairRKPropagator::FairRKPropagator(FairField* field)
    : FairPropagator("FairRKPropagator", "Runge-Kutta propagator")
    , fMaxStep(10.0)
    , fMagField(field)
    , fPropagationFlag(NONE)
    , fDefPlaneV0()
    , fDefPlaneV1()
    , fDefPlaneV2()
    , fPCAPropagationType(0)
    , fPCAPropagationDir(1)
    , fPCAPropagationPar(nullptr)
{
    if (!fMagField) {
        LOG(warning) << "FairRKPropagator: No magnetic field";
    }
}
//______________________________________________________________________________
FairRKPropagator::~FairRKPropagator() = default;

double FairRKPropagator::GetChargeFromPDG(int pdg)
{
    TDatabasePDG* pdgDB = TDatabasePDG::Instance();
    return pdgDB->GetParticle(pdg)->Charge() / 3.;   // Charge(): charge in units of |e|/3
}

bool FairRKPropagator::Propagate(FairTrackParH* TStart, FairTrackParH* TEnd, int PDG)
{
    if (fPropagationFlag == TOPLANE) {
        float x1[3] = {(float)TStart->GetX(), (float)TStart->GetY(), (float)TStart->GetZ()};
        float p1[3] = {(float)TStart->GetPx(), (float)TStart->GetPy(), (float)TStart->GetPz()};
        float x2[3] = {0., 0., 0.};
        float p2[3] = {0., 0., 0.};
        bool ret = Propagate(x1, p1, x2, p2, PDG);
        if (!ret)
            return false;
        TEnd->SetX(x2[0]);
        TEnd->SetY(x2[1]);
        TEnd->SetZ(x2[2]);
        TEnd->SetPx(p2[0]);
        TEnd->SetPy(p2[1]);
        TEnd->SetPz(p2[2]);
        TEnd->SetQp(GetChargeFromPDG(PDG) / sqrt(p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2]));
        TEnd->SetDX(0.);
        TEnd->SetDY(0.);
        TEnd->SetDZ(0.);
        TEnd->SetDPx(0.);
        TEnd->SetDPy(0.);
        TEnd->SetDPz(0.);
        return true;
    }
    LOG(warning) << "FairRKPropagator::Propagate not implemented yet or plane to propagate not set";
    return false;
}

bool FairRKPropagator::Propagate(FairTrackParP* TStart, FairTrackParH* TEnd, int PDG)
{
    if (fPropagationFlag == TOPLANE) {
        float x1[3] = {(float)TStart->GetX(), (float)TStart->GetY(), (float)TStart->GetZ()};
        float p1[3] = {(float)TStart->GetPx(), (float)TStart->GetPy(), (float)TStart->GetPz()};
        float x2[3] = {0., 0., 0.};
        float p2[3] = {0., 0., 0.};
        bool ret = Propagate(x1, p1, x2, p2, PDG);
        if (!ret)
            return false;
        TEnd->SetX(x2[0]);
        TEnd->SetY(x2[1]);
        TEnd->SetZ(x2[2]);
        TEnd->SetPx(p2[0]);
        TEnd->SetPy(p2[1]);
        TEnd->SetPz(p2[2]);
        TEnd->SetQp(GetChargeFromPDG(PDG) / sqrt(p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2]));
        TEnd->SetDX(0.);
        TEnd->SetDY(0.);
        TEnd->SetDZ(0.);
        TEnd->SetDPx(0.);
        TEnd->SetDPy(0.);
        TEnd->SetDPz(0.);
        return true;
    }
    LOG(warning) << "FairRKPropagator::Propagate not implemented yet or plane to propagate not set";
    return false;
}

bool FairRKPropagator::Propagate(FairTrackParP* TStart, FairTrackParP* TEnd, int PDG)
{
    if (fPropagationFlag == TOPLANE) {
        float x1[3] = {(float)TStart->GetX(), (float)TStart->GetY(), (float)TStart->GetZ()};
        float p1[3] = {(float)TStart->GetPx(), (float)TStart->GetPy(), (float)TStart->GetPz()};
        float x2[3] = {0., 0., 0.};
        float p2[3] = {0., 0., 0.};
        bool ret = Propagate(x1, p1, x2, p2, PDG);
        if (!ret)
            return false;
        TEnd->SetX(x2[0]);
        TEnd->SetY(x2[1]);
        TEnd->SetZ(x2[2]);
        TEnd->SetPx(p2[0]);
        TEnd->SetPy(p2[1]);
        TEnd->SetPz(p2[2]);
        TEnd->SetQp(GetChargeFromPDG(PDG) / sqrt(p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2]));
        TEnd->SetDX(0.);
        TEnd->SetDY(0.);
        TEnd->SetDZ(0.);
        TEnd->SetDPx(0.);
        TEnd->SetDPy(0.);
        TEnd->SetDPz(0.);
        return true;
    }
    LOG(warning) << "FairRKPropagator::Propagate not implemented yet or plane to propagate not set";
    return false;
}

bool FairRKPropagator::Propagate(FairTrackParH* TStart, FairTrackParP* TEnd, int PDG)
{
    if (fPropagationFlag == TOPLANE) {
        float x1[3] = {(float)TStart->GetX(), (float)TStart->GetY(), (float)TStart->GetZ()};
        float p1[3] = {(float)TStart->GetPx(), (float)TStart->GetPy(), (float)TStart->GetPz()};
        float x2[3] = {0., 0., 0.};
        float p2[3] = {0., 0., 0.};
        bool ret = Propagate(x1, p1, x2, p2, PDG);
        if (!ret)
            return false;
        TEnd->SetX(x2[0]);
        TEnd->SetY(x2[1]);
        TEnd->SetZ(x2[2]);
        TEnd->SetPx(p2[0]);
        TEnd->SetPy(p2[1]);
        TEnd->SetPz(p2[2]);
        TEnd->SetQp(GetChargeFromPDG(PDG) / sqrt(p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2]));
        TEnd->SetDX(0.);
        TEnd->SetDY(0.);
        TEnd->SetDZ(0.);
        TEnd->SetDPx(0.);
        TEnd->SetDPy(0.);
        TEnd->SetDPz(0.);
        return true;
    }
    LOG(warning) << "FairRKPropagator::Propagate not implemented yet";
    return false;
}

bool FairRKPropagator::Propagate(float* x1, float* p1, float* x2, float* p2, int PDG)
{
    double charge = GetChargeFromPDG(PDG);
    double momIn = TMath::Sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2]);
    if (momIn == 0.)
        return false;
    double vecIn[7] = {x1[0], x1[1], x1[2], p1[0] / momIn, p1[1] / momIn, p1[2] / momIn, momIn};
    double vecOut[7];
    double vec1[3] = {fDefPlaneV1.X(), fDefPlaneV1.Y(), fDefPlaneV1.Z()};
    double vec2[3] = {fDefPlaneV2.X(), fDefPlaneV2.Y(), fDefPlaneV2.Z()};
    double vec3[3] = {fDefPlaneV0.X(), fDefPlaneV0.Y(), fDefPlaneV0.Z()};
    PropagateToPlane(charge, vecIn, vec1, vec2, vec3, vecOut);
    x2[0] = vecOut[0];
    x2[1] = vecOut[1];
    x2[2] = vecOut[2];
    p2[0] = vecOut[3] * vecOut[6];
    p2[1] = vecOut[4] * vecOut[6];
    p2[2] = vecOut[5] * vecOut[6];
    return true;
}

bool FairRKPropagator::SetDestinationPlane(const TVector3& v0, const TVector3& v1, const TVector3& v2)
{
    fDefPlaneV0 = v0;
    fDefPlaneV1 = v1;
    fDefPlaneV2 = v2;
    fPropagationFlag = TOPLANE;
    return true;
}

bool FairRKPropagator::SetOriginPlane([[gnu::unused]] const TVector3& v0, [[gnu::unused]] const TVector3& v1)
{
    LOG(warning) << "FairRKPropagator::SetLengthToPropagateTo not implemented yet";
    return false;
}

bool FairRKPropagator::SetDestinationVolume([[gnu::unused]] std::string volName,
                                            [[gnu::unused]] int copyNo,
                                            [[gnu::unused]] int option)
{
    LOG(warning) << "FairRKPropagator::SetDestinationVolume not implemented yet";
    return false;
}

bool FairRKPropagator::SetDestinationLength([[gnu::unused]] float length)
{
    LOG(warning) << "FairRKPropagator::SetDestinationLength not implemented yet";
    return false;
}

//______________________________________________________________________________
bool FairRKPropagator::SetPCAPropagation(int pca, int dir, FairTrackParP* par)
{
    if (abs(dir) != 1) {
        LOG(warning) << "Set PCA dir to +1 or -1.";
        return false;
    }
    fPCAPropagationType = pca;
    fPCAPropagationDir = dir;
    fPCAPropagationPar = par;
    return true;
}

//______________________________________________________________________________
PCAOutputStruct FairRKPropagator::FindPCA(int PCA,
                                          int PDGCode,
                                          TVector3 Point,
                                          TVector3 Wire1,
                                          TVector3 Wire2,
                                          [[gnu::unused]] double MaxDistance)
{
    PCAOutputStruct pcastruct = PCAOutputStruct();

    if (PCA != 1 && PCA != 2) {
        LOG(info) << "FairRKPropagator::FindPCA implemented for point (pca=1) and wire (pca=2) only";
        return pcastruct;
    }
    double charge = GetChargeFromPDG(PDGCode);
    double momIn = fPCAPropagationDir *   // if set to -1, it will back propagate
                   TMath::Sqrt(fPCAPropagationPar->GetPx() * fPCAPropagationPar->GetPx()
                               + fPCAPropagationPar->GetPy() * fPCAPropagationPar->GetPy()
                               + fPCAPropagationPar->GetPz() * fPCAPropagationPar->GetPz());
    if (momIn == 0.)
        return pcastruct;
    double vecIn[7] = {fPCAPropagationPar->GetX(),
                       fPCAPropagationPar->GetY(),
                       fPCAPropagationPar->GetZ(),
                       fPCAPropagationPar->GetPx() / momIn,
                       fPCAPropagationPar->GetPy() / momIn,
                       fPCAPropagationPar->GetPz() / momIn,
                       momIn};

    double diff;
    if (PCA == 1)
        diff = sqrt((vecIn[0] - Point.X()) * (vecIn[0] - Point.X()) + (vecIn[1] - Point.Y()) * (vecIn[1] - Point.Y())
                    + (vecIn[2] - Point.Z()) * (vecIn[2] - Point.Z()));
    else   // if ( PCA == 2 )
        diff = CalculatePointToWireDistance(
            TVector3(fPCAPropagationPar->GetX(), fPCAPropagationPar->GetY(), fPCAPropagationPar->GetZ()),
            Wire1,
            Wire2,
            pcastruct.OnWirePCA);

    fMaxStep = diff / 25;
    double res_old = diff;
    double res = 100.0;
    double vecOut[7];
    double vecOutT[7];
    for (int i = 0; i < 7; i++) {
        vecOut[i] = 0;
        vecOutT[i] = 0;
    }

    int nIter = 0;
    pcastruct.TrackLength = 0.;

    do {
        double stepLength = Step(charge, vecIn, vecOut);
        double newDiff;
        if (PCA == 1)
            newDiff = sqrt((vecOut[0] - Point.X()) * (vecOut[0] - Point.X())
                           + (vecOut[1] - Point.Y()) * (vecOut[1] - Point.Y())
                           + (vecOut[2] - Point.Z()) * (vecOut[2] - Point.Z()));
        else   // if ( PCA == 2 )
            newDiff = CalculatePointToWireDistance(
                TVector3(vecOut[0], vecOut[1], vecOut[2]), Wire1, Wire2, pcastruct.OnWirePCA);

        res = newDiff / diff;
        if (TMath::Abs(res) < 0.01 || res > res_old) {
            break;
        } else {
            for (int i = 0; i < 7; i++) {
                vecOutT[i] = vecOut[i];
                vecIn[i] = vecOut[i];
            }
            res_old = res;
            pcastruct.TrackLength += stepLength;
        }
        if (nIter++ > 1000) {
            break;
        }
    } while (1);
    if (res > res_old)
        for (int k = 0; k < 7; k++) {
            vecOut[k] = vecOutT[k];
        }

    pcastruct.OnTrackPCA.SetX(vecOut[0]);
    pcastruct.OnTrackPCA.SetY(vecOut[1]);
    pcastruct.OnTrackPCA.SetZ(vecOut[2]);

    if (PCA == 1)
        pcastruct.Distance =
            sqrt((vecOut[0] - Point.X()) * (vecOut[0] - Point.X()) + (vecOut[1] - Point.Y()) * (vecOut[1] - Point.Y())
                 + (vecOut[2] - Point.Z()) * (vecOut[2] - Point.Z()));
    else   // if ( pcastruct.PCA == 2 )
        pcastruct.Distance =
            CalculatePointToWireDistance(TVector3(vecOut[0], vecOut[1], vecOut[2]), Wire1, Wire2, pcastruct.OnWirePCA);
    pcastruct.PCAStatusFlag = 0;
    return pcastruct;
}
//______________________________________________________________________________

//______________________________________________________________________________
double FairRKPropagator::CalculatePointToWireDistance(TVector3 point, TVector3 wire1, TVector3 wire2, TVector3& vwi)
{
    TVector3 ab = wire2 - wire1;
    TVector3 av = point - wire1;

    if (av.Dot(ab) <= 0.0) {   // Point is lagging behind start of the segment, so perpendicular distance is not viable
        vwi = wire1;
        return av.Mag();   // Use distance to start of segment instead
    }

    TVector3 bv = point - wire2;

    if (bv.Dot(ab) >= 0.0) {   // Point is advanced past the end of the segment, so perpendicular distance is not viable
        vwi = wire2;
        return bv.Mag();   // Use distance to end of the segment instead
    }

    vwi = (ab.Dot(av) / ab.Mag() / ab.Mag()) * ab;
    vwi += wire1;
    return (ab.Cross(av)).Mag() / ab.Mag();   // Perpendicular distance of point to segment
}
//______________________________________________________________________________

//______________________________________________________________________________
void FairRKPropagator::PropagateToPlane(double Charge,
                                        double* vecRKIn,
                                        double* vec1,
                                        double* vec2,
                                        double* vec3,
                                        double* vecOut)
{
    /**
  vec1 & vec2 are vectors on the plane
  vec3 a point on the plane
  */
    double Norm[3];
    double Mag;
    double dist[3];
    double distance[3];
    double vecRKoutT[7];

    for (int i = 0; i < 7; i++) {
        vecRKoutT[i] = 0;
    }

    Norm[0] = vec1[1] * vec2[2] - vec2[2] * vec2[1];   // a2b3 − a3b2,
    Norm[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];   // a3b1 − a1b3;
    Norm[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

    Mag = TMath::Sqrt(Norm[0] * Norm[0] + Norm[1] * Norm[1] + Norm[2] * Norm[2]);

    // printf(" Mag = %f   \n ", Mag);

    Norm[0] = Norm[0] / Mag;
    Norm[1] = Norm[1] / Mag;
    Norm[2] = Norm[2] / Mag;
    //   printf(" after normalization : Normal = %f %f %f  \n ", Norm[0],Norm[1],Norm[2]);

    dist[0] = vecRKIn[0] - vec3[0];
    dist[1] = vecRKIn[1] - vec3[1];
    dist[2] = vecRKIn[2] - vec3[2];

    distance[0] = Norm[0] * dist[0];
    distance[1] = Norm[1] * dist[1];
    distance[2] = Norm[2] * dist[2];
    //   printf(" distance = %f %f %f  \n ", distance[0],distance[1],distance[2]);
    double diff = TMath::Abs(distance[0] + distance[1] + distance[2]);
    fMaxStep = diff;
    double res = 100.0;
    double res_old = 100.0;

    double vecRKOut[7];
    // for (int i=0; i< 7; i++) {vecRKOut[i]=0;}
    int nIter = 0;

    //  printf("I am in CPU code  %f %f  %f  res= %f  diff = %f \n ", vecRKIn[0], vecRKIn[1],vecRKIn[2], res, diff);

    do {
        Step(Charge, vecRKIn, vecRKOut);
        dist[0] = (vecRKOut[0] - vec3[0]) * Norm[0];
        dist[1] = (vecRKOut[1] - vec3[1]) * Norm[1];
        dist[2] = (vecRKOut[2] - vec3[2]) * Norm[2];
        fMaxStep = TMath::Sqrt(dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2]);
        res = TMath::Abs(fMaxStep / diff);
        //   printf("After %i step %f %f %f  res = %f \n", nIter ,vecRKOut[0], vecRKOut[1],vecRKOut[2] , res);
        if (res < 0.001 || res > res_old) {
            break;
        } else {
            for (int i = 0; i < 7; i++) {
                vecRKIn[i] = vecRKOut[i];
                vecRKoutT[i] = vecRKOut[i];
            }
            res_old = res;
        }
        if (nIter++ > 1000) {
            break;
        }
    } while (1);
    //  printf("The results is  %f %f %f  , no of iter %i \n", vecRKOut[0],vecRKOut[1],vecRKOut[2], nIter);
    //  printf("\n");
    for (int i = 0; i < 7; i++) {
        if (res > res_old) {
            vecOut[i] = vecRKoutT[i];
        } else {
            vecOut[i] = vecRKOut[i];
        }
    }
}
//______________________________________________________________________________
void FairRKPropagator::Propagate(double Charge, double* vecRKIn, double* Pos)
{
    double diff = Pos[2] - vecRKIn[2];
    fMaxStep = diff / 25;
    double res_old = diff;
    double res = 100.0;
    double vecRKOut[7];
    double vecRKOutT[7];
    for (int i = 0; i < 7; i++) {
        vecRKOut[i] = 0;
        vecRKOutT[i] = 0;
    }

    int nIter = 0;
    do {
        Step(Charge, vecRKIn, vecRKOut);
        res = (vecRKOut[2] - Pos[2]) / diff;
        if (TMath::Abs(res) < 0.01 || res > res_old) {
            break;
        } else {
            for (int i = 0; i < 7; i++) {
                vecRKOutT[i] = vecRKOut[i];
                vecRKIn[i] = vecRKOut[i];
            }
        }
        if (nIter++ > 1000) {
            break;
        }
    } while (1);
    if (res > res_old)
        for (int k = 0; k < 7; k++) {
            vecRKOut[k] = vecRKOutT[k];
        }
    for (int k = 0; k < 3; k++) {
        printf(" vecRKOut[%i] =%f ", k, vecRKOut[k]);
    }
    printf("\n");
}
//______________________________________________________________________________
double FairRKPropagator::Step(double Charge, double* vecRKIn, double* vecOut)
{

    double vecRKOut[7];
    for (int i = 0; i < 7; i++) {
        vecRKOut[i] = 0;
    }
    //  for (int i=0; i< 7; i++) printf( "vectRKIn(%i)=%f  \n",i ,vecRKIn[i]);
    //  printf(" ---------------------------------------------------------------- \n");
    double stepLength = OneStepRungeKutta(Charge, fMaxStep, vecRKIn, vecRKOut);
    //  printf(" now at     x=%f  y=%f  z=%f \n", vecRKOut[0],vecRKOut[1],vecRKOut[2]);
    vecOut[0] = vecRKOut[0];
    vecOut[1] = vecRKOut[1];
    vecOut[2] = vecRKOut[2];
    vecOut[6] = vecRKOut[6];
    vecOut[3] = vecRKOut[3];
    vecOut[4] = vecRKOut[4];
    vecOut[5] = vecRKOut[5];

    return stepLength;
}

//______________________________________________________________________________
double FairRKPropagator::OneStepRungeKutta(double charge, double step, double* vect, double* vout)
{
    // Wrapper to step with method RungeKutta.

    /// ******************************************************************
    /// *                *
    /// *  Runge-Kutta method for tracking a particle through a magnetic *
    /// *  field. Uses Nystroem algorithm (See Handbook Nat. Bur. of   *
    /// *  Standards, procedure 25.5.20)         *
    /// *                *
    /// *  Input parameters            *
    /// * CHARGE    Particle charge        *
    /// * STEP    Step size          *
    /// * VECT    Initial co-ords,direction cosines,momentum   *
    /// *  Output parameters             *
    /// * VOUT    Output co-ords,direction cosines,momentum  *
    /// *  User routine called             *
    /// * CALL GUFLD(X,F)            *
    /// *                *
    /// *    ==>Called by : <USER>, GUSWIM         *
    /// * Authors    R.Brun, M.Hansroul  *********     *
    /// *      V.Perevoztchikov (CUT STEP implementation)  *
    /// *                *
    /// *                *
    /// ******************************************************************

    std::array<double, 4> magneticfield{0., 0., 0., 0.};
    double xyzt[3];
    double secxs[4], secys[4], seczs[4];   // hxp[3];
    //  double /*g1 , g2, g3, g4, g5, g6,*/;
    //  double /*f1, f2, f3, f4, rho, tet, hnorm, hp, rho1, sint, cost*/;

    double track_length = 0.;

    double maxit = 1992;
    double maxcut = 11;

    const double hmin = 1e-4;   // !!! MT ADD,  should be member
    const double kdlt = 1e-6;   // !!! MT CHANGE from 1e-4, should be member
    const double kdlt32 = kdlt / 32.;
    const double kthird = 1. / 3.;
    const double khalf = 0.5;
    const double kec = 2.99792458e-4;
    const double kpisqua = 9.86960440109;
    /*  const int kix  = 0;
    const int kiy  = 1;
    const int kiz  = 2;
    const int kipx = 3;
    const int kipy = 4;
    const int kipz = 5;
  */
    // *.
    // *.    ------------------------------------------------------------------
    // *.
    // *             this constant is for units cm,gev/c and kgauss
    // *
    int iter = 0;
    int ncut = 0;
    for (int j = 0; j < 7; j++) {
        vout[j] = vect[j];
    }

    double pinv = kec * charge / vect[6];
    double tl = 0.;
    double h = step;

    do {
        double rest = step - tl;
        // printf(" Step  no. %i  x=%f  y=%f  z=%f  px/p = %f  py/p =%f  pz/p= %f \n", iter, x,y,z,a,b,c);
        if (TMath::Abs(h) > TMath::Abs(rest)) {
            h = rest;
        }

        if (fMagField) {
            fMagField->GetFieldValue(vout, magneticfield.data());
        }

        // * start of integration
        double x = vout[0];
        double y = vout[1];
        double z = vout[2];
        double a = vout[3];
        double b = vout[4];
        double c = vout[5];

        double h2 = khalf * h;
        double h4 = khalf * h2;
        double ph = pinv * h;
        double ph2 = khalf * ph;

        //   printf(" -------------------------------------------  h2 = %f\n",h2);

        secxs[0] = (b * magneticfield[2] - c * magneticfield[1]) * ph2;
        secys[0] = (c * magneticfield[0] - a * magneticfield[2]) * ph2;
        seczs[0] = (a * magneticfield[1] - b * magneticfield[0]) * ph2;
        double ang2 = (secxs[0] * secxs[0] + secys[0] * secys[0] + seczs[0] * seczs[0]);
        if (ang2 > kpisqua) {
            break;
        }

        double dxt = h2 * a + h4 * secxs[0];
        double dyt = h2 * b + h4 * secys[0];
        double dzt = h2 * c + h4 * seczs[0];
        double xt = x + dxt;
        double yt = y + dyt;
        double zt = z + dzt;
        //   printf(" Position 1 at  xt=%f  yt=%f  zt=%f  \n", xt, yt, zt);
        //   printf(" differance     dxt=%f  dyt=%f  dzt=%f  \n", dxt, dyt, dzt);
        // * second intermediate point
        double est = TMath::Abs(dxt) + TMath::Abs(dyt) + TMath::Abs(dzt);
        if (est > h) {
            if (ncut++ > maxcut) {
                break;
            }
            h *= khalf;
            continue;
        }

        xyzt[0] = xt;
        xyzt[1] = yt;
        xyzt[2] = zt;

        if (fMagField) {
            fMagField->GetFieldValue(xyzt, magneticfield.data());
        }

        double at = a + secxs[0];
        double bt = b + secys[0];
        double ct = c + seczs[0];

        secxs[1] = (bt * magneticfield[2] - ct * magneticfield[1]) * ph2;
        secys[1] = (ct * magneticfield[0] - at * magneticfield[2]) * ph2;
        seczs[1] = (at * magneticfield[1] - bt * magneticfield[0]) * ph2;
        at = a + secxs[1];
        bt = b + secys[1];
        ct = c + seczs[1];
        secxs[2] = (bt * magneticfield[2] - ct * magneticfield[1]) * ph2;
        secys[2] = (ct * magneticfield[0] - at * magneticfield[2]) * ph2;
        seczs[2] = (at * magneticfield[1] - bt * magneticfield[0]) * ph2;
        dxt = h * (a + secxs[2]);
        dyt = h * (b + secys[2]);
        dzt = h * (c + seczs[2]);
        xt = x + dxt;
        yt = y + dyt;
        zt = z + dzt;
        at = a + 2. * secxs[2];
        bt = b + 2. * secys[2];
        ct = c + 2. * seczs[2];
        //  printf(" Position 2 at  xt=%f  yt=%f  zt=%f  \n", xt, yt, zt);

        est = TMath::Abs(dxt) + TMath::Abs(dyt) + TMath::Abs(dzt);
        if (est > 2. * TMath::Abs(h)) {
            if (ncut++ > maxcut) {
                break;
            }
            h *= khalf;
            continue;
        }

        xyzt[0] = xt;
        xyzt[1] = yt;
        xyzt[2] = zt;

        if (fMagField) {
            fMagField->GetFieldValue(xyzt, magneticfield.data());
        }

        z = z + (c + (seczs[0] + seczs[1] + seczs[2]) * kthird) * h;
        y = y + (b + (secys[0] + secys[1] + secys[2]) * kthird) * h;
        x = x + (a + (secxs[0] + secxs[1] + secxs[2]) * kthird) * h;
        //  printf(" Position 3 at  x=%f  y=%f  z=%f  \n", x, y, z);
        secxs[3] = (bt * magneticfield[2] - ct * magneticfield[1]) * ph2;
        secys[3] = (ct * magneticfield[0] - at * magneticfield[2]) * ph2;
        seczs[3] = (at * magneticfield[1] - bt * magneticfield[0]) * ph2;
        a = a + (secxs[0] + secxs[3] + 2. * (secxs[1] + secxs[2])) * kthird;
        b = b + (secys[0] + secys[3] + 2. * (secys[1] + secys[2])) * kthird;
        c = c + (seczs[0] + seczs[3] + 2. * (seczs[1] + seczs[2])) * kthird;

        est = TMath::Abs(secxs[0] + secxs[3] - (secxs[1] + secxs[2]))
              + TMath::Abs(secys[0] + secys[3] - (secys[1] + secys[2]))
              + TMath::Abs(seczs[0] + seczs[3] - (seczs[1] + seczs[2]));

        if (est > kdlt && TMath::Abs(h) > hmin) {
            if (ncut++ > maxcut) {
                break;
            }
            h *= khalf;
            continue;
        }

        ncut = 0;
        // * if too many iterations, go to helix
        if (iter++ > maxit) {
            break;
        }

        tl += h;
        if (est < kdlt32) {
            h *= 2.;
        }
        double cba = 1. / TMath::Sqrt(a * a + b * b + c * c);
        vout[0] = x;
        vout[1] = y;
        vout[2] = z;
        vout[3] = cba * a;
        vout[4] = cba * b;
        vout[5] = cba * c;

        rest = step - tl;
        track_length = tl;
        //  printf(" Position 4 at  x=%f  y=%f  z=%f  Step = %f  \n", x, y, z, step );

        if (step < 0.) {
            rest = -rest;
        }
        if (rest < 1.e-5 * TMath::Abs(step)) {
            return track_length;
        }

    } while (1);

    return track_length;

    // angle too big, use helix
    /*
    f1  = f[0];
    f2  = f[1];
    f3  = f[2];
    f4  = TMath::Sqrt(f1*f1+f2*f2+f3*f3);
    rho = -f4*pinv;
    tet = rho * step;

    hnorm = 1./f4;
    f1 = f1*hnorm;
    f2 = f2*hnorm;
    f3 = f3*hnorm;

    hxp[0] = f2*vect[kipz] - f3*vect[kipy];
    hxp[1] = f3*vect[kipx] - f1*vect[kipz];
    hxp[2] = f1*vect[kipy] - f2*vect[kipx];

    hp = f1*vect[kipx] + f2*vect[kipy] + f3*vect[kipz];

    rho1 = 1./rho;
    sint = TMath::Sin(tet);
    cost = 2.*TMath::Sin(khalf*tet)*TMath::Sin(khalf*tet);

    g1 = sint*rho1;
    g2 = cost*rho1;
    g3 = (tet-sint) * hp*rho1;
    g4 = -cost;
    g5 = sint;
    g6 = cost * hp;

    vout[kix] = vect[kix] + g1*vect[kipx] + g2*hxp[0] + g3*f1;
    vout[kiy] = vect[kiy] + g1*vect[kipy] + g2*hxp[1] + g3*f2;
    vout[kiz] = vect[kiz] + g1*vect[kipz] + g2*hxp[2] + g3*f3;

    vout[kipx] = vect[kipx] + g4*vect[kipx] + g5*hxp[0] + g6*f1;
    vout[kipy] = vect[kipy] + g4*vect[kipy] + g5*hxp[1] + g6*f2;
    vout[kipz] = vect[kipz] + g4*vect[kipz] + g5*hxp[2] + g6*f3;
  */
}
