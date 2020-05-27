/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairTutPropTrack.h"

#include "FairRootManager.h"
#include "FairLogger.h"

ClassImp(FairTutPropTrack);

FairTutPropTrack::FairTutPropTrack()
    : TObject()
    , fPdgCode(0)
    , fTrackParamFirst()
{}

FairTutPropTrack::FairTutPropTrack(int pdgcode, const FairTrackParP &first)
    : TObject()
    , fPdgCode(pdgcode)
    , fTrackParamFirst(first)
{
}

void FairTutPropTrack::Print()
{
    LOG(info) << "FirstTrackPar";
    fTrackParamFirst.Print();
}
