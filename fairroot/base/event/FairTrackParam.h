/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                     FairTrackParam header file                 -----
// -----                  Created 27/01/05  by V. Friese               -----
// -------------------------------------------------------------------------

/**  FairTrackParam.h
 *@author V.Friese <v.friese@gsi.de>
 **
 ** Parameters (x, y, tx, ty, q/p) of a track
 ** resulting from the track fit. The z coordinate is not a parameter.
 ** The 5x5 covariance matrix can be set and accessed by either an array
 ** of size 15, the TMatrixFSym class or elementwise. Note that TMatrixFSym
 ** should not be used when performance is an issue.
 ** The internal representation of the covariance matrix elements is
 ** an array of double.
 **/

#ifndef FAIRSTSTRACKPARAM
#define FAIRSTSTRACKPARAM 1

#include <Rtypes.h>           // for Double_t, Double32_t, Int_t, etc
#include <TMatrixFSymfwd.h>   // for TMatrixFSym
#include <TObject.h>          // for TObject
#include <TVector3.h>         // for TVector3

class FairTrackParam : public TObject
{
  public:
    /** Constructor **/
    FairTrackParam();

    /** Constructor with all variables **/
    FairTrackParam(Double_t x,
                   Double_t y,
                   Double_t z,
                   Double_t tx,
                   Double_t ty,
                   Double_t qp,
                   const TMatrixFSym& covMat);

    /** Copy constructor **/
    FairTrackParam(const FairTrackParam& param);

    /** Destructor **/
    ~FairTrackParam() override;

    /** Output to screen **/
    void Print(Option_t* option = "") const override;

    /** Accessors **/
    Double_t GetX() const { return fX; };
    Double_t GetY() const { return fY; };
    Double_t GetZ() const { return fZ; };
    Double_t GetTx() const { return fTx; };
    Double_t GetTy() const { return fTy; };
    Double_t GetQp() const { return fQp; };
    void Position(TVector3& pos) const { pos.SetXYZ(fX, fY, fZ); };
    void Momentum(TVector3& mom) const;
    void CovMatrix(Double_t cov[]) const;
    void CovMatrix(TMatrixFSym& covMat) const;
    Double_t GetCovariance(Int_t i, Int_t j) const;

    /** Modifiers **/
    void SetX(Double_t x) { fX = x; };
    void SetY(Double_t y) { fY = y; };
    void SetZ(Double_t z) { fZ = z; };
    void SetTx(Double_t tx) { fTx = tx; };
    void SetTy(Double_t ty) { fTy = ty; };
    void SetQp(Double_t qp) { fQp = qp; };
    void SetPosition(const TVector3& pos);
    void SetCovMatrix(Double_t cov[]);
    void SetCovMatrix(const TMatrixFSym& covMat);
    void SetCovariance(Int_t i, Int_t j, Double_t val);

    /** Assignment operator  **/
    FairTrackParam& operator=(const FairTrackParam& par);

  private:
    /** Position of track at given z [cm] **/
    Double32_t fX, fY, fZ;

    /** Direction of track tx = dx/dz; ty = dy/dz **/
    Double32_t fTx, fTy;

    /** Charge over momentum [1/GeV] **/
    Double32_t fQp;

    /** Covariance matrix for the variables x, y, tx, ty, q/p
     ** The 15 elements of the upper triangle of the symmetric matrix
     ** are stored in an array of floats. The sequence of the array is
     ** a[0,0..4], a[1,1..4], a[2,2..4], a[3,3..4], a[4,4].
     **/

    Double32_t fCovMatrix[15];

    ClassDefOverride(FairTrackParam, 1);
};

#endif
