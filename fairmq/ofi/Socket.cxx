/********************************************************************************
 *    Copyright (C) 2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <fairmq/ofi/Socket.h>
#include <fairmq/ofi/TransportFactory.h>
#include <fairmq/Tools.h>
#include <FairMQLogger.h>

#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <rdma/fabric.h>
#include <rdma/fi_endpoint.h>
#include <sstream>
#include <string.h>
#include <sys/socket.h>
#include <zmq.h>

namespace fair
{
namespace mq
{
namespace ofi
{

using namespace std;

Socket::Socket(Context& context, const string& type, const string& name, const string& id /*= ""*/)
    : fDataEndpoint(nullptr)
    , fDataCompletionQueueTx(nullptr)
    , fDataCompletionQueueRx(nullptr)
    , fId(id + "." + name + "." + type)
    , fMetaSocket(nullptr)
    , fMonitorSocket(nullptr)
    , fSndTimeout(100)
    , fRcvTimeout(100)
    , fContext(context)
    , fWaitingForRemoteConnect(false)
{
    if (type != "pair") {
        throw SocketError{tools::ToString("Socket type '", type, "' not implemented for ofi transport.")};
    } else {
        fMetaSocket = zmq_socket(fContext.GetZmqContext(), ZMQ_PAIR);

        if (fMetaSocket == nullptr)
            throw SocketError{tools::ToString("Failed creating zmq meta socket ", fId, ", reason: ", zmq_strerror(errno))};

        if (zmq_setsockopt(fMetaSocket, ZMQ_IDENTITY, fId.c_str(), fId.length()) != 0)
            throw SocketError{tools::ToString("Failed setting ZMQ_IDENTITY socket option, reason: ", zmq_strerror(errno))};

        // Tell socket to try and send/receive outstanding messages for <linger> milliseconds before terminating.
        // Default value for ZeroMQ is -1, which is to wait forever.
        int linger = 1000;
        if (zmq_setsockopt(fMetaSocket, ZMQ_LINGER, &linger, sizeof(linger)) != 0)
            throw SocketError{tools::ToString("Failed setting ZMQ_LINGER socket option, reason: ", zmq_strerror(errno))};

        if (zmq_setsockopt(fMetaSocket, ZMQ_SNDTIMEO, &fSndTimeout, sizeof(fSndTimeout)) != 0)
            throw SocketError{tools::ToString("Failed setting ZMQ_SNDTIMEO socket option, reason: ", zmq_strerror(errno))};

        if (zmq_setsockopt(fMetaSocket, ZMQ_RCVTIMEO, &fRcvTimeout, sizeof(fRcvTimeout)) != 0)
            throw SocketError{tools::ToString("Failed setting ZMQ_RCVTIMEO socket option, reason: ", zmq_strerror(errno))};

        fMonitorSocket = zmq_socket(fContext.GetZmqContext(), ZMQ_PAIR);

        if (fMonitorSocket == nullptr)
            throw SocketError{tools::ToString("Failed creating zmq monitor socket ", fId, ", reason: ", zmq_strerror(errno))};

        auto mon_addr = tools::ToString("inproc://", fId);
        if (zmq_socket_monitor(fMetaSocket, mon_addr.c_str(), ZMQ_EVENT_ACCEPTED) < 0)
            throw SocketError{tools::ToString("Failed setting up monitor on meta socket, reason: ", zmq_strerror(errno))};

        if (zmq_connect(fMonitorSocket, mon_addr.c_str()) != 0)
            throw SocketError{tools::ToString("Failed connecting monitor socket to meta socket, reason: ", zmq_strerror(errno))};
    }
}

auto Socket::Bind(const string& address) -> bool
{
    auto addr2 = fContext.ConvertAddress(address);
    if (addr2.Protocol != "tcp")
        throw SocketError("Wrong protocol: Supported protocols are: tcp");

    if (zmq_bind(fMetaSocket, address.c_str()) != 0) {
        if (errno == EADDRINUSE) {
            // do not print error in this case, this is handled by FairMQDevice
            // in case no connection could be established after trying a number of random ports from a range.
            return false;
        }
        LOG(error) << "Failed binding socket " << fId << ", reason: " << zmq_strerror(errno);
        return false;
    }

    fContext.InitOfi(ConnectionType::Bind, address);

    try {
        InitDataEndpoint();
    } catch (SocketError& e) {
        LOG(error) << e.what();
        return false;
    }

    fWaitingForRemoteConnect = true;

    return true;
}

