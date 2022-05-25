/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   SimpleTreeReader.h
 * Author: winckler
 *
 * Created on November 25, 2014, 11:17 AM
 */

#ifndef SIMPLEROOTSAMPLER_H
#define SIMPLEROOTSAMPLER_H

// std
#include <functional>
#include <stdint.h>
#include <string>
#include <vector>

// ROOT
#include <Rtypes.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>
#include <fairlogger/Logger.h>

template<typename DataType>
class BaseSimpleTreeReader
{
  public:
    BaseSimpleTreeReader()
        : fSendHeader()
        , fGetSocketNumber()
        , fGetCurrentIndex()
        , fInput(nullptr)
        , fFileName("")
        , fTreeName("")
        , fBranchName("")
        , fInputFile(nullptr)
        , fTree(nullptr)
        , fIndex(0)
        , fIndexMax(0)
    {}

    BaseSimpleTreeReader(const BaseSimpleTreeReader&) = delete;
    BaseSimpleTreeReader operator=(const BaseSimpleTreeReader&) = delete;

    virtual ~BaseSimpleTreeReader()
    {
        if (fInputFile) {
            fInputFile->Close();
            delete fInputFile;
        }
    }

    void SetFileProperties(const std::string& filename, const std::string& treename, const std::string& branchname)
    {
        fFileName = filename;
        fTreeName = treename;
        fBranchName = branchname;
    }

    // template < std::enable_if<std::is_base_of<TObject, DataType>::value,int> = 0>
    void InitSource()
    {
        fInputFile = TFile::Open(fFileName.c_str(), "READ");
        if (fInputFile) {
            fTree = fInputFile->Get<TTree>(fTreeName.c_str());
            if (fTree) {
                fTree->SetBranchAddress(fBranchName.c_str(), &fInput);
                fIndexMax = fTree->GetEntries();
            } else {
                LOG(error) << "Could not find tree " << fTreeName;
            }
        } else {
            LOG(error) << "Could not open file " << fFileName << " in SimpleTreeReader::InitSource()";
        }
    }

    void SendMultiPart()
    {
        fSendHeader(0);   // callback that does the zmq multipart AND increment the current index (Event number) in
                          // generic sampler
    }

    void SetIndex(int64_t Event) { fIndex = Event; }

    DataType* GetOutData() { return GetOutData(fIndex); }

    DataType* GetOutData(int64_t Event)
    {
        fTree->GetEntry(Event);
        return fInput;
    }
    void GetOutData(DataType*& data, int64_t Event)
    {
        fTree->GetEntry(Event);
        data = fInput;
    }
    void deserialize_impl(DataType*& data, int64_t Event)
    {
        /*required for MQ*/
        fTree->GetEntry(Event);
        data = fInput;
    }
    void deserialize_impl(int64_t Event)
    {
        /*required for MQ*/
        fTree->GetEntry(Event);
    }

    int64_t GetNumberOfEvent()
    {
        if (fTree) {
            return fIndexMax;
        } else {
            return 0;
        }
    }

    template<typename T>
    std::vector<std::vector<T>> GetDataVector()
    {
        std::vector<std::vector<T>> allObj;
        std::vector<T> tempObj;

        if (std::is_same<DataType, TClonesArray>::value) {
            for (int64_t i = 0; i < fTree->GetEntries(); i++) {
                tempObj.clear();
                fTree->GetEntry(i);
                for (int64_t iobj = 0; iobj < fInput->GetEntriesFast(); ++iobj) {
                    T* data = reinterpret_cast<T*>(fInput->At(iobj));
                    if (!data) {
                        continue;
                    }
                    tempObj.push_back(*data);
                }
                allObj.push_back(tempObj);
            }
        } else {
            for (int64_t i = 0; i < fTree->GetEntries(); i++) {
                tempObj.clear();
                fTree->GetEntry(i);
                T data = *fInput;
                tempObj.push_back(data);
                allObj.push_back(tempObj);
            }
        }
        return allObj;
    }

    // provides a callback to the Sampler.
    void BindSendHeader(std::function<void(int)> callback) { fSendHeader = callback; }

    void BindGetSocketNumber(std::function<int()> callback) { fGetSocketNumber = callback; }

    void BindGetCurrentIndex(std::function<int()> callback) { fGetCurrentIndex = callback; }

  protected:
    DataType* fInput;   // data type of the branch you want to extract

  private:
    std::function<void(int)> fSendHeader;    // function pointer for the Sampler callback.
    std::function<int()> fGetSocketNumber;   // function pointer for the Sampler callback.
    std::function<int()> fGetCurrentIndex;   // function pointer for the Sampler callback.

    std::string fFileName;
    std::string fTreeName;
    std::string fBranchName;
    TFile* fInputFile;
    TTree* fTree;
    int64_t fIndex;
    int64_t fIndexMax;
};

template<typename T>
using SimpleTreeReader = BaseSimpleTreeReader<T>;

#endif /* SIMPLEROOTSAMPLER_H */
