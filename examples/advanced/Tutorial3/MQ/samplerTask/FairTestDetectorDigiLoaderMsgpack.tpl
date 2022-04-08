/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * File:   FairTestDetectorDigiLoaderMsgpack.tpl
 * @since 2014-12-12
 * @author: A. Rybalchenko
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Msgpack data format.

#ifdef MSGPACK

#include <msgpack.hpp>

// Types to be used as template parameters.
struct MsgPack
{};
// struct MsgPackRef { msgpack::vrefbuffer vbuf; std::vector<msgpack::type::tuple<int, int, int, double, double>> digis;
// }; struct MsgPackStream {};

template<>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPack>::Exec(Option_t* /*opt*/)
{
    int nDigis = fInput->GetEntriesFast();

    msgpack::sbuffer* sbuf = new msgpack::sbuffer();
    msgpack::packer<msgpack::sbuffer> packer(sbuf);

    std::vector<msgpack::type::tuple<int, int, int, double, double>> digis;

    for (int i = 0; i < nDigis; ++i) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        digis.push_back(
            std::make_tuple(digi->GetX(), digi->GetY(), digi->GetZ(), digi->GetTimeStamp(), digi->GetTimeStampError()));
    }

    packer.pack(digis);

    fPayload = fTransportFactory->CreateMessage(
        sbuf->data(),
        sbuf->size(),
        [](void* /* data */, void* obj) { delete static_cast<msgpack::sbuffer*>(obj); },
        sbuf);
}

// MsgPackRef version sends the vector of tuples without copying it into the sbuffer
// void free_vrefbuffer(void* data, void* object)
// {
//     delete static_cast<MsgPackRef*>(object);
// }

// template <>
// void FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPackRef>::Exec(Option_t* opt)
// {
//     int nDigis = fInput->GetEntriesFast();

//     MsgPackRef* container = new MsgPackRef();

//     for (int i = 0; i < nDigis; ++i)
//     {
//         FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
//         container->digis.push_back(make_tuple(digi->GetX(), digi->GetY(), digi->GetZ(), digi->GetTimeStamp()));
//     }

//     msgpack::pack(container->vbuf, container->digis);

//     fPayload = fTransportFactory->CreateMessage(container->vbuf.vector()->iov_base,
//     container->vbuf.vector()->iov_len, free_vrefbuffer, container);
// }

// MsgPackStream version copies the data values into a stream of tuples.
// template <>
// void FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPackStream>::Exec(Option_t* opt)
// {
//     int nDigis = fInput->GetEntriesFast();

//     msgpack::sbuffer* sbuf = new msgpack::sbuffer();
//     msgpack::packer<msgpack::sbuffer> packer(sbuf);

//     for (int i = 0; i < nDigis; ++i)
//     {
//         FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
//         packer.pack(std::make_tuple(digi->GetX(), digi->GetY(), digi->GetZ(), digi->GetTimeStamp()));
//     }

//     fPayload = fTransportFactory->CreateMessage(sbuf->data(), sbuf->size(), free_sbuffer, sbuf);
// }

#endif /* MSGPACK */
