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

extern "C"
{
#include "f_evt.h"
#include "s_filhe_swap.h"
#include "s_bufhe_swap.h"
}

#include "FairMQDevice.h"
#include "FairMQMessage.h"

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "RootSerializer.h"


template<typename U, typename T=RootSerializer>
class FairMQUnpacker : public FairMQDevice, public T
{
	typedef U unpacker_type;
	typedef T serialization_type;

public:

	FairMQUnpacker() : serialization_type(),
		fSubEventChanMap(), 
		fUnpacker(nullptr), 
		fInputChannelName()
	{

	}
	virtual ~FairMQUnpacker()
	{}

 	void AddSubEvtKey(short type, short subType, short procid, short subCrate, short control, const std::string& channelName)
 	{
 		if(fSubEventChanMap.size()>0)
 		{
 			LOG(ERROR)<<"Only one input channel allowed for this device";
 		}
 		else
 		{
	 		SubEvtKey key(type, subType, procid, subCrate, control);
	 		fInputChannelName=channelName;

			if(!fSubEventChanMap.count(fInputChannelName))
				fSubEventChanMap[fInputChannelName] = key;
			else
			{
				LOG(WARN) 	<< "FairMQLmdSampler : subevent header key '(" 
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
		if(fInputChannelName.empty() || fSubEventChanMap.size()==0)
		{
			LOG(ERROR)<<"Sub-event map not configured.";
			// TODO : throw something
		}


		// check if given channel exist
		if(!fChannels.count(fInputChannelName))
		{
			LOG(ERROR)<<"MQ-channel name '"<< fInputChannelName <<"' does not exist. Check the MQ-channel configuration";
			// TODO : throw something
		}

		short setype;
		short sesubtype;
		short seprocid;
		short sesubcrate;
		short secontrol;
		std::tie (setype,sesubtype,seprocid,sesubcrate,secontrol) = fSubEventChanMap.at(fInputChannelName);
		fUnpacker = new unpacker_type(setype,sesubtype,seprocid,sesubcrate,secontrol);
		fUnpacker->Init();

	}

	void Run()
	{

		const FairMQChannel& inputChannel = fChannels.at(fInputChannelName).at(0);
        const FairMQChannel& outputChannel = fChannels.at("data-out").at(0);

		while (CheckCurrentState(RUNNING))
		{

			std::unique_ptr<FairMQMessage> msgSize(fTransportFactory->CreateMessage());
			std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());

			if(inputChannel.Receive(msgSize)>=0)
				if(inputChannel.Receive(msg)>=0)
				{
					int dataSize=*(static_cast<int*>(msgSize->GetData()));
					int* subEvt_ptr = static_cast<int*>(msg->GetData());

					LOG(TRACE)<<"array size = "<<dataSize;
					LOG(TRACE)<<"fxEventData = "<<*subEvt_ptr;
					
					fUnpacker->DoUnpack(subEvt_ptr,dataSize);

					serialization_type::SetMessage(msg.get());
					outputChannel.Send(serialization_type::SerializeMsg(fUnpacker->GetOutputData()));
					fUnpacker->Reset();
				}
		}
	}


 	////////////////////// data members

	typedef std::tuple<short,short,short,short,short> SubEvtKey;
	std::map<std::string, SubEvtKey> fSubEventChanMap;

	unpacker_type* fUnpacker;
	std::string fInputChannelName;

};

#endif  /* !FAIRMQUNPACKER_H */

