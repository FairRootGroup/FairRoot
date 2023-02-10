/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of MQRecoTask::Exec() with pure binary transport data format

#include "Payload.h"

template<>
void MQRecoTask<TestDetectorBin>::Exec(Option_t* opt)
{
    int inputSize = fPayload->GetSize();
    int numEntries = inputSize / sizeof(Payload::Digi);

    Payload::Digi* input = static_cast<Payload::Digi*>(fPayload->GetData());

    fRecoTask.fDigiArray->Clear();

    for (int i = 0; i < numEntries; ++i) {
        new ((*fRecoTask.fDigiArray)[i])
            FairTestDetectorDigi(input[i].fX, input[i].fY, input[i].fZ, input[i].fTimeStamp);
        static_cast<FairTestDetectorDigi*>(((*fRecoTask.fDigiArray)[i]))->SetTimeStampError(input[i].fTimeStampError);
    }

    if (!fRecoTask.fDigiArray) {
        LOG(error) << "MQRecoTask::Exec(): No Point array!";
    }

    fRecoTask.Exec(opt);

    size_t hitsSize = numEntries * sizeof(Payload::Hit);

    fPayload->Rebuild(hitsSize);

    Payload::Hit* output = static_cast<Payload::Hit*>(fPayload->GetData());

    if (inputSize > 0) {
        for (int i = 0; i < numEntries; ++i) {
            FairTestDetectorHit* hit = static_cast<FairTestDetectorHit*>(fRecoTask.fHitArray->At(i));

            output[i].detID = hit->GetDetectorID();
            output[i].mcindex = hit->GetRefIndex();
            output[i].posX = hit->GetX();
            output[i].posY = hit->GetY();
            output[i].posZ = hit->GetZ();
            output[i].dposX = hit->GetDx();
            output[i].dposY = hit->GetDy();
            output[i].dposZ = hit->GetDz();
        }
    }
}
