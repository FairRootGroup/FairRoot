/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4CONTFACT_H
#define FAIRTUTORIALDET4CONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for ClassDef

class FairParSet;

class FairTutorialDet4ContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairTutorialDet4ContFact();
    ~FairTutorialDet4ContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairTutorialDet4ContFact,0) // Factory for all MyDet parameter containers
};

#endif  /* !FAIRTUTORIALDETCONTFACT_H */
