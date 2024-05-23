/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOPIPE_H
#define FAIRGEOPIPE_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for FairGeoPipe::Class, Int_t, etc

class FairGeoPipe : public FairGeoSet
{
  protected:
    char modName[2]{"p"};   // name of module
    char eleName[2]{"p"};   // substring for elements in module

  public:
    FairGeoPipe();
    ~FairGeoPipe() override = default;
    const char* getModuleName(Int_t) override { return modName; }
    const char* getEleName(Int_t) override { return eleName; }
    Bool_t create(FairGeoBuilder*) override;
    ClassDefOverride(FairGeoPipe, 0);   // Class for geometry of beam pipe
};

#endif /* !FAIRGEOPIPE_H */
