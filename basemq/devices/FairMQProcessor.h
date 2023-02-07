/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQProcessor.h
 *
 * @since 2012-12-06
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQPROCESSOR_H_
#define FAIRMQPROCESSOR_H_

#include "FairMQ.h"   // for fair::mq::Device, fair::mq::MessagePtr
#include "FairMQProcessorTask.h"

#include <fairlogger/Logger.h>

template<typename Task>
class FairMQProcessor : public fair::mq::Device
{
  public:
    FairMQProcessor()
        : fProcessorTask(new Task)
        , fInChannelName("data1")
        , fOutChannelName("data2")
        , fReceivedMsgs(0)
        , fSentMsgs(0)
    {}

    /// Copy Constructor
    FairMQProcessor(const FairMQProcessor&) = delete;
    FairMQProcessor operator=(const FairMQProcessor&) = delete;

    virtual ~FairMQProcessor() {}

  protected:
    virtual void InitTask()
    {
        std::string inChannelName = fConfig->GetValue<std::string>("in-channel");
        std::string outChannelName = fConfig->GetValue<std::string>("out-channel");
        // check if the returned value actually exists, for the compatibility with old devices.
        if (inChannelName != "") {
            fInChannelName = inChannelName;
        }
        if (outChannelName != "") {
            fOutChannelName = outChannelName;
        }

        fProcessorTask->InitTask();
        OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
            ++fReceivedMsgs;
            fProcessorTask->SetPayload(msg);
            fProcessorTask->Exec("0");
            fProcessorTask->GetPayload(msg);

            Send(msg, fOutChannelName);
            ++fSentMsgs;

            return true;
        });
    }

    virtual void PostRun() { LOG(info) << "Received " << fReceivedMsgs << " and sent " << fSentMsgs << " messages!"; }

  private:
    std::unique_ptr<FairMQProcessorTask> fProcessorTask;
    std::string fInChannelName;
    std::string fOutChannelName;
    int fReceivedMsgs;
    int fSentMsgs;
};

#endif /* FAIRMQPROCESSOR_H_ */
