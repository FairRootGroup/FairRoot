/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQDevice.h
 *
 * @since 2012-10-25
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQDEVICE_H_
#define FAIRMQDEVICE_H_

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "FairMQConfigurable.h"
#include "FairMQStateMachine.h"
#include "FairMQTransportFactory.h"
#include "FairMQSocket.h"
#include "FairMQChannel.h"

class FairMQDevice : public FairMQStateMachine, public FairMQConfigurable
{
  public:
    enum
    {
        Id = FairMQConfigurable::Last,
        MaxInitializationTime,
        NumIoThreads,
        PortRangeMin,
        PortRangeMax,
        LogIntervalInMs,
        Last
    };

    FairMQDevice();

    virtual void LogSocketRates();

    void SortChannel(const std::string& name, const bool reindex = true);
    void PrintChannel(const std::string& name);

    virtual void SetProperty(const int key, const std::string& value);
    virtual std::string GetProperty(const int key, const std::string& default_ = "");
    virtual void SetProperty(const int key, const int value);
    virtual int GetProperty(const int key, const int default_ = 0);

    virtual void SetTransport(FairMQTransportFactory* factory);

    virtual ~FairMQDevice();

    std::map< std::string,std::vector<FairMQChannel> > fChannels;

  protected:
    std::string fId;

    int fMaxInitializationTime;

    int fNumIoThreads;

    int fPortRangeMin;
    int fPortRangeMax;

    int fLogIntervalInMs;

    FairMQSocket* fCommandSocket;

    FairMQTransportFactory* fTransportFactory;

    void InitWrapper();
    virtual void Init();

    void InitTaskWrapper();
    virtual void InitTask();

    void RunWrapper();
    virtual void Run();

    virtual void Pause();

    void ResetTaskWrapper();
    virtual void ResetTask();

    void ResetWrapper();
    virtual void Reset();

    virtual void Shutdown();

    void Terminate();
    void SendCommand(const std::string& command);

    bool InitChannel(FairMQChannel&);

  private:
    /// Copy Constructor
    FairMQDevice(const FairMQDevice&);
    FairMQDevice operator=(const FairMQDevice&);
};

#endif /* FAIRMQDEVICE_H_ */
