//*-- AUTHOR : Ilse Koenig
//*-- Created : 25/10/2004

/////////////////////////////////////////////////////////////
//
//  CbmBaseContFact
//
//  Factory for the parameter containers in libSts
//
/////////////////////////////////////////////////////////////

#include "CbmBaseContFact.h"

#include "CbmBaseParSet.h"

#include "CbmRuntimeDb.h"

ClassImp(CbmBaseContFact)

static CbmBaseContFact gCbmBaseContFact;

CbmBaseContFact::CbmBaseContFact() {
  // Constructor (called when the library is loaded)
  fName="CbmBaseContFact";
  fTitle="Factory for parameter containers in libSts";
  setAllContainers();
  CbmRuntimeDb::instance()->addContFactory(this);
}

void CbmBaseContFact::setAllContainers() {
  /** Creates the Container objects with all accepted contexts and adds them to
   *  the list of containers for the STS library.*/
    CbmContainer* pTest= new CbmContainer("CbmBaseParSet",
                                          "Test class for parameter io",
                                          "TestDefaultContext");
    pTest->addContext("TestNonDefaultContext");
    containers->Add(pTest);
}

CbmParSet* CbmBaseContFact::createContainer(CbmContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */
  const char* name=c->GetName();
  CbmParSet* p=0;
  if (strcmp(name,"CbmBaseParSet")==0) {
    p=new CbmBaseParSet(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }
  return p;
}

