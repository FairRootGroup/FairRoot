/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOMATRIX_H
#define FAIRGEOMATRIX_H

#include "FairGeoVector.h"   // for FairGeoVector

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Double_t, Int_t
#include <TObject.h>      // for TObject

class TBuffer;
class TClass;
class TMemberInspector;

/**
 * @author Ilse koenig
 */
class FairGeoMatrix : public TObject
{
  protected:
    Double_t fM[9];

  public:
    FairGeoMatrix(void);
    ~FairGeoMatrix(void);
    Double_t& operator()(Int_t i, Int_t j) { return fM[i * 3 + j]; }
    Double_t det(void);
    FairGeoVector operator*(FairGeoVector& v);
    FairGeoMatrix& operator/=(Double_t d);
    ClassDef(FairGeoMatrix, 0);
};

#endif
