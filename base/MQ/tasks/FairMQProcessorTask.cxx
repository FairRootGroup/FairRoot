/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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
    : fPayload(nullptr)
    , fTransportFactory(nullptr)
{
}

FairMQProcessorTask::~FairMQProcessorTask()
{
}

void FairMQProcessorTask::Exec(Option_t* /*opt*/)
{
}

FairMQMessage* FairMQProcessorTask::GetPayload()
{
    return fPayload;
}

void FairMQProcessorTask::SetPayload(FairMQMessage* msg)
{
    if (msg)
    {
        fPayload = msg;
    }
    else
    {
        LOG(ERROR) << "FairMQMessage uninitialized or bad format";
    }
}

void FairMQProcessorTask::ClearPayload()
{
    delete fPayload;
}

void FairMQProcessorTask::SetTransport(FairMQTransportFactory* factory)
{
    fTransportFactory = factory;
}
