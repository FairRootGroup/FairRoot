/********************************************************************************
 * Copyright (C) 2019-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPGEOPAR_H
#define FAIRTUTPROPGEOPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet
#include "Rtypes.h"              // for FairTutPropGeoPar::Class, ClassDef, PixelGe...
class FairParamList;             // lines 14-14
class TObjArray;                 // lines 13-13

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
    ~FairTutPropGeoPar() override;
    void clear() override;
    void putParams(FairParamList*) override;
    Bool_t getParams(FairParamList*) override;
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairTutPropGeoPar(const FairTutPropGeoPar&);
    FairTutPropGeoPar& operator=(const FairTutPropGeoPar&);

    ClassDefOverride(FairTutPropGeoPar, 1);
};

#endif   // FAIRTUTPROPGEOPAR_H
