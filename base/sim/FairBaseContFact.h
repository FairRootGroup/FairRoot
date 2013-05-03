#ifndef FAIRBASECONTFACT_H
#define FAIRBASECONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairBaseContFact::Class, etc

class FairParSet;

class FairBaseContFact : public FairContFact
{
    /** Factory for all Base parameter containers */
  private:
    void setAllContainers();
  public:
    /**default ctor*/
    FairBaseContFact();
    /**default dtor*/
    ~FairBaseContFact() {}
    /** Calls the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairBaseContFact,0)
};

#endif  /* !FAIRBASECONTFACT_H */
