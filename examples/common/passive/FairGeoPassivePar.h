/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOPASSIVEPAR_H
#define FAIRGEOPASSIVEPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>   // for FairGeoPassivePar::Class, etc

class FairParamList;
class TObjArray;

class FairGeoPassivePar : public FairParGenericSet
{
  public:
    TObjArray* fGeoSensNodes;   // List of FairGeoNodes for sensitive volumes
    TObjArray* fGeoPassNodes;   // List of FairGeoNodes for sensitive volumes

    FairGeoPassivePar(const char* name = "FairGeoPassivePar",
                      const char* title = "Passive Geometry Parameters",
                      const char* context = "TestDefaultContext");
    ~FairGeoPassivePar();
    void clear();
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairGeoPassivePar(const FairGeoPassivePar&);
    FairGeoPassivePar& operator=(const FairGeoPassivePar&);

    ClassDef(FairGeoPassivePar, 1);
};

#endif /* !FAIRGEOPASSIVEPAR_H */
