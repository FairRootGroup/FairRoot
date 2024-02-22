/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPASSIVECONTFACT_H
#define FAIRPASSIVECONTFACT_H

#include "FairContFact.h"   // for FairContFact, etc

#include <Rtypes.h>   // for FairPassiveContFact::Class, etc

class FairParSet;

class FairPassiveContFact : public FairContFact
{
  public:
    FairPassiveContFact();
    ~FairPassiveContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;

    ClassDefOverride(FairPassiveContFact, 0);   // Factory for all Passive parameter containers
};

#endif /* !FAIRPASSIVECONTFACT_H */
