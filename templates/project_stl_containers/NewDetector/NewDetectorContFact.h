/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef NEWDETECTORCONTFACT_H
#define NEWDETECTORCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class NewDetectorContFact : public FairContFact
{
  public:
    NewDetectorContFact();
    ~NewDetectorContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef(NewDetectorContFact, 0);   // Factory for all NewDetector parameter containers
};

#endif
