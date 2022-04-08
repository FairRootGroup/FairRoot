/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   RootOutFileManager.h
 * Author: winckler
 *
 * Created on October 7, 2014, 9:40 PM
 */

#ifndef ROOTOUTFILEMANAGER_H
#define ROOTOUTFILEMANAGER_H

// std
#include <iostream>
#include <string>
#include <vector>

// ROOT
#include <Rtypes.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TFolder.h>
#include <TKey.h>
#include <TList.h>
#include <TObjString.h>
#include <TTree.h>

// FairRoot
#include "FairLogger.h"

#include <FairMQMessage.h>
#include <options/FairMQProgOptions.h>

template<typename DataType>
class RootOutFileManager
{
  public:
    RootOutFileManager()
        : fFilename()
        , fTreeName()
        , fBranchName()
        , fClassName()
        , fFileOption()
        , fUseClonesArray(false)
        , fFlowMode(true)
        , fWrite(false)
        , fOutFile(nullptr)
        , fTree(nullptr)
        , fOutput(nullptr)
        , fOutputData(nullptr)
        , fFolder(nullptr)
    {}

    RootOutFileManager(const std::string& filename,
                       const std::string& treeName,
                       const std::string& branchName,
                       const std::string& className,
                       const std::string& fileOption)
        : fFilename(filename)
        , fTreeName(treeName)
        , fBranchName(branchName)
        , fClassName(className)
        , fFileOption(fileOption)
        , fUseClonesArray(false)
        , fFlowMode(true)
        , fWrite(false)
        , fOutFile(nullptr)
        , fTree(nullptr)
        , fOutput(nullptr)
        , fOutputData(nullptr)
        , fFolder(nullptr)
    {}

    RootOutFileManager(const RootOutFileManager&) = delete;
    RootOutFileManager operator=(const RootOutFileManager&) = delete;

    virtual ~RootOutFileManager()
    {
        if (fFlowMode && fWrite) {
            fTree->Write("", TObject::kOverwrite);
        }

        delete fTree;

        if (fOutFile) {
            if (fOutFile->IsOpen()) {
                fOutFile->Close();
            }
            delete fOutFile;
        }

        delete fFolder;
    }

    void SetFileProperties(const std::string& filename,
                           const std::string& treeName,
                           const std::string& branchName,
                           const std::string& className = "",
                           const std::string& fileOption = "RECREATE",
                           bool useClonesArray = false,
                           bool flowMode = true)
    {
        fFilename = filename;
        fTreeName = treeName;
        fBranchName = branchName;
        fClassName = className;
        fFileOption = fileOption;
        fUseClonesArray = useClonesArray;
        fFlowMode = flowMode;
        if (!std::is_base_of<TObject, DataType>::value && fUseClonesArray) {
            fUseClonesArray = false;
            LOG(warn) << "Deactivate TClonesArray method: the data class must inherit from TObject.";
        }
    }

    void SetFileProperties(const FairMQProgOptions& config)
    {
        fFilename = config.GetValue<std::string>("output-file-name");
        fTreeName = config.GetValue<std::string>("output-file-tree");
        fBranchName = config.GetValue<std::string>("output-file-branch");
        fClassName = config.GetValue<std::string>("hit-classname");
        fFileOption = config.GetValue<std::string>("output-file-option");
        fUseClonesArray = config.GetValue<bool>("use-clones-array");
        fFlowMode = config.GetValue<bool>("flow-mode");

        if (!std::is_base_of<TObject, DataType>::value && fUseClonesArray) {
            fUseClonesArray = false;
            LOG(warn) << "Deactivate TClonesArray method: the data class must inherit from TObject.";
        }
    }

    void AddToFile(std::vector<DataType>& inputData)
    {
        if (fUseClonesArray) {
            fOutput->Delete();

            for (unsigned int i = 0; i < inputData.size(); ++i) {
                new ((*fOutput)[i]) DataType(inputData.at(i));
            }

            if (fOutput->IsEmpty()) {
                LOG(debug) << "RootOutFileManager::AddToFile(vector<DataType>&): No Output array!";
            }

            fTree->Fill();
        } else {
            for (unsigned int i = 0; i < inputData.size(); ++i) {
                fOutputData = &inputData.at(i);
                fTree->Fill();
            }
        }
        if (!fFlowMode) {
            fTree->Write("", TObject::kOverwrite);
        }
    }

    void AddToFile(DataType* objArr, long size)
    {
        // todo : check if fine when update option
        if (fUseClonesArray) {
            fOutput->Delete();

            for (unsigned int i = 0; i < size; ++i) {
                new ((*fOutput)[i]) DataType(objArr[i]);
            }

            if (fOutput->IsEmpty()) {
                LOG(debug) << "RootOutFileManager::AddToFile(vector<DataType>&): No Output array!";
            }

            fTree->Fill();
            if (!fFlowMode) {
                fTree->Write("", TObject::kOverwrite);
            }
        } else {
            std::vector<DataType> dataVector(objArr, objArr + size);
            AddToFile(dataVector);
        }
    }

    void AddToFile(TClonesArray* inputData)
    {
        if (fUseClonesArray) {
            fOutput = inputData;
            fTree->SetBranchAddress(fBranchName.c_str(), &fOutput);

            if (fOutput->IsEmpty()) {
                LOG(debug) << "RootOutFileManager::AddToFile(TClonesArray*): No Output array!";
            }
            fTree->Fill();
            if (!fFlowMode) {
                fTree->Write("", TObject::kOverwrite);
            }
        } else {
            LOG(debug) << "RootOutFileManager::AddToFile(TClonesArray*): TClonesArray not set as output container";
        }
    }

