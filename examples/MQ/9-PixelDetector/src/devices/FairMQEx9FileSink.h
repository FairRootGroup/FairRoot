/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9FileSink.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9FILESINK_H_
#define FAIRMQEX9FILESINK_H_

#include "TClonesArray.h"
#include "TFile.h"
#include "TFolder.h"
#include "TTree.h"
#include "FairEventHeader.h"

#include "FairMQDevice.h"

class FairMQEx9FileSink : public FairMQDevice
{
  public:
    enum
    {
        OutputFileName = FairMQDevice::Last,
        Last
    };

    FairMQEx9FileSink();
    virtual ~FairMQEx9FileSink();

    void SetProperty(const int key, const std::string& value);
    void SetProperty(const int key, const int value);
    std::string GetProperty(const int key, const std::string& default_ = "");
    int GetProperty(const int key, const int default_ = 0);
    
    void SetOutputFileName(std::string tempString) { fFileName = tempString; }
    void AddOutputBranch  (std::string classString, std::string branchString) 
    { 
      fClassNames .push_back(classString); 
      fBranchNames.push_back(branchString); 
    }
    std::string GetOutputFileName () { return fFileName;}

  protected:
    virtual void Init();
    virtual void Run();

 private:
    std::string fFileName;
    std::string fTreeName;

    std::vector<std::string> fBranchNames;
    std::vector<std::string> fClassNames;

    std::string fFileOption;
    bool fFlowMode;
    bool fWrite;

    TFile* fOutFile;
    TTree* fTree;
    int             fNObjects;
    TObject**       fOutputObjects;
    /* FairEventHeader* fEventHeader; */
    /* TClonesArray*    fOutput; */
    TFolder* fFolder;

};

#endif /* FAIRMQEX9FILESINK_H_ */
