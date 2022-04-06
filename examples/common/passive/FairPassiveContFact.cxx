/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Denis Bertini
//*-- Created : 21/06/2005

/////////////////////////////////////////////////////////////
//
//  FairPassiveContFact
//
//  Factory for the parameter containers in libPassive
//
/////////////////////////////////////////////////////////////
#include "FairPassiveContFact.h"

#include "FairGeoPassivePar.h"   // for FairGeoPassivePar
#include "FairRuntimeDb.h"       // for FairRuntimeDb

#include <TList.h>     // for TList
#include <TString.h>   // for TString
#include <string.h>    // for strcmp

class FairParSet;

ClassImp(FairPassiveContFact);

static FairPassiveContFact gFairPassiveContFact;

FairPassiveContFact::FairPassiveContFact()
    : FairContFact()
{
    // Constructor (called when the library is loaded)
    fName = "FairPassiveContFact";
    fTitle = "Factory for parameter containers in libPassive";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void FairPassiveContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted contexts and adds them to
     *  the list of containers for the STS library.*/

    FairContainer* p = new FairContainer("FairGeoPassivePar", "Passive Geometry Parameters", "TestDefaultContext");
    p->addContext("TestNonDefaultContext");

    containers->Add(p);
}

FairParSet* FairPassiveContFact::createContainer(FairContainer* c)
{
    /** Calls the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */
    const char* name = c->GetName();
    FairParSet* p = nullptr;
    if (strcmp(name, "FairGeoPassivePar") == 0) {
        p = new FairGeoPassivePar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}
