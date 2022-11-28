/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                     FairBaseContFact source file              -----
// -----                Created 25/10/04  by  Ilse Koenig              -----
// -------------------------------------------------------------------------

//  Factory for the parameter containers in Base

#include "FairBaseContFact.h"

#include "FairBaseParSet.h"
#include "FairGeoParSet.h"

#include <TList.h>
#include <TString.h>
#include <string.h>

class FairParSet;

ClassImp(FairBaseContFact);

static FairBaseContFact gFairBaseContFact;

FairBaseContFact::FairBaseContFact()
    : FairContFact("FairBaseContFact", "Factory for parameter containers in libSts")
{
    // Constructor (called when the library is loaded)
    setAllContainers();
}

void FairBaseContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted contexts and adds them to
     *  the list of containers for the base library.*/
    FairContainer* pTest = new FairContainer("FairBaseParSet", "class for parameter io", "DefaultContext");
    containers->Add(pTest);

    FairContainer* pGeo = new FairContainer("FairGeoParSet", "class for Geo parameter", "DefaultContext");
    containers->Add(pGeo);
}

FairParSet* FairBaseContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */
    const char* name = c->GetName();
    FairParSet* p = 0;
    if (strcmp(name, "FairBaseParSet") == 0) {
        p = new FairBaseParSet(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    } else if (strcmp(name, "FairGeoParSet") == 0) {
        p = new FairGeoParSet(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return p;
}
