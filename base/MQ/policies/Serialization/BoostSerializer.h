/*
* File: BoostSerializer.h
* Author: winckler
*
* Created on October 7, 2014, 8:07 PM
*/

#ifndef BOOSTSERIALIZER_H
#define BOOSTSERIALIZER_H

#include "FairMQLogger.h"
#include "FairMQMessage.h"

#include "TClonesArray.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp> // input: a non-portable native binary archive
#include <boost/archive/binary_oarchive.hpp> // output: a non-portable native binary archive

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <type_traits>

namespace fair
{
namespace base
{
namespace serialization
{

template <typename, typename T>
struct has_BoostSerialization
{
    static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");
};

template <typename C, typename Ret, typename... Args>
struct has_BoostSerialization<C, Ret(Args...)>
{
  private:
    template <typename T>
    static constexpr auto check(T*) // attempt to call it and see if the return type is correct
        -> std::is_same<decltype(std::declval<T>().serialize(std::declval<Args>()...)), Ret>;

    template <typename>
    static constexpr std::false_type check(...);

  public:
    static constexpr bool value = decltype(check<C>(0))::value;
};

} // namespace serialization
} // namespace base
} // namespace fair

template <typename DataType>
class BoostSerializer
{
  public:
    void Serialize(FairMQMessage& msg, DataType* data)
    {
        std::ostringstream buffer;
        boost::archive::binary_oarchive outputArchive(buffer);
        outputArchive << *data;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(FairMQMessage& msg, const DataType& data)
    {
        std::ostringstream buffer;
        boost::archive::binary_oarchive outputArchive(buffer);
        outputArchive << data;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(FairMQMessage& msg, const std::vector<DataType>& dataVec)
    {
        std::ostringstream buffer;
        boost::archive::binary_oarchive outputArchive(buffer);
        outputArchive << dataVec;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(FairMQMessage& msg, TClonesArray* input)
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

    void Serialize(FairMQMessage& msg, std::unique_ptr<TClonesArray> input)
    {
        Serialize(msg, input.get());
    }

    void Deserialize(FairMQMessage& msg, DataType& input)
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

    void Deserialize(FairMQMessage& msg, std::vector<DataType>& input)
    {
        input.clear();
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        boost::archive::binary_iarchive inputArchive(buffer);
        inputArchive >> input;
    }

    void Deserialize(FairMQMessage& msg, TClonesArray* input)
    {
        std::vector<DataType> dataVec;
        Deserialize(msg, dataVec);
        if (input) {
            input->Delete();
            for (unsigned int i = 0; i < dataVec.size(); ++i) {
                new ((*input)[i]) DataType(dataVec.at(i));
            }

            if (input->IsEmpty()) {
                LOG(debug) << "BoostSerializer::Deserialize(FairMQMessage& msg, TClonesArray* input): No Output array!";
            }
        }
    }

    void Deserialize(FairMQMessage& msg, std::unique_ptr<TClonesArray>& input)
    {
        Deserialize(msg, input.get());
    }
};

#endif /* BOOSTSERIALIZER_H */
