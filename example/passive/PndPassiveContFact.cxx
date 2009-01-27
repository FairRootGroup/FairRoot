//*-- AUTHOR : Denis Bertini
//*-- Created : 21/06/2005

/////////////////////////////////////////////////////////////
//
//  PndPassiveContFact
//
//  Factory for the parameter containers in libPassive
//
/////////////////////////////////////////////////////////////

using namespace std;
#include "PndPassiveContFact.h"
#include "CbmRuntimeDb.h"
#include "PndGeoPassivePar.h"
#include <iostream>
#include <iomanip>

ClassImp(PndPassiveContFact)

static PndPassiveContFact gPndPassiveContFact;

PndPassiveContFact::PndPassiveContFact() {
  // Constructor (called when the library is loaded)
  fName="PndPassiveContFact";
  fTitle="Factory for parameter containers in libPassive";
  setAllContainers();
  CbmRuntimeDb::instance()->addContFactory(this);
}

void PndPassiveContFact::setAllContainers() {
  /** Creates the Container objects with all accepted contexts and adds them to
   *  the list of containers for the STS library.*/

    CbmContainer* p= new CbmContainer("PndGeoPassivePar",
                                          "Passive Geometry Parameters",
                                          "TestDefaultContext");
    p->addContext("TestNonDefaultContext");

    containers->Add(p);
}

CbmParSet* PndPassiveContFact::createContainer(CbmContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */
  const char* name=c->GetName();
  CbmParSet *p=NULL;
  if (strcmp(name,"PndGeoPassivePar")==0) {
    p=new PndGeoPassivePar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }
  return p;
}

