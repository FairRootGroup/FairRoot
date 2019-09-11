/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutGeaneContFact.h"

#include "FairRuntimeDb.h"          // for FairRuntimeDb
#include "FairTutGeaneGeoPar.h" // for FairTutGeaneGeoPar

#include "TList.h"   // for TList
#include "TString.h" // for TString

#include <string.h> // for strcmp, NULL

class FairParSet;

ClassImp(FairTutGeaneContFact) static FairTutGeaneContFact gFairTutGeaneContFact;

FairTutGeaneContFact::FairTutGeaneContFact()
    : FairContFact()
{
    /** Constructor (called when the library is loaded) */
    fName = "FairTutGeaneContFact";
    fTitle = "Factory for parameter containers in libFairTutGeane";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void FairTutGeaneContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted
        contexts and adds them to
        the list of containers for the FairTutGeane library.
    */

    FairContainer* p = new FairContainer("FairTutGeaneGeoPar", "FairTutGeane Geometry Parameters", "TestDefaultContext");
    p->addContext("TestNonDefaultContext");

    containers->Add(p);
}

FairParSet* FairTutGeaneContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
        For an actual context, which is not an empty string and not
        the default context
        of this container, the name is concatinated with the context.
    */
    const char* name = c->GetName();
    FairParSet* p = NULL;
    if (strcmp(name, "FairTutGeaneGeoPar") == 0)
    {
        p = new FairTutGeaneGeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return p;
}
