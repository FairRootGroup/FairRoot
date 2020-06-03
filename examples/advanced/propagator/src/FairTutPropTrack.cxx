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
    , fHitsIndices()
{}

FairTutPropTrack::FairTutPropTrack(int pdgcode, const FairTrackParP &first, const std::vector<std::pair<int,int>> &hitsvector)
    : TObject()
    , fPdgCode(pdgcode)
    , fTrackParamFirst(first)
    , fHitsIndices(hitsvector)
{
}

void FairTutPropTrack::Print()
{
    LOG(info) << "FirstTrackPar:";
    fTrackParamFirst.Print();
    LOG(info) << "hits:";
    for ( int ih = 0 ; ih < fHitsIndices.size() ; ih++ ) {
        LOG(info) << fHitsIndices[ih].first << " / " << fHitsIndices[ih].second;
    }
    LOG(info) << "-------------------";
}
