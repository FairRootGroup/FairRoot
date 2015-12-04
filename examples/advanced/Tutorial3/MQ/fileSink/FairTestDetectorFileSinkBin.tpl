/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with pure binary transport data format

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>::Run()
{
    int receivedMsgs = 0;

    // channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);
    FairMQChannel& ackOutChannel = fChannels.at("ack-out").at(0);

    while (CheckCurrentState(RUNNING))
    {
        std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

        if (dataInChannel.Receive(msg) > 0)
        {
            receivedMsgs++;
            int inputSize = msg->GetSize();
            // size_t bufferSize = sizeof(*fBigBuffer);
            // size_t hitsSize = inputSize - bufferSize;
            // int numEntries = hitsSize / sizeof(TestDetectorPayload::Hit);
            int numEntries = inputSize / sizeof(TestDetectorPayload::Hit);

            TestDetectorPayload::Hit* input = static_cast<TestDetectorPayload::Hit*>(msg->GetData());

            // memcpy(fBigBuffer->data(), static_cast<unsigned char*>(msg->GetData()) + hitsSize, bufferSize);

            // Check if the data is the same as on the sender
            // LOG(WARN) << (*fBigBuffer)[7];

            fOutput->Delete();

            for (int i = 0; i < numEntries; ++i)
            {
                TVector3 pos(input[i].posX, input[i].posY, input[i].posZ);
                TVector3 dpos(input[i].dposX, input[i].dposY, input[i].dposZ);
                new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
            }

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
            }

            std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
            ackOutChannel.Send(ack);

            fTree->Fill();
        }
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}
