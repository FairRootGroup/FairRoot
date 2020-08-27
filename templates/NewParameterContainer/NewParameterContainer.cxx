/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewParameterContainer.h"

#include "FairParamList.h"

#include <iostream>

ClassImp(NewParameterContainer);

NewParameterContainer ::NewParameterContainer(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{}

NewParameterContainer::~NewParameterContainer(void) {}

void NewParameterContainer::clear(void) {}

void NewParameterContainer::putParams(FairParamList* l)
{
    if (!l) {
        return;
    }
}

Bool_t NewParameterContainer::getParams(FairParamList* l)
{
    if (!l) {
        return kFALSE;
    }
    return kTRUE;
}
