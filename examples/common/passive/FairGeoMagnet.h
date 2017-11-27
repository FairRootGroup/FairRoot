/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOMAGNET_H
#define PNDGEOMAGNET_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for FairGeoMagnet::Class, Int_t, etc

class  FairGeoMagnet : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoMagnet();
    ~FairGeoMagnet() {}
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    ClassDef(FairGeoMagnet,0) // Class for the geometry of Magnet
};

#endif  /* !FAIRGEOMAGNET_H */
