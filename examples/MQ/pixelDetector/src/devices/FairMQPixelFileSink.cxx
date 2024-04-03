/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelFileSink.cxx
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include "FairMQPixelFileSink.h"

#include "RootSerializer.h"

#include <TObject.h>
#include <cstdlib>
#include <fairlogger/Logger.h>
#include <memory>
#include <vector>

FairMQPixelFileSink::FairMQPixelFileSink()
    : FairMQDevice()
    , fInputChannelName("data-in")
    , fAckChannelName("")
    , fFileName()
    , fTreeName()
    , fFileOption()
{}

void FairMQPixelFileSink::InitTask()
{
    fFileName = fConfig->GetValue<std::string>("file-name");
    fInputChannelName = fConfig->GetValue<std::string>("in-channel");
    fAckChannelName = fConfig->GetValue<std::string>("ack-channel");

    LOG(info) << "SHOULD CREATE THE FILE AND TREE";
    fFileOption = "RECREATE";
    fTreeName = "cbmsim";

    if (const char* dds_session_env = ::getenv("DDS_SESSION_ID")) {
        std::string DDS_SESSION_ID{dds_session_env};
        if (fFileName.length() > 5) {
            DDS_SESSION_ID = "." + DDS_SESSION_ID + ".root";
            fFileName.replace(fFileName.length() - 5, 5, DDS_SESSION_ID.c_str());
        }
    }

    fOutFile.reset(TFile::Open(fFileName.c_str(), fFileOption.c_str()));

    OnData(fInputChannelName, &FairMQPixelFileSink::StoreData);
}

bool FairMQPixelFileSink::StoreData(fair::mq::Parts& parts, int /*index*/)
{
    bool creatingTree = false;
    const auto numParts = parts.Size();
    std::vector<std::unique_ptr<TObject>> cleanup;
    std::vector<TObject*> objectsForBranches;

    if (!fTree) {
        creatingTree = true;
        fTree = std::make_unique<TTree>(fTreeName.c_str(), "/cbmout");
    }

    cleanup.reserve(numParts);
    objectsForBranches.resize(numParts, nullptr);
    for (decltype(parts.Size()) ipart = 0; ipart < numParts; ipart++) {
        auto curobj = RootSerializer().DeserializeTo<TObject>(*parts.At(ipart));
        objectsForBranches.at(ipart) = curobj.get();
        if (creatingTree) {
            fTree->Branch(curobj->GetName(), curobj->ClassName(), &objectsForBranches[ipart]);
        }
        fTree->SetBranchAddress(curobj->GetName(), &objectsForBranches[ipart]);
        cleanup.emplace_back(std::move(curobj));
    }
    //   LOG(INFO) << "Finished branches";
    fTree->Fill();

    if (!fAckChannelName.empty()) {
        auto msg(NewMessage());
        Send(msg, fAckChannelName);
    }
    return true;
}

void FairMQPixelFileSink::ResetTask()
{
    if (fTree) {
        fTree->Write();
        // Delete the tree, because we're going to close the file
        fTree.reset();
    }

    if (fOutFile) {
        if (fOutFile->IsOpen()) {
            fOutFile->Close();
        }
    }
}

FairMQPixelFileSink::~FairMQPixelFileSink() = default;
