/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairTutGeaneField source file                  -----
// -----                Created 30/01/07  by M. Al/Turany              -----
// -------------------------------------------------------------------------
#include "FairTutGeaneField.h"

#include "FairRun.h"       // for FairRun
#include "FairRuntimeDb.h" // for FairRuntimeDb
#include "FairLogger.h"    // for logging

#include <iosfwd>    // for ostream
#include "TString.h" // for operator<<, TString

#include <iomanip>  // for operator<<, setw

using std::setw;
using std::setprecision;

// -----   Default constructor   -------------------------------------------
FairTutGeaneField::FairTutGeaneField()
    : fXmin(0)
    , fXmax(0)
    , fYmin(0)
    , fYmax(0)
    , fZmin(0)
    , fZmax(0)
    , fBx(0)
    , fBy(0)
    , fBz(0)
{
    fType = 0;
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTutGeaneField::FairTutGeaneField(const char* name,
                               Double_t xMin,
                               Double_t xMax,
                               Double_t yMin,
                               Double_t yMax,
                               Double_t zMin,
                               Double_t zMax,
                               Double_t bX,
                               Double_t bY,
                               Double_t bZ)
    : FairField(name)
    , fXmin(xMin)
    , fXmax(xMax)
    , fYmin(yMin)
    , fYmax(yMax)
    , fZmin(zMin)
    , fZmax(zMax)
    , fBx(bX)
    , fBy(bY)
    , fBz(bZ)

{
    fType = 0;
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutGeaneField::~FairTutGeaneField()
{
}
// -------------------------------------------------------------------------

// -----   Set field region   ----------------------------------------------
void FairTutGeaneField::SetFieldRegion(Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Double_t zMin, Double_t zMax)
{
    fXmin = xMin;
    fXmax = xMax;
    fYmin = yMin;
    fYmax = yMax;
    fZmin = zMin;
    fZmax = zMax;
}
// -------------------------------------------------------------------------

// -----   Set field values   ----------------------------------------------
void FairTutGeaneField::SetField(Double_t bX, Double_t bY, Double_t bZ)
{
    fBx = bX;
    fBy = bY;
    fBz = bZ;
}
// -------------------------------------------------------------------------

// -----   Get x component of field   --------------------------------------
Double_t FairTutGeaneField::GetBx(Double_t x, Double_t y, Double_t z)
{
    if (x < fXmin || x > fXmax || y < fYmin || y > fYmax || z < fZmin || z > fZmax)
    {
        return 0.;
    }
    return fBx;
}
// -------------------------------------------------------------------------

// -----   Get y component of field   --------------------------------------
Double_t FairTutGeaneField::GetBy(Double_t x, Double_t y, Double_t z)
{
    if (x < fXmin || x > fXmax || y < fYmin || y > fYmax || z < fZmin || z > fZmax)
    {
        return 0.;
    }
    return fBy;
}
// -------------------------------------------------------------------------

// -----   Get z component of field   --------------------------------------
Double_t FairTutGeaneField::GetBz(Double_t x, Double_t y, Double_t z)
{
    if (x < fXmin || x > fXmax || y < fYmin || y > fYmax || z < fZmin || z > fZmax)
    {
        return 0.;
    }
    return fBz;
}
// -------------------------------------------------------------------------

// -----   Screen output   -------------------------------------------------
void FairTutGeaneField::Print(Option_t*) const
{
    LOG(info) << "======================================================" ;
    LOG(info) << "----  " << fTitle << " : " << fName;
    LOG(info) << "----";
    LOG(info) << "----  Field type    : constant";
    LOG(info) << "----";
    LOG(info) << "----  Field regions : ";
    LOG(info) << "----        x = " << setw(4) << fXmin << " to " << setw(4)
              << fXmax << " cm";
    LOG(info) << "----        y = " << setw(4) << fYmin << " to " << setw(4)
              << fYmax << " cm";
    LOG(info) << "----        z = " << setw(4) << fZmin << " to " << setw(4)
              << fZmax << " cm";
    LOG(info) << "----  B = ( " << setprecision(4) << fBx << ", " << fBy
              << ", " << fBz << " ) kG";
    LOG(info) << "======================================================";
}
// -------------------------------------------------------------------------

ClassImp(FairTutGeaneField)
