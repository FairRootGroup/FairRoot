#include "FairTutorialDetContFact.h"

#include "FairTutorialDetGeoPar.h"
#include "FairTutorialDetDigiPar.h"

#include "FairRuntimeDb.h"

#include <iostream>

ClassImp(FairTutorialDetContFact)

static FairTutorialDetContFact gFairTutorialDetContFact;

FairTutorialDetContFact::FairTutorialDetContFact() {
  /** Constructor (called when the library is loaded) */
  fName="FairTutorialDetContFact";
  fTitle="Factory for parameter containers in libTutorial1";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void FairTutorialDetContFact::setAllContainers() {
  /** Creates the Container objects with all accepted 
      contexts and adds them to
      the list of containers for the Tutorial1 library.
  */

  FairContainer* p1= new FairContainer("FairTutorialDetGeoPar",
				     "FairTutorialDet Geometry Parameters",
				     "TestDefaultContext");
  p1->addContext("TestNonDefaultContext");
  
  containers->Add(p1);

  FairContainer* p2= new FairContainer("FairTutorialDetDigiPar",
				     "Tutorial Det Digi Parameters",
				     "TestDefaultContext");
  p2->addContext("TestNonDefaultContext");

  containers->Add(p2);
}

FairParSet* FairTutorialDetContFact::createContainer(FairContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not 
      the default context
      of this container, the name is concatinated with the context. 
  */
  const char* name=c->GetName();
  FairParSet* p=NULL;
  if (strcmp(name,"FairTutorialDetGeoPar")==0) {
    p=new FairTutorialDetGeoPar(c->getConcatName().Data(),
			       c->GetTitle(),c->getContext());
  }
  if (strcmp(name,"FairTutorialDetDigiPar")==0) {
    p=new FairTutorialDetDigiPar(c->getConcatName().Data(),
			       c->GetTitle(),c->getContext());
  }
  return p;
}
