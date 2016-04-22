/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairConstField source file                  -----
// -----                Created 30/01/07  by M. Al/Turany              -----
// -------------------------------------------------------------------------
#include "FairConstField.h"

#include "FairConstPar.h"  // for FairConstPar
#include "FairRun.h"       // for FairRun
#include "FairRuntimeDb.h" // for FairRuntimeDb
#include "FairLogger.h"    // for logging

#include "Riosfwd.h" // for ostream
#include "TString.h" // for operator<<, TString

#include <iomanip>  // for operator<<, setw

using std::setw;
using std::setprecision;

// -----   Default constructor   -------------------------------------------
FairConstField::FairConstField()
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
FairConstField::FairConstField(const char* name,
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

// --------   Constructor from PndFieldPar   -------------------------------
FairConstField::FairConstField(FairConstPar* fieldPar)
    : FairField()
    , fXmin(0)
    , fXmax(0)
    , fYmin(0)
    , fYmax(0)
    , fZmin(0)
    , fZmax(0)
    , fBx(0)
    , fBy(0)
    , fBz(0)
{
    if (!fieldPar)
    {
      LOG(WARNING) << "empty parameter container!" << FairLogger::endl;
        fType = -1;
    }
    else
    {
        fXmin = fieldPar->GetXmin();
        fXmax = fieldPar->GetXmax();
        fYmin = fieldPar->GetYmin();
        fYmax = fieldPar->GetYmax();
        fZmin = fieldPar->GetZmin();
        fZmax = fieldPar->GetZmax();
        fBx = fieldPar->GetBx();
        fBy = fieldPar->GetBy();
        fBz = fieldPar->GetBz();
        fType = fieldPar->GetType();
    }
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairConstField::~FairConstField()
{
}
// -------------------------------------------------------------------------

// -----   Set field region   ----------------------------------------------
void FairConstField::SetFieldRegion(Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Double_t zMin, Double_t zMax)
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
void FairConstField::SetField(Double_t bX, Double_t bY, Double_t bZ)
{
    fBx = bX;
    fBy = bY;
    fBz = bZ;
}
// -------------------------------------------------------------------------

// -----   Get x component of field   --------------------------------------
Double_t FairConstField::GetBx(Double_t x, Double_t y, Double_t z)
{
    if (x < fXmin || x > fXmax || y < fYmin || y > fYmax || z < fZmin || z > fZmax)
    {
        return 0.;
    }
    return fBx;
}
// -------------------------------------------------------------------------

// -----   Get y component of field   --------------------------------------
Double_t FairConstField::GetBy(Double_t x, Double_t y, Double_t z)
{
    if (x < fXmin || x > fXmax || y < fYmin || y > fYmax || z < fZmin || z > fZmax)
    {
        return 0.;
    }
    return fBy;
}
// -------------------------------------------------------------------------

// -----   Get z component of field   --------------------------------------
Double_t FairConstField::GetBz(Double_t x, Double_t y, Double_t z)
{
    if (x < fXmin || x > fXmax || y < fYmin || y > fYmax || z < fZmin || z > fZmax)
    {
        return 0.;
    }
    return fBz;
}
// -------------------------------------------------------------------------

// -----   Screen output   -------------------------------------------------
void FairConstField::Print(Option_t*) const
{
    LOG(INFO) << "======================================================" 
	      << FairLogger::endl;
    LOG(INFO) << "----  " << fTitle << " : " << fName << FairLogger::endl;
    LOG(INFO) << "----" << FairLogger::endl;
    LOG(INFO) << "----  Field type    : constant" << FairLogger::endl;
    LOG(INFO) << "----" << FairLogger::endl;
    LOG(INFO) << "----  Field regions : " << FairLogger::endl;
    LOG(INFO) << "----        x = " << setw(4) << fXmin << " to " << setw(4) 
	      << fXmax << " cm" << FairLogger::endl;
    LOG(INFO) << "----        y = " << setw(4) << fYmin << " to " << setw(4) 
	      << fYmax << " cm" << FairLogger::endl;
    LOG(INFO) << "----        z = " << setw(4) << fZmin << " to " << setw(4) 
	      << fZmax << " cm" << FairLogger::endl;
    LOG(INFO) << "----  B = ( " << setprecision(4) << fBx << ", " << fBy 
	      << ", " << fBz << " ) kG" << FairLogger::endl;
    LOG(INFO) << "======================================================" 
	      << FairLogger::endl;
}
// -------------------------------------------------------------------------
// ---------   Fill the parameters   --------------------------------------------
void FairConstField::FillParContainer()
{
    TString MapName = GetName();
    //  LOG(INFO) << "FairConstField::FillParContainer() " 
    //            << FairLogger::endl;
    FairRun* fRun = FairRun::Instance();
    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
    //Bool_t kParameterMerged = kTRUE;
    FairConstPar* Par = static_cast<FairConstPar*>(rtdb->getContainer("FairConstPar"));
    Par->SetParameters(this);
    Par->setInputVersion(fRun->GetRunId(), 1);
    Par->setChanged();
}

ClassImp(FairConstField)
