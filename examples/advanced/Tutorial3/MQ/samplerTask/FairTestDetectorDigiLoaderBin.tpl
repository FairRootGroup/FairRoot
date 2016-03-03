/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with pure binary transport data format
template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>::Exec(Option_t* opt)
{
    // // Example of how to send multipart messages (uncomment the code lines to test).
    // // 1. create some data and put it into message (optionaly in one step with zero-copy):
    // string test = "hello";
    // fOutput = fTransportFactory->CreateMessage(test.size());
    // memcpy ((void *) fOutput->GetData(), test.c_str(), test.size());
    // // 2. Send the current message as a part:
    // SendPart();
    // // This will schedule the sending to queueing system.
    // // For the next part, create new message object.
    // // The final part will be sent by the sampler.

    // Write some data to check it on the receiver side
    // (*fBigBuffer)[7] = 'c';

    int numEntries = fInput->GetEntriesFast();
    // size_t bufferSize = sizeof(*fBigBuffer);
    size_t digisSize = numEntries * sizeof(TestDetectorPayload::Digi);

    fOutput = fTransportFactory->CreateMessage(digisSize);
    // fOutput = fTransportFactory->CreateMessage(digisSize + bufferSize);

    // memcpy(static_cast<unsigned char*>(fOutput->GetData()) + digisSize, fBigBuffer->data(), bufferSize);

    TestDetectorPayload::Digi* digiPayload = static_cast<TestDetectorPayload::Digi*>(fOutput->GetData());

    for (int i = 0; i < numEntries; ++i)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }
        new (&digiPayload[i]) TestDetectorPayload::Digi();
        digiPayload[i] = TestDetectorPayload::Digi();
        digiPayload[i].fX = digi->GetX();
        digiPayload[i].fY = digi->GetY();
        digiPayload[i].fZ = digi->GetZ();
        digiPayload[i].fTimeStamp = digi->GetTimeStamp();
        digiPayload[i].fTimeStampError = digi->GetTimeStampError();
    }
}
