/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                          FairRemoteSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------
#include "FairRemoteSource.h"

#include "MRevBuffer.h"
#include "ptrevmbsdef.h"   // MBS data definitions

#include <TSocket.h>
#include <unistd.h>   // usleep

FairRemoteSource::FairRemoteSource(char* node)
    : FairMbsSource()
    , fNode(node)
    , fSocket(nullptr)
    , fBuffer(new MRevBuffer(1))
    , fREvent(nullptr)
{
}

FairRemoteSource::FairRemoteSource(const FairRemoteSource& source)
    : FairMbsSource(source)
    , fNode(const_cast<char*>(source.GetNode()))
    , fSocket(nullptr)
    , fBuffer(new MRevBuffer(1))
    , fREvent(nullptr)
{
}

FairRemoteSource::~FairRemoteSource() { delete fBuffer; }

Bool_t FairRemoteSource::Init()
{
    fBuffer->RevStatus(0);
    fSocket = fBuffer->RevOpen(fNode, 6003, 0);
    fBuffer->RevStatus(0);
    return fSocket != nullptr;
}

Int_t FairRemoteSource::ReadEvent(UInt_t)
{
    usleep(10000);
    fREvent = fBuffer->RevGet(fSocket, 0, 0);
    fBuffer->RevStatus(0);
    if (!fREvent) {
        return 1;
    }

    // Decode event header
    Bool_t result = Unpack(fREvent->GetData(), sizeof(sMbsEv101), -2, -2, -2, -2, -2);

    for (Int_t i = 0; i < fREvent->nSubEvt; i++) {
        if (Unpack(fREvent->pSubEvt[i],
                   fREvent->subEvtSize[i],
                   fREvent->subEvtType[i],
                   fREvent->subEvtSubType[i],
                   fREvent->subEvtProcId[i],
                   fREvent->subEvtSubCrate[i],
                   fREvent->subEvtControl[i])) {
            result = kTRUE;
        }
    }

    if (!result) {
        return 2;
    }

    return 0;
}

void FairRemoteSource::Close()
{
    fBuffer->RevClose(fSocket);
    fBuffer->RevStatus(0);
}
