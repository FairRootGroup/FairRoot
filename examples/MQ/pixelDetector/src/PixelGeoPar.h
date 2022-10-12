/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEOPAR_H
#define PIXELGEOPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>   // for PixelGeoPar::Class, ClassDef, PixelGe...

class FairParamList;
class TObjArray;

class PixelGeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    PixelGeoPar(const char* name = "PixelGeoPar",
                const char* title = "Pixel Geometry Parameters",
                const char* context = "TestDefaultContext");
    ~PixelGeoPar() override;
    void clear() override;
    void putParams(FairParamList*) override;
    Bool_t getParams(FairParamList*) override;
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    PixelGeoPar(const PixelGeoPar&);
    PixelGeoPar& operator=(const PixelGeoPar&);

    ClassDefOverride(PixelGeoPar, 1);
};

#endif
