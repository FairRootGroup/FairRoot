/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyPassiveContFact  file                    -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------

#ifndef My_PASSIVECONTFACT_H
#define My_PASSIVECONTFACT_H

#include "FairContFact.h"   // for FairContFact, etc

class MyPassiveContFact : public FairContFact
{
  public:
    MyPassiveContFact();
    ~MyPassiveContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(MyPassiveContFact, 0);   // Factory for all Passive parameter containers
};

#endif /* !My_PASSIVECONTFACT_H */
