/********************************************************************************
 * Copyright (C) 2019-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPCONTFACT_H_
#define FAIRTUTPROPCONTFACT_H_

#include "FairContFact.h"   // for FairContFact, etc
#include "Rtypes.h"         // for ClassDef

class FairParSet;

class FairTutPropContFact : public FairContFact
{
  public:
    FairTutPropContFact();
    ~FairTutPropContFact() override = default;
    FairParSet* createContainer(FairContainer*) override;

    // Factory for all FairTutProp parameter containers
    ClassDefOverride(FairTutPropContFact, 0);
};

#endif /* FAIRTUTPROPCONTFACT_H_ */
