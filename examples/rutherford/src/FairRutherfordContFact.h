/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDCONTFACT_H
#define CBMRUTHERFORDCONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for ClassDef

class FairParSet;

class FairRutherfordContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairRutherfordContFact();
    ~FairRutherfordContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairRutherfordContFact,0) // Factory for all FairRutherford parameter containers
};

#endif
