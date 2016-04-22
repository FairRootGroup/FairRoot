/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with pure binary transport data format
template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorPayload::Digi, TestDetectorPayload::Hit>::Exec(Option_t* opt)
{
    int inputSize = fPayload->GetSize();
    // size_t bufferSize = sizeof(*fBigBuffer);
    // size_t digisSize = inputSize - bufferSize;
    // int numEntries = digisSize / sizeof(TestDetectorPayload::Digi);
    int numEntries = inputSize / sizeof(TestDetectorPayload::Digi);

    TestDetectorPayload::Digi* input = static_cast<TestDetectorPayload::Digi*>(fPayload->GetData());

    // memcpy(fBigBuffer->data(), static_cast<unsigned char*>(fPayload->GetData()) + digisSize, bufferSize);

    // Check if the data is the same as on the sender
    // LOG(WARN) << (*fBigBuffer)[7];

    fRecoTask->fDigiArray->Clear();

    for (int i = 0; i < numEntries; ++i)
    {
        new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(input[i].fX, input[i].fY, input[i].fZ, input[i].fTimeStamp);
        static_cast<FairTestDetectorDigi*>(((*fRecoTask->fDigiArray)[i]))->SetTimeStampError(input[i].fTimeStampError);
    }

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    size_t hitsSize = numEntries * sizeof(TestDetectorPayload::Hit);

    // fPayload->Rebuild(hitsSize + bufferSize);
    fPayload->Rebuild(hitsSize);

    // memcpy(static_cast<unsigned char*>(fPayload->GetData()) + hitsSize, fBigBuffer->data(), bufferSize);

    TestDetectorPayload::Hit* output = static_cast<TestDetectorPayload::Hit*>(fPayload->GetData());

    if (inputSize > 0)
    {
        for (int i = 0; i < numEntries; ++i)
        {
            FairTestDetectorHit* hit = static_cast<FairTestDetectorHit*>(fRecoTask->fHitArray->At(i));

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
