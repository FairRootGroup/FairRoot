/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyPassiveContFact  file                    -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------

//*-- AUTHOR : Denis Bertini
//*-- Created : 21/06/2005

/////////////////////////////////////////////////////////////
//
//  MyPassiveContFact
//
//  Factory for the parameter containers in libPassive
//
/////////////////////////////////////////////////////////////
#include "MyPassiveContFact.h"

#include <TList.h>     // for TList
#include <TString.h>   // for TString
#include <string.h>    // for strcmp, NULL

class FairParSet;

static MyPassiveContFact gMyPassiveContFact;

MyPassiveContFact::MyPassiveContFact()
    : FairContFact("MyPassiveContFact", "Factory for parameter containers in libPassive")
{
    // Constructor (called when the library is loaded)

    /** Creates the Container objects with all accepted contexts and adds them to
     *  the list of containers for the STS library.*/

    auto p = new FairContainer("FairGeoPassivePar", "Passive Geometry Parameters", "TestDefaultContext");
    AddContainer(p);
}

FairParSet* MyPassiveContFact::createContainer(FairContainer* c)
{
    return nullptr;
    /** Calls the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */
    /* const char* name=c->GetName();
  FairParSet* p=NULL;
  if (strcmp(name,"FairGeoPassivePar")==0) {
    p=new FairGeoPassivePar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }
  return p;
*/
}
