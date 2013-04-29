#ifndef FAIRGEOROOTBUILDER_H
#define FAIRGEOROOTBUILDER_H

#include "FairGeoBuilder.h"


class TGeoManager;

/**
 * class to create geometry in ROOT
 * @author M. Al-Turany
 */
class FairGeoRootBuilder : public FairGeoBuilder
{
  private:
    FairGeoRootBuilder(const FairGeoRootBuilder&);
    FairGeoRootBuilder& operator=(const FairGeoRootBuilder&);
  protected:
    TGeoManager* geoManager; // ROOT geometry manager
  public:
    FairGeoRootBuilder();
    FairGeoRootBuilder(const char*,const char*);
    ~FairGeoRootBuilder() {}
    void setGeoManager(TGeoManager* me) {geoManager=me;}
    Bool_t createNode(FairGeoNode*, Int_t hadFormat=0);
    Int_t createMedium(FairGeoMedium*);
    void finalize();
    void checkOverlaps(Double_t ovlp=0.0001);
    ClassDef(FairGeoRootBuilder,0) //
};

#endif /* !FAIRGEOROOTBUILDER_H */
