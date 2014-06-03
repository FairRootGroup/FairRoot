/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4Point.h"

#include "Riosfwd.h"                    // for ostream

#include <iostream>                     // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTutorialDet4Point::FairTutorialDet4Point()
  : FairMCPoint()
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTutorialDet4Point::FairTutorialDet4Point(Int_t trackID, Int_t detID,
    TVector3 pos, TVector3 mom,
    Double_t tof, Double_t length,
    Double_t eLoss)
  : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss)
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutorialDet4Point::~FairTutorialDet4Point() { }
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTutorialDet4Point::Print(const Option_t* opt) const
{
  cout << "-I- FairTutorialDet4Point: TutorialDet point for track " << fTrackID
       << " in detector " << fDetectorID << endl;
  cout << "    Position (" << fX << ", " << fY << ", " << fZ
       << ") cm" << endl;
  cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
       << ") GeV" << endl;
  cout << "    Time " << fTime << " ns,  Length " << fLength
       << " cm,  Energy loss " << fELoss*1.0e06 << " keV" << endl;
}
// -------------------------------------------------------------------------

ClassImp(FairTutorialDet4Point)

