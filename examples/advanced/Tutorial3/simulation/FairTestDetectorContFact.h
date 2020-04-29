/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORCONTFACT_H_
#define FAIRTESTDETECTORCONTFACT_H_

#include "FairContFact.h"   // for FairContFact, etc

#include <Rtypes.h>   // for ClassDef

class FairParSet;

class FairTestDetectorContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairTestDetectorContFact();
    ~FairTestDetectorContFact() {}
    FairParSet* createContainer(FairContainer*);

    // Factory for all FairTestDetector parameter containers
    ClassDef(FairTestDetectorContFact, 0);
};

#endif /* FAIRTESTDETECTORCONTFACT_H_ */
