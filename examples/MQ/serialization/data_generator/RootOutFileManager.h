/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef ROOTOUTFILEMANAGER_H
#define ROOTOUTFILEMANAGER_H

// FairRoot
#include "FairLogger.h"
#include "FairMQ.h"   // for fair::mq::Message, fair::mq::ProgOptions

// ROOT
#include <TClonesArray.h>
#include <TFile.h>
#include <TFolder.h>
#include <TList.h>
#include <TObjString.h>
#include <TTree.h>

// std
#include <memory>
#include <string>
#include <vector>

template<typename DataType>
class RootOutFileManager
{
  public:
    RootOutFileManager(const std::string& fileName,
                       const std::string& treeName,
                       const std::string& branchName,
                       const std::string& className)
        : fFileName(fileName)
        , fTreeName(treeName)
        , fBranchName(branchName)
        , fClassName(className)
        , fTree(fTreeName.c_str(), "Test output")
        , fFolder("cbmroot", "/cbmroot")
        , fOutput(new TClonesArray(fClassName.c_str()))
    {
        fOutputFile.reset(TFile::Open(fFileName.c_str(), "RECREATE"));
        fTree.Branch(fBranchName.c_str(), "TClonesArray", &fOutput);

        TList branchNameList;
        branchNameList.AddLast(new TObjString(fBranchName.c_str()));
        branchNameList.Write("BranchList", TObject::kSingleKey);
        branchNameList.Delete();
    }

    RootOutFileManager(const RootOutFileManager&) = delete;
    RootOutFileManager operator=(const RootOutFileManager&) = delete;

    void AddToFile(std::vector<DataType>& inputData)
    {
        fOutput->Delete();
        for (unsigned int i = 0; i < inputData.size(); ++i) {
            new ((*fOutput)[i]) DataType(inputData.at(i));
        }
        if (fOutput->IsEmpty()) {
            LOG(debug) << "RootOutFileManager::AddToFile(vector<DataType>&): No Output array!";
        }
        fTree.Fill();
    }

    virtual ~RootOutFileManager()
    {
        fTree.Write("", TObject::kOverwrite);
        if (fOutput) {
            delete fOutput;
        }
    }

    std::string fFileName;
    std::string fTreeName;
    std::string fBranchName;
    std::string fClassName;

    std::unique_ptr<TFile> fOutputFile;
    TTree fTree;
    TFolder fFolder;
    TClonesArray* fOutput;
};

#endif /* ROOTOUTFILEMANAGER_H */
