/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelFileSinkBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELFILESINKBIN_H_
#define FAIRMQPIXELFILESINKBIN_H_

#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts

#include <string>
#include <vector>

class TFile;
class TFolder;
class TObject;
class TTree;

class FairMQPixelFileSinkBin : public fair::mq::Device
{
  public:
    FairMQPixelFileSinkBin();
    virtual ~FairMQPixelFileSinkBin();

    void SetOutputFileName(const std::string& tempString) { fFileName = tempString; }
    void AddOutputBranch(const std::string& classString, const std::string& branchString)
    {
        fClassNames.push_back(classString);
        fBranchNames.push_back(branchString);
    }
    std::string GetOutputFileName() { return fFileName; }

    void SetInputChannelName(const std::string& tstr) { fInputChannelName = tstr; }
    void SetAckChannelName(const std::string& tstr) { fAckChannelName = tstr; }

  protected:
    bool StoreData(fair::mq::Parts&, int);
    virtual void Init();

  private:
    std::string fInputChannelName;
    std::string fAckChannelName;

    std::string fFileName;
    std::string fTreeName;

    std::vector<std::string> fBranchNames;
    std::vector<std::string> fClassNames;

    std::string fFileOption;
    bool fFlowMode;
    bool fWrite;

    TFile* fOutFile;
    TTree* fTree;
    unsigned int fNObjects;
    TObject** fOutputObjects;
    /* FairEventHeader* fEventHeader; */
    /* TClonesArray*    fOutput; */
    TFolder* fFolder;

    FairMQPixelFileSinkBin(const FairMQPixelFileSinkBin&);
    FairMQPixelFileSinkBin& operator=(const FairMQPixelFileSinkBin&);
};

#endif /* FAIRMQPIXELFILESINK_H_ */
