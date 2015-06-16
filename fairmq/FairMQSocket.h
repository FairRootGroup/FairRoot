/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSocket.h
 *
 * @since 2012-12-05
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQSOCKET_H_
#define FAIRMQSOCKET_H_

#include <string>

#include "FairMQMessage.h"

class FairMQSocket
{
  public:
    const int SNDMORE;
    const int RCVMORE;
    const int NOBLOCK;

    FairMQSocket(int sndMore, int rcvMore, int noBlock)
        : SNDMORE(sndMore)
        , RCVMORE(rcvMore)
        , NOBLOCK(noBlock)
        {}

    virtual std::string GetId() = 0;

    virtual bool Bind(const std::string& address) = 0;
    virtual void Connect(const std::string& address) = 0;

    virtual int Send(FairMQMessage* msg, const std::string& flag = "") = 0;
    virtual int Send(FairMQMessage* msg, const int flags = 0) = 0;
    virtual int Receive(FairMQMessage* msg, const std::string& flag = "") = 0;
    virtual int Receive(FairMQMessage* msg, const int flags = 0) = 0;

    virtual void* GetSocket() = 0;
    virtual int GetSocket(int nothing) = 0;
    virtual void Close() = 0;
    virtual void Terminate() = 0;

    virtual void SetOption(const std::string& option, const void* value, size_t valueSize) = 0;
    virtual void GetOption(const std::string& option, void* value, size_t* valueSize) = 0;

    virtual unsigned long GetBytesTx() = 0;
    virtual unsigned long GetBytesRx() = 0;
    virtual unsigned long GetMessagesTx() = 0;
    virtual unsigned long GetMessagesRx() = 0;

    virtual ~FairMQSocket() {};
};

#endif /* FAIRMQSOCKET_H_ */
