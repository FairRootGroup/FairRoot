#ifndef Target_H
#define Target_H

#include "FairDetector.h"
#include "FairModule.h"

class FairTarget : public FairModule
{
  public:
    FairTarget(const char* name, const char* Title="PND Target");
    FairTarget();
    virtual ~FairTarget();
    virtual void ConstructGeometry();
    ClassDef(FairTarget,1)

};

#endif //Target_H

