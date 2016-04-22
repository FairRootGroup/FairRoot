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
void FairTestDetectorFileSink<TIn, TPayloadIn>::Run()
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
            std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
            std::istringstream iss(msgStr);
            TPayloadIn InputArchive(iss);

            try
            {
                InputArchive >> fHitVector;
                // InputArchive >> boost::serialization::make_binary_object(fBigBuffer->data(), sizeof(*fBigBuffer));
            }
            catch (boost::archive::archive_exception& e)
            {
                LOG(ERROR) << e.what();
            }

            // Check if the data is the same as on the sender
            // LOG(WARN) << (*fBigBuffer)[7];

            int numInput = fHitVector.size();
            fOutput->Delete();

            for (int i = 0; i < numInput; ++i)
            {
                new ((*fOutput)[i]) TIn(fHitVector.at(i));
            }

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
            }

            std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
            ackOutChannel.Send(ack);

            fTree->Fill();
        }

        fHitVector.clear();
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}
