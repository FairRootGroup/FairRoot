/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2ContFact.h"

#include "FairTutorialDet2DigiPar.h"
#include "FairTutorialDet2GeoPar.h"

#include <cstring>   // strcmp

ClassImp(FairTutorialDet2ContFact);

static FairTutorialDet2ContFact gFairTutorialDet2ContFact;

FairTutorialDet2ContFact::FairTutorialDet2ContFact()
    : FairContFact("FairTutorialDet2ContFact", "Factory for parameter containers in libTutorial1")
{
    /** Constructor (called when the library is loaded) */

    /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the Tutorial1 library.
  */

    FairContainer* p1 =
        new FairContainer("FairTutorialDet2GeoPar", "FairTutorialDet2 Geometry Parameters", "TestDefaultContext");
    containers->Add(p1);

    FairContainer* p2 =
        new FairContainer("FairTutorialDet2DigiPar", "Tutorial Det Digi Parameters", "TestDefaultContext");
    containers->Add(p2);
}

FairParSet* FairTutorialDet2ContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
    const char* name = c->GetName();
    FairParSet* p = nullptr;
    if (strcmp(name, "FairTutorialDet2GeoPar") == 0) {
        p = new FairTutorialDet2GeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    if (strcmp(name, "FairTutorialDet2DigiPar") == 0) {
        p = new FairTutorialDet2DigiPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return p;
}
