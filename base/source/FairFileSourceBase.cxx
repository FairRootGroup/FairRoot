/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairFileSourceBase.h"

#include <algorithm>   // for std::for_each

ClassImp(FairFileSourceBase);

FairFileSourceBase::~FairFileSourceBase()
{
    std::for_each(fCheckInputBranches.begin(), fCheckInputBranches.end(), [](auto el) {
        delete el.second;
        el.second = nullptr;
    });
    fCheckInputBranches.clear();
}
