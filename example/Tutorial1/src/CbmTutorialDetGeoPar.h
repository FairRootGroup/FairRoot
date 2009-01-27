#ifndef CBMTUTORIALDETGEOPAR_H
#define CBMTUTORIALDETGEOPAR_H

#include "CbmParGenericSet.h"

class TObjArray;
class CbmParamList;

class CbmTutorialDetGeoPar       : public CbmParGenericSet {
public:
 
  /** List of CbmGeoNodes for sensitive  volumes */
  TObjArray      *fGeoSensNodes; 

  /** List of CbmGeoNodes for sensitive  volumes */
  TObjArray      *fGeoPassNodes; 

  CbmTutorialDetGeoPar(const char* name="CbmTutorialDetGeoPar",
		       const char* title="CbmTutorialDet Geometry Parameters",
		       const char* context="TestDefaultContext");
  ~CbmTutorialDetGeoPar(void);
  void clear(void);
  void putParams(CbmParamList*);
  Bool_t getParams(CbmParamList*);
  TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
  TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  ClassDef(CbmTutorialDetGeoPar,1)
};

#endif /* CBMTUTORIALDETGEOPAR_H */
