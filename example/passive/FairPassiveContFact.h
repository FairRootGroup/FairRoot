#ifndef PNDPASSIVECONTFACT_H
#define PNDPASSIVECONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairPassiveContFact::Class, etc

class FairParSet;

class FairPassiveContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairPassiveContFact();
    ~FairPassiveContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairPassiveContFact,0) // Factory for all Passive parameter containers
};

#endif  /* !PNDPASSIVECONTFACT_H */
