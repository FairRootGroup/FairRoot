/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * File:   FairTestDetectorMQRecoTaskMsgpack.tpl
 * @since 2014-12-12
 * @author: A. Rybalchenko
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Msgpack data format

#ifdef MSGPACK

#include <msgpack.hpp>

// Types to be used as template parameters.
struct MsgPack
{};
// struct MsgPackRef { msgpack::vrefbuffer vbuf; std::vector<msgpack::type::tuple<int, int, double, double, double,
// double, double, double>> hits; }; struct MsgPackStream {};

template<>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPack, MsgPack>::Exec(Option_t* opt)
{
    // deserialize

    std::vector<msgpack::type::tuple<int, int, int, double, double>> digis;

    msgpack::unpacked unpackedDigis;

    size_t offset = 0;

    msgpack::unpack(unpackedDigis, static_cast<char*>(fPayload->GetData()), fPayload->GetSize(), offset);

    msgpack::object digisObj = unpackedDigis.get();

    digisObj.convert(digis);

    int numEntries = digis.size();

    fRecoTask.fDigiArray->Clear();

    for (int i = 0; i < numEntries; ++i) {
        new ((*fRecoTask.fDigiArray)[i]) FairTestDetectorDigi(
            std::get<0>(digis.at(i)), std::get<1>(digis.at(i)), std::get<2>(digis.at(i)), std::get<3>(digis.at(i)));
        static_cast<FairTestDetectorDigi*>(((*fRecoTask.fDigiArray)[i]))->SetTimeStampError(std::get<4>(digis.at(i)));
    }

    if (!fRecoTask.fDigiArray) {
        LOG(error) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    // execute task on the deserialized data (digis)

    fRecoTask.Exec(opt);

    // serialize the task results (hits)

    msgpack::sbuffer* sbuf = new msgpack::sbuffer();
    msgpack::packer<msgpack::sbuffer> packer(sbuf);

    std::vector<msgpack::type::tuple<int, int, double, double, double, double, double, double>> hits;

    for (int i = 0; i < numEntries; ++i) {
        FairTestDetectorHit* hit = static_cast<FairTestDetectorHit*>(fRecoTask.fHitArray->At(i));
        hits.push_back(std::make_tuple(hit->GetDetectorID(),
                                       hit->GetRefIndex(),
                                       hit->GetX(),
                                       hit->GetY(),
                                       hit->GetZ(),
                                       hit->GetDx(),
                                       hit->GetDy(),
                                       hit->GetDz()));
    }

    packer.pack(hits);

    fPayload->Rebuild(
        sbuf->data(),
        sbuf->size(),
        [](void* /* data */, void* obj) { delete static_cast<msgpack::sbuffer*>(obj); },
        sbuf);
}

// MsgPackRef version sends the vector of tuples without copying it into the sbuffer
// void free_vrefbuffer(void *data, void *hint)
// {
//     delete static_cast<MsgPackRef*>(hint);
// }

// template <>
// void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPackRef, MsgPackRef>::Exec(Option_t*
// opt)
// {
//     msgpack::unpacked msg;
//     msgpack::unpack(&msg, static_cast<char*>(fPayload->GetData()), fPayload->GetSize());
//     msgpack::object digisObj = msg.get();

//     std::vector<msgpack::type::tuple<int, int, int, double, double>> digis;
//     digisObj.convert(&digis);

//     int numEntries = digis.size();

//     fRecoTask.fDigiArray->Clear();

//     for (int i = 0; i < numEntries; ++i)
//     {
//         new ((*fRecoTask.fDigiArray)[i]) FairTestDetectorDigi(std::get<0>(digis.at(i)), std::get<1>(digis.at(i)),
//         std::get<2>(digis.at(i)), std::get<3>(digis.at(i)));
//     }

//     if (!fRecoTask.fDigiArray)
//     {
//         LOG(error) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
//     }

//     fRecoTask.Exec(opt);

//     MsgPackRef* container = new MsgPackRef();

//     for (int i = 0; i < numEntries; ++i)
//     {
//         FairTestDetectorHit* hit = static_cast<FairTestDetectorHit*>(fRecoTask.fHitArray->At(i));
//         container->hits.push_back(std::make_tuple(hit->GetDetectorID(), hit->GetX(), hit->GetY(), hit->GetZ(),
//         hit->GetDx(), hit->GetDy(), hit->GetDz()));
//     }

//     msgpack::pack(container->vbuf, container->hits);

//     fPayload->Rebuild(container->vbuf.vector()->iov_base, container->vbuf.vector()->iov_len, free_vrefbuffer,
//     container);
// }

// template <>
// void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPackStream,
// MsgPackStream>::Exec(Option_t* opt)
// {
//     fRecoTask.fDigiArray->Clear();

//     msgpack::unpacker pac;

//     pac.reserve_buffer(fPayload->GetSize());
//     memcpy(pac.buffer(), fPayload->GetData(), fPayload->GetSize());
//     pac.buffer_consumed(fPayload->GetSize());

//     msgpack::unpacked msg;

//     int numEntries = 0;
//     while (pac.next(&msg))
//     {
//         msgpack::object digiObj = msg.get();
//         msgpack::type::tuple<int, int, int, double, double> digi;
//         digiObj.convert(&digi);
//         new ((*fRecoTask.fDigiArray)[numEntries]) FairTestDetectorDigi(std::get<0>(digi), std::get<1>(digi),
//         std::get<2>(digi), std::get<3>(digi)); numEntries++;
//     }

//     if (!fRecoTask.fDigiArray)
//     {
//         LOG(error) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
//     }

//     fRecoTask.Exec(opt);

//     msgpack::sbuffer* sbuf = new msgpack::sbuffer();
//     msgpack::packer<msgpack::sbuffer> packer(sbuf);

//     for (int i = 0; i < numEntries; ++i)
//     {
//         FairTestDetectorHit* hit = static_cast<FairTestDetectorHit*>(fRecoTask.fHitArray->At(i));
//         packer.pack(std::make_tuple(hit->GetDetectorID(), hit->GetX(), hit->GetY(), hit->GetZ(), hit->GetDx(),
//         hit->GetDy(), hit->GetDz()));
//     }

//     fPayload->Rebuild(sbuf->data(), sbuf->size(), free_sbuffer, sbuf);
// }

#endif /* MSGPACK */
