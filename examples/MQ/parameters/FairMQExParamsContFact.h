/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXPARAMSCONTFACT_H
#define FAIRMQEXPARAMSCONTFACT_H

#include "FairContFact.h"   // for FairContFact, FairContainer (ptr only)

#include <Rtypes.h>   // for THashConsistencyHolder, ClassDef

class FairContainer;
class FairParSet;
class TBuffer;
class TClass;
class TMemberInspector;

class FairMQExParamsContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairMQExParamsContFact();
    ~FairMQExParamsContFact() {}

    FairParSet* createContainer(FairContainer*);
    ClassDef(FairMQExParamsContFact, 0);
};

#endif /* FAIRMQEXPARAMSCONTFACT_H */
