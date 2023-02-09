/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4Point.h"

#include "FairLogger.h"

FairTutorialDet4Point::FairTutorialDet4Point()
    : FairMCPoint()
{}

FairTutorialDet4Point::FairTutorialDet4Point(Int_t trackID,
                                             Int_t detID,
                                             TVector3 pos,
                                             TVector3 mom,
                                             Double_t tof,
                                             Double_t length,
                                             Double_t eLoss)
    : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss)
{}

void FairTutorialDet4Point::Print(const Option_t* /*opt*/) const
{
    LOG(info) << "-I- FairTutorialDet4Point: TutorialDet point for track " << fTrackID << " in detector "
              << fDetectorID;
    LOG(info) << "    Position (" << fX << ", " << fY << ", " << fZ << ") cm";
    LOG(info) << "    Momentum (" << fPx << ", " << fPy << ", " << fPz << ") GeV";
    LOG(info) << "    Time " << fTime << " ns,  Length " << fLength << " cm,  Energy loss " << fELoss * 1.0e06
              << " keV";
}
