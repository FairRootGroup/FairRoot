// -------------------------------------------------------------------------
// -----                     FairTrackParam source file                 -----
// -----                  Created 27/01/05  by V. Friese               -----
// -------------------------------------------------------------------------

#include "FairTrackParam.h"

#include "TMath.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTrackParam::FairTrackParam()
  : TObject(),
    fX(0),
    fY(0),
    fZ(0),
    fTx(0),
    fTy(0),
    fQp(0)
{
  //  fX = fY = fZ = fTx = fTy = fQp = 0.;
  for (int i=0; i<15; i++) { fCovMatrix[i] = 0; }
}
// -------------------------------------------------------------------------



// -----   Constructor with parameters   -----------------------------------
FairTrackParam::FairTrackParam(Double_t x, Double_t y, Double_t z,
                               Double_t tx, Double_t ty, Double_t qp,
                               const TMatrixFSym& covMat)
  : TObject(),
    fX(x),
    fY(y),
    fZ(z),
    fTx(tx),
    fTy(ty),
    fQp(qp)
{
  int index = 0;
  for (int i=0; i<5; i++) {
    for (int j=i; j<5; j++) { fCovMatrix[index++] = covMat[i][j]; }
  }
}
// -------------------------------------------------------------------------
// -----   Copy Constructor             -----------------------------------
FairTrackParam::FairTrackParam(const FairTrackParam& param)
  : TObject(param),
    fX(param.GetX()),
    fY(param.GetY()),
    fZ(param.GetZ()),
    fTx(param.GetTx()),
    fTy(param.GetTy()),
    fQp(param.GetQp())
{
  *this = param;
}

// -----   Destructor   ----------------------------------------------------
FairTrackParam::~FairTrackParam() {}
// -------------------------------------------------------------------------



// -----   Public method Print   -------------------------------------------
void FairTrackParam::Print(Option_t* option) const
{
  cout << "Position : (";
  cout.precision(2);
  cout << fX << ", " << fY << ", " << fZ << ")" << endl;
  cout << "Slopes : dx/dz = " << fTx << ", dy/dz = " << fTy << endl;
  cout << "q/p = " << fQp << endl;
}
// -------------------------------------------------------------------------




// -----  Accessor to momentum   -------------------------------------------
void FairTrackParam::Momentum(TVector3& mom) const
{
  Double_t p  = ( TMath::Abs(fQp)>1.e-4 ) ?1./TMath::Abs(fQp) :1.e4;
  Double_t pz = TMath::Sqrt( p*p / ( fTx*fTx + fTy*fTy + 1 ) );
  Double_t px = fTx * pz;
  Double_t py = fTy * pz;
  mom.SetXYZ(px, py, pz);

}
// -------------------------------------------------------------------------



// -----   Accessor to covariance matrix (array)   -------------------------
void FairTrackParam::CovMatrix(Double_t cov[]) const
{
  for (Int_t i=0; i<15; i++) { cov[i] = fCovMatrix[i]; }
}
// -------------------------------------------------------------------------



// -----   Accessor to covariance matrix (TMatrixFSym)    ------------------
void FairTrackParam::CovMatrix(TMatrixFSym& covMat) const
{
  Int_t index = 0;
  for (int i=0; i<5; i++) {
    for (int j=i; j<5; j++) {
      covMat[i][j] = fCovMatrix[index];
      covMat[j][i] = fCovMatrix[index];
      index++;
    }
  }
}
// -------------------------------------------------------------------------



// -----   Accessor to covariance matrix elements   ------------------------
Double_t FairTrackParam::GetCovariance(Int_t i, Int_t j) const
{
  if ( i<0 || j<0 || i>4 || j>4 ) {
    cout << "-E- FairTrackParam::GetCovariance: Invalid index pair ("
         << i << "," << j << ") !" << endl;
    return 0;
  }
  if (i>j) {
    Int_t k = i;
    i = j;
    j = k;
  }
  Int_t index = 0;
  if (i==0) { index = j; }
  else if (i==1) { index =  4 + j; }
  else if (i==2) { index =  7 + j; }
  else if (i==3) { index =  9 + j; }
  else if (i==4) { index = 10 + j; }
  return fCovMatrix[index];
}
// -------------------------------------------------------------------------



// -----   Position modifier    --------------------------------------------
void FairTrackParam::SetPosition(const TVector3& pos)
{
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}
// -------------------------------------------------------------------------



// -----   Covariance matrix modifier (array)  -----------------------------
void FairTrackParam::SetCovMatrix(Double_t cov[])
{
  for (Int_t i=0; i<15; i++) { fCovMatrix[i] = cov[i]; }
}
// -------------------------------------------------------------------------



// -----   Covariance matrix modifier (TMatrixFSym)  -----------------------
void FairTrackParam::SetCovMatrix(const TMatrixFSym& covMat)
{
  Int_t index = 0;
  for (int i=0; i<5; i++) {
    for (int j=i; j<5; j++) { fCovMatrix[index++] = covMat[i][j]; }
  }
}
// -------------------------------------------------------------------------



// -----   Covariance matrix element modifier   ----------------------------
void FairTrackParam::SetCovariance(Int_t i, Int_t j, Double_t val)
{
  if (i < 0 || i > 4) {
    cout << "-W- FairTrackParam::SetCovariance: "
         << "First index out of range!  " << i << endl;
    return;
  }
  if (j < 0 || j > 4) {
    cout << "-W- FairTrackParam::SetCovariance: "
         << "Second index out of range!  " << j << endl;
    return;
  }
  if (i>j) {
    Int_t k = i;
    i = j;
    j = k;
  }
  Int_t index = 0;
  if (i==0) { index = j; }
  else if (i==1) { index =  4 + j; }
  else if (i==2) { index =  7 + j; }
  else if (i==3) { index =  9 + j; }
  else if (i==4) { index = 10 + j; }
  fCovMatrix[index] = val;
  return;
}
// -------------------------------------------------------------------------



// -----   Assignment operator   -------------------------------------------
FairTrackParam& FairTrackParam::operator=(const FairTrackParam& par)
{
  fX  = par.GetX();
  fY  = par.GetY();
  fZ  = par.GetZ();
  fTx = par.GetTx();
  fTy = par.GetTy();
  fQp = par.GetQp();
  Double_t cov[15];
  par.CovMatrix(cov);
  SetCovMatrix(cov);
  return *this;
}
// -------------------------------------------------------------------------





ClassImp(FairTrackParam)


