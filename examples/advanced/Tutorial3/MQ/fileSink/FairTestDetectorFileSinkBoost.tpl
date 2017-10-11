/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Boost transport data format

// example TIn: FairTestDetectorHit
// example TPayloadIn: boost::archive::binary_iarchive, boost::archive::text_iarchive
template <typename TIn, typename TPayloadIn>
void FairTestDetectorFileSink<TIn, TPayloadIn>::InitTask()
{
    OnData(fInChannelName, [this](FairMQMessagePtr& msg, int /*index*/)
    {
        ++fReceivedMsgs;
        fOutput->Delete();
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream iss(msgStr);
        TPayloadIn inputArchive(iss);

        try
        {
            inputArchive >> fHitVector;
        }
        catch (boost::archive::archive_exception& e)
        {
            LOG(ERROR) << e.what();
        }

        int numInput = fHitVector.size();

        for (int i = 0; i < numInput; ++i)
        {
            new ((*fOutput)[i]) TIn(fHitVector.at(i));
        }

        if (fOutput->IsEmpty())
        {
            LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
        }

        FairMQMessagePtr ack(fTransportFactory->CreateMessage());
        fChannels.at(fAckChannelName).at(0).Send(ack);

        fTree->Fill();

        fHitVector.clear();

        return true;
    });
}
