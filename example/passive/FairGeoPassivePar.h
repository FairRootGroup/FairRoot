/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOPASSIVEPAR_H
#define PNDGEOPASSIVEPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for FairGeoPassivePar::Class, etc

class FairParamList;
class TObjArray;

class FairGeoPassivePar : public FairParGenericSet
{
  public:
    TObjArray*            fGeoSensNodes; // List of FairGeoNodes for sensitive volumes
    TObjArray*            fGeoPassNodes; // List of FairGeoNodes for sensitive volumes

    FairGeoPassivePar(const char* name="FairGeoPassivePar",
                      const char* title="Passive Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~FairGeoPassivePar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray*             GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray*             GetGeoPassiveNodes() {return fGeoPassNodes;}

  private:
    FairGeoPassivePar(const FairGeoPassivePar&);
    FairGeoPassivePar& operator=(const FairGeoPassivePar&);

    ClassDef(FairGeoPassivePar,1)
};

#endif /* !PNDGEOPASSIVEPAR_H */
