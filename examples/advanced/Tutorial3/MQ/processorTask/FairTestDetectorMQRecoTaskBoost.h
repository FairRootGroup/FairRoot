/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairTestDetectorMQRecoTask.h
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Boost transport data format

#include "BoostSerializer.h"

// example TIn: FairTestDetectorDigi
// example TOut: FairTestDetectorHit
// example TPayloadIn: boost::archive::binary_iarchive
// example TPayloadOut: boost::archive::binary_oarchive
template<typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
void FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::Exec(Option_t* opt)
{
    BoostSerializer<TIn>().Deserialize(*fPayload, fRecoTask.fDigiArray);

    if (!fRecoTask.fDigiArray) {
        LOG(error) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask.Exec(opt);

    BoostSerializer<TOut>().Serialize(*fPayload, fRecoTask.fHitArray);
}
