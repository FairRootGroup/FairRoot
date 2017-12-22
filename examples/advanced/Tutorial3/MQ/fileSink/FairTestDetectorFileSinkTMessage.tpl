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
void FairTestDetectorFileSink<FairTestDetectorHit, TMessage>::InitTask()
{
    OnData(fInChannelName, [this](FairMQMessagePtr& msg, int /*index*/)
    {
        ++fReceivedMsgs;

        TestDetectorTMessage tm(msg->GetData(), msg->GetSize());

        fOutput = static_cast<TClonesArray*>(tm.ReadObject(tm.GetClass()));

        if (fOutput->IsEmpty())
        {
            LOG(error) << "FairTestDetectorFileSink::Run(): No Output array!";
        }

        FairMQMessagePtr ack(fTransportFactory->CreateMessage());
        fChannels.at(fAckChannelName).at(0).Send(ack);

        fTree->Fill();

        delete fOutput;
        fOutput = nullptr;

        return true;
    });
}
