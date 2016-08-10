/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#include "FairMQDevice.h"
#include "FairMQProcessorTask.h"
#include "FairMQLogger.h"

template <typename Task>
class FairMQProcessor : public FairMQDevice
{
  public:
    FairMQProcessor()
        : fProcessorTask(new Task)
        , fReceivedMsgs(0)
        , fSentMsgs(0)
    {}

    /// Copy Constructor
    FairMQProcessor(const FairMQProcessor&) = delete;
    FairMQProcessor operator=(const FairMQProcessor&) = delete;

    virtual ~FairMQProcessor()
    {
        delete fProcessorTask;
    }

  protected:
    virtual void InitTask()
    {
        fProcessorTask->InitTask();
        OnData("data1", [this](std::unique_ptr<FairMQMessage>& msg, int /*index*/)
        {
            ++fReceivedMsgs;
            fProcessorTask->SetPayload(msg);
            fProcessorTask->Exec();
            fProcessorTask->GetPayload(msg);

            fChannels.at("data2").at(0).Send(msg);
            ++fSentMsgs;

            return true;
        });
    }

    virtual void PostRun()
    {
        LOG(INFO) << "Received " << fReceivedMsgs << " and sent " << fSentMsgs << " messages!";
    }

  private:
    FairMQProcessorTask* fProcessorTask;
    int fReceivedMsgs;
    int fSentMsgs;
};

#endif /* FAIRMQPROCESSOR_H_ */
