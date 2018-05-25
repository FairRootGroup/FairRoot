/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelFileSink.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELFILESINK_H_
#define FAIRMQPIXELFILESINK_H_

#include "TClonesArray.h"
#include "TFile.h"
#include "TFolder.h"
#include "TTree.h"
#include "FairEventHeader.h"

#include "FairMQDevice.h"

class FairMQPixelFileSink : public FairMQDevice
{
  public:
    FairMQPixelFileSink();
    virtual ~FairMQPixelFileSink();

    void SetOutputFileName(std::string tempString) { fFileName = tempString; }
    void AddOutputBranch  (std::string classString, std::string branchString) 
    { 
      fClassNames .push_back(classString); 
      fBranchNames.push_back(branchString); 
    }
    std::string GetOutputFileName () { return fFileName;}

    void SetInputChannelName (std::string tstr) {fInputChannelName = tstr;}
    void SetAckChannelName(std::string tstr) {fAckChannelName = tstr;}

  protected:
    bool StoreData(FairMQParts&, int);
    virtual void Init();

 private:
    std::string     fInputChannelName;
    std::string     fAckChannelName;

    std::string fFileName;
    std::string fTreeName;

    std::vector<std::string> fBranchNames;
    std::vector<std::string> fClassNames;

    std::string fFileOption;
    bool fFlowMode;
    bool fWrite;

    TFile* fOutFile;
    TTree* fTree;
    unsigned int    fNObjects;
    TObject**       fOutputObjects;
    /* FairEventHeader* fEventHeader; */
    /* TClonesArray*    fOutput; */
    TFolder* fFolder;

    FairMQPixelFileSink(const FairMQPixelFileSink&);
    FairMQPixelFileSink& operator=(const FairMQPixelFileSink&);
};

#endif /* FAIRMQPIXELFILESINK_H_ */
