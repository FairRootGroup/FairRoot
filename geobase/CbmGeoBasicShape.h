#ifndef CBMGEOBASICSHAPE_H
#define CBMGEOBASICSHAPE_H

//#include "CbmGeoTransform.h"

#include "TNamed.h"
//#include "TString.h"
//#include "TArrayD.h"
//#include "TShape.h"

#include <fstream>

class CbmGeoTransform;
class CbmGeoVolume;
class TArrayD;
/**
 * base class for all shapes
 * @author Ilse koenig 
 */
class CbmGeoBasicShape : public TNamed {
protected:
  Int_t nPoints;            // number of points describing the shape 
  Int_t nParam;             // number of parameters needed to create the ROOT shape
  TArrayD* param;           // parameters needed to create the ROOT shape
  CbmGeoTransform* center;   // position of the volume center in the technical KS
  CbmGeoTransform* position; // position of the ROOT volume in its ROOT mother
public:
  CbmGeoBasicShape();
  virtual ~CbmGeoBasicShape();
  Int_t getNumPoints() {return nPoints;}
  Int_t getNumParam() {return nParam;}
  TArrayD* getParam() {return param;}
  CbmGeoTransform* getCenterPosition() {return center;}
  CbmGeoTransform* getVoluPosition() {return position;}
  virtual Int_t readPoints(fstream*,CbmGeoVolume*);   
  virtual Bool_t writePoints(fstream*,CbmGeoVolume*);   
  virtual void printPoints(CbmGeoVolume* volu);
  virtual TArrayD* calcVoluParam(CbmGeoVolume*) {return 0;} 
  virtual void calcVoluPosition(CbmGeoVolume*,const CbmGeoTransform&);
  virtual void calcVoluPosition(CbmGeoVolume*,const CbmGeoTransform&,
			  const CbmGeoTransform&) {return;}
  void printParam();
protected:
  void posInMother(const CbmGeoTransform&,const CbmGeoTransform&);
  ClassDef(CbmGeoBasicShape,0) // base class for all shapes
private:
  CbmGeoBasicShape(const CbmGeoBasicShape &L);
  CbmGeoBasicShape& operator= (const CbmGeoBasicShape&) {return *this;}
  
};

#endif  /* !CBMGEOBASICSHAPE_H */
