/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBTUTCONTFACT_H
#define FAIRDBTUTCONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairDbTutContFact::Class, etc

class FairParSet;

class FairDbTutContFact : public FairContFact
{
  public:
    FairDbTutContFact();
    ~FairDbTutContFact() {}
    FairParSet* createContainer(FairContainer* c);
  private:
    void setAllContainers();

    ClassDef( FairDbTutContFact,0); // Factory for parameter containers
};

#endif  /* !FAIRDBTUTCONTFACT_H */
