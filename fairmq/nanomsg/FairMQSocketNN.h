/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSocketNN.h
 *
 * @since 2013-12-05
 * @author A. Rybalchenko
 */

#ifndef FAIRMQSOCKETNN_H_
#define FAIRMQSOCKETNN_H_

#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/pubsub.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pair.h>

#include "FairMQSocket.h"

class FairMQSocketNN : public FairMQSocket
{
  public:
    FairMQSocketNN(const std::string& type, const std::string& name, int numIoThreads); // numIoThreads is not used in nanomsg.

    virtual std::string GetId();

    virtual bool Bind(const std::string& address);
    virtual void Connect(const std::string& address);

    virtual int Send(FairMQMessage* msg, const std::string& flag = "");
    virtual int Send(FairMQMessage* msg, const int flags = 0);
    virtual int Receive(FairMQMessage* msg, const std::string& flag = "");
    virtual int Receive(FairMQMessage* msg, const int flags = 0);

    virtual void* GetSocket();
    virtual int GetSocket(int nothing);
    virtual void Close();
    virtual void Terminate();

    virtual void SetOption(const std::string& option, const void* value, size_t valueSize);
    virtual void GetOption(const std::string& option, void* value, size_t* valueSize);

    unsigned long GetBytesTx();
    unsigned long GetBytesRx();
    unsigned long GetMessagesTx();
    unsigned long GetMessagesRx();

    static int GetConstant(const std::string& constant);

    virtual ~FairMQSocketNN();

  private:
    int fSocket;
    std::string fId;
    unsigned long fBytesTx;
    unsigned long fBytesRx;
    unsigned long fMessagesTx;
    unsigned long fMessagesRx;
};

#endif /* FAIRMQSOCKETNN_H_ */
