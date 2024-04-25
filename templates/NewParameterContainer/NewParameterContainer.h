/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef NEWPARAMETERCONTAINER_H
#define NEWPARAMETERCONTAINER_H

#include "FairParGenericSet.h"

class FairParamList;

class NewParameterContainer : public FairParGenericSet
{
  public:
    NewParameterContainer(const char* name = "NewParameterContainer",
                          const char* title = "NewParameterContainer Parameters",
                          const char* context = "TestDefaultContext");
    ~NewParameterContainer();
    void clear();
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

  private:
    NewParameterContainer(const NewParameterContainer&);
    NewParameterContainer& operator=(const NewParameterContainer&);

    ClassDef(NewParameterContainer, 1);
};

#endif
