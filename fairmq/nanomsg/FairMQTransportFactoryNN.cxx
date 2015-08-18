/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQTransportFactoryNN.cxx
 *
 * @since 2014-01-20
 * @author: A. Rybalchenko
 */

#include "FairMQTransportFactoryNN.h"

using namespace std;

FairMQTransportFactoryNN::FairMQTransportFactoryNN()
{
    LOG(INFO) << "Using nanomsg library";
}

FairMQMessage* FairMQTransportFactoryNN::CreateMessage()
{
    return new FairMQMessageNN();
}

FairMQMessage* FairMQTransportFactoryNN::CreateMessage(size_t size)
{
    return new FairMQMessageNN(size);
}

FairMQMessage* FairMQTransportFactoryNN::CreateMessage(void* data, size_t size, fairmq_free_fn *ffn, void* hint)
{
    return new FairMQMessageNN(data, size, ffn, hint);
}

FairMQSocket* FairMQTransportFactoryNN::CreateSocket(const string& type, const std::string& name, int numIoThreads)
{
    return new FairMQSocketNN(type, name, numIoThreads);
}

FairMQPoller* FairMQTransportFactoryNN::CreatePoller(const vector<FairMQChannel>& channels)
{
    return new FairMQPollerNN(channels);
}

FairMQPoller* FairMQTransportFactoryNN::CreatePoller(std::map< std::string,std::vector<FairMQChannel> >& channelsMap, std::initializer_list<std::string> channelList)
{
    return new FairMQPollerNN(channelsMap, channelList);
}

FairMQPoller* FairMQTransportFactoryNN::CreatePoller(FairMQSocket& dataSocket, FairMQSocket& cmdSocket)
{
    return new FairMQPollerNN(dataSocket, cmdSocket);
}
