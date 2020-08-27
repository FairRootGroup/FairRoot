/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutPropContFact.h"

#include "FairRuntimeDb.h"       // for FairRuntimeDb
#include "FairTutPropGeoPar.h"   // for FairTutPropGeoPar
#include "TList.h"               // for TList
#include "TString.h"             // for TString

#include <string.h>   // for strcmp, NULL

class FairParSet;

static FairTutPropContFact gFairTutPropContFact;

FairTutPropContFact::FairTutPropContFact()
    : FairContFact()
{
    /** Constructor (called when the library is loaded) */
    fName = "FairTutPropContFact";
    fTitle = "Factory for parameter containers in libFairTutProp";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void FairTutPropContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted
        contexts and adds them to
        the list of containers for the FairTutProp library.
    */

    FairContainer* p = new FairContainer("FairTutPropGeoPar", "FairTutProp Geometry Parameters", "TestDefaultContext");
    p->addContext("TestNonDefaultContext");

    containers->Add(p);
}

FairParSet* FairTutPropContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
        For an actual context, which is not an empty string and not
        the default context
        of this container, the name is concatinated with the context.
    */
    const char* name = c->GetName();
    if (strcmp(name, "FairTutPropGeoPar") == 0) {
        return new FairTutPropGeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return nullptr;
}

ClassImp(FairTutPropContFact);
