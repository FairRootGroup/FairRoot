#ifndef NEWDETECTORCONTFACT_H
#define NEWDETECTORCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class NewDetectorContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    NewDetectorContFact();
    ~NewDetectorContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( NewDetectorContFact,0) // Factory for all NewDetector parameter containers
};

#endif
