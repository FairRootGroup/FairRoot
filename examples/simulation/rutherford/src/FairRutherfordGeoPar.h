/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDGEOPAR_H
#define CBMRUTHERFORDGEOPAR_H

#include <Rtypes.h>             // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>         // for Bool_t
#include "FairParGenericSet.h"  // for FairParGenericSet
class FairParamList;  // lines 16-16
class TBuffer;
class TClass;
class TObjArray;   // lines 15-15

class FairRutherfordGeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    FairRutherfordGeoPar(const char* name = "FairRutherfordGeoPar",
                         const char* title = "FairRutherford Geometry Parameters",
                         const char* context = "TestDefaultContext");
    ~FairRutherfordGeoPar() override;
    void clear() override;
    void putParams(FairParamList*) override;
    Bool_t getParams(FairParamList*) override;
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairRutherfordGeoPar(const FairRutherfordGeoPar&);
    FairRutherfordGeoPar& operator=(const FairRutherfordGeoPar&);

    ClassDefOverride(FairRutherfordGeoPar, 1);
};

#endif
