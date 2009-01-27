#ifndef CBMGEOSHAPES_H
#define CBMGEOSHAPES_H


//#include "FairGeoTransform.h"

#include "TObject.h"
#include "TString.h"
//#include "TList.h"

#include <fstream>

class FairGeoVolume;
class FairGeoBasicShape;
class TList;
/**
 * manager class for geometry shapes
 * @author Ilse koenig 
 */
class  FairGeoShapes : public TObject {
private:
  FairGeoShapes(const FairGeoShapes &L);
  FairGeoShapes& operator= (const FairGeoShapes&) {return *this;}
protected:
  TList* shapes;  // list of already created shape classes
public :
  FairGeoShapes();
  ~FairGeoShapes();
  FairGeoBasicShape* selectShape(FairGeoVolume *);  
  FairGeoBasicShape* selectShape(const TString&);  
  Int_t readPoints(fstream*,FairGeoVolume*);
  Bool_t writePoints(fstream*,FairGeoVolume*);
  void printPoints(FairGeoVolume* volu);
  ClassDef(FairGeoShapes,0) //
};

#endif  /* !CBMGEOSHAPES_H */
