//*-- AUTHOR : Ilse Koenig
//*-- Created : 25/10/2004

/////////////////////////////////////////////////////////////
//
//  FairBaseContFact
//
//  Factory for the parameter containers in libSts
//
/////////////////////////////////////////////////////////////

#include "FairBaseContFact.h"

#include "FairBaseParSet.h"

#include "FairRuntimeDb.h"

ClassImp(FairBaseContFact)

static FairBaseContFact gFairBaseContFact;

FairBaseContFact::FairBaseContFact() {
  // Constructor (called when the library is loaded)
  fName="FairBaseContFact";
  fTitle="Factory for parameter containers in libSts";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void FairBaseContFact::setAllContainers() {
  /** Creates the Container objects with all accepted contexts and adds them to
   *  the list of containers for the STS library.*/
    FairContainer* pTest= new FairContainer("FairBaseParSet",
                                          "Test class for parameter io",
                                          "TestDefaultContext");
    pTest->addContext("TestNonDefaultContext");
    containers->Add(pTest);
}

FairParSet* FairBaseContFact::createContainer(FairContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */
  const char* name=c->GetName();
  FairParSet* p=0;
  if (strcmp(name,"FairBaseParSet")==0) {
    p=new FairBaseParSet(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }
  return p;
}

