#ifndef PNDGEOPASSIVEPAR_H
#define PNDGEOPASSIVEPAR_H

#include "CbmParGenericSet.h"
#include "TH1F.h"

class PndGeoPassivePar : public CbmParGenericSet {
public:
  TObjArray            *fGeoSensNodes; // List of CbmGeoNodes for sensitive volumes
  TObjArray            *fGeoPassNodes; // List of CbmGeoNodes for sensitive volumes

  PndGeoPassivePar(const char* name="PndGeoPassivePar",
             const char* title="Passive Geometry Parameters",
             const char* context="TestDefaultContext");
  ~PndGeoPassivePar(void);
  void clear(void);
  void putParams(CbmParamList*);
  Bool_t getParams(CbmParamList*);
  TObjArray             *GetGeoSensitiveNodes(){return fGeoSensNodes;}
  TObjArray             *GetGeoPassiveNodes(){return fGeoPassNodes;}

  ClassDef(PndGeoPassivePar,1)
};

#endif /* !PNDGEOPASSIVEPAR_H */
