/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of MQRecoTask::Exec() with Root TMessage transport data format

#ifndef FAIR_TESTDETECTOR_PROCESSORTASK_TMESSAGE_H
#define FAIR_TESTDETECTOR_PROCESSORTASK_TMESSAGE_H

#include "Payload.h"
#include "RootSerializer.h"

template<>
void MQRecoTask<TestDetectorTMessage>::Exec(Option_t* opt)
{
    RootSerializer().Deserialize(*fPayload, fRecoTask.fDigiArray);
    fRecoTask.Exec(opt);
    RootSerializer().Serialize(*fPayload, fRecoTask.fHitArray);
}

#endif   // FAIR_TESTDETECTOR_PROCESSORTASK_TMESSAGE_H
