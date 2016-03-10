/* 
 * File:   RootOutFileManager.h
 * Author: winckler
 *
 * Created on October 7, 2014, 9:40 PM
 */

#ifndef ROOTOUTFILEMANAGER_H
#define	ROOTOUTFILEMANAGER_H

// std
#include <iostream>
#include <vector>
#include <string>

// ROOT
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

#include "TKey.h"
#include "TFolder.h"
#include "TObjString.h"
#include "TList.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "BaseSinkPolicy.h"

template <typename DataType>
class RootOutFileManager : public BaseSinkPolicy<RootOutFileManager<DataType>>
{
  public:
    RootOutFileManager();
    RootOutFileManager(const std::string &filename, const std::string &treename, 
                     const std::string &branchname, const std::string &Classname, const std::string &FileOption);

    RootOutFileManager(const RootOutFileManager&) = delete;
    RootOutFileManager operator=(const RootOutFileManager&) = delete;

    virtual ~RootOutFileManager();

    void SetRootFileProperties(const std::string &filename, const std::string &treename, 
                           const std::string &branchname, const std::string &Classname="", 
                           const std::string &FileOption="RECREATE", bool UseClonesArray=false, bool flowmode=true);

    void SetFileProperties(const std::string &filename, const std::string &treename, 
                           const std::string &branchname, const std::string &Classname="", 
                           const std::string &FileOption="RECREATE", bool UseClonesArray=false, bool flowmode=true);

    void AddToFile(std::vector<DataType>& InputData);
    void AddToFile(DataType* ObjArr, long size);
    void AddToFile(TClonesArray* InputData);
    void AddToFile(FairMQMessage* msg);
    void InitOutputFile();
    void InitTCA(const std::string &classname);
    std::vector<std::vector<DataType> > GetAllObj(const std::string &filename,
                                                  const std::string &treename,
                                                  const std::string &branchname
                                                  );

  protected:
    virtual void Init();

    std::string fFileName;
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

#include "RootOutFileManager.tpl"

#endif /* ROOTOUTFILEMANAGER_H */
