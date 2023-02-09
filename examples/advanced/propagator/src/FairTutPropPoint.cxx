/********************************************************************************
 * Copyright (C) 2019-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutPropPoint.h"

#include <TVector3.h>
#include <iostream>

// -----   Default constructor   -------------------------------------------
FairTutPropPoint::FairTutPropPoint()
    : FairMCPoint()
{}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTutPropPoint::FairTutPropPoint(Int_t trackID,
                                   Int_t detID,
                                   TVector3 pos,
                                   TVector3 mom,
                                   Double_t tof,
                                   Double_t length,
                                   Double_t eLoss)
    : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss)
{}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutPropPoint::~FairTutPropPoint() {}
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTutPropPoint::Print(const Option_t* /*opt*/) const
{
    using std::cout;
    using std::endl;

    cout << "-I- FairTutPropPoint: FairTutProp point for track " << fTrackID << " in detector " << fDetectorID << endl;
    cout << "    Position (" << fX << ", " << fY << ", " << fZ << ") cm" << endl;
    cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz << ") GeV" << endl;
    cout << "    Time " << fTime << " ns,  Length " << fLength << " cm,  Energy loss " << fELoss * 1.0e06 << " keV"
         << endl;
}
// -------------------------------------------------------------------------
