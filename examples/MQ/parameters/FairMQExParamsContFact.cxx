/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQExParamsContFact.h"

#include "FairMQExParamsParOne.h"

#include <cstring>   // strcmp

static FairMQExParamsContFact gFairMQExParamsContFact;

FairMQExParamsContFact::FairMQExParamsContFact()
    : FairContFact("FairMQExParamsContFact", "Factory for parameter containers in FairMQ Example 7")
{
    FairContainer* container =
        new FairContainer("FairMQExParamsParOne", "FairMQExParamsParOne Parameters", "TestDefaultContext");
    containers->Add(container);
}

FairParSet* FairMQExParamsContFact::createContainer(FairContainer* container)
{
    const char* name = container->GetName();
    FairParSet* p = nullptr;

    if (strcmp(name, "FairMQExParamsParOne") == 0) {
        p = new FairMQExParamsParOne(container->getConcatName().Data(), container->GetTitle(), container->getContext());
    }

    return p;
}

ClassImp(FairMQExParamsContFact);
