/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQTransportFactory.h
 *
 * @since 2014-01-20
 * @author: A. Rybalchenko
 */

#ifndef FAIRMQTRANSPORTFACTORY_H_
#define FAIRMQTRANSPORTFACTORY_H_

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "FairMQMessage.h"
#include "FairMQSocket.h"
#include "FairMQPoller.h"
#include "FairMQLogger.h"
#include "FairMQTransports.h"

class FairMQChannel;

class FairMQTransportFactory
{
  public:
    virtual FairMQMessagePtr CreateMessage() const = 0;
    virtual FairMQMessagePtr CreateMessage(const size_t size) const = 0;
    virtual FairMQMessagePtr CreateMessage(void* data, const size_t size, fairmq_free_fn* ffn, void* hint = nullptr) const = 0;

    virtual FairMQSocketPtr CreateSocket(const std::string& type, const std::string& name, const int numIoThreads, const std::string& id = "") const = 0;

    virtual FairMQPollerPtr CreatePoller(const std::vector<FairMQChannel>& channels) const = 0;
    virtual FairMQPollerPtr CreatePoller(const std::unordered_map<std::string, std::vector<FairMQChannel>>& channelsMap, const std::vector<std::string>& channelList) const = 0;
    virtual FairMQPollerPtr CreatePoller(const FairMQSocket& cmdSocket, const FairMQSocket& dataSocket) const = 0;

    virtual FairMQ::Transport GetType() const = 0;

    virtual ~FairMQTransportFactory() {};
};

#endif /* FAIRMQTRANSPORTFACTORY_H_ */
