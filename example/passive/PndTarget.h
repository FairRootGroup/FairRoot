#ifndef Target_H
#define Target_H

#include "CbmDetector.h"
#include "CbmModule.h"

class PndTarget : public CbmModule {
  public:
    PndTarget(const char * name, const char *Title="PND Target");
    PndTarget();
    virtual ~PndTarget();
    virtual void ConstructGeometry();
    ClassDef(PndTarget,1) 
  
};

#endif //Target_H

