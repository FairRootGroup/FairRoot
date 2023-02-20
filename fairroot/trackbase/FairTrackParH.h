/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the representation of a track as helix (SC system)
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
//
// GEANE parameters (q/p, lambda, phi, y_perp, z_perp) of Helix track
// The Helix can be constructed using the Helix parameter (1/p, lambda, phi,y_perp,z_perp) in SC reference
// and the covariance matrix. Or using position and momentum in LAB referance.

#ifndef FAIRSTSTRACKPARH
#define FAIRSTSTRACKPARH 1

#include <Rtypes.h>        // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>    // for Double_t, Int_t, Option_t
#include <TVector3.h>      // for TVector3
#include "FairTrackPar.h"  // for FairTrackPar
class FairTrackParP;  // lines 25-25
class TBuffer;
class TClass;
class TMemberInspector;


class FairTrackParH : public FairTrackPar
{
  public:
    /** Constructor **/
    FairTrackParH();

    /** Constructor with track variables  (in SC) **/
    FairTrackParH(Double_t x,
                  Double_t y,
                  Double_t z,
                  Double_t lambda,
                  Double_t phi,
                  Double_t qp,
                  Double_t CovMatrix[15]);

    /** Constructor track parameters with position and momentum (in LAB)**/

    FairTrackParH(TVector3 pos, TVector3 Mom, TVector3 posErr, TVector3 MomErr, Int_t q);

    /** copy Constructor **/
    FairTrackParH(FairTrackPar& Trkbase);

    // FairTrackParH(FairTrackParH &Trk);

    FairTrackParH(FairTrackParP* parab, Int_t& ierr);

    /** Destructor **/
    virtual ~FairTrackParH();

    /** Output to screen **/
    //   void Print();
    virtual void Print(Option_t* option = "") const;

    /** Accessors **/
    Double_t GetLambda() { return fLm; };
    Double_t GetPhi() { return fPhi; };
    Double_t GetDLambda(); /**Get Error in Lambda*/
    Double_t GetDPhi();    /**Get Error in Phi*/
    /**Get the coveriant matrix*/
    void GetCov(Double_t* Cov)
    {
        for (Int_t i = 0; i < 15; i++) {
            Cov[i] = fCovMatrix[i];
        }
    }
    void GetCovQ(Double_t* CovQ);
    // MARS
    void GetMARSCov(Double_t Cov66[6][6])
    {
        for (Int_t i = 0; i < 6; i++)
            for (Int_t j = 0; j < 6; j++) {
                Cov66[i][j] = fCovMatrix66[i][j];
            }
    }
    Double_t GetDX_sc();                 /**Get dx in SC*/
    Double_t GetDY_sc();                 /**Get dy in SC*/
    Double_t GetDZ_sc();                 /**Get dz in SC*/
    Double_t GetX_sc() { return fX_sc; } /**Get x in SC*/
    Double_t GetY_sc() { return fY_sc; } /**Get y in SC*/
    Double_t GetZ_sc() { return fZ_sc; } /**Get z in SC*/
                                         // Double_t GetDPx() ;   /**Get error in Px (in SC frame)*/
                                         // Double_t GetDPy() ;   /**Get error in Py (in SC frame)*/
                                         // Double_t GetDPz() ;   /**Get error in Pz (in SC frame)*/
                                         //  Double_t GetDQp() ;   /**Get error in Q/P*/
    Double_t GetX();                     /**Get X in Lab*/
    Double_t GetY();                     /**Get Y in Lab*/
    Double_t GetZ();                     /**Get Z in Lab*/

    /** Modifiers **/
    void SetLambda(Double_t Lm) { fLm = Lm; };
    void SetPhi(Double_t Phi) { fPhi = Phi; };

    void SetDLambda(Double_t DLm) { fDLm = DLm; };
    void SetDPhi(Double_t DPhi) { fDPhi = DPhi; };

    void SetX_sc(Double_t x) { fX_sc = x; } /**Set x in SC*/
    void SetY_sc(Double_t y) { fY_sc = y; } /**Set y in SC*/
    void SetZ_sc(Double_t z) { fZ_sc = z; } /**Set z in SC*/
    void SetCov(Double_t* Cov)
    {
        for (Int_t i = 0; i < 15; i++) {
            fCovMatrix[i] = Cov[i];
        }
    }
    void SetTrackPar(Double_t x,
                     Double_t y,
                     Double_t z,
                     Double_t Px,
                     Double_t Py,
                     Double_t Pz,
                     Int_t Q,
                     Double_t CovMatrix[15]);

    void
        SetTrackPar(Double_t x, Double_t y, Double_t z, Double_t pq, Double_t lm, Double_t phi, Double_t CovMatrix[15]);
    void Reset();
    ClassDef(FairTrackParH, 1);

  private:
    /** fLm = Dip angle **/
    Double_t fLm;
    /**fPhi = azimuthal angle **/
    Double_t fPhi;
    /** Error in Lambda*/
    Double_t fDLm;
    /** Error in Phi*/
    Double_t fDPhi;
    /** Points coordinates in SC system */
    Double_t fX_sc, fY_sc, fZ_sc;
    /** Errors for X,Y,Z  (in SC system) */
    Double_t fDX_sc, fDY_sc, fDZ_sc;
    /** Covariant matrix in SC*/
    Double_t fCovMatrix[15];
    // in MARS
    Double_t fCovMatrix66[6][6];

    /**Calculate the cov. mat. for this helix*/
    void CalCov();

    /** just to simplify a little bit typing the equations
       cLm  = Cos(Lambda),
       sLm  = Sin(Lambda),
       cphi = cos(Phi),
       sphi = Sin(Phi)
       //! do not streame this to the file
    */
    Double_t cLm, sLm, cphi, sphi;   //!
};

#endif
