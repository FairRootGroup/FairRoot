/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPCONTFACT_H_
#define FAIRTUTPROPCONTFACT_H_

#include "FairContFact.h"  // for FairContFact, FairContainer (ptr only)
#include "Rtypes.h"        // for THashConsistencyHolder, ClassDef

class FairParSet;
class TBuffer;
class TClass;
class TMemberInspector;

class FairTutPropContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairTutPropContFact();
    ~FairTutPropContFact() {}
    FairParSet* createContainer(FairContainer*);

    // Factory for all FairTutProp parameter containers
    ClassDef(FairTutPropContFact, 0);
};

#endif /* FAIRTUTPROPCONTFACT_H_ */
