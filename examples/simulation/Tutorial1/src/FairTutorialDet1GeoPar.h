/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1GEOPAR_H
#define FAIRTUTORIALDET1GEOPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>   // for ClassDef

class TObjArray;
class FairParamList;

class FairTutorialDet1GeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    FairTutorialDet1GeoPar(const char* name = "FairTutorialDet1GeoPar",
                           const char* title = "FairTutorialDet1 Geometry Parameters",
                           const char* context = "TestDefaultContext");
    ~FairTutorialDet1GeoPar();
    void clear();
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairTutorialDet1GeoPar(const FairTutorialDet1GeoPar&);
    FairTutorialDet1GeoPar& operator=(const FairTutorialDet1GeoPar&);

    ClassDef(FairTutorialDet1GeoPar, 1);
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
