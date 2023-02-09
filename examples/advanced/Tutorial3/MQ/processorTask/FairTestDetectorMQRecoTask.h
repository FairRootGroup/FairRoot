/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include "FairMQProcessorTask.h"
#include "FairRootManager.h"
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"
#include "FairTestDetectorRecoTask.h"

#include <TClonesArray.h>
#include <fairlogger/Logger.h>

template<typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    FairTestDetectorMQRecoTask()
        : fRecoTask()
    {}

    FairTestDetectorMQRecoTask(Int_t /*verbose*/)
        : fRecoTask()
    {}

    FairTestDetectorMQRecoTask(const FairTestDetectorMQRecoTask&) = delete;
    FairTestDetectorMQRecoTask operator=(const FairTestDetectorMQRecoTask&) = delete;

    ~FairTestDetectorMQRecoTask() override
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

#endif /* FAIRTESTDETECTORMQRECOTASK_H */
