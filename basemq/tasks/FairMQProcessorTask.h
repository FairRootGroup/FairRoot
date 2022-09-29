/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQProcessorTask.h
 *
 * @since Dec 6, 2012-12-06
 * @author: D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQPROCESSORTASK_H_
#define FAIRMQPROCESSORTASK_H_

#include "FairMQ.h"   // for fair::mq::Message
#include "FairTask.h"

class FairMQProcessorTask : public FairTask
{
  public:
    FairMQProcessorTask();
    FairMQProcessorTask(const FairMQProcessorTask&) = delete;
    FairMQProcessorTask operator=(const FairMQProcessorTask&) = delete;

    virtual ~FairMQProcessorTask();

    virtual void Exec(Option_t* opt = "0");

    void SetPayload(std::unique_ptr<fair::mq::Message>& msg);
    void GetPayload(std::unique_ptr<fair::mq::Message>& msg);

  protected:
    std::unique_ptr<fair::mq::Message> fPayload;
};

#endif /* FAIRMQPROCESSORTASK_H_ */
