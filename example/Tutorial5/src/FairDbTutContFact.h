#ifndef FAIRDBTUTCONTFACT_H
#define FAIRDBTUTCONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairDbTutContFact::Class, etc

class FairParSet;

class FairDbTutContFact : public FairContFact
{
  public:
    FairDbTutContFact();
    ~FairDbTutContFact() {}
    FairParSet* createContainer(FairContainer* c);
  private:
    void setAllContainers();

    ClassDef( FairDbTutContFact,0); // Factory for parameter containers
};

#endif  /* !FAIRDBTUTCONTFACT_H */
