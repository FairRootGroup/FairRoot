/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOMATRIX_H
#define FAIRGEOMATRIX_H

#include "FairGeoVector.h"   // for FairGeoVector

#include <Rtypes.h>    // for Double_t, etc
#include <TObject.h>   // for TObject

/**
 * @author Ilse koenig
 */
class FairGeoMatrix : public TObject
{
  protected:
    Double_t fM[9];

  public:
    FairGeoMatrix();
    ~FairGeoMatrix() override;
    Double_t& operator()(Int_t i, Int_t j) { return fM[i * 3 + j]; }
    Double_t det();
    FairGeoVector operator*(FairGeoVector& v);
    FairGeoMatrix& operator/=(Double_t d);
    ClassDefOverride(FairGeoMatrix, 0);
};

#endif