auto Socket::Connect(const string& address) -> void
{
    auto addr2 = fContext.ConvertAddress(address);
    if (addr2.Protocol != "tcp")
        throw SocketError("Wrong protocol: Supported protocols are: tcp");

    if (zmq_connect(fMetaSocket, address.c_str()) != 0) {
        throw SocketError(tools::ToString("Failed connecting socket ", fId, ", reason: ", zmq_strerror(errno)));
    }

    fContext.InitOfi(ConnectionType::Connect, address);

    InitDataEndpoint();

    fRemoteAddr = fContext.InsertAddressVector(fContext.ConvertAddress(addr2));
}

auto Socket::InitDataEndpoint() -> void
{
    if (!fDataEndpoint) {
        try {
            fDataEndpoint = fContext.CreateOfiEndpoint();
        } catch (ContextError& e) {
            throw SocketError(tools::ToString("Failed creating ofi endpoint, reason: ", e.what()));
        }

        if (!fDataCompletionQueueTx)
            fDataCompletionQueueTx = fContext.CreateOfiCompletionQueue(Direction::Transmit);
        auto ret = fi_ep_bind(fDataEndpoint, &fDataCompletionQueueTx->fid, FI_TRANSMIT);
        if (ret != FI_SUCCESS)
            throw SocketError(tools::ToString("Failed binding ofi transmit completion queue to endpoint, reason: ", fi_strerror(ret)));

        if (!fDataCompletionQueueRx)
            fDataCompletionQueueRx = fContext.CreateOfiCompletionQueue(Direction::Receive);
        ret = fi_ep_bind(fDataEndpoint, &fDataCompletionQueueRx->fid, FI_RECV);
        if (ret != FI_SUCCESS)
            throw SocketError(tools::ToString("Failed binding ofi receive completion queue to endpoint, reason: ", fi_strerror(ret)));

        ret = fi_enable(fDataEndpoint);
        if (ret != FI_SUCCESS)
            throw SocketError(tools::ToString("Failed opening ofi fabric, reason: ", fi_strerror(ret)));
    }
}

auto Socket::WaitForRemoteConnect() -> void
{
    assert(fWaitingForRemoteConnect);

    // First frame in message contains event number and value
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    if (zmq_msg_recv(&msg, fMonitorSocket, 0) == -1)
        throw SocketError(tools::ToString("Failed to get monitor event, reason: ", zmq_strerror(errno)));

    uint8_t* data = (uint8_t*) zmq_msg_data(&msg);
    uint16_t event = *(uint16_t*)(data);
    int value = *(uint32_t *)(data + 2);

    // Second frame in message contains event address
    zmq_msg_init(&msg);
    if (zmq_msg_recv(&msg, fMonitorSocket, 0) == -1)
        throw SocketError(tools::ToString("Failed to get monitor event, reason: ", zmq_strerror(errno)));

    string localAddress = string(static_cast<char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));

    assert(event == ZMQ_EVENT_ACCEPTED); // we only subscribed for this event

    sockaddr_in remoteAddr;
    socklen_t addrSize = sizeof(sockaddr_in);
    int ret = getpeername(value, (sockaddr*)&remoteAddr, &addrSize);
    if (ret != 0)
        throw SocketError(tools::ToString("Failed retrieving peer address, reason: ", strerror(errno)));
    string remoteIp(inet_ntoa(remoteAddr.sin_addr));
    int remotePort = ntohs(remoteAddr.sin_port);
    LOG(debug) << "peer connected from " << remoteIp << ":" << remotePort << " at " << localAddress;

    fRemoteAddr = fContext.InsertAddressVector(remoteAddr);
    fWaitingForRemoteConnect = false;
}

auto Socket::Send(MessagePtr& msg, const int timeout) -> int { return SendImpl(msg, 0, timeout); }
auto Socket::Receive(MessagePtr& msg, const int timeout) -> int { return ReceiveImpl(msg, 0, timeout); }
auto Socket::Send(std::vector<MessagePtr>& msgVec, const int timeout) -> int64_t { return SendImpl(msgVec, 0, timeout); }
auto Socket::Receive(std::vector<MessagePtr>& msgVec, const int timeout) -> int64_t { return ReceiveImpl(msgVec, 0, timeout); }

