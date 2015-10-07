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

    int nDigis = fInput->GetEntriesFast();
    int size = nDigis * sizeof(TestDetectorPayload::Digi);

    fOutput = fTransportFactory->CreateMessage(size);
    TestDetectorPayload::Digi* ptr = static_cast<TestDetectorPayload::Digi*>(fOutput->GetData());

    for (Int_t i = 0; i < nDigis; ++i)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }
        new (&ptr[i]) TestDetectorPayload::Digi();
        ptr[i] = TestDetectorPayload::Digi();
        ptr[i].fX = digi->GetX();
        ptr[i].fY = digi->GetY();
        ptr[i].fZ = digi->GetZ();
        ptr[i].fTimeStamp = digi->GetTimeStamp();
    }
}
