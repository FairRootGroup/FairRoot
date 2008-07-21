#ifndef CBMBASECONTFACT_H
#define CBMBASECONTFACT_H

#include "CbmContFact.h"

class CbmContainer;

class CbmBaseContFact : public CbmContFact {
private:
  void setAllContainers();
public:
  CbmBaseContFact();
  ~CbmBaseContFact() {}
  CbmParSet* createContainer(CbmContainer*);
  ClassDef( CbmBaseContFact,0) // Factory for all Base parameter containers
};

#endif  /* !CBMBASECONTFACT_H */
