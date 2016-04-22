// Implementation of FairTestDetectorFileSink::Run() with Google FlatBuffers transport data format

#ifdef FLATBUFFERS

#include "flatbuffers/flatbuffers.h"
#include "FairTestDetectorPayloadHit_generated.h"

using namespace TestDetectorFlat;

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorFlat::HitPayload>::Run()
{
    int receivedMsgs = 0;

    // channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

    while (CheckCurrentState(RUNNING))
    {
        std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

        if (dataInChannel.Receive(msg) > 0)
        {
            ++receivedMsgs;
            fOutput->Delete();

            auto hitPayload = GetHitPayload(msg->GetData());
            auto hits = hitPayload->hits();
            // auto rbigBuffer = hitPayload->bigBuffer();
            // memcpy(fBigBuffer->data(), rbigBuffer->Data(), sizeof(*fBigBuffer));

            // Check if the data is the same as on the sender
            // LOG(WARN) << (*fBigBuffer)[7];

            int numEntries = hits->size();

            for (auto it = hits->begin(); it != hits->end(); ++it)
            {
                TVector3 pos((*it)->x(), (*it)->y(), (*it)->z());
                TVector3 dpos((*it)->dx(), (*it)->dy(), (*it)->dz());
                new ((*fOutput)[it - hits->begin()]) FairTestDetectorHit((*it)->detID(), (*it)->mcIndex(), pos, dpos);
                // LOG(WARN) << " " << (*it)->detID() << " " << (*it)->x() << " " << (*it)->y() << " " << (*it)->z() << " " << (*it)->dx() << " " << (*it)->dy() << " " << (*it)->dz();
            }

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
            }

            std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
            fChannels.at("ack-out").at(0).Send(ack);

            fTree->Fill();
        }
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}

#endif /* FLATBUFFERS */
