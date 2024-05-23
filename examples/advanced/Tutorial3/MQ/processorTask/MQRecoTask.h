/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_MQRECOTASK_H
#define FAIR_TESTDETECTOR_MQRECOTASK_H

// this example
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorRecoTask.h"
#include "Payload.h"
#include "ProcessorTask.h"

// FairRoot
#include "FairRootManager.h"

// ROOT
#include <TClonesArray.h>

// logger
#include <fairlogger/Logger.h>

template<typename T>
class MQRecoTask : public ProcessorTask
{
  public:
    MQRecoTask()
        : fRecoTask()
    {}

    MQRecoTask(Int_t /*verbose*/)
        : fRecoTask()
    {}

    MQRecoTask(const MQRecoTask&) = delete;
    MQRecoTask operator=(const MQRecoTask&) = delete;

    ~MQRecoTask() override
    {
        if (fRecoTask.fDigiArray) {
            fRecoTask.fDigiArray->Delete();
            delete fRecoTask.fDigiArray;
        }
        if (fRecoTask.fHitArray) {
            fRecoTask.fHitArray->Delete();
            delete fRecoTask.fHitArray;
        }
    }

    InitStatus Init() override
    {
        fRecoTask.SetStreamProcessing(kTRUE);
        fRecoTask.fDigiArray = new TClonesArray("FairTestDetectorDigi");
        fRecoTask.fHitArray = new TClonesArray("FairTestDetectorHit");

        return kSUCCESS;
    }

    void Exec(Option_t* opt = "0") override;

  private:
    FairTestDetectorRecoTask fRecoTask;
};

#endif /* FAIR_TESTDETECTOR_MQRECOTASK_H */
