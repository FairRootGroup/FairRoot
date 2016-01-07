/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#include <vector>

#include <boost/function.hpp>

#include "FairTask.h"

#include "FairMQMessage.h"
#include "FairMQTransportFactory.h"

class FairMQProcessorTask : public FairTask
{
  public:
    FairMQProcessorTask();
    FairMQProcessorTask(const FairMQProcessorTask&) = delete;
    FairMQProcessorTask operator=(const FairMQProcessorTask&) = delete;

    virtual ~FairMQProcessorTask();

    virtual void Exec(Option_t* opt = "0");

    void SetSendPart(boost::function<void()>); // provides a callback to the Processor.
    void SetReceivePart(boost::function<bool()>); // provides a callback to the Processor.

    void SetPayload(FairMQMessage* msg);
    FairMQMessage* GetPayload();
    void ClearPayload();

  protected:
    FairMQMessage* fPayload;
    boost::function<void()> SendPart; // function pointer for the Processor callback.
    boost::function<bool()> ReceivePart; // function pointer for the Processor callback.
};

#endif /* FAIRMQPROCESSORTASK_H_ */
