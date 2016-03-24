/*
* File: BoostSerializer.h
* Author: winckler
*
* Created on October 7, 2014, 8:07 PM
*/


#ifndef BOOSTSERIALIZER_H
#define	BOOSTSERIALIZER_H

// std
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>

// boost
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

// root
#include "TClonesArray.h"

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "BaseSerializationPolicy.h"
#include "BaseDeserializationPolicy.h"

 #include "MQPolicyDef.h"

// Recall:
// a portable text archive
// boost::archive::text_oarchive // saving
// boost::archive::text_iarchive // loading

// a portable text archive using a wide character stream
// boost::archive::text_woarchive // saving
// boost::archive::text_wiarchive // loading

// a portable XML archive
// boost::archive::xml_oarchive // saving
// boost::archive::xml_iarchive // loading

// a portable XML archive which uses wide characters - use for utf-8 output
// boost::archive::xml_woarchive // saving
// boost::archive::xml_wiarchive // loading

// a non-portable native binary archive
// boost::archive::binary_oarchive // saving
// boost::archive::binary_iarchive // loading

// Remark : boost binary archives are not multiplatform --> use xml or text format for cross-platform use
typedef boost::archive::binary_iarchive         BoostBinArchIn;
typedef boost::archive::binary_oarchive         BoostBinArchOut;

///    ////////////////////////////////////////////////////////////////////////
///    ////////////////////////   serialize   /////////////////////////////////
///    ////////////////////////////////////////////////////////////////////////

template <typename DataType, typename BoostArchiveOut = BoostBinArchOut>
class BoostSerializer
{

public:

    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        // first copy the data to a std::vector
        std::vector<DataType> input_vector;
        for (Int_t i = 0; i < input->GetEntriesFast(); ++i)
        {
            DataType* data = reinterpret_cast<DataType*>(input->At(i));
            if (!data)
            {
                continue;
            }
            input_vector.push_back(*data);
        }
        DoSerialization(msg,input_vector);
    }

    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, const std::vector<DataType>& DataVector)
    {
        DoSerialization(msg,DataVector);
    }


    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, DataType* Data)
    {
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        OutputArchive << *Data;
        int size = buffer.str().length();
        msg->Rebuild(size);
        std::memcpy(msg->GetData(), buffer.str().c_str(), size);
    }

    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, const DataType& Data)
    {
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        OutputArchive << Data;
        int size = buffer.str().length();
        msg->Rebuild(size);
        std::memcpy(msg->GetData(), buffer.str().c_str(), size);
    }



protected:
    void DoSerialization(std::unique_ptr<FairMQMessage>& msg, const std::vector<DataType>& DataVector)
    {
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        OutputArchive << DataVector;
        int size = buffer.str().length();
        msg->Rebuild(size);
        std::memcpy(msg->GetData(), buffer.str().c_str(), size);
    }

};





///    ////////////////////////////////////////////////////////////////////////
///    ////////////////////////   deserialize   ///////////////////////////////
///    ////////////////////////////////////////////////////////////////////////

template <typename DataType, typename BoostArchiveIn = BoostBinArchIn>
class BoostDeSerializer 
{
  public:
    BoostDeSerializer() 
    {
    }

    BoostDeSerializer(const BoostDeSerializer&) = delete;
    BoostDeSerializer operator=(const BoostDeSerializer&) = delete;

    ~BoostDeSerializer()
    {
    }

    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, std::vector<DataType>& input)
    {
        if (input.size() > 0)
        {
                input.clear();
        }
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream buffer(msgStr);
        BoostArchiveIn InputArchive(buffer);
        InputArchive >> input;
    }

    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        std::vector<DataType> input_vector;
        deserialize_impl(msg,input_vector);// deserialize msg into vector
        // fill TClonesArray from vector
        if (input)
        {
            input->Delete();
            for (unsigned int i = 0; i < input_vector.size(); ++i)
            {
                new ((*input)[i]) DataType(input_vector.at(i));
            }
            if (input->IsEmpty())
            {
                LOG(DEBUG) << "BoostDeserializer::deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, TClonesArray* input): No Output array!";
            }
        }
    }

    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, DataType& input)
    {
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream buffer(msgStr);
        BoostArchiveIn InputArchive(buffer);
        try
        {
            InputArchive >> input;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }
    }

};













#endif	/* BOOSTSERIALIZER_H */
