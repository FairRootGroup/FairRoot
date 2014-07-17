/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/////////////////////////////////////////////////////////////
//
//  FairDbTutContFact
//
//  Factory for the parameter containers
//
/////////////////////////////////////////////////////////////
#include "FairDbTutContFact.h"

#include "FairDbTutPar.h"               // for FairDbTutPar
#include "FairDbTutParBin.h"            // for FairDbTutParBin
#include "FairParSet.h"                 // for FairParSet
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "Riosfwd.h"                    // for ostream
#include "TList.h"                      // for TList
#include "TString.h"                    // for TString

#include <string.h>                     // for strcmp, NULL
#include <iostream>                     // for operator<<, basic_ostream, etc

using namespace std;

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

  FairContainer* p3 = new FairContainer("TUTParBin", "Binary tutorial parameters", "TestDefaultContext");
  p3->addContext("TestNonDefaultContext");
  containers->Add(p3);

}

FairParSet* FairDbTutContFact::createContainer(FairContainer* c)
{
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */

  const char* name=c->GetName();
  cout << "-I-FairDbTutContFact::createContainer " << name << endl;
  FairParSet* p=NULL;
  if (strcmp(name,"TUTParDefault")==0) {
    p=new FairDbTutPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
    // Set Arguments needed for SQL versioning managment
    p->SetVersion(0);
    p->SetComboNo(-1);
    p->SetDbEntry(0);
    p->SetLogTitle(name);
  }

  if (strcmp(name,"TUTParAlternative")==0) {
    p=new FairDbTutPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
    // Set Arguments needed for SQL versioning managment
    p->SetVersion(1);
    p->SetComboNo(-1);
    p->SetDbEntry(0);
    p->SetLogTitle(name);
  }

  if (strcmp(name,"TUTParBin")==0) {
    p=new FairDbTutParBin(c->getConcatName().Data(),c->GetTitle(),c->getContext());
    // Set Arguments needed for SQL versioning managment
    p->SetVersion(0);
    p->SetComboNo(-1);
    p->SetDbEntry(0);
    p->SetLogTitle(name);
  }

  return p;
}
