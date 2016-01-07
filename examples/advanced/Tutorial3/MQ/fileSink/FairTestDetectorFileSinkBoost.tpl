/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Boost transport data format

template <typename TIn, typename TPayloadIn>
void FairTestDetectorFileSink<TIn, TPayloadIn>::Run()
{
    if (fHasBoostSerialization)
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
                string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
                istringstream ibuffer(msgStr);
                TPayloadIn InputArchive(ibuffer);

                try
                {
                    InputArchive >> fHitVector;
                }
                catch (boost::archive::archive_exception& e)
                {
                    LOG(ERROR) << e.what();
                }

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

                unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
                ackOutChannel.Send(ack);

                fTree->Fill();
            }

            if (fHitVector.size() > 0)
            {
                fHitVector.clear();
            }
        }

        LOG(INFO) << "I've received " << receivedMsgs << " messages!";
    }
    else
    {
        LOG(ERROR) << " Boost Serialization not ok";
    }
}
