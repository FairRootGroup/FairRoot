/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRutherfordContFact.h"

#include "FairRuntimeDb.h"          // for FairRuntimeDb
#include "FairRutherfordGeoPar.h"   // for FairRutherfordGeoPar

#include <TList.h>     // for TList
#include <TString.h>   // for TString
#include <cstring>     // for strcmp

class FairParSet;

ClassImp(FairRutherfordContFact);

static FairRutherfordContFact gFairRutherfordContFact;

FairRutherfordContFact::FairRutherfordContFact()
    : FairContFact()
{
    /** Constructor (called when the library is loaded) */
    fName = "FairRutherfordContFact";
    fTitle = "Factory for parameter containers in libFairRutherford";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void FairRutherfordContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the FairRutherford library.
  */

    FairContainer* p =
        new FairContainer("FairRutherfordGeoPar", "FairRutherford Geometry Parameters", "TestDefaultContext");
    p->addContext("TestNonDefaultContext");

    containers->Add(p);
}

FairParSet* FairRutherfordContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
    const char* name = c->GetName();
    FairParSet* p = nullptr;
    if (strcmp(name, "FairRutherfordGeoPar") == 0) {
        p = new FairRutherfordGeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}
