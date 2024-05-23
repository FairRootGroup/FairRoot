/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDCONTFACT_H
#define CBMRUTHERFORDCONTFACT_H

#include "FairContFact.h"   // for FairContFact, etc

class FairRutherfordContFact : public FairContFact
{
  public:
    FairRutherfordContFact();
    ~FairRutherfordContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(FairRutherfordContFact, 0);   // Factory for all FairRutherford parameter containers
};

#endif
