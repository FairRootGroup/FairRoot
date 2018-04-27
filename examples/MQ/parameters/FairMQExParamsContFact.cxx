/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <iostream>

#include "FairRuntimeDb.h"

#include "FairMQExParamsContFact.h"
#include "FairMQExParamsParOne.h"

static FairMQExParamsContFact gFairMQExParamsContFact;

FairMQExParamsContFact::FairMQExParamsContFact()
{
    fName = "FairMQExParamsContFact";
    fTitle = "Factory for parameter containers in FairMQ Example 7";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void FairMQExParamsContFact::setAllContainers()
{
    FairContainer* container = new FairContainer("FairMQExParamsParOne", "FairMQExParamsParOne Parameters", "TestDefaultContext");
    container->addContext("TestNonDefaultContext");

    containers->Add(container);
}

FairParSet* FairMQExParamsContFact::createContainer(FairContainer* container)
{
    const char* name = container->GetName();
    FairParSet* p = NULL;

    if (strcmp(name, "FairMQExParamsParOne") == 0)
    {
        p = new FairMQExParamsParOne(container->getConcatName().Data(), container->GetTitle(), container->getContext());
    }

    return p;
}

ClassImp(FairMQExParamsContFact);
