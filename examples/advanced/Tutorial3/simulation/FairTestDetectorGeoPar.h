/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORGEOPAR_H_
#define FAIRTESTDETECTORGEOPAR_H_

#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>   // for Class Def

class TObjArray;
class FairParamList;

class FairTestDetectorGeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    FairTestDetectorGeoPar(const char* name = "FairTestDetectorGeoPar",
                           const char* title = "FairTestDetector Geometry Parameters",
                           const char* context = "TestDefaultContext");
    ~FairTestDetectorGeoPar() override;
    void clear() override;
    void putParams(FairParamList*) override;
    Bool_t getParams(FairParamList*) override;
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    FairTestDetectorGeoPar(const FairTestDetectorGeoPar&);
    FairTestDetectorGeoPar& operator=(const FairTestDetectorGeoPar&);

    ClassDefOverride(FairTestDetectorGeoPar, 1);
};

#endif /* FAIRTESTDETECTORGEOPAR_H_ */
