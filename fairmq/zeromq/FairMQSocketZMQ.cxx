/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSocketZMQ.cxx
 *
 * @since 2012-12-05
 * @author D. Klein, A. Rybalchenko
 */

#include <sstream>

#include "FairMQSocketZMQ.h"
#include "FairMQLogger.h"

boost::shared_ptr<FairMQContextZMQ> FairMQSocketZMQ::fContext = boost::shared_ptr<FairMQContextZMQ>(new FairMQContextZMQ(1));

FairMQSocketZMQ::FairMQSocketZMQ(const string& type, int num, int numIoThreads)
    : fBytesTx(0)
    , fBytesRx(0)
    , fMessagesTx(0)
    , fMessagesRx(0)
{
    stringstream id;
    id << type << "." << num;
    fId = id.str();

    int rc = zmq_ctx_set(fContext->GetContext(), ZMQ_IO_THREADS, numIoThreads);
    if (rc != 0)
    {
        LOG(ERROR) << "failed configuring context, reason: " << zmq_strerror(errno);
    }

    fSocket = zmq_socket(fContext->GetContext(), GetConstant(type));

    rc = zmq_setsockopt(fSocket, ZMQ_IDENTITY, &fId, fId.length());
    if (rc != 0)
    {
        LOG(ERROR) << "failed setting ZMQ_IDENTITY socket option, reason: " << zmq_strerror(errno);
    }

    // Tell socket to try and send/receive outstanding messages for <linger> milliseconds before terminating.
    // Default value for ZeroMQ is -1, which is to wait forever.
    int linger = 500;
    rc = zmq_setsockopt(fSocket, ZMQ_LINGER, &linger, sizeof(linger));
    if (rc != 0)
    {
        LOG(ERROR) << "failed setting ZMQ_LINGER socket option, reason: " << zmq_strerror(errno);
    }

    if (type == "sub")
    {
        rc = zmq_setsockopt(fSocket, ZMQ_SUBSCRIBE, NULL, 0);
        if (rc != 0)
        {
            LOG(ERROR) << "failed setting ZMQ_SUBSCRIBE socket option, reason: " << zmq_strerror(errno);
        }
    }

    LOG(INFO) << "created socket #" << fId;
}

string FairMQSocketZMQ::GetId()
{
    return fId;
}

void FairMQSocketZMQ::Bind(const string& address)
{
    LOG(INFO) << "bind socket #" << fId << " on " << address;

    int rc = zmq_bind(fSocket, address.c_str());
    if (rc != 0)
    {
        LOG(ERROR) << "failed binding socket #" << fId << ", reason: " << zmq_strerror(errno);
    }
}

void FairMQSocketZMQ::Connect(const string& address)
{
    LOG(INFO) << "connect socket #" << fId << " on " << address;

    int rc = zmq_connect(fSocket, address.c_str());
    if (rc != 0)
    {
        LOG(ERROR) << "failed connecting socket #" << fId << ", reason: " << zmq_strerror(errno);
    }
}

int FairMQSocketZMQ::Send(FairMQMessage* msg, const string& flag)
{
    int nbytes = zmq_msg_send(static_cast<zmq_msg_t*>(msg->GetMessage()), fSocket, GetConstant(flag));
    if (nbytes >= 0)
    {
        fBytesTx += nbytes;
        ++fMessagesTx;
        return nbytes;
    }
    if (zmq_errno() == EAGAIN)
    {
        return 0;
    }
    if (zmq_errno() == ETERM)
    {
        LOG(INFO) << "terminating socket #" << fId;
        return -1;
    }
    LOG(ERROR) << "failed sending on socket #" << fId << ", reason: " << zmq_strerror(errno);
    return nbytes;
}

int FairMQSocketZMQ::Receive(FairMQMessage* msg, const string& flag)
{
    int nbytes = zmq_msg_recv(static_cast<zmq_msg_t*>(msg->GetMessage()), fSocket, GetConstant(flag));
    if (nbytes >= 0)
    {
        fBytesRx += nbytes;
        ++fMessagesRx;
        return nbytes;
    }
    if (zmq_errno() == EAGAIN)
    {
        return 0;
    }
    if (zmq_errno() == ETERM)
    {
        LOG(INFO) << "terminating socket #" << fId;
        return -1;
    }
    LOG(ERROR) << "failed receiving on socket #" << fId << ", reason: " << zmq_strerror(errno);
    return nbytes;
}

void FairMQSocketZMQ::Close()
{
    if (fSocket == NULL)
    {
        return;
    }

    int rc = zmq_close(fSocket);
    if (rc != 0)
    {
        LOG(ERROR) << "failed closing socket, reason: " << zmq_strerror(errno);
    }

    fSocket = NULL;
}

void FairMQSocketZMQ::Terminate()
{
    int rc = zmq_ctx_destroy(fContext->GetContext());
    if (rc != 0)
    {
        LOG(ERROR) << "failed terminating context, reason: " << zmq_strerror(errno);
    }
}

void* FairMQSocketZMQ::GetSocket()
{
    return fSocket;
}

int FairMQSocketZMQ::GetSocket(int nothing)
{
    // dummy method to comply with the interface. functionality not possible in zeromq.
    return -1;
}

void FairMQSocketZMQ::SetOption(const string& option, const void* value, size_t valueSize)
{
    int rc = zmq_setsockopt(fSocket, GetConstant(option), value, valueSize);
    if (rc < 0)
    {
        LOG(ERROR) << "failed setting socket option, reason: " << zmq_strerror(errno);
    }
}

void FairMQSocketZMQ::GetOption(const string& option, void* value, size_t* valueSize)
{
    int rc = zmq_getsockopt(fSocket, GetConstant(option), value, valueSize);
    if (rc < 0) {
        LOG(ERROR) << "failed getting socket option, reason: " << zmq_strerror(errno);
    }
}

unsigned long FairMQSocketZMQ::GetBytesTx()
{
    return fBytesTx;
}

unsigned long FairMQSocketZMQ::GetBytesRx()
{
    return fBytesRx;
}

unsigned long FairMQSocketZMQ::GetMessagesTx()
{
    return fMessagesTx;
}

unsigned long FairMQSocketZMQ::GetMessagesRx()
{
    return fMessagesRx;
}

int FairMQSocketZMQ::GetConstant(const string& constant)
{
    if (constant == "")
        return 0;
    if (constant == "sub")
        return ZMQ_SUB;
    if (constant == "pub")
        return ZMQ_PUB;
    if (constant == "xsub")
        return ZMQ_XSUB;
    if (constant == "xpub")
        return ZMQ_XPUB;
    if (constant == "push")
        return ZMQ_PUSH;
    if (constant == "pull")
        return ZMQ_PULL;
    if (constant == "snd-hwm")
        return ZMQ_SNDHWM;
    if (constant == "rcv-hwm")
        return ZMQ_RCVHWM;
    if (constant == "snd-more")
        return ZMQ_SNDMORE;
    if (constant == "rcv-more")
        return ZMQ_RCVMORE;
    if (constant == "linger")
        return ZMQ_LINGER;

    return -1;
}

FairMQSocketZMQ::~FairMQSocketZMQ()
{
}
