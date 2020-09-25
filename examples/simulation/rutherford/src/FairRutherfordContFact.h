/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDCONTFACT_H
#define CBMRUTHERFORDCONTFACT_H

#include "FairContFact.h"   // for FairContFact, FairContainer (ptr only)

#include <Rtypes.h>   // for THashConsistencyHolder, ClassDef

class FairParSet;
class TBuffer;
class TClass;
class TMemberInspector;

class FairRutherfordContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairRutherfordContFact();
    ~FairRutherfordContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef(FairRutherfordContFact, 0);   // Factory for all FairRutherford parameter containers
};

#endif
