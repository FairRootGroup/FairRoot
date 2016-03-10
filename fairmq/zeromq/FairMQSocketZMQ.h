/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSocketZMQ.h
 *
 * @since 2012-12-05
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQSOCKETZMQ_H_
#define FAIRMQSOCKETZMQ_H_

#include <boost/shared_ptr.hpp>

#include "FairMQSocket.h"
#include "FairMQContextZMQ.h"

class FairMQSocketZMQ : public FairMQSocket
{
  public:
    FairMQSocketZMQ(const std::string& type, const std::string& name, const int numIoThreads, const std::string& id = "");
    FairMQSocketZMQ(const FairMQSocketZMQ&) = delete;
    FairMQSocketZMQ operator=(const FairMQSocketZMQ&) = delete;

    virtual std::string GetId();

    virtual bool Bind(const std::string& address);
    virtual void Connect(const std::string& address);

    virtual int Send(FairMQMessage* msg, const std::string& flag = "");
    virtual int Send(FairMQMessage* msg, const int flags = 0);
    virtual int Receive(FairMQMessage* msg, const std::string& flag = "");
    virtual int Receive(FairMQMessage* msg, const int flags = 0);

    virtual void* GetSocket() const;
    virtual int GetSocket(int nothing) const;
    virtual void Close();
    virtual void Terminate();

    virtual void SetOption(const std::string& option, const void* value, size_t valueSize);
    virtual void GetOption(const std::string& option, void* value, size_t* valueSize);

    virtual unsigned long GetBytesTx() const;
    virtual unsigned long GetBytesRx() const;
    virtual unsigned long GetMessagesTx() const;
    virtual unsigned long GetMessagesRx() const;

    virtual bool SetSendTimeout(const int timeout, const std::string& address, const std::string& method);
    virtual int GetSendTimeout() const;
    virtual bool SetReceiveTimeout(const int timeout, const std::string& address, const std::string& method);
    virtual int GetReceiveTimeout() const;

    static int GetConstant(const std::string& constant);

    virtual ~FairMQSocketZMQ();

  private:
    void* fSocket;
    std::string fId;
    unsigned long fBytesTx;
    unsigned long fBytesRx;
    unsigned long fMessagesTx;
    unsigned long fMessagesRx;

    static boost::shared_ptr<FairMQContextZMQ> fContext;
};

#endif /* FAIRMQSOCKETZMQ_H_ */
