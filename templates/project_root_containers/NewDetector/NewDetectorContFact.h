/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef NEWDETECTORCONTFACT_H
#define NEWDETECTORCONTFACT_H

#include "FairContFact.h"

class NewDetectorContFact : public FairContFact
{
  public:
    NewDetectorContFact();
    ~NewDetectorContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(NewDetectorContFact, 0);   // Factory for all NewDetector parameter containers
};

#endif
