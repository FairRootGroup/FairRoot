/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4ContFact.h"

#include "FairTutorialDet4GeoPar.h"   // for FairTutorialDet4GeoPar
#include "FairTutorialDet4MisalignPar.h"

#include <TList.h>     // for TList
#include <TString.h>   // for TString
#include <cstring>     // for strcmp

class FairParSet;

ClassImp(FairTutorialDet4ContFact);

static FairTutorialDet4ContFact gFairTutorialDet4ContFact;

FairTutorialDet4ContFact::FairTutorialDet4ContFact()
    : FairContFact("FairTutorialDet4ContFact", "Factory for parameter containers in libTutorial1")
{
    /** Constructor (called when the library is loaded) */

    /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the Tutorial1 library.
  */

    auto p = new FairContainer("FairTutorialDet4GeoPar", "FairTutorialDet4 Geometry Parameters", "TestDefaultContext");
    AddContainer(p);

    auto p1 = new FairContainer(
        "FairTutorialDet4MissallignPar", "FairTutorialDet4 Missallignment Parameters", "TestDefaultContext");
    AddContainer(p1);
}

FairParSet* FairTutorialDet4ContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
    const char* name = c->GetName();
    FairParSet* p = nullptr;
    if (strcmp(name, "FairTutorialDet4GeoPar") == 0) {
        p = new FairTutorialDet4GeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    if (strcmp(name, "FairTutorialDet4MissallignPar") == 0) {
        p = new FairTutorialDet4MisalignPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}
