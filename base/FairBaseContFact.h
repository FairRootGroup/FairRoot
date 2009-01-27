#ifndef FAIRBASECONTFACT_H
#define FAIRBASECONTFACT_H

#include "FairContFact.h"

class FairContainer;

class FairBaseContFact : public FairContFact {
private:
  void setAllContainers();
public:
  FairBaseContFact();
  ~FairBaseContFact() {}
  FairParSet* createContainer(FairContainer*);
  ClassDef( FairBaseContFact,0) // Factory for all Base parameter containers
};

#endif  /* !FAIRBASECONTFACT_H */
