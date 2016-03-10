/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEOPAR_H
#define PIXELGEOPAR_H

#include "FairParGenericSet.h"  // for FairParGenericSet
#include "Rtypes.h"             // for PixelGeoPar::Class, ClassDef, PixelGe...
#include "RtypesCore.h"         // for Bool_t
class FairParamList;  // lines 14-14
class TObjArray;  // lines 13-13

class PixelGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    PixelGeoPar(const char* name="PixelGeoPar",
                      const char* title="Pixel Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~PixelGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    PixelGeoPar(const PixelGeoPar&);
    PixelGeoPar& operator=(const PixelGeoPar&);

    ClassDef(PixelGeoPar,1)
};

#endif
