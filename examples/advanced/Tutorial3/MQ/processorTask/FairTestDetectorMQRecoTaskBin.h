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

// Implementation of FairTestDetectorMQRecoTask::Exec() with pure binary transport data format
template<>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                FairTestDetectorHit,
                                TestDetectorPayload::Digi,
                                TestDetectorPayload::Hit>::Exec(Option_t* opt)
{
    int inputSize = fPayload->GetSize();
    int numEntries = inputSize / sizeof(TestDetectorPayload::Digi);

    TestDetectorPayload::Digi* input = static_cast<TestDetectorPayload::Digi*>(fPayload->GetData());

    fRecoTask.fDigiArray->Clear();

    for (int i = 0; i < numEntries; ++i) {
        new ((*fRecoTask.fDigiArray)[i])
            FairTestDetectorDigi(input[i].fX, input[i].fY, input[i].fZ, input[i].fTimeStamp);
        static_cast<FairTestDetectorDigi*>(((*fRecoTask.fDigiArray)[i]))->SetTimeStampError(input[i].fTimeStampError);
    }

    if (!fRecoTask.fDigiArray) {
        LOG(error) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask.Exec(opt);

    size_t hitsSize = numEntries * sizeof(TestDetectorPayload::Hit);

    fPayload->Rebuild(hitsSize);

    TestDetectorPayload::Hit* output = static_cast<TestDetectorPayload::Hit*>(fPayload->GetData());

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
