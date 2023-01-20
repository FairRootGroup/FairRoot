/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorContFact.h"

#include "FairConstPar.h"             // for FairConstPar
#include "FairTestDetectorGeoPar.h"   // for FairTestDetectorGeoPar

#include <TList.h>     // for TList
#include <TString.h>   // for TString
#include <cstring>     // for strcmp

class FairParSet;

ClassImp(FairTestDetectorContFact);

static FairTestDetectorContFact gFairTestDetectorContFact;

FairTestDetectorContFact::FairTestDetectorContFact()
    : FairContFact("FairTestDetectorContFact", "Factory for parameter containers in libFairTestDetector")
{
    /** Constructor (called when the library is loaded) */

    /** Creates the Container objects with all accepted
        contexts and adds them to
        the list of containers for the FairTestDetector library.
    */

    auto p = new FairContainer("FairTestDetectorGeoPar", "FairTestDetector Geometry Parameters", "TestDefaultContext");
    AddContainer(p);

    auto p1 = new FairContainer("FairConstPar", "Constant Field Parameters", "TestDefaultContext");
    AddContainer(p1);
}

FairParSet* FairTestDetectorContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
        For an actual context, which is not an empty string and not
        the default context
        of this container, the name is concatinated with the context.
    */
    const char* name = c->GetName();
    FairParSet* p = nullptr;
    if (strcmp(name, "FairTestDetectorGeoPar") == 0) {
        p = new FairTestDetectorGeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    if (strcmp(name, "FairConstPar") == 0) {
        p = new FairConstPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return p;
}
