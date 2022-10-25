/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/** FairConstField.h
 ** @author M.Al-Turany <m.al/turany@gsi.de>
 ** @since 30.01.2007
 ** @version 1.0
 ** A constant  magnetic field
 **/

#ifndef FairConstFIELD_H
#define FairConstFIELD_H 1

#include "FairField.h"   // for FairField

#include <Rtypes.h>   // for Double_t, etc

class FairConstPar;

class FairConstField : public FairField
{
  public:
    /** Default constructor **/
    FairConstField();

    /** Standard constructor
     ** @param name   Object name
     ** @param xMin,xMax   x region of field (global coordinates)
     ** @param yMin,yMax   y region of field (global coordinates)
     ** @param zMin,zMax   z region of field (global coordinates)
     ** @param bX,bY,bZ    Field values [kG]
     **/
    FairConstField(const char* name,
                   Double_t xMin,
                   Double_t xMax,
                   Double_t yMin,
                   Double_t yMax,
                   Double_t zMin,
                   Double_t zMax,
                   Double_t bX,
                   Double_t bY,
                   Double_t bZ);

    /** Constructor from FairConstPar **/
    FairConstField(FairConstPar* fieldPar);

    /** Destructor **/
    ~FairConstField() override;

    void FillParContainer() override;

    /** Set the field region
     ** @param xMin,xMax   x region of field (global coordinates)
     ** @param yMin,yMax   y region of field (global coordinates)
     ** @param zMin,zMax   z region of field (global coordinates)
     **/
    void SetFieldRegion(Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Double_t zMin, Double_t zMax);

    /** Set the field values
     ** @param bX,bY,bZ    Field values [kG]
     **/
    void SetField(Double_t bX, Double_t bY, Double_t bZ);

    Double_t GetBx(Double_t x, Double_t y, Double_t z) override;
    Double_t GetBy(Double_t x, Double_t y, Double_t z) override;
    Double_t GetBz(Double_t x, Double_t y, Double_t z) override;

    /** Accessors to field region **/
    Double_t GetXmin() const { return fXmin; }
    Double_t GetXmax() const { return fXmax; }
    Double_t GetYmin() const { return fYmin; }
    Double_t GetYmax() const { return fYmax; }
    Double_t GetZmin() const { return fZmin; }
    Double_t GetZmax() const { return fZmax; }

    /** Accessors to field values **/
    Double_t GetBx() const { return fBx; }
    Double_t GetBy() const { return fBy; }
    Double_t GetBz() const { return fBz; }

    /** Screen output **/
    void Print(Option_t*) const override;

    ClassDefOverride(FairConstField, 1);

  private:
    /** Limits of the field region **/
    Double_t fXmin;
    Double_t fXmax;
    Double_t fYmin;
    Double_t fYmax;
    Double_t fZmin;
    Double_t fZmax;

    /** Field components inside the field region **/
    Double_t fBx;
    Double_t fBy;
    Double_t fBz;
};

#endif
