/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   BinaryBaseClassSerializer.h
 * Author: winckler
 *
 * Created on October 10, 2014, 5:22 PM
 */

#ifndef BINARYBASECLASSSERIALIZER_H
#define BINARYBASECLASSSERIALIZER_H

#include <FairMQMessage.h>

template<typename TPayload>
class BinaryBaseClassSerializer
{
  public:
    BinaryBaseClassSerializer()
        : fPayload(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)
    {}

    BinaryBaseClassSerializer(const BinaryBaseClassSerializer&) = delete;
    BinaryBaseClassSerializer operator=(const BinaryBaseClassSerializer&) = delete;

    virtual ~BinaryBaseClassSerializer() {}

    void GetPayload(FairMQMessage* msg)
    {
        int inputSize = msg->GetSize();
        if (inputSize > 0) {
            fNumInput = inputSize / sizeof(TPayload);
        }
        fPayload = static_cast<TPayload*>(msg->GetData());
    }

    void SetMessage(FairMQMessage* msg) { fMessage = msg; }

    FairMQMessage* GetMessage() { return fMessage; }

  protected:
    TPayload* fPayload;
    FairMQMessage* fMessage;
    int fNumInput;
};

#endif /* BINARYBASECLASSSERIALIZER_H */
