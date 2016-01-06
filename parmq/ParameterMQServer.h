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
        Last
    };

    ParameterMQServer();
    ParameterMQServer(const ParameterMQServer&) = delete;
    ParameterMQServer operator=(const ParameterMQServer&) = delete;
    virtual ~ParameterMQServer();

    virtual void Run();
    virtual void InitTask();

    static void CustomCleanup(void *data, void* hint);

    virtual void SetProperty(const int key, const std::string& value);
    virtual std::string GetProperty(const int key, const std::string& default_ = "");
    virtual void SetProperty(const int key, const int value);
    virtual int GetProperty(const int key, const int default_ = 0);

  private:
    FairRuntimeDb* fRtdb;

    std::string fFirstInputName;
    std::string fFirstInputType;
    std::string fSecondInputName;
    std::string fSecondInputType;
    std::string fOutputName;
    std::string fOutputType;
};

#endif /* PARAMETERMQSERVER_H_ */
