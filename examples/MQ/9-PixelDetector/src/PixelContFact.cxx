/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "PixelContFact.h"

#include "PixelGeoPar.h"

#include "FairRuntimeDb.h"

#include <iostream>

ClassImp(PixelContFact)

static PixelContFact gPixelContFact;

PixelContFact::PixelContFact()
  : FairContFact()
{
  /** Constructor (called when the library is loaded) */
  fName="PixelContFact";
  fTitle="Factory for parameter containers in libPixel";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void PixelContFact::setAllContainers()
{
  /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the Pixel library.
  */

  FairContainer* p= new FairContainer("PixelGeoPar",
                                      "Pixel Geometry Parameters",
                                      "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);
}

FairParSet* PixelContFact::createContainer(FairContainer* c)
{
  /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
  const char* name=c->GetName();
  FairParSet* p=NULL;
  if (strcmp(name,"PixelGeoPar")==0) {
    p=new PixelGeoPar(c->getConcatName().Data(),
                            c->GetTitle(),c->getContext());
  }
  return p;
}