    void AddToFile(FairMQMessage* msg)
    {
        int inputSize = msg->GetSize();
        int numInput = 0;
        if (inputSize > 0) {
            numInput = inputSize / sizeof(DataType);
        }
        fOutputData = static_cast<DataType*>(msg->GetData());
        AddToFile(fOutputData, numInput);
    }

    void AddToFile(std::unique_ptr<TClonesArray>& input) { AddToFile(input.get()); }

    void InitOutputFile()
    {
        fWrite = true;
        fOutFile = TFile::Open(fFilename.c_str(), fFileOption.c_str());

        bool updateTree = false;

        // if given option is update attempt to get tree from file
        if (fFileOption == "UPDATE") {
            fTree = static_cast<TTree*>(fOutFile->Get(fTreeName.c_str()));
            if (fTree) {
                updateTree = true;
                LOG(info) << "Update tree";
            } else {
                updateTree = false;
                LOG(info) << "Create new tree";
            }
        }

        // if tree not found or option is not UPDATE, create a new tree
        if (!updateTree) {
            fTree = new TTree(fTreeName.c_str(), "Test output");
        }

        // direct storage or TClonesArray
        if (fUseClonesArray) {
            fOutput = new TClonesArray(fClassName.c_str());
            if (updateTree) {
                fTree->SetBranchAddress(fBranchName.c_str(), &fOutput);
            } else {
                fTree->Branch(fBranchName.c_str(), "TClonesArray", &fOutput);
            }
        } else {
            if (updateTree) {
                fTree->SetBranchAddress(fBranchName.c_str(), &fOutputData);
            } else {
                fTree->Branch(fBranchName.c_str(), fClassName.c_str(), &fOutputData);
            }
        }

        fFolder = new TFolder("cbmroot", "/cbmroot");
        TList* branchNameList = new TList();
        branchNameList->AddLast(new TObjString(fBranchName.c_str()));
        branchNameList->Write("BranchList", TObject::kSingleKey);

        branchNameList->Delete();
        delete branchNameList;
    }
    void InitTCA(const std::string& classname);

    std::vector<std::vector<DataType>> GetAllObj(const std::string& filename,
                                                 const std::string& treename,
                                                 const std::string& branchname)
    {
        fWrite = false;

        TFile* file = TFile::Open(filename.c_str(), "READ");

        std::vector<std::vector<DataType>> allObj;
        std::vector<DataType> tempObj;

        if (file) {
            fTree = static_cast<TTree*>(file->Get(fTreeName.c_str()));
        } else {
            LOG(error) << "Could not open file" << fTreeName.c_str();
        }

        if (fTree) {
            if (fUseClonesArray) {
                fOutput = new TClonesArray(fClassName.c_str());
                fTree->SetBranchAddress(fBranchName.c_str(), &fOutput);

                for (Long64_t i = 0; i < fTree->GetEntries(); i++) {
                    tempObj.clear();
                    fTree->GetEntry(i);
                    for (Int_t iobj = 0; iobj < fOutput->GetEntriesFast(); ++iobj) {
                        DataType* data = reinterpret_cast<DataType*>(fOutput->At(iobj));
                        if (!data) {
                            continue;
                        }
                        tempObj.push_back(*data);
                    }
                    allObj.push_back(tempObj);
                }
            } else {
                fTree->SetBranchAddress(branchname.c_str(), &fOutputData);
                for (Long64_t i = 0; i < fTree->GetEntries(); i++) {
                    fTree->GetEntry(i);
                    DataType data = *fOutputData;
                    tempObj.push_back(data);
                }
                allObj.push_back(tempObj);
            }
        } else {
            LOG(error) << "Could not find tree " << treename.c_str();
        }

        if (file) {
            file->Close();
        }
        return allObj;
    }

    template<typename... Args>
    void Serialize(Args&&... args)
    {
        AddToFile(std::forward<Args>(args)...);
    }

  protected:
    virtual void Init()
    {
        fWrite = true;
        fOutFile = TFile::Open(fFilename.c_str(), fFileOption.c_str());

        bool updateTree = false;

        // if given option is update attempt to get tree from file
        if (fFileOption == "UPDATE") {
            fTree = static_cast<TTree*>(fOutFile->Get(fTreeName.c_str()));
            if (fTree) {
                updateTree = true;
                LOG(info) << "Update tree";
            } else {
                updateTree = false;
                LOG(info) << "Create new tree";
            }
        }

        // if tree not found or option is not UPDATE, create a new tree
        if (!updateTree) {
            fTree = new TTree(fTreeName.c_str(), "Test output");
        }

        // direct storage or TClonesArray
        if (fUseClonesArray) {
            fOutput = new TClonesArray(fClassName.c_str());
            if (updateTree) {
                fTree->SetBranchAddress(fBranchName.c_str(), &fOutput);
            } else {
                fTree->Branch(fBranchName.c_str(), "TClonesArray", &fOutput);
            }
        } else {
            if (updateTree) {
                fTree->SetBranchAddress(fBranchName.c_str(), &fOutputData);
            } else {
                fTree->Branch(fBranchName.c_str(), fClassName.c_str(), &fOutputData);
            }
        }
    }

    std::string fFilename;
    std::string fTreeName;
    std::string fBranchName;
    std::string fClassName;
    std::string fFileOption;
    bool fUseClonesArray;
    bool fFlowMode;
    bool fWrite;

    TFile* fOutFile;
    TTree* fTree;
    TClonesArray* fOutput;
    DataType* fOutputData;
    TFolder* fFolder;
};

#endif /* ROOTOUTFILEMANAGER_H */
