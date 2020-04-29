/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4GEO_H
#define FAIRTUTORIALDET4GEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>    // for Int_t, etc
#include <TString.h>   // for TString

class FairTutorialDet4Geo : public FairGeoSet
{
  protected:
    char modName[20];   // name of module
    char eleName[20];   // substring for elements in module

  public:
    FairTutorialDet4Geo();
    ~FairTutorialDet4Geo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTutorialDet4Geo, 1);
};

inline Int_t FairTutorialDet4Geo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   tutdet ?? has to be 6.
  */
    return static_cast<Int_t>((name[6] - '0') - 1);   //
}

#endif /*  FAIRTUTORIALDETGEO_H */
