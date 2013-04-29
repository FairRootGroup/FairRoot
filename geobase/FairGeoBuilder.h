#ifndef FAIRGEOBUILDER_H
#define FAIRGEOBUILDER_H

#include "TNamed.h"

//class FairGeoSet;
class FairGeoNode;
class FairGeoMedium;

/**
 * abstract base class for geometry builders
 * @author ilse koenig
 */
class FairGeoBuilder : public TNamed
{
  protected:
    Int_t nRot;  // number of defined rotations
    Int_t nMed;  // number of defined media

    FairGeoBuilder();
    FairGeoBuilder(const char* name,const char* title);
  public:
    virtual ~FairGeoBuilder() {}
    virtual Bool_t createNode(FairGeoNode*, Int_t hadFormat =0)=0;
    virtual Int_t createMedium(FairGeoMedium*)=0;
    virtual void finalize() {}
    ClassDef(FairGeoBuilder,0)
};

#endif /* !FAIRGEOBUILDER_H */
