/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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
    char modName[20];   // name of module
    char eleName[20];   // substring for elements in module
  public:
    FairTutPropGeo();
    ~FairTutPropGeo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTutPropGeo, 1);
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
