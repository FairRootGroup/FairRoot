/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPGEOPAR_H
#define FAIRTUTPROPGEOPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet
#include "Rtypes.h"              // for THashConsistencyHolder, ClassDef

#include <RtypesCore.h>   // for Bool_t

class FairParamList;   // lines 14-14
class TObjArray;       // lines 13-13
class TBuffer;
class TClass;
class TMemberInspector;

class FairTutPropGeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    FairTutPropGeoPar(const char* name = "FairTutPropGeoPar",
                      const char* title = "Pixel Geometry Parameters",
                      const char* context = "TestDefaultContext");
    ~FairTutPropGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairTutPropGeoPar(const FairTutPropGeoPar&);
    FairTutPropGeoPar& operator=(const FairTutPropGeoPar&);

    ClassDef(FairTutPropGeoPar, 1);
};

#endif   // FAIRTUTPROPGEOPAR_H
