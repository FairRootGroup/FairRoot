/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixAltSamplerBin.cpp
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include "FairMQPixAltSamplerBin.h"

#include <FairMQMessage.h>
#include <TBranch.h>
#include <TChain.h>
#include <cstddef>
#include <fairlogger/Logger.h>
#include <utility>

using namespace std;

FairMQPixAltSamplerBin::FairMQPixAltSamplerBin()
    : FairMQDevice()
    , fOutputChannelName("data-out")
    , fAckChannelName("")
    , fFileNames()
    , fInputFile()
    , fCurrentFile(0)
    , fInputChain(nullptr)
    , fEventHeader(nullptr)
    , fDigiBranch(nullptr)
    , fDigiArray(nullptr)
    , fAggregateLevel(1)
    , fMaxIndex(-1)
    , fEventCounter(0)
    , fNofRecAcks(0)
    , fReadingRootFiles(false)
    , fAckListener()
{}

void FairMQPixAltSamplerBin::InitTask()
{
    fFileNames = fConfig->GetValue<std::vector<std::string>>("file-name");
    fMaxIndex = fConfig->GetValue<int64_t>(
        "max-index");   // RK 2818.05.28 int64_t will print "Unknown value", but the value is still passed
    fOutputChannelName = fConfig->GetValue<std::string>("out-channel");
    fAckChannelName = fConfig->GetValue<std::string>("ack-channel");
    fAggregateLevel = fConfig->GetValue<int>("aggregate");
}

void FairMQPixAltSamplerBin::PreRun()
{
    if (fAggregateLevel < 1)
        fAggregateLevel = 1;

    LOG(info) << "FairMQPixAltSamplerBin::PreRun() started. fAggregateLevel = " << fAggregateLevel;

    fReadingRootFiles = false;

    fAckListener = std::thread(&FairMQPixAltSamplerBin::ListenForAcks, this);

    if (fFileNames.size() == 0)
        return;

    if (fFileNames[0].find(".root") == std::string::npos)
        return;

    fInputChain = new TChain("fairdata");

    for (int ifile = 0; ifile < (int)fFileNames.size(); ifile++) {
        fInputChain->Add(fFileNames[ifile].c_str());
    }

    fEventHeader = new PixelPayload::EventHeader();
    fInputChain->SetBranchAddress("EventHeader.", &fEventHeader);
    fInputChain->SetBranchAddress("DigiVector", &fDigiArray, &fDigiBranch);

    LOG(info) << "Loaded " << fFileNames.size() << " root files. Chain has now " << fInputChain->GetEntriesFast()
              << " entries";
    fReadingRootFiles = true;
}

bool FairMQPixAltSamplerBin::ConditionalRun()
{
    if (fReadingRootFiles) {
        return ReadRootFile();
    } else {
        return ReadBinFile();
    }
}

