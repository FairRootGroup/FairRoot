/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDGEOPAR_H
#define CBMRUTHERFORDGEOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for FairRutherfordGeoPar::Class, etc

class TObjArray;
class FairParamList;

class FairRutherfordGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairRutherfordGeoPar(const char* name="FairRutherfordGeoPar",
                         const char* title="FairRutherford Geometry Parameters",
                         const char* context="TestDefaultContext");
    ~FairRutherfordGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairRutherfordGeoPar(const FairRutherfordGeoPar&);
    FairRutherfordGeoPar& operator=(const FairRutherfordGeoPar&);

    ClassDef(FairRutherfordGeoPar,1)
};

#endif
