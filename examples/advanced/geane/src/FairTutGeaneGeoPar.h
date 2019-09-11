/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTGEANEGEOPAR_H
#define FAIRTUTGEANEGEOPAR_H

#include "FairParGenericSet.h"  // for FairParGenericSet
#include "Rtypes.h"             // for FairTutGeaneGeoPar::Class, ClassDef, PixelGe...
class FairParamList;  // lines 14-14
class TObjArray;  // lines 13-13

class FairTutGeaneGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairTutGeaneGeoPar(const char* name="FairTutGeaneGeoPar",
                      const char* title="Pixel Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~FairTutGeaneGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairTutGeaneGeoPar(const FairTutGeaneGeoPar&);
    FairTutGeaneGeoPar& operator=(const FairTutGeaneGeoPar&);

    ClassDef(FairTutGeaneGeoPar,1)
};

#endif
