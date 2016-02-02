/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELCONTFACT_H
#define PIXELCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class PixelContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    PixelContFact();
    ~PixelContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( PixelContFact,0) // Factory for all Pixel parameter containers
};

#endif
