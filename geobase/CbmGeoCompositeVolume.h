#ifndef CBMGEOCOMPOSITEVOLUME_H
#define CBMGEOCOMPOSITEVOLUME_H

#include "CbmGeoVolume.h"

class TObjArray;
/**
 * basic geometry of a volume with components
 * @author Ilse koenig 
 */
class CbmGeoCompositeVolume : public CbmGeoVolume {
protected:
  TObjArray* components;    // array of components (type CbmGeoVolume)
public:
  CbmGeoCompositeVolume(Int_t nComp=0);
  ~CbmGeoCompositeVolume();
  Int_t getNumComponents();
  CbmGeoVolume* getComponent(const Int_t);
  void createComponents(const Int_t);
  void setComponent(CbmGeoVolume*,const Int_t);
  void clear();
  void print();
  ClassDef(CbmGeoCompositeVolume,1) 
private:
  CbmGeoCompositeVolume(const CbmGeoCompositeVolume &L);
  CbmGeoCompositeVolume& operator= (const CbmGeoCompositeVolume&) {return *this;}

};

#endif /* !CBMGEOCOMPOSITEVOLUME_H */
