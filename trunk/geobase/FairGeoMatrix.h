#ifndef FAIRGEOMATRIX_H
#define FAIRGEOMATRIX_H

#include "FairGeoVector.h"

#include "TObject.h"

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
    Double_t& operator()(Int_t i,Int_t j) { return fM[i*3+j]; }
    Double_t det(void);
    FairGeoVector operator*(FairGeoVector& v);
    FairGeoMatrix& operator/=(Double_t d);
    ClassDef(FairGeoMatrix,0)
};

#endif
