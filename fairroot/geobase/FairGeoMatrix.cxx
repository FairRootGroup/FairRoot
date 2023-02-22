/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- Author : M. Sanchez
//*-- Modified : 07.03.2001

#include "FairGeoMatrix.h"

////////////////////////////////////////////////////////
// FairGeoMatrix
//
//   Simple 3D matrix interface for use with FairGeoVector.
//
//   Note:
//     This class is completely incomplete. Features will be
//     added as needed
/////////////////////////////////////////////////////////

FairGeoMatrix::FairGeoMatrix(void)
    : TObject()
{
    // Initializes the matrix to 0
    for (int i = 0; i < 9; i++) {
        fM[i] = 0.0;
    }
}

FairGeoMatrix::~FairGeoMatrix(void) {}

Double_t FairGeoMatrix::det(void)
{
    // Computes de determinat of the 3D matrix
    return (fM[0] * fM[4] * fM[8] + fM[1] * fM[5] * fM[6] + fM[3] * fM[7] * fM[2] - fM[2] * fM[4] * fM[6]
            - fM[1] * fM[3] * fM[8] - fM[5] * fM[7] * fM[0]);
}

FairGeoVector FairGeoMatrix::operator*(FairGeoVector& v)
{
    // Matrix multiplication
    FairGeoVector vo;
    vo.setX(fM[0] * v.getX() + fM[1] * v.getY() + fM[2] * v.getZ());
    vo.setY(fM[3] * v.getX() + fM[4] * v.getY() + fM[5] * v.getZ());
    vo.setZ(fM[6] * v.getX() + fM[7] * v.getY() + fM[8] * v.getZ());
    return vo;
}

FairGeoMatrix& FairGeoMatrix::operator/=(Double_t d)
{
    // Matrix division by a constant. Divides each element on the
    // matrix by the constant "d"
    for (int i = 0; i < 9; i++) {
        fM[i] /= d;
    }
    return *this;
}
