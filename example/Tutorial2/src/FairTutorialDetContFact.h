#ifndef CBMTUTORIALDETCONTFACT_H
#define CBMTUTORIALDETCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class FairTutorialDetContFact : public FairContFact {
 private:
  void setAllContainers();
 public:
  FairTutorialDetContFact();
  ~FairTutorialDetContFact() {}
  FairParSet* createContainer(FairContainer*);
  ClassDef( FairTutorialDetContFact,0) // Factory for all MyDet parameter containers
};

#endif  /* !CBMTUTORIALDETCONTFACT_H */
