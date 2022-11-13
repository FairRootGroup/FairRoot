/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDGEO_H
#define CBMRUTHERFORDGEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>    // for Int_t, etc
#include <TString.h>   // for TString

class FairRutherfordGeo : public FairGeoSet
{
  protected:
    char modName[22];   // name of module
    char eleName[22];   // substring for elements in module
  public:
    FairRutherfordGeo();
    ~FairRutherfordGeo() override {}
    const char* getModuleName(Int_t) override;
    const char* getEleName(Int_t) override;
    inline Int_t getModNumInMod(const TString&) override;
    ClassDefOverride(FairRutherfordGeo, 1);
};

inline Int_t FairRutherfordGeo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   newdetector ?? has to be 11.
  */
    return static_cast<Int_t>((name[10] - '0') - 1);   //
}

#endif
