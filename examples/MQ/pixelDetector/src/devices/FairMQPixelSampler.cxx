/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelSampler.cpp
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include "FairMQPixelSampler.h"

#include "FairFileSource.h"
#include "FairRunAna.h"
#include "FairSource.h"
#include "RootSerializer.h"

#include <Rtypes.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <cstring>
#include <fairlogger/Logger.h>
#include <utility>   // move

using namespace std;

FairMQPixelSampler::FairMQPixelSampler()
    : FairMQDevice()
    , fOutputChannelName("data-out")
    , fAckChannelName("")
    , fRunAna(nullptr)
    , fSource(nullptr)
    , fInputObjects()
    , fNObjects(0)
    , fMaxIndex(-1)
    , fEventCounter(0)
    , fBranchNames()
    , fFileNames()
    , fAckListener()
{}

void FairMQPixelSampler::InitTask()
{
    fFileNames = fConfig->GetValue<std::vector<std::string>>("file-name");
    fMaxIndex = fConfig->GetValue<int64_t>("max-index");
    fBranchNames = fConfig->GetValue<std::vector<std::string>>("branch-name");
    fOutputChannelName = fConfig->GetValue<std::string>("out-channel");
    fAckChannelName = fConfig->GetValue<std::string>("ack-channel");

    fRunAna = new FairRunAna();

    if (fSource == nullptr) {
        fSource = new FairFileSource(fFileNames.at(0).c_str());
        for (unsigned int ifile = 1; ifile < fFileNames.size(); ifile++) {
            ((FairFileSource*)fSource)->AddFile(fFileNames.at(ifile));
        }
    }

    fSource->Init();
    LOG(info) << "Going to request " << fBranchNames.size() << "  branches:";
    for (unsigned int ibrn = 0; ibrn < fBranchNames.size(); ibrn++) {
        LOG(info) << " requesting branch \"" << fBranchNames[ibrn] << "\"";
        int branchStat = fSource->ActivateObject((TObject**)&fInputObjects[fNObjects],
                                                 fBranchNames[ibrn].c_str());   // should check the status...
        if (fInputObjects[fNObjects]) {
            LOG(info) << "Activated object \"" << fInputObjects[fNObjects] << "\" with name \"" << fBranchNames[ibrn]
                      << "\" (" << branchStat << "), it got name: \"" << fInputObjects[fNObjects]->GetName() << "\"";
            if (strcmp(fInputObjects[fNObjects]->GetName(), fBranchNames[ibrn].c_str()))
                if (strcmp(fInputObjects[fNObjects]->ClassName(), "TClonesArray") == 0)
                    ((TClonesArray*)fInputObjects[fNObjects])->SetName(fBranchNames[ibrn].c_str());
            fNObjects++;
        }
    }

    if (fMaxIndex < 0)
        fMaxIndex = fSource->CheckMaxEventNo();
    LOG(info) << "Input source has " << fMaxIndex << " events.";
}

void FairMQPixelSampler::PreRun()
{
    if (fAckChannelName != "") {
        fAckListener = thread(&FairMQPixelSampler::ListenForAcks, this);
    }

    LOG(info) << "FairMQPixelSampler::PreRun() finished!";
}

bool FairMQPixelSampler::ConditionalRun()
{
    if (fEventCounter == fMaxIndex)
        return false;

    Int_t readEventReturn = fSource->ReadEvent(fEventCounter);

    if (readEventReturn != 0)
        return false;

    fair::mq::Parts parts;

    for (int iobj = 0; iobj < fNObjects; iobj++) {
        auto mess(NewMessage());
        RootSerializer().Serialize(*mess, fInputObjects[iobj]);
        parts.AddPart(std::move(mess));
    }

    Send(parts, fOutputChannelName);

    fEventCounter++;

    return true;
}

void FairMQPixelSampler::PostRun()
{
    if (fAckChannelName != "") {
        fAckListener.join();
    }

    LOG(info) << "PostRun() finished!";
}

void FairMQPixelSampler::ListenForAcks()
{
    if (fAckChannelName != "") {
        Long64_t numAcks = 0;
        do {
            auto ack(NewMessage());
            if (Receive(ack, fAckChannelName) >= 0) {
                numAcks++;
            }
        } while (numAcks < fMaxIndex);

        LOG(info) << "Acknowledged " << numAcks << " messages.";
    }
}

FairMQPixelSampler::~FairMQPixelSampler() {}
