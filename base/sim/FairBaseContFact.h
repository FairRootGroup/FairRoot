/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRBASECONTFACT_H
#define FAIRBASECONTFACT_H

#include "FairContFact.h"   // for FairContFact, etc

#include <Rtypes.h>   // for FairBaseContFact::Class, etc

class FairParSet;

class FairBaseContFact : public FairContFact
{
    /** Factory for all Base parameter containers */
  public:
    /**default ctor*/
    FairBaseContFact();
    /**default dtor*/
    ~FairBaseContFact() override {}
    /** Calls the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */
    FairParSet* createContainer(FairContainer*) override;
    ClassDefOverride(FairBaseContFact, 0);
};

#endif /* !FAIRBASECONTFACT_H */
