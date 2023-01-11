/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1CONTFACT_H
#define FAIRTUTORIALDET1CONTFACT_H

#include "FairContFact.h"   // for FairContFact, etc

#include <Rtypes.h>

class FairParSet;

class FairTutorialDet1ContFact : public FairContFact
{
  public:
    FairTutorialDet1ContFact();
    ~FairTutorialDet1ContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef(FairTutorialDet1ContFact, 0);   // Factory for all MyDet parameter containers
};

#endif /* !FAIRTUTORIALDETCONTFACT_H */