auto Socket::TrySend(MessagePtr& msg) -> int { return SendImpl(msg, ZMQ_DONTWAIT, 0); }
auto Socket::TryReceive(MessagePtr& msg) -> int { return ReceiveImpl(msg, ZMQ_DONTWAIT, 0); }
auto Socket::TrySend(std::vector<MessagePtr>& msgVec) -> int64_t { return SendImpl(msgVec, ZMQ_DONTWAIT, 0); }
auto Socket::TryReceive(std::vector<MessagePtr>& msgVec) -> int64_t { return ReceiveImpl(msgVec, ZMQ_DONTWAIT, 0); }

auto Socket::SendImpl(FairMQMessagePtr& msg, const int flags, const int timeout) -> int
{
    if (fWaitingForRemoteConnect) {
        try {
            WaitForRemoteConnect(); 
        } catch (const std::exception& e) {
            LOG(error) << e.what();
            return -1;
        }
    }

    // void* metadata = malloc(sizeof(size_t));
    
    auto ret = zmq_send(fMetaSocket, nullptr, 0, flags);
    if (ret == EAGAIN) {
        return -2;
    } else if (ret < 0) {
        LOG(error) << "Failed sending meta message on socket " << fId << ", reason: " << zmq_strerror(errno);
        return -1;
    } else {
        // auto ret2 = fi_send(fDataEndpoint, msg->GetData(), msg->GetSize(), nullptr, fi_addr_t dest_addr, nullptr);
        return ret;
    }
}

auto Socket::ReceiveImpl(FairMQMessagePtr& msg, const int flags, const int timeout) -> int
{
    auto ret = zmq_recv(fMetaSocket, nullptr, 0, flags);
    if (ret == EAGAIN) {
        return -2;
    } else if (ret < 0) {
        LOG(error) << "Failed receiving meta message on socket " << fId << ", reason: " << zmq_strerror(errno);
        return -1;
    } else {
        return ret;
    }
}

auto Socket::SendImpl(vector<FairMQMessagePtr>& msgVec, const int flags, const int timeout) -> int64_t 
{
    throw SocketError{"Not yet implemented."};
    // const unsigned int vecSize = msgVec.size();
    // int elapsed = 0;
    //
    // // Sending vector typicaly handles more then one part
    // if (vecSize > 1)
    // {
    //     int64_t totalSize = 0;
    //     int nbytes = -1;
    //     bool repeat = false;
    //
    //     while (true && !fInterrupted)
    //     {
    //         for (unsigned int i = 0; i < vecSize; ++i)
    //         {
    //             nbytes = zmq_msg_send(static_cast<FairMQMessageSHM*>(msgVec[i].get())->GetMessage(),
    //                                   fSocket,
    //                                   (i < vecSize - 1) ? ZMQ_SNDMORE|flags : flags);
    //             if (nbytes >= 0)
    //             {
    //                 static_cast<FairMQMessageSHM*>(msgVec[i].get())->fQueued = true;
    //                 size_t size = msgVec[i]->GetSize();
    //
    //                 totalSize += size;
    //             }
    //             else
    //             {
    //                 // according to ZMQ docs, this can only occur for the first part
    //                 if (zmq_errno() == EAGAIN)
    //                 {
    //                     if (!fInterrupted && ((flags & ZMQ_DONTWAIT) == 0))
    //                     {
    //                         if (timeout)
    //                         {
    //                             elapsed += fSndTimeout;
    //                             if (elapsed >= timeout)
    //                             {
    //                                 return -2;
    //                             }
    //                         }
    //                         repeat = true;
    //                         break;
    //                     }
    //                     else
    //                     {
    //                         return -2;
    //                     }
    //                 }
    //                 if (zmq_errno() == ETERM)
    //                 {
    //                     LOG(info) << "terminating socket " << fId;
    //                     return -1;
    //                 }
    //                 LOG(error) << "Failed sending on socket " << fId << ", reason: " << zmq_strerror(errno);
    //                 return nbytes;
    //             }
    //         }
    //
    //         if (repeat)
    //         {
    //             continue;
    //         }
    //
    //         // store statistics on how many messages have been sent (handle all parts as a single message)
    //         ++fMessagesTx;
    //         fBytesTx += totalSize;
    //         return totalSize;
    //     }
    //
    //     return -1;
    // } // If there's only one part, send it as a regular message
    // else if (vecSize == 1)
    // {
    //     return Send(msgVec.back(), flags);
    // }
    // else // if the vector is empty, something might be wrong
    // {
    //     LOG(warn) << "Will not send empty vector";
    //     return -1;
    // }
}

