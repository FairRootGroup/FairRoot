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

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);
    FairMQChannel& ackOutChannel = fChannels.at("ack-out").at(0);

    while (CheckCurrentState(RUNNING))
    {
        unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

        if (dataInChannel.Receive(msg) > 0)
        {
            receivedMsgs++;
            int inputSize = msg->GetSize();
            int numInput = inputSize / sizeof(TestDetectorPayload::Hit);
            TestDetectorPayload::Hit* input = static_cast<TestDetectorPayload::Hit*>(msg->GetData());

            fOutput->Delete();

            for (int i = 0; i < numInput; ++i)
            {
                TVector3 pos(input[i].posX, input[i].posY, input[i].posZ);
                TVector3 dpos(input[i].dposX, input[i].dposY, input[i].dposZ);
                new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
            }

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
            }

            unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
            ackOutChannel.Send(ack);

            fTree->Fill();
        }
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}
