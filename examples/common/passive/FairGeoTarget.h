/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTARGET_H
#define FAIRGEOTARGET_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for FairGeoTarget::Class, Int_t, etc

class FairGeoTarget : public FairGeoSet
{
  protected:
    char modName[2];   // name of module
    char eleName[2];   // substring for elements in module
  public:
    FairGeoTarget();
    ~FairGeoTarget() {}
    const char* getModuleName(Int_t) { return modName; }
    const char* getEleName(Int_t) { return eleName; }
    ClassDef(FairGeoTarget, 0);   // Class for geometry of Target
};

#endif /* !FAIRGEOTARGET_H */
