/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Root TMessage transport data format

#include "RootSerializer.h"

template<>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TMessage, TMessage>::Exec(Option_t* opt)
{
    RootSerializer().Deserialize(*fPayload, fRecoTask.fDigiArray);
    fRecoTask.Exec(opt);
    RootSerializer().Serialize(*fPayload, fRecoTask.fHitArray);
}
