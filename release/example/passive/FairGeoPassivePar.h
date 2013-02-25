#ifndef PNDGEOPASSIVEPAR_H
#define PNDGEOPASSIVEPAR_H

#include "FairParGenericSet.h"
#include "TH1F.h"

class FairGeoPassivePar : public FairParGenericSet
{
  public:
    TObjArray*            fGeoSensNodes; // List of FairGeoNodes for sensitive volumes
    TObjArray*            fGeoPassNodes; // List of FairGeoNodes for sensitive volumes

    FairGeoPassivePar(const char* name="FairGeoPassivePar",
                      const char* title="Passive Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~FairGeoPassivePar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray*             GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray*             GetGeoPassiveNodes() {return fGeoPassNodes;}

  private:
    FairGeoPassivePar(const FairGeoPassivePar&);
    FairGeoPassivePar& operator=(const FairGeoPassivePar&);

    ClassDef(FairGeoPassivePar,1)
};

#endif /* !PNDGEOPASSIVEPAR_H */
