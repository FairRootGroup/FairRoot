/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2GEO_H
#define FAIRTUTORIALDET2GEO_H

#include "FairGeoSet.h"

#include <Rtypes.h>

class FairTutorialDet2Geo : public FairGeoSet
{
  protected:
    char modName[20]{"tutdet"};   // name of module
    char eleName[20]{"tutdet"};   // substring for elements in module

  public:
    FairTutorialDet2Geo();
    ~FairTutorialDet2Geo() override = default;
    const char* getModuleName(Int_t) override;
    const char* getEleName(Int_t) override;
    inline Int_t getModNumInMod(const TString&) override;
    ClassDefOverride(FairTutorialDet2Geo, 1);
};

inline Int_t FairTutorialDet2Geo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   tutdet ?? has to be 6.
  */
    return static_cast<Int_t>((name[6] - '0') - 1);   //
}

#endif /*  FAIRTUTORIALDETGEO_H */
