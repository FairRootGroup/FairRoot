#ifndef CBMGEOROOTBUILDER_H
#define CBMGEOROOTBUILDER_H

#include "CbmGeoBuilder.h"


class TGeoManager;

/**
 * class to create geometry in ROOT
 * @author M. Al-Turany 
 */
class CbmGeoRootBuilder : public CbmGeoBuilder {
private:
  CbmGeoRootBuilder(const CbmGeoRootBuilder &L);
  CbmGeoRootBuilder& operator= (const CbmGeoRootBuilder&) {return *this;}
protected:
  TGeoManager* geoManager; // ROOT geometry manager
public:
  CbmGeoRootBuilder();
  CbmGeoRootBuilder(const char*,const char*);
  ~CbmGeoRootBuilder() {}
  void setGeoManager(TGeoManager* m) {geoManager=m;}
  Bool_t createNode(CbmGeoNode*, Int_t hadFormat=0);
  Int_t createMedium(CbmGeoMedium*);
  void finalize();
  void checkOverlaps(Double_t ovlp=0.0001);
  ClassDef(CbmGeoRootBuilder,0) //
};

#endif /* !CBMGEOROOTBUILDER_H */
