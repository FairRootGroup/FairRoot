/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
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

#include "FairTask.h"
#include "FairEventHeader.h"
#include <vector>
#include <string>

#include <boost/function.hpp>

#include "FairTask.h"
#include "TClonesArray.h"

#include "FairMQMessage.h"
#include "FairMQTransportFactory.h"

class FairMQSamplerTask : public FairTask
{
  public:
    FairMQSamplerTask();
    FairMQSamplerTask(const Text_t *name, int iVerbose = 1);

    virtual ~FairMQSamplerTask();

    virtual InitStatus Init();
    virtual void Exec(Option_t *opt);
    void
    SetSendPart(boost::function<void()>); // provides a callback to the Sampler.
    void SetEventIndex(Long64_t EventIndex);
    void SetBranch(string branch);
    FairMQMessage *GetOutput();
    void SetTransport(FairMQTransportFactory *factory);

  protected:
    TClonesArray *fInput;
    string fBranch;
    FairMQMessage *fOutput;
    FairMQTransportFactory *fTransportFactory;
    Long64_t fEventIndex;
    boost::function<void()> SendPart; // function pointer for the Sampler callback.
    FairEventHeader *fEvtHeader;
};

#endif /* FAIRMQSAMPLERTASK_H_ */
