/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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

#ifndef FAIRSTSTRACKPARP
#define FAIRSTSTRACKPARP 1

#include <Rtypes.h>        // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>    // for Double_t, Int_t, Option_t
#include <TVector3.h>      // for TVector3
#include "FairTrackPar.h"  // for FairTrackPar
class FairTrackParH;  // lines 25-25
class TBuffer;
class TClass;
class TMemberInspector;


class FairTrackParP : public FairTrackPar
{

  public:
    /** Constructor **/
    FairTrackParP();

    /** Constructor with all track variables in SD **/
    // spu = the sign of u-component of particle momentum
    // constructor without spu, to be used when spu is calculated as output
    //  DJ(3)     UNIT VECTOR IN V-DIRECTION
    //      DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM

    FairTrackParP(Double_t v,
                  Double_t w,
                  Double_t Tv,
                  Double_t Tw,
                  Double_t qp,
                  Double_t CovMatrix[15],
                  TVector3 o,
                  TVector3 dj,
                  TVector3 dk);
    // constructor with spu, to be used when spu is needed as input
    FairTrackParP(Double_t v,
                  Double_t w,
                  Double_t Tv,
                  Double_t Tw,
                  Double_t qp,
                  Double_t CovMatrix[15],
                  TVector3 o,
                  TVector3 dj,
                  TVector3 dk,
                  Double_t spu);

    /** Constructor with position and momentum track in LAB **/
    // DIAGONAL MARS covariance matrix
    FairTrackParP(TVector3 pos,
                  TVector3 Mom,
                  TVector3 posErr,
                  TVector3 MomErr,
                  Int_t q,
                  TVector3 o,
                  TVector3 dj,
                  TVector3 dk);
    // NON DIAGONAL MARS covariance matrix
    FairTrackParP(TVector3 pos, TVector3 Mom, Double_t covMARS[6][6], Int_t q, TVector3 o, TVector3 dj, TVector3 dk);
    // constructor from helix
    FairTrackParP(FairTrackParH* helix, TVector3 dj, TVector3 dk, Int_t& ierr);

    /** Destructor **/
    virtual ~FairTrackParP();

    /** copy Constructor **/
    // to be implemented

    /** Output to screen **/
    virtual void Print(Option_t* option = "") const;

    // define track parameters in LAB
    void SetTrackPar(Double_t X,
                     Double_t Y,
                     Double_t Z,
                     Double_t Px,
                     Double_t Py,
                     Double_t Pz,
                     Int_t Q,
                     Double_t CovMatrix[15],
                     TVector3 o,
                     TVector3 di,
                     TVector3 dj,
                     TVector3 dk);
    // void SetTrackPar(Double_t X,  Double_t Y,  Double_t Z, Double_t Px, Double_t Py, Double_t Pz, Int_t Q, Double_t
    // CovMatrix[15]); define track parameters in SD
    void SetTrackPar(Double_t v,
                     Double_t w,
                     Double_t Tv,
                     Double_t Tw,
                     Double_t qp,
                     Double_t CovMatrix[15],
                     TVector3 o,
                     TVector3 di,
                     TVector3 dj,
                     TVector3 dk,
                     Double_t spu);
    // void SetTrackPar(Double_t v, Double_t w, Double_t Tv, Double_t Tw, Double_t qp,Double_t CovMatrix[15]);

    /** Modifiers **/
    void SetTV(Double_t tv) { fTV = tv; };
    void SetTW(Double_t tw) { fTW = tw; };

    void Reset();
    ClassDef(FairTrackParP, 1);

    /** Accessors **/

    // MARS
    /* Double_t GetDX();
     Double_t GetDY();
     Double_t GetDZ();
     Double_t GetDPx();
     Double_t GetDPy();
     Double_t GetDPz();
     Double_t GetDQp();
     Double_t GetX();
     Double_t GetY();
     Double_t GetZ();
    */
    // MARS
    void GetMARSCov(Double_t Cov66[6][6])
    {
        for (Int_t i = 0; i < 6; i++)
            for (Int_t j = 0; j < 6; j++) {
                Cov66[i][j] = fCovMatrix66[i][j];
            }
    }

    // SD
    Double_t* GetCov() { return fCovMatrix; };
    void GetCov(Double_t* Cov)
    {
        for (Int_t i = 0; i < 15; i++) {
            Cov[i] = fCovMatrix[i];
        }
    }
    void GetCovQ(Double_t* CovQ);
    Double_t GetV();
    Double_t GetW();
    Double_t GetTV();
    Double_t GetTW();
    Double_t GetDV();
    Double_t GetDW();
    Double_t GetDTV();
    Double_t GetDTW();

    // SD MOMENTUM
    TVector3 GetSDMomentum() { return TVector3(fPx_sd, fPy_sd, fPz_sd); }

    // plane
    TVector3 GetOrigin();
    TVector3 GetIVer();
    TVector3 GetJVer();
    TVector3 GetKVer();
    void SetPlane(TVector3 o, TVector3 dj, TVector3 dk);

    // spu
    Double_t GetSPU() { return fSPU; };

    // set/get transport matrix
    void SetTransportMatrix(Double_t mat[5][5]);
    void GetTransportMatrix(Double_t mat[5][5]);

  private:
    /** Points coordinates in SD system */
    Double_t fU, fV, fW, fTV, fTW;
    /** momentum id SD **/
    Double_t fPx_sd, fPy_sd, fPz_sd;
    /** Errors in SD system */
    Double_t fDU, fDV, fDW, fDTV, fDTW;
    /** Covariant matrix*/
    // in SD
    Double_t fCovMatrix[15];
    // in MARS
    Double_t fCovMatrix66[6][6];

    /**Calculate the cov. mat. for this helix*/
    void CalCov();

    // plane
    TVector3 forigin;
    TVector3 fiver;
    TVector3 fjver;
    TVector3 fkver;
    Double_t fDI[3];   //!
    Double_t fDJ[3];   //!
    Double_t fDK[3];   //!
    // spu
    Double_t fSPU;
    // transport matrix
    Double_t ftrmat[5][5];   //!
};

#endif
