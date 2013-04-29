#ifndef CBMRUTHERFORDCONTFACT_H
#define CBMRUTHERFORDCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class FairRutherfordContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairRutherfordContFact();
    ~FairRutherfordContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairRutherfordContFact,0) // Factory for all FairRutherford parameter containers
};

#endif
