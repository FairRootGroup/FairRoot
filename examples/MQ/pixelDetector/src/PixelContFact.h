/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELCONTFACT_H
#define PIXELCONTFACT_H

#include "FairContFact.h"

#include <Rtypes.h>   // for PixelContFact::Class, ClassDef, PixelContF...

class PixelContFact : public FairContFact
{
  public:
    PixelContFact();
    ~PixelContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(PixelContFact, 0);   // Factory for all Pixel parameter containers
};

#endif
