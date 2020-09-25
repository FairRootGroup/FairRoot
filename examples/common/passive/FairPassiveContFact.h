/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPASSIVECONTFACT_H
#define FAIRPASSIVECONTFACT_H

#include "FairContFact.h"   // for FairContFact, FairContainer (ptr only)

#include <Rtypes.h>   // for THashConsistencyHolder, ClassDef

class FairParSet;
class TBuffer;
class TClass;
class TMemberInspector;

class FairPassiveContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairPassiveContFact();
    ~FairPassiveContFact() {}
    FairParSet* createContainer(FairContainer*);

    ClassDef(FairPassiveContFact, 0);   // Factory for all Passive parameter containers
};

#endif /* !FAIRPASSIVECONTFACT_H */
