/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMCSplitEventHeader.h"

#include "FairRootManager.h"

FairMCSplitEventHeader::FairMCSplitEventHeader()
    : FairMCEventHeader()
    , fNofChunks(1)
    , fChunkStart(0)
{}

FairMCSplitEventHeader::FairMCSplitEventHeader(UInt_t runID, UInt_t eventID, UInt_t nofChunks, UInt_t chunkStart)
    : FairMCEventHeader(runID)
    , fNofChunks(nofChunks)
    , fChunkStart(chunkStart)
{
    SetEventID(eventID);
}

FairMCSplitEventHeader::~FairMCSplitEventHeader() {}

void FairMCSplitEventHeader::Register()
{
    // Dot at the end of the name is needed for splitting!!
    FairRootManager::Instance()->Register("MCEventHeader.", "Event", this, kTRUE);
}
