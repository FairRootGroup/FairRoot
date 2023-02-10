/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of MQRecoTask::Exec() with Boost transport data format

#include "Payload.h"
#include "BoostSerializer.h"

template<>
void MQRecoTask<TestDetectorBoost>::Exec(Option_t* opt)
{
    BoostSerializer<FairTestDetectorDigi>().Deserialize(*fPayload, fRecoTask.fDigiArray);

    if (!fRecoTask.fDigiArray) {
        LOG(error) << "MQRecoTask::Exec(): No Point array!";
    }

    fRecoTask.Exec(opt);

    BoostSerializer<FairTestDetectorHit>().Serialize(*fPayload, fRecoTask.fHitArray);
}
