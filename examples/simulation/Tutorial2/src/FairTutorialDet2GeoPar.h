/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2GEOPAR_H
#define FAIRTUTORIALDET2GEOPAR_H

#include "FairParGenericSet.h"

#include <Rtypes.h>

class TObjArray;
class FairParamList;

class FairTutorialDet2GeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    FairTutorialDet2GeoPar(const char* name = "FairTutorialDet2GeoPar",
                           const char* title = "FairTutorialDet2 Geometry Parameters",
                           const char* context = "TestDefaultContext");
    ~FairTutorialDet2GeoPar();
    void clear();
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairTutorialDet2GeoPar(const FairTutorialDet2GeoPar&);
    FairTutorialDet2GeoPar& operator=(const FairTutorialDet2GeoPar&);

    ClassDef(FairTutorialDet2GeoPar, 1);
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
