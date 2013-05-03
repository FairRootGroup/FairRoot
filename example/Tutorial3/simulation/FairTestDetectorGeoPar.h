#ifndef PNDTORINODETECTORGEOPAR_H
#define PNDTORINODETECTORGEOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for Class Def

class TObjArray;
class FairParamList;

class FairTestDetectorGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairTestDetectorGeoPar(const char* name="FairTestDetectorGeoPar",
                           const char* title="FairTestDetector Geometry Parameters",
                           const char* context="TestDefaultContext");
    ~FairTestDetectorGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairTestDetectorGeoPar(const FairTestDetectorGeoPar&);
    FairTestDetectorGeoPar& operator=(const FairTestDetectorGeoPar&);

    ClassDef(FairTestDetectorGeoPar,1)
};

#endif
