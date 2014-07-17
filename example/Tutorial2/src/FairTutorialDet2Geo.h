/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2GEO_H
#define FAIRTUTORIALDET2GEO_H

#include "FairGeoSet.h"

class  FairTutorialDet2Geo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    FairTutorialDet2Geo();
    ~FairTutorialDet2Geo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTutorialDet2Geo,1)
};

inline Int_t FairTutorialDet2Geo::getModNumInMod(const TString& name)
{
  /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   tutdet ?? has to be 6.
  */
  return (Int_t)(name[6]-'0')-1; //
}

#endif  /*  FAIRTUTORIALDETGEO_H */
