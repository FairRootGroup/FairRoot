/********************************************************************************
 * Copyright (C) 2019-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPGEO_H
#define FAIRTUTPROPGEO_H

#include "FairGeoSet.h"   // for FairGeoSet
#include "Rtypes.h"       // for FairTutPropGeo::Class, ClassDef, FairTutPropGeo::Streamer
#include "TString.h"      // for TString

class FairTutPropGeo : public FairGeoSet
{
  protected:
    static constexpr int maxbuf{20}; //!
    char modName[maxbuf]{"Pixel"};   // name of module
    char eleName[maxbuf]{"Pixel"};   // substring for elements in module
  public:
    FairTutPropGeo();
    ~FairTutPropGeo() override = default;
    const char* getModuleName(Int_t) override;
    const char* getEleName(Int_t) override;
    inline Int_t getModNumInMod(const TString&) override;
    ClassDefOverride(FairTutPropGeo, 1);
};

inline Int_t FairTutPropGeo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   newdetector ?? has to be 11.
  */
    return static_cast<Int_t>((name[5] - '0') - 1);   //
}

#endif   // FAIRTUTPROPGEO_H
