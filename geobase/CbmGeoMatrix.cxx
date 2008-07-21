//*-- Author : M. Sanchez
//*-- Modified : 07.03.2001

#include "CbmGeoMatrix.h"


////////////////////////////////////////////////////////
// CbmGeoMatrix
//
//   Simple 3D matrix interface for use with CbmGeoVector.
//   
//   Note:
//     This class is completely incomplete. Features will be
//     added as needed
/////////////////////////////////////////////////////////


CbmGeoMatrix::CbmGeoMatrix(void) {
  // Initializes the matrix to 0
  for (int i=0;i<9;i++) fM[i]=0.0;
}

CbmGeoMatrix::~CbmGeoMatrix(void) {
}

Double_t CbmGeoMatrix::det(void) {
  // Computes de determinat of the 3D matrix
  return (fM[0] * fM[4] * fM[8] + fM[1] * fM[5] * fM[6] + fM[3] *fM[7] * fM[2] -
	  fM[2] * fM[4] * fM[6] - fM[1] * fM[3] * fM[8] - fM[5] *fM[7] * fM[0]);
}

CbmGeoVector CbmGeoMatrix::operator*(CbmGeoVector &v) {
  // Matrix multiplication
  CbmGeoVector vo;
  vo.setX(fM[0] * v.getX() + fM[1] * v.getY() + fM[2] * v.getZ());
  vo.setY(fM[3] * v.getX() + fM[4] * v.getY() + fM[5] * v.getZ());
  vo.setZ(fM[6] * v.getX() + fM[7] * v.getY() + fM[8] * v.getZ());
  return vo;
}

CbmGeoMatrix &CbmGeoMatrix::operator/=(Double_t d) {
  // Matrix division by a constant. Divides each element on the
  //matrix by the constant "d"
  for (int i=0;i<9;i++) fM[i]/=d;
  return *this;
}

ClassImp(CbmGeoMatrix)
