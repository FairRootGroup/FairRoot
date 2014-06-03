/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorPoint.h"

#include "Riosfwd.h" // for ostream

#include <iostream> // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTestDetectorPoint::FairTestDetectorPoint()
    : FairMCPoint()
    , fX_out(0.)
    , fY_out(0.)
    , fZ_out(0.)
    , fPx_out(0.)
    , fPy_out(0.)
    , fPz_out(0.)
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTestDetectorPoint::FairTestDetectorPoint(Int_t trackID,
                                             Int_t detID,
                                             TVector3 pos,
                                             TVector3 mom,
                                             TVector3 posOut,
                                             TVector3 momOut,
                                             Double_t tof,
                                             Double_t length,
                                             Double_t eLoss)
    : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss)
    , fX_out(posOut.X())
    , fY_out(posOut.Y())
    , fZ_out(posOut.Z())
    , fPx_out(momOut.Px())
    , fPy_out(momOut.Py())
    , fPz_out(momOut.Pz())
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTestDetectorPoint::~FairTestDetectorPoint()
{
}
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTestDetectorPoint::Print(const Option_t* opt) const
{
    cout << "-I- FairTestDetectorPoint: FairTestDetector point for track " << fTrackID << " in detector " << fDetectorID << endl;
    cout << "    Position (" << fX << ", " << fY << ", " << fZ << ") cm" << endl;
    cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz << ") GeV" << endl;
    cout << "    Time " << fTime << " ns,  Length " << fLength << " cm,  Energy loss " << fELoss * 1.0e06 << " keV" << endl;
}
// -------------------------------------------------------------------------

ClassImp(FairTestDetectorPoint)
