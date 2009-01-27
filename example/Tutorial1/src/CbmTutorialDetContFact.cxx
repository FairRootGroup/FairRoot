#include "CbmTutorialDetContFact.h"

#include "CbmTutorialDetGeoPar.h"

#include "CbmRuntimeDb.h"

#include <iostream>

ClassImp(CbmTutorialDetContFact)

static CbmTutorialDetContFact gCbmTutorialDetContFact;

CbmTutorialDetContFact::CbmTutorialDetContFact() {
  /** Constructor (called when the library is loaded) */
  fName="CbmTutorialDetContFact";
  fTitle="Factory for parameter containers in libTutorial1";
  setAllContainers();
  CbmRuntimeDb::instance()->addContFactory(this);
}

void CbmTutorialDetContFact::setAllContainers() {
  /** Creates the Container objects with all accepted 
      contexts and adds them to
      the list of containers for the Tutorial1 library.
  */

  CbmContainer* p= new CbmContainer("CbmTutorialDetGeoPar",
				    "CbmTutorialDet Geometry Parameters",
				    "TestDefaultContext");
  p->addContext("TestNonDefaultContext");
  
  containers->Add(p);
}

CbmParSet* CbmTutorialDetContFact::createContainer(CbmContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not 
      the default context
      of this container, the name is concatinated with the context. 
  */
  const char* name=c->GetName();
  CbmParSet* p=NULL;
  if (strcmp(name,"CbmTutorialDetGeoPar")==0) {
    p=new CbmTutorialDetGeoPar(c->getConcatName().Data(),
			       c->GetTitle(),c->getContext());
  }
  return p;
}
