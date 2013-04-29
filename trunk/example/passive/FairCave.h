#ifndef Cave_H
#define Cave_H

#include "FairDetector.h"
#include "FairModule.h"


class FairCave : public FairModule
{
  public:
    FairCave(const char* name, const char* Title="Exp Cave");
    FairCave();
    virtual ~FairCave();
    virtual void ConstructGeometry();


  private:
    Double_t world[3];
    ClassDef(FairCave,1) //PNDCaveSD
};

#endif //Cave_H

