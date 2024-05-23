/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef NEWDETECTORGEOPAR_H
#define NEWDETECTORGEOPAR_H

#include "FairParGenericSet.h"

class TObjArray;
class FairParamList;

class NewDetectorGeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    NewDetectorGeoPar(const char* name = "NewDetectorGeoPar",
                      const char* title = "NewDetector Geometry Parameters",
                      const char* context = "TestDefaultContext");
    ~NewDetectorGeoPar();
    void clear();
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

  private:
    NewDetectorGeoPar(const NewDetectorGeoPar&);
    NewDetectorGeoPar& operator=(const NewDetectorGeoPar&);

    ClassDef(NewDetectorGeoPar, 1);
};

#endif
