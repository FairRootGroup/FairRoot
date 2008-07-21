#ifndef CBMGEOSHAPES_H
#define CBMGEOSHAPES_H


//#include "CbmGeoTransform.h"

#include "TObject.h"
#include "TString.h"
//#include "TList.h"

#include <fstream>

class CbmGeoVolume;
class CbmGeoBasicShape;
class TList;
/**
 * manager class for geometry shapes
 * @author Ilse koenig 
 */
class  CbmGeoShapes : public TObject {
private:
  CbmGeoShapes(const CbmGeoShapes &L);
  CbmGeoShapes& operator= (const CbmGeoShapes&) {return *this;}
protected:
  TList* shapes;  // list of already created shape classes
public :
  CbmGeoShapes();
  ~CbmGeoShapes();
  CbmGeoBasicShape* selectShape(CbmGeoVolume *);  
  CbmGeoBasicShape* selectShape(const TString&);  
  Int_t readPoints(fstream*,CbmGeoVolume*);
  Bool_t writePoints(fstream*,CbmGeoVolume*);
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoShapes,0) //
};

#endif  /* !CBMGEOSHAPES_H */
