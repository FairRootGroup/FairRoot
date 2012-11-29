#ifndef PNDTORINODETECTORCONTFACT_H
#define PNDTORINODETECTORCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class FairTestDetectorContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairTestDetectorContFact();
    ~FairTestDetectorContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairTestDetectorContFact,0) // Factory for all FairTestDetector parameter containers
};

#endif
