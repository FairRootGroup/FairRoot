/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyConstField header file                  -----
// -----                Created 25/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------

/** MyConstField.h
 ** @author M.Al-Turany <m.al/turany@gsi.de>
 ** @since 25.03.2014
 ** @version 1.0
 **
 ** A constant (homogeneous) magnetic field
 **/

#ifndef MyConstField_H
#define MyConstField_H 1

#include "FairField.h"

class MyFieldPar;

class MyConstField : public FairField
{

  public:
    /** Default constructor **/
    MyConstField();

    /** Standard constructor
     ** @param name   Object name
     ** @param xMin,xMax   x region of field (global coordinates)
     ** @param yMin,yMax   y region of field (global coordinates)
     ** @param zMin,zMax   z region of field (global coordinates)
     ** @param bX,bY,bZ    Field values [kG]
     **/
    MyConstField(const char* name,
                 Double_t xMin,
                 Double_t xMax,
                 Double_t yMin,
                 Double_t yMax,
                 Double_t zMin,
                 Double_t zMax,
                 Double_t bX,
                 Double_t bY,
                 Double_t bZ);

    /** Constructor from MyFieldPar **/
    MyConstField(MyFieldPar* fieldPar);

    /** Destructor **/
    virtual ~MyConstField();

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

    /** Get components of field at a given point
     ** @param x,y,z   Point coordinates [cm]
     **/
    virtual Double_t GetBx(Double_t x, Double_t y, Double_t z);
    virtual Double_t GetBy(Double_t x, Double_t y, Double_t z);
    virtual Double_t GetBz(Double_t x, Double_t y, Double_t z);

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
    virtual void Print();

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

    ClassDef(MyConstField, 1);
};

#endif
