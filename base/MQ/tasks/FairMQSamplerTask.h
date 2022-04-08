/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSamplerTask.h
 *
 * @since 2012-11-22
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQSAMPLERTASK_H_
#define FAIRMQSAMPLERTASK_H_

#include "FairEventHeader.h"
#include "FairMQ.h"   // for fair::mq::Message, fair::mq::TransportFactory
#include "FairTask.h"

#include <TClonesArray.h>
#include <memory>
#include <string>

class FairMQSamplerTask : public FairTask
{
  public:
    FairMQSamplerTask();
    FairMQSamplerTask(const Text_t* name, int iVerbose = 1);
    FairMQSamplerTask(const FairMQSamplerTask&) = delete;
    FairMQSamplerTask operator=(const FairMQSamplerTask&) = delete;

    virtual ~FairMQSamplerTask();

    virtual InitStatus Init();
    virtual void Exec(Option_t* opt);

    void SetEventIndex(Long64_t eventIndex);
    void SetBranch(const std::string& branch);

    void GetPayload(std::unique_ptr<fair::mq::Message>& msg);
    void SetTransport(std::shared_ptr<fair::mq::TransportFactory> factory);

  protected:
    std::string fBranch;
    TClonesArray* fInput;
    fair::mq::MessagePtr fPayload;
    Long64_t fEventIndex;
    FairEventHeader* fEvtHeader;
    std::shared_ptr<fair::mq::TransportFactory> fTransportFactory;
};

#endif /* FAIRMQSAMPLERTASK_H_ */
