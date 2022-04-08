/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   BaseMQFileSink.h
 * Author: winckler
 *
 * Created on October 7, 2014, 6:06 PM
 */

#ifndef BASEMQFILESINK_H
#define BASEMQFILESINK_H

#include <FairMQDevice.h>
#include <fairlogger/Logger.h>

template<typename InputPolicy, typename OutputPolicy>
class BaseMQFileSink
    : public FairMQDevice
    , public InputPolicy
    , public OutputPolicy
{
  public:
    BaseMQFileSink()
        : InputPolicy()
        , OutputPolicy()
        , fInputChanName()
    {}

    virtual ~BaseMQFileSink() {}

    template<typename... Args>
    void InitInputData(Args&&... args)
    {
        InputPolicy::Create(std::forward<Args>(args)...);
    }

  protected:
    virtual void InitTask()
    {
        fInputChanName = fConfig->GetValue<std::string>("in-chan-name");
        OutputPolicy::SetFileProperties(*fConfig);
        OutputPolicy::InitOutputFile();
    }

    virtual void Run()
    {
        int receivedMsg = 0;
        while (!NewStatePending()) {
            auto msg(NewMessage());
            if (Receive(msg, fInputChanName) > 0) {
                InputPolicy::Deserialize(*msg, InputPolicy::fInput);   // get data from message.
                OutputPolicy::Serialize(InputPolicy::fInput);          // put data into output.
                receivedMsg++;
            }
        }

        LOG(info) << "Received " << receivedMsg << " messages!";
    }

  private:
    std::string fInputChanName;
};

#endif /* BASEMQFILESINK_H */
