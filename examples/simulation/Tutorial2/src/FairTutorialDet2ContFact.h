/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2CONTFACT_H
#define FAIRTUTORIALDET2CONTFACT_H

#include "FairContFact.h"

class FairTutorialDet2ContFact : public FairContFact
{
  public:
    FairTutorialDet2ContFact();
    ~FairTutorialDet2ContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(FairTutorialDet2ContFact, 0);   // Factory for all MyDet parameter containers
};

#endif /* !FAIRTUTORIALDETCONTFACT_H */
