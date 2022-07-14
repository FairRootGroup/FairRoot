/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewDetectorContFact.h"

#include "NewDetectorGeoPar.h"

#include <iostream>

ClassImp(NewDetectorContFact);

static NewDetectorContFact gNewDetectorContFact;

NewDetectorContFact::NewDetectorContFact()
    : FairContFact("NewDetectorContFact", "Factory for parameter containers in libNewDetector")
{
    /** Constructor (called when the library is loaded) */
    setAllContainers();
}

void NewDetectorContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the NewDetector library.
  */

    FairContainer* p = new FairContainer("NewDetectorGeoPar", "NewDetector Geometry Parameters", "TestDefaultContext");
    p->addContext("TestNonDefaultContext");

    containers->Add(p);
}

FairParSet* NewDetectorContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
    const char* name = c->GetName();
    FairParSet* p = NULL;
    if (strcmp(name, "NewDetectorGeoPar") == 0) {
        p = new NewDetectorGeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}
