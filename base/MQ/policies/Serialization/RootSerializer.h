/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   RootSerializer.h
 * Author: winckler
 *
 * Created on January 14, 2015, 3:44 PM
 */

#ifndef ROOTSERIALIZER_H
#define ROOTSERIALIZER_H

#include "FairMQ.h"   // for fair::mq::Message

#include <TClonesArray.h>
#include <TMessage.h>
#include <memory>

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

struct RootSerializer
{
    RootSerializer() = default;
    virtual ~RootSerializer() = default;

    template<typename T>
    void Serialize(fair::mq::Message& msg, T* input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input);
        msg.Rebuild(
            tm->Buffer(), tm->BufferSize(), [](void*, void* tmsg) { delete static_cast<TMessage*>(tmsg); }, tm);
    }

    template<typename T>
    void Serialize(fair::mq::Message& msg, const std::unique_ptr<T>& input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input.get());
        msg.Rebuild(
            tm->Buffer(), tm->BufferSize(), [](void*, void* tmsg) { delete static_cast<TMessage*>(tmsg); }, tm);
    }

    template<typename T>
    void Deserialize(fair::mq::Message& msg, T*& output)
    {
        delete output;
        FairTMessage tm(msg.GetData(), msg.GetSize());
        output = static_cast<T*>(tm.ReadObjectAny(tm.GetClass()));
    }

    template<typename T>
    void Deserialize(fair::mq::Message& msg, std::unique_ptr<T>& output)
    {
        FairTMessage tm(msg.GetData(), msg.GetSize());
        output.reset(static_cast<T*>(tm.ReadObjectAny(tm.GetClass())));
    }
};

#endif /* ROOTSERIALIZER_H */
