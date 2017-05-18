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
#include "../options/FairMQProgOptions.h"

#include <nanomsg/nn.h>

using namespace std;

FairMQ::Transport FairMQTransportFactoryNN::fTransportType = FairMQ::Transport::NN;

FairMQTransportFactoryNN::FairMQTransportFactoryNN()
{
    LOG(DEBUG) << "Transport: Using nanomsg library";
}

void FairMQTransportFactoryNN::Initialize(const FairMQProgOptions* config)
{
    // nothing to do for nanomsg, transport is ready to be used any time (until nn_term()).
}

FairMQMessagePtr FairMQTransportFactoryNN::CreateMessage() const
{
    return unique_ptr<FairMQMessage>(new FairMQMessageNN());
}

FairMQMessagePtr FairMQTransportFactoryNN::CreateMessage(const size_t size) const
{
    return unique_ptr<FairMQMessage>(new FairMQMessageNN(size));
}

FairMQMessagePtr FairMQTransportFactoryNN::CreateMessage(void* data, const size_t size, fairmq_free_fn* ffn, void* hint) const
{
    return unique_ptr<FairMQMessage>(new FairMQMessageNN(data, size, ffn, hint));
}

FairMQSocketPtr FairMQTransportFactoryNN::CreateSocket(const string& type, const string& name, const string& id /*= ""*/) const
{
    return unique_ptr<FairMQSocket>(new FairMQSocketNN(type, name, id));
}

FairMQPollerPtr FairMQTransportFactoryNN::CreatePoller(const vector<FairMQChannel>& channels) const
{
    return unique_ptr<FairMQPoller>(new FairMQPollerNN(channels));
}

FairMQPollerPtr FairMQTransportFactoryNN::CreatePoller(const unordered_map<string, vector<FairMQChannel>>& channelsMap, const vector<string>& channelList) const
{
    return unique_ptr<FairMQPoller>(new FairMQPollerNN(channelsMap, channelList));
}

FairMQPollerPtr FairMQTransportFactoryNN::CreatePoller(const FairMQSocket& cmdSocket, const FairMQSocket& dataSocket) const
{
    return unique_ptr<FairMQPoller>(new FairMQPollerNN(cmdSocket, dataSocket));
}

void FairMQTransportFactoryNN::Shutdown()
{
    nn_term();
}

void FairMQTransportFactoryNN::Terminate()
{
    // nothing to do for nanomsg
}

FairMQ::Transport FairMQTransportFactoryNN::GetType() const
{
    return fTransportType;
}

FairMQTransportFactoryNN::~FairMQTransportFactoryNN()
{
    Terminate();
}
