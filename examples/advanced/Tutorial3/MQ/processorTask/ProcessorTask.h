/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_PROCESSORTASK_H
#define FAIR_TESTDETECTOR_PROCESSORTASK_H

#include "FairMQ.h"   // for fair::mq::Message
#include "FairTask.h"

class ProcessorTask : public FairTask
{
  public:
    ProcessorTask() = default;
    ProcessorTask(const ProcessorTask&) = delete;
    ProcessorTask operator=(const ProcessorTask&) = delete;

    ~ProcessorTask() override = default;

    void SetPayload(std::unique_ptr<fair::mq::Message>& msg) { fPayload = std::move(msg); }
    void GetPayload(std::unique_ptr<fair::mq::Message>& msg) { msg = std::move(fPayload); }

  protected:
    std::unique_ptr<fair::mq::Message> fPayload;
};

#endif /* FAIR_TESTDETECTOR_PROCESSORTASK_H */
