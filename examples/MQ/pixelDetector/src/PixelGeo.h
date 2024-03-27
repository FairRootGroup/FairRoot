/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEO_H
#define PIXELGEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>    // for PixelGeo::Class, ClassDef, PixelGeo::Streamer
#include <TString.h>   // for TString

class PixelGeo : public FairGeoSet
{
  protected:
    static constexpr int maxbuf{20}; //!
    char modName[maxbuf]{"Pixel"};   // name of module
    char eleName[maxbuf]{"Pixel"};   // substring for elements in module

  public:
    PixelGeo();
    ~PixelGeo() override = default;
    const char* getModuleName(Int_t) override;
    const char* getEleName(Int_t) override;
    inline Int_t getModNumInMod(const TString&) override;

    ClassDefOverride(PixelGeo, 1);
};

inline Int_t PixelGeo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   newdetector ?? has to be 11.
  */
    return static_cast<Int_t>((name[5] - '0') - 1);   //
}

#endif
