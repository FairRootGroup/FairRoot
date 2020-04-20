/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewDetectorPoint.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
NewDetectorPoint::NewDetectorPoint()
    : fTrackID(0)
    , fPx(0.)
    , fPy(0.)
    , fPz(0.)
    , fTime(0.)
    , fLength(0.)
    , fELoss(0.)
    , fDetectorID(0)
    , fX(0.)
    , fY(0.)
    , fZ(0.)
{}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
NewDetectorPoint::NewDetectorPoint(Int_t trackID,
                                   Int_t detID,
                                   TVector3 pos,
                                   TVector3 mom,
                                   Double_t tof,
                                   Double_t length,
                                   Double_t eLoss)
    : fTrackID(trackID)
    , fPx(mom.X())
    , fPy(mom.Y())
    , fPz(mom.Z())
    , fTime(tof)
    , fLength(length)
    , fELoss(eLoss)
    , fDetectorID(detID)
    , fX(pos.X())
    , fY(pos.Y())
    , fZ(pos.Z())
{}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
NewDetectorPoint::~NewDetectorPoint() {}
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void NewDetectorPoint::Print(const Option_t* /*opt*/) const
{
    cout << "-I- NewDetectorPoint: NewDetector point for track " << fTrackID << " in detector " << fDetectorID << endl;
    cout << "    Position (" << fX << ", " << fY << ", " << fZ << ") cm" << endl;
    cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz << ") GeV" << endl;
    cout << "    Time " << fTime << " ns,  Length " << fLength << " cm,  Energy loss " << fELoss * 1.0e06 << " keV"
         << endl;
}
// -------------------------------------------------------------------------

ClassImp(NewDetectorPoint);
