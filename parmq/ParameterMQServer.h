/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#include <string>

#include "FairMQDevice.h"

class FairRuntimeDb;

class ParameterMQServer : public FairMQDevice
{
  public:
    enum
    {
        FirstInputName = FairMQDevice::Last,
        FirstInputType,
        SecondInputName,
        SecondInputType,
        OutputName,
        OutputType,
        ChannelName,
        Last
    };

    ParameterMQServer();

    ParameterMQServer(const ParameterMQServer&) = delete;
    ParameterMQServer operator=(const ParameterMQServer&) = delete;

    virtual ~ParameterMQServer();

    virtual void Run();
    virtual void InitTask();

    virtual void SetProperty(const int key, const std::string& value);
    virtual std::string GetProperty(const int key, const std::string& default_ = "");
    virtual void SetProperty(const int key, const int value);
    virtual int GetProperty(const int key, const int default_ = 0);

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

    void SetChannelName(const std::string& channelName) { fChannelName = channelName; }
    std::string GetChannelName() { return fChannelName; }

  private:
    FairRuntimeDb* fRtdb;

    std::string fFirstInputName;
    std::string fFirstInputType;
    std::string fSecondInputName;
    std::string fSecondInputType;
    std::string fOutputName;
    std::string fOutputType;

    std::string fChannelName;
};

#endif /* PARAMETERMQSERVER_H_ */
