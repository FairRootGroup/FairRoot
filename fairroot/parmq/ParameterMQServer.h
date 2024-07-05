/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * ParameterMQServer.h
 *
 * @since 2015-10-26
 * @author M. Al-Turany, A. Rybalchenko
 */

#ifndef PARAMETERMQSERVER_H_
#define PARAMETERMQSERVER_H_

#include "FairMQ.h"   // for fair::mq::Message, fair::mq::MessagePtr

#include <string>

class FairRuntimeDb;

class ParameterMQServer : public fair::mq::Device
{
  public:
    ParameterMQServer();

    ParameterMQServer(const ParameterMQServer&) = delete;
    ParameterMQServer operator=(const ParameterMQServer&) = delete;

    ~ParameterMQServer() override;

    void InitTask() override;
    void Init() override;
    bool ProcessRequest(fair::mq::MessagePtr&, int);
    bool ProcessUpdate(fair::mq::MessagePtr&, int);

    void SetFirstInputName(const std::string& firstInputName) { fFirstInputName = firstInputName; }
    std::string GetFirstInputName() { return fFirstInputName; }
    void SetFirstInputType(const std::string& firstInputType) { fFirstInputType = firstInputType; }
    std::string GetFirstInputType() { return fFirstInputType; }
    void SetSecondInputName(const std::string& secondInputName) { fSecondInputName = secondInputName; }
    std::string GetSecondInputName() { return fSecondInputName; }
    void SetSecondInputType(const std::string& secondInputType) { fSecondInputType = secondInputType; }
    std::string GetSecondInputType() { return fSecondInputType; }
    void SetOutputName(const std::string& outputName) { fOutputName = outputName; }
    std::string GetOutputName() { return fOutputName; }
    void SetOutputType(const std::string& outputType) { fOutputType = outputType; }
    std::string GetOutputType() { return fOutputType; }

    void SetChannelName(const std::string& channelName) { fRequestChannelName = channelName; }
    std::string GetChannelName() { return fRequestChannelName; }

    void SetUpdateChannelName(const std::string& channelName) { fUpdateChannelName = channelName; }
    std::string GetUpdateChannelName() { return fUpdateChannelName; }

  private:
    FairRuntimeDb* fRtdb;
    int fRunId;
    int fNofSimDevices;

    std::string fFirstInputName;
    std::string fFirstInputType;
    std::string fSecondInputName;
    std::string fSecondInputType;
    std::string fOutputName;
    std::string fOutputType;

    std::string fRequestChannelName;
    std::string fUpdateChannelName;
};

#endif /* PARAMETERMQSERVER_H_ */
