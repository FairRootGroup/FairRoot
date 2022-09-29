/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQProcessorTask.cxx
 *
 * @since Dec 6, 2012-12-06
 * @author: D. Klein, A. Rybalchenko
 */

#include "FairMQProcessorTask.h"

FairMQProcessorTask::FairMQProcessorTask()
    : fPayload()
{}

FairMQProcessorTask::~FairMQProcessorTask() {}

void FairMQProcessorTask::Exec(Option_t* /*opt*/) {}

void FairMQProcessorTask::SetPayload(std::unique_ptr<fair::mq::Message>& msg) { fPayload = std::move(msg); }

void FairMQProcessorTask::GetPayload(std::unique_ptr<fair::mq::Message>& msg) { msg = std::move(fPayload); }
