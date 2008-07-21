#ifndef CBMGEOBUILDER_H
#define CBMGEOBUILDER_H

#include "TNamed.h"

//class CbmGeoSet;
class CbmGeoNode;
class CbmGeoMedium;

/**
 * abstract base class for geometry builders
 * @author ilse koenig 
 */
class CbmGeoBuilder : public TNamed {
protected:
  Int_t nRot;  // number of defined rotations
  Int_t nMed;  // number of defined media 

  CbmGeoBuilder();
  CbmGeoBuilder(const char* name,const char* title);
public:
  virtual ~CbmGeoBuilder() {}
  virtual Bool_t createNode(CbmGeoNode*, Int_t hadFormat =0)=0;
  virtual Int_t createMedium(CbmGeoMedium*)=0;
  virtual void finalize() {}
  ClassDef(CbmGeoBuilder,0) 
};

#endif /* !CBMGEOBUILDER_H */
