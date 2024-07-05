/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelSampler.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELSAMPLER_H_
#define FAIRMQPIXELSAMPLER_H_

#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts

#include <cstdint>
#include <string>
#include <thread>
#include <vector>

class FairSource;
class FairRunAna;
class TObject;

class FairMQPixelSampler : public fair::mq::Device
{
  public:
    FairMQPixelSampler();
    ~FairMQPixelSampler() override;

    void AddInputFileName(const std::string& tempString) { fFileNames.push_back(tempString); }
    void AddInputBranchName(const std::string& tempString) { fBranchNames.push_back(tempString); }

    void SetMaxIndex(int64_t tempInt) { fMaxIndex = tempInt; }

    void SetSource(FairSource* tempSource) { fSource = tempSource; }

    void ListenForAcks();

    void SetOutputChannelName(const std::string& tstr) { fOutputChannelName = tstr; }
    void SetAckChannelName(const std::string& tstr) { fAckChannelName = tstr; }

  protected:
    bool ConditionalRun() override;
    void PreRun() override;
    void PostRun() override;
    void InitTask() override;

  private:
    std::string fOutputChannelName;
    std::string fAckChannelName;

    FairRunAna* fRunAna;
    FairSource* fSource;
    TObject* fInputObjects[100];
    int fNObjects;
    int64_t fMaxIndex;

    int fEventCounter;

    std::vector<std::string> fBranchNames;
    std::vector<std::string> fFileNames;

    FairMQPixelSampler(const FairMQPixelSampler&);
    FairMQPixelSampler& operator=(const FairMQPixelSampler&);

    std::thread fAckListener;
};

#endif /* FAIRMQPIXELSAMPLER_H_ */
