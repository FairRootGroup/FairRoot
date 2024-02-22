/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORCONTFACT_H_
#define FAIRTESTDETECTORCONTFACT_H_

#include "FairContFact.h"   // for FairContFact, etc

class FairTestDetectorContFact : public FairContFact
{
  public:
    FairTestDetectorContFact();
    ~FairTestDetectorContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;

    // Factory for all FairTestDetector parameter containers
    ClassDefOverride(FairTestDetectorContFact, 0);
};

#endif /* FAIRTESTDETECTORCONTFACT_H_ */
