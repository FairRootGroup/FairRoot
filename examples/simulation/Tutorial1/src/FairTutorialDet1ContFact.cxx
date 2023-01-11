/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet1ContFact.h"

#include "FairTutorialDet1GeoPar.h"   // for FairTutorialDet1GeoPar

#include <TList.h>     // for TList
#include <TString.h>   // for TString
#include <cstring>     // for strcmp

class FairParSet;

ClassImp(FairTutorialDet1ContFact);

static FairTutorialDet1ContFact gFairTutorialDet1ContFact;

FairTutorialDet1ContFact::FairTutorialDet1ContFact()
    : FairContFact("FairTutorialDet1ContFact", "Factory for parameter containers in libTutorial1")
{
    /** Constructor (called when the library is loaded) */

    /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the Tutorial1 library.
  */

    FairContainer* p =
        new FairContainer("FairTutorialDet1GeoPar", "FairTutorialDet1 Geometry Parameters", "TestDefaultContext");
    containers->Add(p);
}

FairParSet* FairTutorialDet1ContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
    const char* name = c->GetName();
    FairParSet* p = nullptr;
    if (strcmp(name, "FairTutorialDet1GeoPar") == 0) {
        p = new FairTutorialDet1GeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}