auto Socket::ReceiveImpl(vector<FairMQMessagePtr>& msgVec, const int flags, const int timeout) -> int64_t
{
    throw SocketError{"Not yet implemented."};
    // int64_t totalSize = 0;
    // int64_t more = 0;
    // bool repeat = false;
    // int elapsed = 0;
    //
    // while (true)
    // {
    //     // Warn if the vector is filled before Receive() and empty it.
    //     // if (msgVec.size() > 0)
    //     // {
    //     //     LOG(warn) << "Message vector contains elements before Receive(), they will be deleted!";
    //     //     msgVec.clear();
    //     // }
    //
    //     totalSize = 0;
    //     more = 0;
    //     repeat = false;
    //
    //     do
    //     {
    //         FairMQMessagePtr part(new FairMQMessageSHM(fManager));
    //         zmq_msg_t* msgPtr = static_cast<FairMQMessageSHM*>(part.get())->GetMessage();
    //
    //         int nbytes = zmq_msg_recv(msgPtr, fSocket, flags);
    //         if (nbytes == 0)
    //         {
    //             msgVec.push_back(move(part));
    //         }
    //         else if (nbytes > 0)
    //         {
    //             MetaHeader* hdr = static_cast<MetaHeader*>(zmq_msg_data(msgPtr));
    //             size_t size = 0;
    //             static_cast<FairMQMessageSHM*>(part.get())->fHandle = hdr->fHandle;
    //             static_cast<FairMQMessageSHM*>(part.get())->fSize = hdr->fSize;
    //             static_cast<FairMQMessageSHM*>(part.get())->fRegionId = hdr->fRegionId;
    //             static_cast<FairMQMessageSHM*>(part.get())->fHint = hdr->fHint;
    //             size = part->GetSize();
    //
    //             msgVec.push_back(move(part));
    //
    //             totalSize += size;
    //         }
    //         else if (zmq_errno() == EAGAIN)
    //         {
    //             if (!fInterrupted && ((flags & ZMQ_DONTWAIT) == 0))
    //             {
    //                 if (timeout)
    //                 {
    //                     elapsed += fSndTimeout;
    //                     if (elapsed >= timeout)
    //                     {
    //                         return -2;
    //                     }
    //                 }
    //                 repeat = true;
    //                 break;
    //             }
    //             else
    //             {
    //                 return -2;
    //             }
    //         }
    //         else
    //         {
    //             return nbytes;
    //         }
    //
    //         size_t more_size = sizeof(more);
    //         zmq_getsockopt(fSocket, ZMQ_RCVMORE, &more, &more_size);
    //     }
    //     while (more);
    //
    //     if (repeat)
    //     {
    //         continue;
    //     }
    //
    //     // store statistics on how many messages have been received (handle all parts as a single message)
    //     ++fMessagesRx;
    //     fBytesRx += totalSize;
    //     return totalSize;
    // }
}

auto Socket::Close() -> void
{
    if (zmq_close(fMetaSocket) != 0)
        throw SocketError(tools::ToString("Failed closing zmq meta socket, reason: ", zmq_strerror(errno)));

    if (zmq_close(fMonitorSocket) != 0)
        throw SocketError(tools::ToString("Failed closing zmq monitor socket, reason: ", zmq_strerror(errno)));

	if (fDataEndpoint) {
        auto ret = fi_close(&fDataEndpoint->fid);
        if (ret != FI_SUCCESS)
            throw SocketError(tools::ToString("Failed closing ofi endpoint, reason: ", fi_strerror(ret)));
    }

	if (fDataCompletionQueueTx) {
        auto ret = fi_close(&fDataCompletionQueueTx->fid);
        if (ret != FI_SUCCESS)
            throw SocketError(tools::ToString("Failed closing ofi transmit completion queue, reason: ", fi_strerror(ret)));
    }

	if (fDataCompletionQueueRx) {
        auto ret = fi_close(&fDataCompletionQueueRx->fid);
        if (ret != FI_SUCCESS)
            throw SocketError(tools::ToString("Failed closing ofi receive completion queue, reason: ", fi_strerror(ret)));
    }
}

