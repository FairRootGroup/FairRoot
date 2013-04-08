/////////////////////////////////////////////////////////////
//
//  FairDbTutContFact
//
//  Factory for the parameter containers
//
/////////////////////////////////////////////////////////////

using namespace std;
#include "FairDbTutContFact.h"
#include "FairRuntimeDb.h"
#include "FairDbTutPar.h"
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include <iostream>
#include <iomanip>

ClassImp(FairDbTutContFact);

static FairDbTutContFact gFairDbTutContFact;

FairDbTutContFact::FairDbTutContFact()
{
  // Constructor (called when the library is loaded)
  fName="FairDbTutContFact";
  fTitle="Tutorial factory for parameter containers";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void FairDbTutContFact::setAllContainers()
{
  /** Creates the Container objects with all accepted contexts and adds them to
   *  the list of containers.*/

  FairContainer* p1 = new FairContainer("TUTParDefault", "Default tutorial parameters",
                                        "TestDefaultContext");
  p1->addContext("TestNonDefaultContext");
  containers->Add(p1);

  FairContainer* p2 = new FairContainer("TUTParAlternative", "Alternative to the default tutorial parameters", "TestDefaultContext");
  p2->addContext("TestNonDefaultContext");
  containers->Add(p2);

}

FairParSet* FairDbTutContFact::createContainer(FairContainer* c)
{
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */
  const char* name=c->GetName();
  cout << " -I-FairDbTutContFact::createContainer " << name << endl;
  FairParSet* p=NULL;
  if (strcmp(name,"TUTParDefault")==0) {
    p=new FairDbTutPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
    p->SetVersion(0);
  }

  if (strcmp(name,"TUTParAlternative")==0) {
    p=new FairDbTutPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
    p->SetVersion(1);
  }

  return p;
}
