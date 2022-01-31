/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef __FAIRROOT__FairFileSourceBase__
#define __FAIRROOT__FairFileSourceBase__

#include "FairSource.h"

#include <list>
#include <map>

/**
 * \brief Internal base class for FairFileSource and FairMixedSource
 */
class FairFileSourceBase : public FairSource
{
  protected:
    FairFileSourceBase()
        : FairSource(){};
    virtual ~FairFileSourceBase();

    std::map<TString, std::list<TString>*> fCheckInputBranches{};   //!

    ClassDefOverride(FairFileSourceBase, 0);
};

#endif
