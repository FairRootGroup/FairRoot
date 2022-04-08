/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include <TFile.h>
#include <TObject.h>
#include <TTree.h>
#include <cstdlib>
#include <fairlogger/Logger.h>
#include <memory>
#include <vector>

using namespace std;

FairMQPixelFileSink::FairMQPixelFileSink()
    : FairMQDevice()
    , fInputChannelName("data-in")
    , fAckChannelName("")
    , fFileName()
    , fTreeName()
    , fFileOption()
    , fFlowMode(false)
    , fWrite(false)
    , fOutFile(nullptr)
    , fTree(nullptr)
    , fNObjects(0)
    , fOutputObjects(new TObject*[1000])
{}

void FairMQPixelFileSink::InitTask()
{
    fFileName = fConfig->GetValue<std::string>("file-name");
    fInputChannelName = fConfig->GetValue<std::string>("in-channel");
    fAckChannelName = fConfig->GetValue<std::string>("ack-channel");

    LOG(info) << "SHOULD CREATE THE FILE AND TREE";
    fFileOption = "RECREATE";
    fTreeName = "cbmsim";

    if (::getenv("DDS_SESSION_ID")) {
        std::string DDS_SESSION_ID = ::getenv("DDS_SESSION_ID");
        if (fFileName.length() > 5) {
            DDS_SESSION_ID = "." + DDS_SESSION_ID + ".root";
            fFileName.replace(fFileName.length() - 5, 5, DDS_SESSION_ID.c_str());
        }
    }

    fOutFile = TFile::Open(fFileName.c_str(), fFileOption.c_str());

    OnData(fInputChannelName, &FairMQPixelFileSink::StoreData);
}

bool FairMQPixelFileSink::StoreData(FairMQParts& parts, int /*index*/)
{
    bool creatingTree = false;
    std::vector<TObject*> tempObjects;
    if (!fTree) {
        creatingTree = true;
        fTree = new TTree(fTreeName.c_str(), "/cbmout");
    }

    for (int ipart = 0; ipart < parts.Size(); ipart++) {
        fOutputObjects[ipart] = nullptr;
        RootSerializer().Deserialize(*parts.At(ipart), fOutputObjects[ipart]);
        tempObjects.push_back(fOutputObjects[ipart]);
        if (creatingTree)
            fTree->Branch(tempObjects.back()->GetName(), tempObjects.back()->ClassName(), &fOutputObjects[ipart]);
        fTree->SetBranchAddress(tempObjects.back()->GetName(), &fOutputObjects[ipart]);
    }
    //   LOG(INFO) << "Finished branches";
    fTree->Fill();

    for (unsigned int ipart = 0; ipart < tempObjects.size(); ipart++) {
        if (tempObjects[ipart]) {
            delete tempObjects[ipart];
        }
    }
    tempObjects.clear();

    if (fAckChannelName != "") {
        unique_ptr<FairMQMessage> msg(NewMessage());
        Send(msg, fAckChannelName);
    }
    return true;
}

void FairMQPixelFileSink::ResetTask()
{
    if (fTree) {
        fTree->Write();
    }

    if (fOutFile) {
        if (fOutFile->IsOpen()) {
            fOutFile->Close();
        }
    }
}

FairMQPixelFileSink::~FairMQPixelFileSink()
{
    if (fTree) {
        delete fTree;
    }

    if (fOutFile) {
        delete fOutFile;
    }
}
