/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet1Point.h"

#include "FairLogger.h"

// -----   Default constructor   -------------------------------------------
FairTutorialDet1Point::FairTutorialDet1Point()
  : FairMCPoint()
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTutorialDet1Point::FairTutorialDet1Point(Int_t trackID, Int_t detID,
    TVector3 pos, TVector3 mom,
    Double_t tof, Double_t length,
    Double_t eLoss)
  : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss)
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutorialDet1Point::~FairTutorialDet1Point() { }
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTutorialDet1Point::Print(const Option_t* /*opt*/) const
{
  LOG(INFO) << "TutorialDet point for track " << fTrackID
            << " in detector " << fDetectorID << FairLogger::endl;
  LOG(INFO) << "    Position (" << fX << ", " << fY << ", " << fZ
            << ") cm" << FairLogger::endl;
  LOG(INFO) << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
            << ") GeV" << FairLogger::endl;
  LOG(INFO) << "    Time " << fTime << " ns,  Length " << fLength
            << " cm,  Energy loss " << fELoss*1.0e06 << " keV" 
            << FairLogger::endl;
}
// -------------------------------------------------------------------------

ClassImp(FairTutorialDet1Point)