bool FairMQPixAltSamplerBin::ReadBinFile()
{
    FairMQParts parts;

    for (int iaggr = 0; iaggr < fAggregateLevel; iaggr++) {

        if (fEventCounter == fMaxIndex) {   // check if reached event limit
            if (parts.Size() > 0) {
                Send(parts, fOutputChannelName);
            }
            return false;
        }

        if (!fInputFile.is_open()) {                        // file not there
            if (fCurrentFile == (int)fFileNames.size()) {   // this is last file
                if (parts.Size() > 0) {
                    Send(parts, fOutputChannelName);
                }
                return false;
            }
            fInputFile.open(fFileNames[fCurrentFile], std::fstream::in | std::fstream::binary);
            fCurrentFile++;
        }

        if (!fInputFile.is_open()) {   // wrong file name
            LOG(error) << "FairMQPixAltSamplerBin::ConditionalRun fInputFile \"" << fFileNames[fCurrentFile]
                       << "\" could not be open!";
            if (parts.Size() > 0) {
                Send(parts, fOutputChannelName);
            }
            return false;
        }

        std::string buffer;

        int head[4];   // runId, MCEntryNo, PartNo, NofDigis
        fInputFile.read((char*)head, sizeof(head));

        if (fInputFile.eof()) {
            LOG(info) << "End of file reached!";
            fInputFile.close();
            if (fCurrentFile == (int)fFileNames.size()) {   // this is the last file
                if (parts.Size() > 0) {
                    Send(parts, fOutputChannelName);
                }
                return false;
            } else
                return true;
        }

        int dataSize = 4;   // detId, feId, col, row
        const int constNofData = head[3] * dataSize;
        short int dataCont[constNofData];
        fInputFile.read((char*)dataCont, sizeof(dataCont));

        PixelPayload::EventHeader* header = new PixelPayload::EventHeader();
        header->fRunId = head[0];
        header->fMCEntryNo = head[1];
        header->fPartNo = head[2];
        FairMQMessagePtr msgHeader(
            NewMessage(header, sizeof(PixelPayload::EventHeader), [](void* data, void* /*hint*/) {
                delete static_cast<PixelPayload::EventHeader*>(data);
            }));
        parts.AddPart(std::move(msgHeader));

        size_t digisSize = head[3] * sizeof(PixelPayload::Digi);

        FairMQMessagePtr msgDigis(NewMessage(digisSize));

        PixelPayload::Digi* digiPayload = static_cast<PixelPayload::Digi*>(msgDigis->GetData());

        for (int idigi = 0; idigi < head[3]; idigi++) {
            new (&digiPayload[idigi]) PixelPayload::Digi();
            digiPayload[idigi].fDetectorID = (int)dataCont[idigi * dataSize + 0];
            digiPayload[idigi].fFeID = (int)dataCont[idigi * dataSize + 1];
            digiPayload[idigi].fCharge = 1.;
            digiPayload[idigi].fCol = (int)dataCont[idigi * dataSize + 2];
            digiPayload[idigi].fRow = (int)dataCont[idigi * dataSize + 3];
        }
        parts.AddPart(std::move(msgDigis));

        fEventCounter++;
    }

    Send(parts, fOutputChannelName);

    if (fInputFile.eof()) {
        LOG(info) << "End of file reached!";
        fInputFile.close();
    }

    return true;
}

bool FairMQPixAltSamplerBin::ReadRootFile()
{
    if (fEventCounter == fMaxIndex)
        return false;

    // fill the input data containers
    fInputChain->GetEntry(fEventCounter);
    fDigiBranch->GetEntry(fEventCounter);

    // create output multipart message
    FairMQParts parts;

    PixelPayload::EventHeader* header = new PixelPayload::EventHeader();
    header->fRunId = fEventHeader->fRunId;
    header->fMCEntryNo = fEventHeader->fMCEntryNo;
    header->fPartNo = fEventHeader->fPartNo;
    FairMQMessagePtr msgHeader(NewMessage(header, sizeof(PixelPayload::EventHeader), [](void* data, void* /*hint*/) {
        delete static_cast<PixelPayload::EventHeader*>(data);
    }));
    parts.AddPart(std::move(msgHeader));

    size_t digisSize = sizeof(PixelPayload::Digi) * fDigiArray->size();

    FairMQMessagePtr msgDigis(NewMessage(digisSize));
    PixelPayload::Digi* digiPayload = static_cast<PixelPayload::Digi*>(msgDigis->GetData());

    for (int idigi = 0; idigi < (int)fDigiArray->size(); idigi++) {
        new (&digiPayload[idigi]) PixelPayload::Digi();
        digiPayload[idigi].fDetectorID = fDigiArray->at(idigi).fDetectorID;
        digiPayload[idigi].fFeID = fDigiArray->at(idigi).fFeID;
        digiPayload[idigi].fCharge = fDigiArray->at(idigi).fCharge;
        digiPayload[idigi].fCol = fDigiArray->at(idigi).fCol;
        digiPayload[idigi].fRow = fDigiArray->at(idigi).fRow;
    }
    parts.AddPart(std::move(msgDigis));

    Send(parts, fOutputChannelName);

    fEventCounter++;

    if (fInputFile.eof()) {
        LOG(info) << "End of file reached!";
        fInputFile.close();
    }

    return true;
}

void FairMQPixAltSamplerBin::PostRun()
{
    if (fAckChannelName != "") {
        fAckListener.join();
    }
    LOG(info) << "PostRun() finished!";
}

void FairMQPixAltSamplerBin::ListenForAcks()
{
    if (fAckChannelName != "") {
        do {
            FairMQMessagePtr ack(NewMessage());
            if (Receive(ack, fAckChannelName) >= 0) {
                fNofRecAcks++;
            }
        } while (fNofRecAcks < fMaxIndex / fAggregateLevel);

        LOG(info) << "Acknowledged " << fNofRecAcks << " messages (" << fAggregateLevel << " events each) out of "
                  << fMaxIndex << " events.";
    }
}

FairMQPixAltSamplerBin::~FairMQPixAltSamplerBin() {}
