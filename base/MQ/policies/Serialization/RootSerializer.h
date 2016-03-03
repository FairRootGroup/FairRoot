/* 
 * File:   RootSerializer.h
 * Author: winckler
 *
 * Created on January 14, 2015, 3:44 PM
 */

#ifndef ROOTBASECLASSSERIALIZER_H
#define ROOTBASECLASSSERIALIZER_H

//std
#include <iostream>
#include <type_traits>

//Root
#include "TClonesArray.h"
#include "TMessage.h"
//FairRoot
#include "FairMQMessage.h"


template<typename T, typename U>
using enable_if_match = typename std::enable_if<std::is_same<T,U>::value,int>::type;


// special class to expose protected TMessage constructor
class FairTMessage : public TMessage
{
  public:
    FairTMessage(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

// helper function to clean up the object holding the data after it is transported.
void free_tmessage(void *data, void *hint)
{
    delete (TMessage*)hint;
}

template <typename T>
class base_RootSerializer
{
  public:
    typedef T container_type;
    base_RootSerializer()
        : fMessage(nullptr)
    {}

    base_RootSerializer(const base_RootSerializer&) = delete;
    base_RootSerializer operator=(const base_RootSerializer&) = delete;

    virtual ~base_RootSerializer()
    {
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    // serialize

    void DoSerialization(container_type* array)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(array);
        fMessage->Rebuild(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
    }

    FairMQMessage* SerializeMsg(container_type* array)
    {
        DoSerialization(array);
        return fMessage;
    }

    void SetMessage(FairMQMessage* msg)
    {
        fMessage=msg;
    }

    FairMQMessage* GetMessage()
    {
        return fMessage;
    }

  protected:
    FairMQMessage* fMessage;
};


// hack while waiting for refactoring
struct has_ownership{};
struct has_no_ownership{};

template<typename T, typename U=has_ownership>
class base_RootDeSerializer
{
  public:
    typedef T container_type;

    base_RootDeSerializer()
        : fContainer(nullptr)
        , fMessage(nullptr)
    {}

    base_RootDeSerializer(const base_RootDeSerializer&) = delete;
    base_RootDeSerializer operator=(const base_RootDeSerializer&) = delete;

    virtual ~base_RootDeSerializer()
    {
        destructor();
    }

    template <typename V = U, enable_if_match<V, has_ownership> = 0>
    void destructor()
    {
        if(fContainer)
            delete fContainer;
        fContainer=nullptr;
    }

    template <typename V = U, enable_if_match<V, has_no_ownership> = 0>
    void destructor()
    {
    }


    // todo: propagate the changes -> using the variadic template method below in tutorial7
    template <typename V = T, enable_if_match<V, TClonesArray> = 0>
    void InitContainer(const std::string &ClassName)
    {
        fContainer = new container_type(ClassName.c_str());
    }

    template <typename... Args>
    void InitContainer(Args... args)
    {
        fContainer = new container_type(std::forward<Args>(args)...);
    }

    void InitContainer(container_type* container)
    {
        fContainer = container;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    // deserialize

    void DoDeSerialization(FairMQMessage* msg)
    {
        FairTMessage tm(msg->GetData(), msg->GetSize());
        fContainer  = (container_type*)(tm.ReadObject(tm.GetClass()));
    }

    container_type* DeserializeMsg(FairMQMessage* msg)
    {
        DoDeSerialization(msg);
        return fContainer;
    }

    void SetMessage(FairMQMessage* msg)
    {
        fMessage=msg;
    }

    FairMQMessage* GetMessage()
    {
        return fMessage;
    }

  protected:
    container_type* fContainer;
    FairMQMessage* fMessage;
};

typedef base_RootDeSerializer<TClonesArray,has_ownership> RootDeSerializer;
typedef base_RootSerializer<TClonesArray> RootSerializer;

#endif /* ROOTBASECLASSSERIALIZER_H */
