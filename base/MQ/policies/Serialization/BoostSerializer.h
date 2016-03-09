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

////// base template class
template <typename DataType, typename BoostArchiveOut=BoostBinArchOut>
class BoostSerializer : public BaseSerializationPolicy<BoostSerializer<DataType,BoostArchiveOut>>
{
  public:
    BoostSerializer() :
        BaseSerializationPolicy<BoostSerializer<DataType,BoostArchiveOut>>(),
        fMessage(nullptr),
        fTransport(nullptr),
        fDataVector()
    {}

    BoostSerializer(const BoostSerializer&) = delete;
    BoostSerializer operator=(const BoostSerializer&) = delete;

    ~BoostSerializer()
    {}
    
    void CloseMessage()
    {
        if (fMessage)
        {
            fMessage->CloseMessage();
        }
    }

    void SetMessage(FairMQMessage* msg)
    {
        fMessage = msg;
    }

    void GetMessage()
    {
        return fMessage;
    }

    void Init()
    {
        // InitContainer();
    }

    /// --------------------------------------------------------
    /// main method to boost serialize
    void DoSerialization()
    {
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        try
        {
            OutputArchive << fDataVector;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }

        int size = buffer.str().length();
        // fMessage = fTransport->CreateMessage(size);
        fMessage->Rebuild(size);
        std::memcpy(fMessage->GetData(), buffer.str().c_str(), size);

        // delete the vector content
        if (fDataVector.size() > 0)
        {
            fDataVector.clear();
        }
    }

    void DoSerialization(const std::vector<DataType>& DataVector)
    {
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        try
        {
            OutputArchive << DataVector;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }

        int size = buffer.str().length();
        // fMessage = fTransport->CreateMessage(size);
        fMessage->Rebuild(size);
        std::memcpy(fMessage->GetData(), buffer.str().c_str(), size);
    }

    /// --------------------------------------------------------
    /// DataType&    -------->  FairMQMessage*
    FairMQMessage* SerializeMsg(DataType& Data)
    {
        //fDataVector.push_back(Data);
        //DoSerialization();
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        try
        {
            OutputArchive << Data;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }

        int size = buffer.str().length();
        // fMessage = fTransport->CreateMessage(size);
        fMessage->Rebuild(size);
        std::memcpy(fMessage->GetData(), buffer.str().c_str(), size);
        return fMessage;
    }

    FairMQMessage* SerializeMsg(DataType* Data)
    {
        std::ostringstream buffer;
        BoostArchiveOut OutputArchive(buffer);
        try
        {
            OutputArchive << *Data;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }

        int size = buffer.str().length();
        // fMessage = fTransport->CreateMessage(size);
        fMessage->Rebuild(size);
        std::memcpy(fMessage->GetData(), buffer.str().c_str(), size);
        return fMessage;
    }
    /// --------------------------------------------------------    
    /// vector<DataType>&    -------->  FairMQMessage*
    FairMQMessage* SerializeMsg(const std::vector<DataType>& DataVector)
    {
        DoSerialization(DataVector);
        return fMessage;
    }
    /// --------------------------------------------------------
    /// TClonesArray*    -------->  FairMQMessage*
    FairMQMessage* SerializeMsg(TClonesArray* clonesArray)
    {
        // convert TClonesArray to vector<DataType>
        for (Int_t i = 0; i < clonesArray->GetEntriesFast(); ++i)
        {
            DataType* data = reinterpret_cast<DataType*>(clonesArray->At(i));
            if (!data)
            {
                continue;
            }
            fDataVector.push_back(*data);
        }
        DoSerialization();
        return fMessage;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Diverse

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& fDataVector;
    }

  protected:
    void SetTransport(FairMQTransportFactory* transport)
    {
        fTransport = transport;
    }

    FairMQMessage*          fMessage;
    FairMQTransportFactory* fTransport;
    std::vector<DataType>   fDataVector;
};

///    ////////////////////////////////////////////////////////////////////////
///    ////////////////////////   deserialize   ///////////////////////////////
///    ////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
using enable_if_match = typename std::enable_if<std::is_same<T,U>::value,int>::type;

template<typename T, typename U>
using enable_ifnot_match = typename std::enable_if<!std::is_same<T,U>::value,int>::type;

template<typename T>
using enable_if_pointer = typename std::enable_if<std::is_pointer<T>::value,int>::type;

template<typename T>
using enable_ifnot_pointer = typename std::enable_if<!std::is_pointer<T>::value,int>::type;

////// base template class
template <typename DataType, typename TContainer = std::vector<DataType>, typename BoostArchiveIn = BoostBinArchIn>
class BoostDeSerializer : public BaseSerializationPolicy<BoostDeSerializer<DataType,TContainer,BoostArchiveIn>>
{
  public:
    BoostDeSerializer() :
        BaseSerializationPolicy<BoostDeSerializer<DataType,TContainer,BoostArchiveIn>>(),
        fMessage(nullptr),
        fTransport(nullptr),
        fDataVector(),
        fDataContainer()
    {
        DefaultContainerInit();
    }

