/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** FairMapPar.h
 ** @author M.Al-Turany
 ** @since 30.01.2007
 ** @version 1.0
 **
 ** Parameter set field maps.
 **/

#ifndef FairMAPPAR_H
#define FairMAPPAR_H 1

#include "FairParGenericSet.h" // for FairParGenericSet

#include "Rtypes.h"  // for Double_t, FairMapPar::Class, etc
#include "TString.h" // for TString

class FairMapPar : public FairParGenericSet
{

  public:
    /** Standard constructor  **/
    FairMapPar(const char* name, const char* title, const char* context);

    /** default constructor  **/
    FairMapPar();

    /** Destructor **/
    ~FairMapPar();

    /** Accessors **/
    Int_t GetType() const
    {
        return fType;
    }
    Double_t GetXmin() const
    {
        return fXmin;
    }
    Double_t GetXmax() const
    {
        return fXmax;
    }
    Double_t GetYmin() const
    {
        return fYmin;
    }
    Double_t GetYmax() const
    {
        return fYmax;
    }
    Double_t GetZmin() const
    {
        return fZmin;
    }
    Double_t GetZmax() const
    {
        return fZmax;
    }
    void MapName(TString& name)
    {
        name = fMapName;
    }
    Double_t GetPositionX() const
    {
        return fPosX;
    }
    Double_t GetPositionY() const
    {
        return fPosY;
    }
    Double_t GetPositionZ() const
    {
        return fPosZ;
    }
    Double_t GetScale() const
    {
        return fScale;
    }

  protected:
    /** Field type
     ** 0 = constant field
     ** 1 = field map
     ** 2 = field map sym2 (symmetries in x and y)
     ** 3 = field map sym3 (symmetries in x, y and z)
     **/
    Int_t fType;

    /** Field limits in case of constant field **/
    Double_t fXmin, fXmax;
    Double_t fYmin, fYmax;
    Double_t fZmin, fZmax;

    /** Field map name in case of field map **/
    TString fMapName;

    /** Field centre position for field map **/
    Double_t fPosX, fPosY, fPosZ;

    /** Scaling factor for field map **/
    Double_t fScale;

    ClassDef(FairMapPar, 1);
};

#endif
