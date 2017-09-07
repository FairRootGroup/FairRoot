/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
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

#include "FairMQDevice.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"

template <typename InputPolicy, typename OutputPolicy>
class BaseMQFileSink : public FairMQDevice, public InputPolicy, public OutputPolicy
{
  public:
    BaseMQFileSink()
        : InputPolicy()
        , OutputPolicy()
    {}

    virtual ~BaseMQFileSink()
    {}

    template<typename... Args>
    void InitInputData(Args&&... args)
    {
        InputPolicy::Create(std::forward<Args>(args)...);
    }

  protected:
    virtual void InitTask()
    {
        OutputPolicy::SetFileProperties(*fConfig);
        OutputPolicy::InitOutputFile();
    }

    virtual void Run()
    {
        int receivedMsg = 0;
        while (CheckCurrentState(RUNNING))
        {
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            if (Receive(msg, "data-in") > 0)
            {
                Deserialize<typename InputPolicy::DeserializerType>(*msg, InputPolicy::fInput); // get data from message.
                OutputPolicy::Serialize(InputPolicy::fInput); // put data into output.
                receivedMsg++;
            }
        }

        LOG(INFO) << "Received " << receivedMsg << " messages!";
    }
};

#endif /* BASEMQFILESINK_H */
