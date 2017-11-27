/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOPIPE_H
#define PNDGEOPIPE_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for FairGeoPipe::Class, Int_t, etc

class FairGeoBuilder;

class  FairGeoPipe : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoPipe();
    virtual ~FairGeoPipe();
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    Bool_t create(FairGeoBuilder*);
    ClassDef(FairGeoPipe,0) // Class for geometry of beam pipe
};

#endif  /* !PNDGEOPIPE_H */
