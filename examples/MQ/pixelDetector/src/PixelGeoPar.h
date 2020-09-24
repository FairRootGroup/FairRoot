/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEOPAR_H
#define PIXELGEOPAR_H

#include <Rtypes.h>             // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>         // for Bool_t

#include "FairParGenericSet.h"  // for FairParGenericSet

class FairParamList;
class TObjArray;
class TBuffer;
class TClass;
class TMemberInspector;

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
    ~PixelGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    PixelGeoPar(const PixelGeoPar&);
    PixelGeoPar& operator=(const PixelGeoPar&);

    ClassDef(PixelGeoPar, 1);
};

#endif
