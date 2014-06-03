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
#include <vector>
#include "TClonesArray.h"
#include <string>
#include "FairMQMessage.h"
#include "FairMQTransportFactory.h"


class FairMQSamplerTask: public FairTask
{
  public:
    FairMQSamplerTask();
    FairMQSamplerTask(const Text_t* name, int iVerbose=1);
    virtual ~FairMQSamplerTask();
    virtual InitStatus Init();
    virtual void Exec(Option_t* opt);
    void SetBranch(string branch);
    FairMQMessage* GetOutput();
    void SetTransport(FairMQTransportFactory* factory);

  protected:
    TClonesArray* fInput;
    string fBranch;
    FairMQMessage* fOutput;
    FairMQTransportFactory* fTransportFactory;
};

#endif /* FAIRMQSAMPLERTASK_H_ */
