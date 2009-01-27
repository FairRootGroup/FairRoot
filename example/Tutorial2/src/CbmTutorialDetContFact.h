#ifndef CBMTUTORIALDETCONTFACT_H
#define CBMTUTORIALDETCONTFACT_H

#include "CbmContFact.h"

class CbmContainer;

class CbmTutorialDetContFact : public CbmContFact {
 private:
  void setAllContainers();
 public:
  CbmTutorialDetContFact();
  ~CbmTutorialDetContFact() {}
  CbmParSet* createContainer(CbmContainer*);
  ClassDef( CbmTutorialDetContFact,0) // Factory for all MyDet parameter containers
};

#endif  /* !CBMTUTORIALDETCONTFACT_H */
