/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4GEOPAR_H
#define FAIRTUTORIALDET4GEOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef 

class TObjArray;
class FairParamList;

class FairTutorialDet4GeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairTutorialDet4GeoPar(const char* name="FairTutorialDet4GeoPar",
                           const char* title="FairTutorialDet4 Geometry Parameters",
                           const char* context="TestDefaultContext");
    ~FairTutorialDet4GeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairTutorialDet4GeoPar(const FairTutorialDet4GeoPar&);
    FairTutorialDet4GeoPar& operator=(const FairTutorialDet4GeoPar&);

    ClassDef(FairTutorialDet4GeoPar,1)
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
