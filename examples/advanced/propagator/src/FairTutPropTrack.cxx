/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairTutPropTrack.h"

#include "FairLogger.h"
#include "FairRootManager.h"

ClassImp(FairTutPropTrack);

FairTutPropTrack::FairTutPropTrack()
    : TObject()
    , fPdgCode(0)
    , fTrackParamFirst()
    , fHitsIndices()
    , fMCTrackIndex(-1)
{}

FairTutPropTrack::FairTutPropTrack(int pdgcode,
                                   const FairTrackParP &first,
                                   const std::vector<std::pair<int, int>> &hitsvector,
                                   int trueMCTrackIndex)
    : TObject()
    , fPdgCode(pdgcode)
    , fTrackParamFirst(first)
    , fHitsIndices(hitsvector)
    , fMCTrackIndex(trueMCTrackIndex)
{}

void FairTutPropTrack::Print()
{
    LOG(info) << "FirstTrackPar:";
    fTrackParamFirst.Print();
    LOG(info) << "hits:";
    for (const auto &hitind_elem : fHitsIndices) {
        LOG(info) << hitind_elem.first << " / " << hitind_elem.second;
    }
    LOG(info) << "-------------------";
}
