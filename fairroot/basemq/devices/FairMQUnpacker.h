/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairMQUnpacker.h
 * Author: winckler
 *
 * Created on October 27, 2015, 2:07 PM
 */

#ifndef FAIRMQUNPACKER_H
#define FAIRMQUNPACKER_H

#include "FairMQ.h"   // for fair::mq::Channel, fair::mq::Device
#include "RootSerializer.h"

#include <map>
#include <stdexcept>
#include <string>
#include <tuple>

template<typename UnpackerType, typename SerializationType = RootSerializer>
class FairMQUnpacker : public fair::mq::Device
{
  public:
    FairMQUnpacker()
        : fSubEventChanMap()
        , fUnpacker(nullptr)
        , fInputChannelName()
        , fType(0)
        , fSubType(0)
        , fProcId(0)
        , fSubCrate(0)
        , fControl(0)
        , fInputChanName()
        , fOutputChanName()
    {}

    FairMQUnpacker(const FairMQUnpacker&) = delete;
    FairMQUnpacker operator=(const FairMQUnpacker&) = delete;

    virtual ~FairMQUnpacker() { delete fUnpacker; }

    void AddSubEvtKey(short type,
                      short subType,
                      short procid,
                      short subCrate,
                      short control,
                      const std::string& channelName)
    {
        if (fSubEventChanMap.size() > 0) {
            LOG(error) << "Only one input channel allowed for this device";
        } else {
            SubEvtKey key(type, subType, procid, subCrate, control);
            fInputChannelName = channelName;

            if (fSubEventChanMap.count(fInputChannelName)) {
                LOG(warn) << "FairMQLmdSampler : subevent header key '(" << type << "," << subType << "," << procid
                          << "," << subCrate << "," << control << ")' has already been defined. "
                          << "It will be overwritten with new channel name = " << fInputChannelName;
            }
            fSubEventChanMap[fInputChannelName] = key;
        }
    }

  protected:
    void InitTask()
    {
        fType = fConfig->GetValue<short>("lmd-type");
        fSubType = fConfig->GetValue<short>("lmd-sub-type");
        fProcId = fConfig->GetValue<short>("lmd-proc-id");
        fSubCrate = fConfig->GetValue<short>("lmd-sub-crate");
        fControl = fConfig->GetValue<short>("lmd-control");
        fInputChanName = fConfig->GetValue<std::string>("lmd-chan-name");
        fOutputChanName = fConfig->GetValue<std::string>("out-chan-name");

        // combination of sub-event header value = one special channel
        // this channel MUST be defined in the json file for the MQ configuration
        AddSubEvtKey(fType, fSubType, fProcId, fSubCrate, fControl, fInputChanName);

        // check if subevt map is configured
        if (fInputChannelName.empty() || fSubEventChanMap.size() == 0) {
            throw std::runtime_error(std::string("Sub-event map not configured."));
        }

        // check if given channel exist
        try {
            GetChannel(fInputChannelName);
        } catch (const std::out_of_range&) {
            throw std::runtime_error(std::string("MQ-channel name '") + fInputChannelName
                                     + "' does not exist. Check the MQ-channel configuration");
        }

        short setype;
        short sesubtype;
        short seprocid;
        short sesubcrate;
        short secontrol;
        std::tie(setype, sesubtype, seprocid, sesubcrate, secontrol) = fSubEventChanMap.at(fInputChannelName);
        fUnpacker = new UnpackerType(setype, sesubtype, seprocid, sesubcrate, secontrol);
        // fUnpacker->Init(); // a priori not needed -> only required for Registering in FairRootManager
    }

    void Run()
    {
        auto& inputChannel = GetChannel(fInputChannelName);

        while (!NewStatePending()) {
            auto msgSize(NewMessage());
            auto msg(NewMessage());

            if (inputChannel.Receive(msgSize) >= 0) {
                if (inputChannel.Receive(msg) >= 0) {
                    int dataSize = *(static_cast<int*>(msgSize->GetData()));
                    int* subEvtPtr = static_cast<int*>(msg->GetData());

                    // LOG(debug) << "array size = " << dataSize;
                    // if (dataSize > 0)
                    // {
                    //     LOG(debug) << "first element in array = " << *subEvtPtr;
                    // }

                    fUnpacker->DoUnpack(subEvtPtr, dataSize);
                    SerializationType().Serialize(*msg, fUnpacker->GetOutputData());
                    Send(msg, fOutputChanName);
                    fUnpacker->Reset();
                }
            }
        }
    }

    typedef std::tuple<short, short, short, short, short> SubEvtKey;
    std::map<std::string, SubEvtKey> fSubEventChanMap;

    UnpackerType* fUnpacker;
    std::string fInputChannelName;

    short fType;
    short fSubType;
    short fProcId;
    short fSubCrate;
    short fControl;
    std::string fInputChanName;
    std::string fOutputChanName;
};

#endif /* !FAIRMQUNPACKER_H */
