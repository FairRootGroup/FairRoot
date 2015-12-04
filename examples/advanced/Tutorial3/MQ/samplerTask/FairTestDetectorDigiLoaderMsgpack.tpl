/**
 * File:   FairTestDetectorDigiLoaderMsgpack.tpl
 * @since 2014-12-12
 * @author: A. Rybalchenko
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Msgpack data format.

#ifdef MSGPACK

#include <msgpack.hpp>

// Types to be used as template parameters.
struct MsgPack {};
// struct MsgPackRef { msgpack::vrefbuffer vbuf; std::vector<msgpack::type::tuple<int, int, int, double>> digis; };
// struct MsgPackStream {};

void free_sbuffer(void *data, void *hint)
{
    delete static_cast<msgpack::sbuffer*>(hint);
}

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPack>::Exec(Option_t* opt)
{
    int nDigis = fInput->GetEntriesFast();

    msgpack::sbuffer* sbuf = new msgpack::sbuffer();
    msgpack::packer<msgpack::sbuffer> packer(sbuf);

    std::vector<msgpack::type::tuple<int, int, int, double>> digis;

    for (int i = 0; i < nDigis; ++i)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        digis.push_back(std::make_tuple(digi->GetX(), digi->GetY(), digi->GetZ(), digi->GetTimeStamp()));
    }

    // Write some data to check it on the receiver side
    // (*fBigBuffer)[7] = 'c';

    packer.pack(digis);
    // packer.pack_bin(sizeof(*fBigBuffer));
    // packer.pack_bin_body(reinterpret_cast<char *>(fBigBuffer->data()), sizeof(*fBigBuffer));

    fOutput = fTransportFactory->CreateMessage(sbuf->data(), sbuf->size(), free_sbuffer, sbuf);
}

// MsgPackRef version sends the vector of tuples without copying it into the sbuffer
// void free_vrefbuffer(void *data, void *hint)
// {
//     delete static_cast<MsgPackRef*>(hint);
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

//     fOutput = fTransportFactory->CreateMessage(container->vbuf.vector()->iov_base, container->vbuf.vector()->iov_len, free_vrefbuffer, container);
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

//     fOutput = fTransportFactory->CreateMessage(sbuf->data(), sbuf->size(), free_sbuffer, sbuf);
// }

#endif /* MSGPACK */