    BoostDeSerializer(const BoostDeSerializer&) = delete;
    BoostDeSerializer operator=(const BoostDeSerializer&) = delete;

    ~BoostDeSerializer()
    {
        DestroyContainer();
    }

    void CloseMessage()
    {
        if (fMessage)
        {
            fMessage->CloseMessage();
        }
    }

    void SetMessage(FairMQMessage* msg)
    {
        fMessage = msg;
    }

    void GetMessage()
    {
        return fMessage;
    }

    void Init()
    {
        // InitContainer();
    }

    /// --------------------------------------------------------
    /// main method to boost deserialize
    void DoDeSerialization(FairMQMessage* msg)
    {
        if (fDataVector.size() > 0)
        {
                fDataVector.clear();
        }
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream buffer(msgStr);
        BoostArchiveIn InputArchive(buffer);
        try
        {
            InputArchive >> fDataVector;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }
    }

    /// --------------------------------------------------------
    /// FairMQMessage*  -------->  std::vector<DataType>& 
    template <typename T = TContainer, enable_if_match<T, std::vector<DataType>> = 0>
    T& DeserializeMsg(FairMQMessage* msg)
    {
        DoDeSerialization(msg);
        return fDataVector;
    }

    /// --------------------------------------------------------
    /// FairMQMessage*  -------->  TClonesArray* 
    template <typename T = TContainer, enable_if_match<T, TClonesArray*> = 0>
    void InitTClonesArray(const std::string &ClassName)
    {
        if (fDataContainer)
        {
            delete fDataContainer;
        }
        fDataContainer = new TClonesArray(ClassName.c_str());
    }

    template <typename T = TContainer, enable_if_match<T, TClonesArray*> = 0>
    T DeserializeMsg(FairMQMessage* msg)
    {
        DoDeSerialization(msg);
        if (fDataContainer)
        {
            fDataContainer->Delete();
            for (unsigned int i = 0; i < fDataVector.size(); ++i)
            {
                new ((*fDataContainer)[i]) DataType(fDataVector.at(i));
            }
            if (fDataContainer->IsEmpty())
            {
                MQLOG(ERROR) << "TClonesArray* BoostSerializer::DeserializeMsg(): No Output array!";
            }
        }
        return fDataContainer;
    }

    /// --------------------------------------------------------
    /// FairMQMessage*  -------->  DataType
    template <typename T = TContainer, enable_if_match<T, DataType> = 0>
    T& DeserializeMsg(FairMQMessage* msg)
    {
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream buffer(msgStr);
        BoostArchiveIn InputArchive(buffer);
        try
        {
            InputArchive >> fDataContainer;
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }
        return fDataContainer;
    }

    /// --------------------------------------------------------
    /// FairMQMessage*  -------->  FairMQMessage* 
    template <typename T = TContainer, enable_if_match<T, FairMQMessage*> = 0>
    T DeserializeMsg(FairMQMessage* msg)
    {
        return msg;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Diverse

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& fDataVector;
    }

    template <typename T = TContainer, enable_if_pointer<T> = 0, typename... Args>
    void InitContainer(Args... args)
    {
        typedef typename std::remove_pointer<T>::type NoptrT;
        fDataContainer = new NoptrT(std::forward<Args>(args)...);
    }


    template <typename T = TContainer, enable_if_pointer<T> = 0>
    void InitContainer(TContainer container)
    {
        fDataContainer = container;
    }

    template <typename T = TContainer, enable_ifnot_pointer<T> = 0>
    void InitContainer()
    {
    }

  protected:
    void SetTransport(FairMQTransportFactory* transport)
    {
        fTransport = transport;
    }

    FairMQMessage*          fMessage;
    FairMQTransportFactory* fTransport;
    std::vector<DataType>   fDataVector;
    TContainer              fDataContainer;

    //////////////////////////////////////////////////////////////////////////
    /// container init/destroy specialization for pointer/not pointer type ///
    //////////////////////////////////////////////////////////////////////////

    template <typename T = TContainer, enable_if_pointer<T> = 0>
    void DefaultContainerInit()
    {
        fDataContainer = nullptr;
    }

    template <typename T = TContainer, enable_ifnot_pointer<T> = 0>
    void DefaultContainerInit()
    {
    }

    template <typename T = TContainer, enable_if_pointer<T> = 0>
    void DestroyContainer()
    {
        if (fDataContainer)
        {
            delete fDataContainer;
        }
    }

    template <typename T = TContainer, enable_ifnot_pointer<T> = 0>
    void DestroyContainer()
    {
    }
};

#endif	/* BOOSTSERIALIZER_H */
