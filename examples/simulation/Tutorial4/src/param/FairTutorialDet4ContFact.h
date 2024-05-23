/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4CONTFACT_H
#define FAIRTUTORIALDET4CONTFACT_H

#include "FairContFact.h"   // for FairContFact, etc

class FairTutorialDet4ContFact : public FairContFact
{
  public:
    FairTutorialDet4ContFact();
    ~FairTutorialDet4ContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(FairTutorialDet4ContFact, 0);   // Factory for all MyDet parameter containers
};

#endif /* !FAIRTUTORIALDETCONTFACT_H */
