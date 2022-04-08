/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixAltSamplerBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXALTSAMPLERBIN_H_
#define FAIRMQPIXALTSAMPLERBIN_H_

#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "PixelPayload.h"

#include <cstdint>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

class TBranch;
class TChain;

class FairMQPixAltSamplerBin : public fair::mq::Device
{
  public:
    FairMQPixAltSamplerBin();
    virtual ~FairMQPixAltSamplerBin();

    void AddInputFileName(const std::string& tempString) { fFileNames.push_back(tempString); }

    void SetMaxIndex(int64_t tempInt) { fMaxIndex = tempInt; }

    void ListenForAcks();

    void SetOutputChannelName(const std::string& tstr) { fOutputChannelName = tstr; }
    void SetAckChannelName(const std::string& tstr) { fAckChannelName = tstr; }

    void SetAggregateFactor(int nal) { fAggregateLevel = nal; }

  protected:
    virtual bool ConditionalRun();
    virtual void PreRun();
    virtual void PostRun();
    virtual void InitTask();

    bool ReadBinFile();
    bool ReadRootFile();

  private:
    std::string fOutputChannelName;
    std::string fAckChannelName;

    std::vector<std::string> fFileNames;
    std::ifstream fInputFile;
    int fCurrentFile;

    TChain* fInputChain;
    PixelPayload::EventHeader* fEventHeader;
    TBranch* fDigiBranch;
    std::vector<PixelPayload::Digi>* fDigiArray;

    int fAggregateLevel;

    int64_t fMaxIndex;

    int fEventCounter;
    int fNofRecAcks;

    bool fReadingRootFiles;

    FairMQPixAltSamplerBin(const FairMQPixAltSamplerBin&);
    FairMQPixAltSamplerBin& operator=(const FairMQPixAltSamplerBin&);

    std::thread fAckListener;
};

#endif /* FAIRMQPIXALTSAMPLER_H_ */