auto Socket::SetOption(const string& option, const void* value, size_t valueSize) -> void
{
    if (zmq_setsockopt(fMetaSocket, GetConstant(option), value, valueSize) < 0) {
        throw SocketError{tools::ToString("Failed setting socket option, reason: ", zmq_strerror(errno))};
    }
}

auto Socket::GetOption(const string& option, void* value, size_t* valueSize) -> void
{
    if (zmq_getsockopt(fMetaSocket, GetConstant(option), value, valueSize) < 0) {
        throw SocketError{tools::ToString("Failed getting socket option, reason: ", zmq_strerror(errno))};
    }
}

auto Socket::SetSendTimeout(const int timeout, const string& address, const string& method) -> bool
{
    throw SocketError{"Not yet implemented."};
    // fSndTimeout = timeout;
    // if (method == "bind")
    // {
    //     if (zmq_unbind(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed unbinding socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_setsockopt(fSocket, ZMQ_SNDTIMEO, &fSndTimeout, sizeof(fSndTimeout)) != 0)
    //     {
    //         LOG(error) << "Failed setting option on socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_bind(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed binding socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    // }
    // else if (method == "connect")
    // {
    //     if (zmq_disconnect(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed disconnecting socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_setsockopt(fSocket, ZMQ_SNDTIMEO, &fSndTimeout, sizeof(fSndTimeout)) != 0)
    //     {
    //         LOG(error) << "Failed setting option on socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_connect(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed connecting socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    // }
    // else
    // {
    //     LOG(error) << "timeout failed - unknown method provided!";
    //     return false;
    // }
    //
    // return true;
}

auto Socket::GetSendTimeout() const -> int
{
    throw SocketError{"Not yet implemented."};
    // return fSndTimeout;
}

auto Socket::SetReceiveTimeout(const int timeout, const string& address, const string& method) -> bool
{
    throw SocketError{"Not yet implemented."};
    // fRcvTimeout = timeout;
    // if (method == "bind")
    // {
    //     if (zmq_unbind(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed unbinding socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_setsockopt(fSocket, ZMQ_RCVTIMEO, &fRcvTimeout, sizeof(fRcvTimeout)) != 0)
    //     {
    //         LOG(error) << "Failed setting option on socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_bind(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed binding socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    // }
    // else if (method == "connect")
    // {
    //     if (zmq_disconnect(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed disconnecting socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_setsockopt(fSocket, ZMQ_RCVTIMEO, &fRcvTimeout, sizeof(fRcvTimeout)) != 0)
    //     {
    //         LOG(error) << "Failed setting option on socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    //     if (zmq_connect(fSocket, address.c_str()) != 0)
    //     {
    //         LOG(error) << "Failed connecting socket " << fId << ", reason: " << zmq_strerror(errno);
    //         return false;
    //     }
    // }
    // else
    // {
    //     LOG(error) << "timeout failed - unknown method provided!";
    //     return false;
    // }
    //
    // return true;
}

auto Socket::GetReceiveTimeout() const -> int
{
    throw SocketError{"Not yet implemented."};
    // return fRcvTimeout;
}

auto Socket::GetConstant(const string& constant) -> int
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
    if (constant == "req")
        return ZMQ_REQ;
    if (constant == "rep")
        return ZMQ_REP;
    if (constant == "dealer")
        return ZMQ_DEALER;
    if (constant == "router")
        return ZMQ_ROUTER;
    if (constant == "pair")
        return ZMQ_PAIR;

    if (constant == "snd-hwm")
        return ZMQ_SNDHWM;
    if (constant == "rcv-hwm")
        return ZMQ_RCVHWM;
    if (constant == "snd-size")
        return ZMQ_SNDBUF;
    if (constant == "rcv-size")
        return ZMQ_RCVBUF;
    if (constant == "snd-more")
        return ZMQ_SNDMORE;
    if (constant == "rcv-more")
        return ZMQ_RCVMORE;

    if (constant == "linger")
        return ZMQ_LINGER;
    if (constant == "no-block")
        return ZMQ_DONTWAIT;
    if (constant == "snd-more no-block")
        return ZMQ_DONTWAIT|ZMQ_SNDMORE;

    return -1;
}

Socket::~Socket()
{
    try {
        Close(); // NOLINT(clang-analyzer-optin.cplusplus.VirtualCall)
    } catch (SocketError& e) {
        LOG(error) << e.what();
    }
}

} /* namespace ofi */
} /* namespace mq */
} /* namespace fair */
