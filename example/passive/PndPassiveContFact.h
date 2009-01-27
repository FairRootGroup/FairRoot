#ifndef PNDPASSIVECONTFACT_H
#define PNDPASSIVECONTFACT_H

#include "CbmContFact.h"

class CbmContainer;

class PndPassiveContFact : public CbmContFact {
private:
  void setAllContainers();
public:
  PndPassiveContFact();
  ~PndPassiveContFact() {}
  CbmParSet* createContainer(CbmContainer*);
  ClassDef( PndPassiveContFact,0) // Factory for all Passive parameter containers
};

#endif  /* !PNDPASSIVECONTFACT_H */
