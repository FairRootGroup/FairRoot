/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with pure binary transport data format

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>::InitTask()
{
    OnData(fInChannelName, [this](FairMQMessagePtr& msg, int /*index*/)
    {
        ++fReceivedMsgs;
        fOutput->Delete();

        int numEntries = msg->GetSize() / sizeof(TestDetectorPayload::Hit);

        TestDetectorPayload::Hit* input = static_cast<TestDetectorPayload::Hit*>(msg->GetData());

        for (int i = 0; i < numEntries; ++i)
        {
            TVector3 pos(input[i].posX, input[i].posY, input[i].posZ);
            TVector3 dpos(input[i].dposX, input[i].dposY, input[i].dposZ);
            new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
        }

        if (fOutput->IsEmpty())
        {
            LOG(error) << "FairTestDetectorFileSink::Run(): No Output array!";
        }

        FairMQMessagePtr ack(fTransportFactory->CreateMessage());
        fChannels.at(fAckChannelName).at(0).Send(ack);

        fTree.Fill();

        return true;
    });
}
