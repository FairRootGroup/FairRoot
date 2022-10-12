/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXPARAMSCONTFACT_H
#define FAIRMQEXPARAMSCONTFACT_H

#include "FairContFact.h"

class FairContainer;
class FairParSet;

class FairMQExParamsContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairMQExParamsContFact();
    ~FairMQExParamsContFact() override = default;

    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(FairMQExParamsContFact, 0);
};

#endif /* FAIRMQEXPARAMSCONTFACT_H */
