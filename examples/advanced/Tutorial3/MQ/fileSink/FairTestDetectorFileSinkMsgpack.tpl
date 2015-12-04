// Implementation of FairTestDetectorFileSink::Run() with Msgpack data format

#ifdef MSGPACK

#include <msgpack.hpp>

struct MsgPack {};
// struct MsgPackRef { msgpack::vrefbuffer* container; void* content; };
// struct MsgPackStream {};

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, MsgPack>::Run()
{
    int receivedMsgs = 0;

    // channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

    while (CheckCurrentState(RUNNING))
    {
        std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

        if (dataInChannel.Receive(msg) > 0)
        {
            receivedMsgs++;

            // deserialize

            std::vector<msgpack::type::tuple<int, double, double, double, double, double, double>> hits;

            msgpack::unpacked unpackedHits;
            // msgpack::unpacked unpackedBigBuffer;

            size_t offset = 0;

            msgpack::unpack(unpackedHits, static_cast<char*>(msg->GetData()), msg->GetSize(), offset);
            // msgpack::unpack(unpackedBigBuffer, static_cast<char*>(msg->GetData()), msg->GetSize(), offset);

            msgpack::object hitsObj = unpackedHits.get();
            // msgpack::object bigBufferObj = unpackedBigBuffer.get();

            hitsObj.convert(&hits);
            // bigBufferObj.convert(fBigBuffer);

            // Check if the data is the same as on the sender
            // LOG(WARN) << (*fBigBuffer)[7];

            int numEntries = hits.size();

            fOutput->Clear();

            for (int i = 0; i < numEntries; ++i)
            {
                TVector3 pos(std::get<1>(hits.at(i)), std::get<2>(hits.at(i)), std::get<3>(hits.at(i)));
                TVector3 dpos(std::get<4>(hits.at(i)), std::get<5>(hits.at(i)), std::get<6>(hits.at(i)));
                new ((*fOutput)[i]) FairTestDetectorHit(std::get<0>(hits.at(i)), 0, pos, dpos);
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

// template <>
// void FairTestDetectorFileSink<FairTestDetectorHit, MsgPackRef>::Run()
// {
//     int receivedMsgs = 0;

//     // channel references to avoid traversing the map on every loop iteration
//     FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

//     while (CheckCurrentState(RUNNING))
//     {
//         std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

//         if (dataInChannel.Receive(msg) > 0)
//         {
//             receivedMsgs++;

//             msgpack::unpacked pmsg;
//             msgpack::unpack(&pmsg, static_cast<char*>(msg->GetData()), msg->GetSize());
//             msgpack::object hitsObj = pmsg.get();

//             std::vector<msgpack::type::tuple<int, double, double, double, double, double, double>> hits;
//             hitsObj.convert(&hits);

//             int numEntries = hits.size();

//             fOutput->Clear();

//             for (int i = 0; i < numEntries; ++i)
//             {
//                 TVector3 pos(std::get<1>(hits.at(i)), std::get<2>(hits.at(i)), std::get<3>(hits.at(i)));
//                 TVector3 dpos(std::get<4>(hits.at(i)), std::get<5>(hits.at(i)), std::get<6>(hits.at(i)));
//                 new ((*fOutput)[i]) FairTestDetectorHit(std::get<0>(hits.at(i)), 0, pos, dpos);
//             }

//             if (fOutput->IsEmpty())
//             {
//                 LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
//             }

//             std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
//             fChannels.at("ack-out").at(0).Send(ack);

//             fTree->Fill();
//         }
//     }

//     LOG(INFO) << "I've received " << receivedMsgs << " messages!";
// }

// template <>
// void FairTestDetectorFileSink<FairTestDetectorHit, MsgPackStream>::Run()
// {
//     int receivedMsgs = 0;

//     // channel references to avoid traversing the map on every loop iteration
//     FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

//     while (CheckCurrentState(RUNNING))
//     {
//         std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

//         if (dataInChannel.Receive(msg) > 0)
//         {
//             receivedMsgs++;

//             fOutput->Clear();

//             msgpack::unpacker pac;

//             pac.reserve_buffer(msg->GetSize());
//             memcpy(pac.buffer(), msg->GetData(), msg->GetSize());
//             pac.buffer_consumed(msg->GetSize());

//             msgpack::unpacked umsg;

//             int numEntries = 0;
//             while (pac.next(&umsg))
//             {
//                 msgpack::object hitObj = umsg.get();
//                 msgpack::type::tuple<int, double, double, double, double, double, double> hit;
//                 hitObj.convert(&hit);
//                 TVector3 pos(std::get<1>(hit), std::get<2>(hit), std::get<3>(hit));
//                 TVector3 dpos(std::get<4>(hit), std::get<5>(hit), std::get<6>(hit));
//                 new ((*fOutput)[numEntries]) FairTestDetectorHit(std::get<0>(hit), 0, pos, dpos);
//                 numEntries++;
//             }

//             if (fOutput->IsEmpty())
//             {
//                 LOG(ERROR) << "FairTestDetectorFileSink::Run(): No Output array!";
//             }

//             std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
//             fChannels.at("ack-out").at(0).Send(ack);

//             fTree->Fill();
//         }
//     }

//     LOG(INFO) << "I've received " << receivedMsgs << " messages!";
// }

#endif /* MSGPACK */
