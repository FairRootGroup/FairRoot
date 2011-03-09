#ifndef FAIRTUTORIALDETGEOPAR_H
#define FAIRTUTORIALDETGEOPAR_H

#include "FairParGenericSet.h"

class TObjArray;
class FairParamList;

class FairTutorialDetGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairTutorialDetGeoPar(const char* name="FairTutorialDetGeoPar",
                          const char* title="FairTutorialDet Geometry Parameters",
                          const char* context="TestDefaultContext");
    ~FairTutorialDetGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

    ClassDef(FairTutorialDetGeoPar,1)
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
