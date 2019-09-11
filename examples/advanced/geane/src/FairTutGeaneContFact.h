/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTGEANECONTFACT_H_
#define FAIRTUTGEANECONTFACT_H_

#include "FairContFact.h" // for FairContFact, etc

#include "Rtypes.h" // for ClassDef

class FairParSet;

class FairTutGeaneContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairTutGeaneContFact();
    ~FairTutGeaneContFact()
    {
    }
    FairParSet* createContainer(FairContainer*);
    ClassDef(FairTutGeaneContFact, 0) // Factory for all FairTutGeane parameter containers
};

#endif /* FAIRTESTDETECTORCONTFACT_H_ */
