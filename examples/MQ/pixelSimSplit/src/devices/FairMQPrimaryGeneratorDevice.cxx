/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPrimaryGeneratorDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQPrimaryGeneratorDevice.h"

#include "FairMCEventHeader.h"
#include "FairMCSplitEventHeader.h"
#include "FairPrimaryGenerator.h"
#include "FairStack.h"
#include "RootSerializer.h"

#include <FairMQMessage.h>
#include <Rtypes.h>
#include <TClonesArray.h>
#include <fairlogger/Logger.h>
#include <utility>   // move

using namespace std;

FairMQPrimaryGeneratorDevice::FairMQPrimaryGeneratorDevice()
    : fGeneratorChannelName("primariesChannel")
    , fAckChannelName("")
    , fRunConditional(true)
    , fPrimaryGenerator(nullptr)
    , fMCEventHeader(nullptr)
    , fStack(nullptr)
    , fNofEvents(10)
    , fEventCounter(0)
    , fChunkSize(0)
    , fChunkPointer(0)
    , fAckListener()
{}

void FairMQPrimaryGeneratorDevice::InitTask()
{
    fAckChannelName = fConfig->GetValue<std::string>("ack-channel");

    fStack = new FairStack();
    fMCEventHeader = new FairMCEventHeader();
    fPrimaryGenerator->SetEvent(fMCEventHeader);
    fPrimaryGenerator->Init();

    if (!fRunConditional)
        OnData(fGeneratorChannelName, &FairMQPrimaryGeneratorDevice::Reply);
    if (fChunkSize < 0)
        fChunkSize = 0;
}

void FairMQPrimaryGeneratorDevice::PreRun()
{
    if (fAckChannelName != "") {
        fAckListener = thread(&FairMQPrimaryGeneratorDevice::ListenForAcks, this);
    }
}

bool FairMQPrimaryGeneratorDevice::ConditionalRun()
{
    if (!fRunConditional)
        return false;
    return GenerateAndSendData();
}

bool FairMQPrimaryGeneratorDevice::Reply([[gnu::unused]] FairMQMessagePtr& mPtr, [[gnu::unused]] int /*index*/)
{
    return GenerateAndSendData();
}

bool FairMQPrimaryGeneratorDevice::GenerateAndSendData()
{
    if (fChunkPointer == 0) {
        //        LOG(INFO) << "Reseting fStack and generating new event!!!";
        fStack->Reset();
        fPrimaryGenerator->GenerateEvent(fStack);
        ++fEventCounter;
    }
    if (fEventCounter > fNofEvents)
        return false;

    FairMQParts parts;

    // even if sending in chunks is set, send all of the primaries anyway, the transporter takes care of transporting
    // needed primaries create FairMCEventHeader, misuse not-yet-set fRunID to store begin
    TClonesArray* prims = fStack->GetListOfParticles();

    FairMCSplitEventHeader* meh = new FairMCSplitEventHeader(
        0, fEventCounter, 1, 0);   // RunId will be provided in the Transport from ParameterServer
    meh->SetNPrim(prims->GetEntries());
    if (fChunkSize != 0) {
        meh->SetNofChunks((UInt_t)(prims->GetEntries() / fChunkSize));
        meh->SetChunkStart(fChunkPointer);
        meh->SetNPrim(fChunkPointer + fChunkSize);
        if (fChunkPointer + fChunkSize > prims->GetEntries())
            meh->SetNPrim(prims->GetEntries() - fChunkPointer);
    }

    FairMQMessagePtr messEH(NewMessage());
    RootSerializer().Serialize(*messEH, meh);
    parts.AddPart(std::move(messEH));

    FairMQMessagePtr mess(NewMessage());
    RootSerializer().Serialize(*mess, prims);
    parts.AddPart(std::move(mess));

    //    LOG(INFO) << "sending event " << fEventCounter << ", chunk starts at " << fChunkPointer;
    if (Send(parts, fGeneratorChannelName) > 0) {}

    int numberofparticles = (int)prims->GetEntries();

    if (fChunkSize != 0) {   // should send events in chunks with maximum size of fChunkSize
        // the whole work should be done after
        fChunkPointer += fChunkSize;
        if (fChunkPointer >= numberofparticles) {   // it means that already sent all primaries from this event
            fChunkPointer = 0;                      // this will cause the reset of the stack and generating new event
        }
    }

    return true;
}

void FairMQPrimaryGeneratorDevice::PostRun()
{
    if (fAckChannelName != "") {
        fAckListener.join();
    }
}

void FairMQPrimaryGeneratorDevice::ListenForAcks()
{
    if (fAckChannelName != "") {
        Long64_t numAcks = 0;
        do {
            FairMQMessagePtr ack(NewMessage());
            if (Receive(ack, fAckChannelName) >= 0) {
                LOG(info) << "RECEIVED ACK!";
                numAcks++;
            }
        } while (numAcks < fNofEvents);

        LOG(info) << "Acknowledged " << numAcks << " messages.";
    }
}

FairMQPrimaryGeneratorDevice::~FairMQPrimaryGeneratorDevice() {}

void FairMQPrimaryGeneratorDevice::SendPrimaries() {}
