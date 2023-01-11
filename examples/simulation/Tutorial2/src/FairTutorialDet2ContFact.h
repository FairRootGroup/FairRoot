/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2CONTFACT_H
#define FAIRTUTORIALDET2CONTFACT_H

#include "FairContFact.h"

#include <Rtypes.h>

class FairParSet;

class FairTutorialDet2ContFact : public FairContFact
{
  public:
    FairTutorialDet2ContFact();
    ~FairTutorialDet2ContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef(FairTutorialDet2ContFact, 0);   // Factory for all MyDet parameter containers
};

#endif /* !FAIRTUTORIALDETCONTFACT_H */
