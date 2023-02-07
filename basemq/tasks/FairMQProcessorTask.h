/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQPROCESSORTASK_H_
#define FAIRMQPROCESSORTASK_H_

#include "FairMQ.h"   // for fair::mq::Message
#include "FairTask.h"

class FairMQProcessorTask : public FairTask
{
  public:
    FairMQProcessorTask() = default;
    FairMQProcessorTask(const FairMQProcessorTask&) = delete;
    FairMQProcessorTask operator=(const FairMQProcessorTask&) = delete;

    ~FairMQProcessorTask() override = default;

    void SetPayload(std::unique_ptr<fair::mq::Message>& msg) { fPayload = std::move(msg); }
    void GetPayload(std::unique_ptr<fair::mq::Message>& msg) { msg = std::move(fPayload); }

  protected:
    std::unique_ptr<fair::mq::Message> fPayload;
};

#endif /* FAIRMQPROCESSORTASK_H_ */
