/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File: BoostSerializer.h
 * Author: winckler
 *
 * Created on October 7, 2014, 8:07 PM
 */

#ifndef BOOSTSERIALIZER_H
#define BOOSTSERIALIZER_H

#include "FairMQ.h"   // for fair::mq::Message

namespace boost {
namespace serialization {
class access;
}
}   // namespace boost
#include <TClonesArray.h>
#include <boost/archive/binary_iarchive.hpp>   // input: a non-portable native binary archive
#include <boost/archive/binary_oarchive.hpp>   // output: a non-portable native binary archive
#include <boost/serialization/vector.hpp>
#include <fairlogger/Logger.h>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace fair {
namespace base {
namespace serialization {

template<typename, typename T>
struct has_BoostSerialization
{
    static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct has_BoostSerialization<C, Ret(Args...)>
{
  private:
    template<typename T>
    static constexpr auto check(T*)   // attempt to call it and see if the return type is correct
        -> std::is_same<decltype(std::declval<T>().serialize(std::declval<Args>()...)), Ret>;

    template<typename>
    static constexpr std::false_type check(...);

  public:
    static constexpr bool value = decltype(check<C>(0))::value;
};

}   // namespace serialization
}   // namespace base
}   // namespace fair

template<typename DataType>
class BoostSerializer
{
  public:
    void Serialize(fair::mq::Message& msg, DataType* data)
    {
        std::ostringstream buffer;
        boost::archive::binary_oarchive outputArchive(buffer);
        outputArchive << *data;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(fair::mq::Message& msg, const DataType& data)
    {
        std::ostringstream buffer;
        boost::archive::binary_oarchive outputArchive(buffer);
        outputArchive << data;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(fair::mq::Message& msg, const std::vector<DataType>& dataVec)
    {
        std::ostringstream buffer;
        boost::archive::binary_oarchive outputArchive(buffer);
        outputArchive << dataVec;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(fair::mq::Message& msg, TClonesArray* input)
    {
        std::vector<DataType> dataVec;
        for (int i = 0; i < input->GetEntriesFast(); ++i) {
            DataType* data = static_cast<DataType*>(input->At(i));
            if (!data) {
                continue;
            }
            dataVec.push_back(*data);
        }
        Serialize(msg, dataVec);
    }

    void Serialize(fair::mq::Message& msg, std::unique_ptr<TClonesArray> input) { Serialize(msg, input.get()); }

    void Deserialize(fair::mq::Message& msg, DataType& input)
    {
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        boost::archive::binary_iarchive inputArchive(buffer);
        try {
            inputArchive >> input;
        } catch (boost::archive::archive_exception& e) {
            LOG(error) << e.what();
        }
    }

    void Deserialize(fair::mq::Message& msg, std::vector<DataType>& input)
    {
        input.clear();
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        boost::archive::binary_iarchive inputArchive(buffer);
        inputArchive >> input;
    }

    void Deserialize(fair::mq::Message& msg, TClonesArray* input)
    {
        std::vector<DataType> dataVec;
        Deserialize(msg, dataVec);
        if (input) {
            input->Delete();
            for (unsigned int i = 0; i < dataVec.size(); ++i) {
                new ((*input)[i]) DataType(dataVec.at(i));
            }

            if (input->IsEmpty()) {
                LOG(debug)
                    << "BoostSerializer::Deserialize(fair::mq::Message& msg, TClonesArray* input): No Output array!";
            }
        }
    }

    void Deserialize(fair::mq::Message& msg, std::unique_ptr<TClonesArray>& input) { Deserialize(msg, input.get()); }
};

#endif /* BOOSTSERIALIZER_H */
