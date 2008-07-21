#ifndef CBMGEOMATRIX_H
#define CBMGEOMATRIX_H

#include "CbmGeoVector.h"

#include "TObject.h"

/**
 * @author Ilse koenig 
 */
class CbmGeoMatrix : public TObject {
protected:
  Double_t fM[9];
public:
  CbmGeoMatrix(void);
  ~CbmGeoMatrix(void);
  Double_t &operator()(Int_t i,Int_t j) { return fM[i*3+j]; }
  Double_t det(void);
  CbmGeoVector operator*(CbmGeoVector &v);
  CbmGeoMatrix &operator/=(Double_t d);
  ClassDef(CbmGeoMatrix,0)
};

#endif
