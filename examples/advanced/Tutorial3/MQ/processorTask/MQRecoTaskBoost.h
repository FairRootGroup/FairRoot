/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of MQRecoTask::Exec() with Boost transport data format

#ifndef FAIR_TESTDETECTOR_PROCESSORTASK_BOOST_H
#define FAIR_TESTDETECTOR_PROCESSORTASK_BOOST_H

#include "BoostSerializer.h"
#include "Payload.h"

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

#endif   // FAIR_TESTDETECTOR_PROCESSORTASK_BOOST_H
