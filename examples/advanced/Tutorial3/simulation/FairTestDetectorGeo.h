/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORGEO_H_
#define FAIRTESTDETECTORGEO_H_

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>    // for Int_t, etc
#include <TString.h>   // for TString

class FairTestDetectorGeo : public FairGeoSet
{
  protected:
    char modName[20]{"torino"};   // name of module
    char eleName[20]{"torino"};   // substring for elements in module
  public:
    FairTestDetectorGeo();
    ~FairTestDetectorGeo() override = default;
    const char* getModuleName(Int_t) override;
    const char* getEleName(Int_t) override;
    inline Int_t getModNumInMod(const TString&) override;
    ClassDefOverride(FairTestDetectorGeo, 1);
};

inline Int_t FairTestDetectorGeo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
     ?? in name[??] has to be the length of the detector name in the
     .geo file. For example if all nodes in this file starts with
     newdetector ?? has to be 11.
    */
    return static_cast<Int_t>((name[6] - '0') - 1);   //
}

#endif /* FAIRTESTDETECTORGEO_H_ */
