/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#include "FairMQDevice.h"
#include "FairMQMessage.h"
#include "RootSerializer.h"

#include <stdexcept>
#include <string>
#include <tuple>
#include <map>

template<typename U, typename T = RootSerializer>
class FairMQUnpacker : public FairMQDevice
{
    typedef U unpacker_type;
    typedef T serialization_type;

  public:
    FairMQUnpacker() : 
        fSubEventChanMap(),
        fUnpacker(nullptr),
        fInputChannelName()
    {
    }
    /// Copy Constructor
    FairMQUnpacker(const FairMQUnpacker&) = delete;
    FairMQUnpacker operator=(const FairMQUnpacker&) = delete;

    virtual ~FairMQUnpacker()
    {
        if (fUnpacker)
        {
            delete fUnpacker;
        }
    }

    void AddSubEvtKey(short type, short subType, short procid, short subCrate, short control, const std::string& channelName)
    {
        if (fSubEventChanMap.size() > 0)
        {
            LOG(ERROR) << "Only one input channel allowed for this device";
        }
        else
        {
             SubEvtKey key(type, subType, procid, subCrate, control);
             fInputChannelName=channelName;

            if (!fSubEventChanMap.count(fInputChannelName))
                fSubEventChanMap[fInputChannelName] = key;
            else
            {
                LOG(WARN)   << "FairMQLmdSampler : subevent header key '(" 
                            << type
                            << "," 
                            << subType
                            << ","
                            << procid
                            << ","
                            << subCrate
                            << ","
                            << control
                            << ")' has already been defined. "
                            << "It will be overwritten with new channel name = "
                            << fInputChannelName;
                            fSubEventChanMap[fInputChannelName] = key;
            }
        }
    }

  protected:
    void InitTask()
    {
        // check if subevt map is configured
        if (fInputChannelName.empty() || fSubEventChanMap.size()==0)
        {
            throw std::runtime_error(std::string("Sub-event map not configured.") );
        }

        // check if given channel exist
        if (!fChannels.count(fInputChannelName))
        {
            throw std::runtime_error(std::string("MQ-channel name '")+fInputChannelName+ "' does not exist. Check the MQ-channel configuration");
        }

        short setype;
        short sesubtype;
        short seprocid;
        short sesubcrate;
        short secontrol;
        std::tie (setype,sesubtype,seprocid,sesubcrate,secontrol) = fSubEventChanMap.at(fInputChannelName);
        fUnpacker = new unpacker_type(setype,sesubtype,seprocid,sesubcrate,secontrol);
        //fUnpacker->Init(); // a priori not needed -> only required for Registering in FairRootManager
    }

    void Run()
    {
        const FairMQChannel& inputChannel = fChannels.at(fInputChannelName).at(0);

        while (CheckCurrentState(RUNNING))
        {

            std::unique_ptr<FairMQMessage> msgSize(fTransportFactory->CreateMessage());
            std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

            if (inputChannel.Receive(msgSize) >= 0)
                if (inputChannel.Receive(msg) >= 0)
                {
                    int dataSize=*(static_cast<int*>(msgSize->GetData()));
                    int* subEvt_ptr = static_cast<int*>(msg->GetData());

                    LOG(TRACE)<<"array size = "<<dataSize;
                    if (dataSize>0)
                        LOG(TRACE)<<"first element in array = "<<*subEvt_ptr;

                    fUnpacker->DoUnpack(subEvt_ptr,dataSize);
                    Serialize<serialization_type>(*msg,fUnpacker->GetOutputData());
                    Send(msg,"data-out");
                    fUnpacker->Reset();
                }
        }
    }

    typedef std::tuple<short,short,short,short,short> SubEvtKey;
    std::map<std::string, SubEvtKey> fSubEventChanMap;

    unpacker_type* fUnpacker;
    std::string fInputChannelName;
};

#endif  /* !FAIRMQUNPACKER_H */
