// Implementation of FairTestDetectorFileSink::Run() with Google FlatBuffers transport data format

#ifdef FLATBUFFERS

#include "flatbuffers/flatbuffers.h"
#include "FairTestDetectorPayloadHit_generated.h"

using namespace TestDetectorFlat;

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorFlat::HitPayload>::InitTask()
{
    OnData(fInChannelName, [this](FairMQMessagePtr& msg, int /*index*/)
    {
        ++fReceivedMsgs;
        fOutput->Delete();

        auto hitPayload = GetHitPayload(msg->GetData());
        auto hits = hitPayload->hits();

        // int numEntries = hits->size();

        for (auto it = hits->begin(); it != hits->end(); ++it)
        {
            TVector3 pos((*it)->x(), (*it)->y(), (*it)->z());
            TVector3 dpos((*it)->dx(), (*it)->dy(), (*it)->dz());
            new ((*fOutput)[it - hits->begin()]) FairTestDetectorHit((*it)->detID(), (*it)->mcIndex(), pos, dpos);
            // LOG(warn) << " " << (*it)->detID() << " " << (*it)->x() << " " << (*it)->y() << " " << (*it)->z() << " " << (*it)->dx() << " " << (*it)->dy() << " " << (*it)->dz();
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

#endif /* FLATBUFFERS */
