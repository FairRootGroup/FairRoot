/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Google Protocol Buffers transport data format

#ifdef PROTOBUF
#include "FairTestDetectorPayload.pb.h"

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorProto::HitPayload>::Run()
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
            fOutput->Delete();

            TestDetectorProto::HitPayload hp;
            hp.ParseFromArray(msg->GetData(), msg->GetSize());

            int numEntries = hp.hit_size();

            // memcpy(fBigBuffer->data(), hp.bigbuffer().c_str(), sizeof(*fBigBuffer));

            // Check if the data is the same as on the sender
            // LOG(WARN) << (*fBigBuffer)[7];

            for (int i = 0; i < numEntries; ++i)
            {
                const TestDetectorProto::Hit& hit = hp.hit(i);
                TVector3 pos(hit.posx(), hit.posy(), hit.posz());
                TVector3 dpos(hit.dposx(), hit.dposy(), hit.dposz());
                new ((*fOutput)[i]) FairTestDetectorHit(hit.detid(), hit.mcindex(), pos, dpos);
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

#endif /* PROTOBUF */
