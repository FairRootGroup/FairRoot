/*
* File: BoostSerializer.h
* Author: winckler
*
* Created on October 7, 2014, 8:07 PM
*/

#ifndef BOOSTSERIALIZER_H
#define BOOSTSERIALIZER_H

// std
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>

// boost
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp> // input: a non-portable native binary archive
#include <boost/archive/binary_oarchive.hpp> // output: a non-portable native binary archive
#include <boost/archive/text_iarchive.hpp> // input: a portable text archive
#include <boost/archive/text_oarchive.hpp> // output: a portable text archive
#include <boost/archive/xml_iarchive.hpp> // input: a portable XML archive
#include <boost/archive/xml_oarchive.hpp> // output: a portable XML archive

// root
#include "TClonesArray.h"

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "BaseSerializationPolicy.h"
#include "BaseDeserializationPolicy.h"

#include "MQPolicyDef.h"

template <typename DataType, typename BoostArchiveOut = boost::archive::binary_oarchive>
class BoostSerializer
{
  public:
    void Serialize(FairMQMessage& msg, TClonesArray* input)
    {
        // first copy the data to a std::vector
        std::vector<DataType> dataVec;
        for (Int_t i = 0; i < input->GetEntriesFast(); ++i)
        {
            DataType* data = reinterpret_cast<DataType*>(input->At(i));
            if (!data)
            {
                continue;
            }
            dataVec.push_back(*data);
        }
        Serialize(msg, dataVec);
    }

    void Serialize(FairMQMessage& msg, const std::vector<DataType>& dataVec)
    {
        std::ostringstream buffer;
        BoostArchiveOut outputArchive(buffer);
        outputArchive << dataVec;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(FairMQMessage& msg, DataType* Data)
    {
        std::ostringstream buffer;
        BoostArchiveOut outputArchive(buffer);
        outputArchive << *Data;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }

    void Serialize(FairMQMessage& msg, const DataType& Data)
    {
        std::ostringstream buffer;
        BoostArchiveOut outputArchive(buffer);
        outputArchive << Data;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }
};

template <typename DataType, typename BoostArchiveIn = boost::archive::binary_iarchive>
class BoostDeserializer
{
  public:
    void Deserialize(FairMQMessage& msg, std::vector<DataType>& input)
    {
        input.clear();
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        BoostArchiveIn inputArchive(buffer);
        inputArchive >> input;
    }

    void Deserialize(FairMQMessage& msg, TClonesArray* input)
    {
        std::vector<DataType> dataVec;
        Deserialize(msg, dataVec);// deserialize msg into vector
        // fill TClonesArray from vector
        if (input)
        {
            input->Delete();
            for (unsigned int i = 0; i < dataVec.size(); ++i)
            {
                new ((*input)[i]) DataType(dataVec.at(i));
            }
            if (input->IsEmpty())
            {
                LOG(DEBUG) << "BoostDeserializer::Deserialize(FairMQMessage& msg, TClonesArray* input): No Output array!";
            }
        }
    }

    void Deserialize(FairMQMessage& msg, DataType& input)
    {
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        BoostArchiveIn inputArchive(buffer);
        try
        {
            inputArchive >> input;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }
    }
};

#endif /* BOOSTSERIALIZER_H */
