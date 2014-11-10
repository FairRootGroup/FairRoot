/* 
 * File:   SimpleTreeReader.h
 * Author: winckler
 *
 * Created on November 25, 2014, 11:17 AM
 */

#ifndef SIMPLEROOTSAMPLER_H
#define	SIMPLEROOTSAMPLER_H


// std
#include <iostream>
#include <vector>
#include <string>

// ROOT
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"




template <typename DataBranchType>
class SimpleTreeReader 
{
public:
    SimpleTreeReader() : fFileName(),    fTreeName(), 
                          fBranchName(),  fInputFile(nullptr),
                          fTree(nullptr), fDataBranch(nullptr)
                          {}
    virtual ~SimpleTreeReader()
    {
        if(fInputFile)
        {
            if(fInputFile)
                fInputFile->Close();
            delete fInputFile;
        }
    }
    
    void SetFileProperties(const std::string &filename, const std::string &treename, const std::string &branchname)
    {
        fFileName=filename;
        fTreeName=treename;
        fBranchName=branchname;
    }
    
    //template < std::enable_if<std::is_base_of<TObject, DataBranchType>::value,int> = 0>
    void InitSampler()
    {
        fInputFile = TFile::Open(fFileName.c_str(),"READ");
        if(fInputFile)
        {
            fTree=(TTree*)fInputFile->Get(fTreeName.c_str());
            if(fTree)
                fTree->SetBranchAddress(fBranchName.c_str(),&fDataBranch);
            else
                MQLOG(ERROR)<<"Could not find tree "<<fTreeName;
        }
        else
            MQLOG(ERROR)<<"Could not open file "<<fFileName<<" in SimpleTreeReader::InitSampler()";
    }
    
    DataBranchType* GetDataBranch(const Long64_t &Event)
    {
        fTree->GetEntry(Event);
        return fDataBranch;
    }
    
    int GetDataBunchNumber()
    {
        if(fTree) 
            return fTree->GetEntries();
        else 
            return 0;
    }
    
    template<typename T>
        std::vector< std::vector<T> > GetDataVector()
        {
            std::vector<std::vector<T> > Allobj;
            std::vector<T> TempObj;
            if(std::is_same<DataBranchType,TClonesArray>::value)
            {
                for(Long64_t i(0);i<fTree->GetEntries() ;i++)
                {
                    TempObj.clear();
                    fTree->GetEntry(i);
                    for (Int_t iobj = 0; iobj < fDataBranch->GetEntriesFast(); ++iobj)
                    {
                        T* Data_i = reinterpret_cast<T*>(fDataBranch->At(iobj));
                        if (!Data_i)
                            continue;
                        TempObj.push_back(*Data_i);
                    }
                    Allobj.push_back(TempObj);
                }
            }
            else
            {
                for(Long64_t i(0);i<fTree->GetEntries() ;i++)
                {
                    TempObj.clear();
                    fTree->GetEntry(i);
                    T Data_i=*fDataBranch;
                    TempObj.push_back(Data_i);
                    Allobj.push_back(TempObj);
                }
            }
            return Allobj;
        }
    
    
private:
    std::string fFileName;
    std::string fTreeName;
    std::string fBranchName;
    TFile* fInputFile;
    TTree* fTree;
    DataBranchType* fDataBranch;
};

#endif	/* SIMPLEROOTSAMPLER_H */

