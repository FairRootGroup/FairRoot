/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Root TMessage transport data format

// special class to expose protected TMessage constructor
class TestDetectorTMessage : public TMessage
{
  public:
    TestDetectorTMessage(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TMessage>::Run()
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

            TestDetectorTMessage tm(msg->GetData(), msg->GetSize());

            fOutput = static_cast<TClonesArray*>(tm.ReadObject(tm.GetClass()));

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
            }

            std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
            ackOutChannel.Send(ack);

            fTree->Fill();

            delete fOutput;
        }
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}
