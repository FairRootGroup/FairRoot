#ifndef FAIRGEOCOMPOSITEVOLUME_H
#define FAIRGEOCOMPOSITEVOLUME_H

#include "FairGeoVolume.h"

class TObjArray;
/**
 * basic geometry of a volume with components
 * @author Ilse koenig
 */
class FairGeoCompositeVolume : public FairGeoVolume
{
  protected:
    TObjArray* components;    // array of components (type FairGeoVolume)
  public:
    FairGeoCompositeVolume(Int_t nComp=0);
    ~FairGeoCompositeVolume();
    Int_t getNumComponents();
    FairGeoVolume* getComponent(const Int_t);
    void createComponents(const Int_t);
    void setComponent(FairGeoVolume*,const Int_t);
    void clear();
    void print();
    ClassDef(FairGeoCompositeVolume,1)
  private:
    FairGeoCompositeVolume(const FairGeoCompositeVolume& );
    FairGeoCompositeVolume& operator=(const FairGeoCompositeVolume&);

};

#endif /* !FAIRGEOCOMPOSITEVOLUME_H */
