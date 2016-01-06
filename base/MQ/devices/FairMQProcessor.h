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

class FairMQProcessor : public FairMQDevice
{
  public:
    FairMQProcessor();
    FairMQProcessor(const FairMQProcessor&) = delete;
    FairMQProcessor operator=(const FairMQProcessor&) = delete;
    virtual ~FairMQProcessor();

    void SetTask(FairMQProcessorTask* task);
    void SendPart();
    bool ReceivePart();

  protected:
    virtual void InitTask();
    virtual void Run();

  private:
    FairMQProcessorTask* fProcessorTask;
};

#endif /* FAIRMQPROCESSOR_H_ */
