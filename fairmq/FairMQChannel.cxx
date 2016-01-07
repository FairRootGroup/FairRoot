/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQChannel.cxx
 *
 * @since 2015-06-02
 * @author A. Rybalchenko
 */

#include <set>

#include <boost/exception/all.hpp>

#include "FairMQChannel.h"
#include "FairMQLogger.h"

using namespace std;

boost::mutex FairMQChannel::fChannelMutex;

FairMQChannel::FairMQChannel()
    : fType("unspecified")
    , fMethod("unspecified")
    , fAddress("unspecified")
    , fSndBufSize(1000)
    , fRcvBufSize(1000)
    , fRateLogging(1)
    , fSocket(nullptr)
    , fChannelName("")
    , fIsValid(false)
    , fPoller(nullptr)
    , fCmdSocket(nullptr)
    , fTransportFactory(nullptr)
    , fNoBlockFlag(0)
    , fSndMoreFlag(0)
    , fSndTimeoutInMs(-1)
    , fRcvTimeoutInMs(-1)
{
}

FairMQChannel::FairMQChannel(const string& type, const string& method, const string& address)
    : fType(type)
    , fMethod(method)
    , fAddress(address)
    , fSndBufSize(1000)
    , fRcvBufSize(1000)
    , fRateLogging(1)
    , fSocket(nullptr)
    , fChannelName("")
    , fIsValid(false)
    , fPoller(nullptr)
    , fCmdSocket(nullptr)
    , fTransportFactory(nullptr)
    , fNoBlockFlag(0)
    , fSndMoreFlag(0)
    , fSndTimeoutInMs(-1)
    , fRcvTimeoutInMs(-1)
{
}

FairMQChannel::FairMQChannel(const FairMQChannel& chan)
    : fType(chan.fType)
    , fMethod(chan.fMethod)
    , fAddress(chan.fAddress)
    , fSndBufSize(chan.fSndBufSize)
    , fRcvBufSize(chan.fRcvBufSize)
    , fRateLogging(chan.fRateLogging)
    , fSocket(nullptr)
    , fChannelName(chan.fChannelName)
    , fIsValid(false)
    , fPoller(nullptr)
    , fCmdSocket(nullptr)
    , fTransportFactory(nullptr)
    , fNoBlockFlag(chan.fNoBlockFlag)
    , fSndMoreFlag(chan.fSndMoreFlag)
    , fSndTimeoutInMs(chan.fSndTimeoutInMs)
    , fRcvTimeoutInMs(chan.fRcvTimeoutInMs)
{}

FairMQChannel& FairMQChannel::operator=(const FairMQChannel& chan)
{
    fType = chan.fType;
    fMethod = chan.fMethod;
    fAddress = chan.fAddress;
    fSndBufSize = chan.fSndBufSize;
    fRcvBufSize = chan.fRcvBufSize;
    fRateLogging = chan.fRateLogging;
    fSocket = nullptr;
    fChannelName = chan.fChannelName;
    fIsValid = false;
    fPoller = nullptr;
    fCmdSocket = nullptr;
    fTransportFactory = nullptr;
    fNoBlockFlag = chan.fNoBlockFlag;
    fSndMoreFlag = chan.fSndMoreFlag;
    fSndTimeoutInMs = chan.fSndTimeoutInMs;
    fRcvTimeoutInMs = chan.fRcvTimeoutInMs;

    return *this;
}

string FairMQChannel::GetType() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fType;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetType: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

string FairMQChannel::GetMethod() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fMethod;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetMethod: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

string FairMQChannel::GetAddress() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fAddress;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetAddress: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetSndBufSize() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fSndBufSize;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetSndBufSize: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetRcvBufSize() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fRcvBufSize;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetRcvBufSize: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetRateLogging() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fRateLogging;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetRateLogging: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateType(const string& type)
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        fIsValid = false;
        fType = type;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateType: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateMethod(const string& method)
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        fIsValid = false;
        fMethod = method;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateMethod: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateAddress(const string& address)
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        fIsValid = false;
        fAddress = address;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateAddress: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateSndBufSize(const int sndBufSize)
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        fIsValid = false;
        fSndBufSize = sndBufSize;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateSndBufSize: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateRcvBufSize(const int rcvBufSize)
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        fIsValid = false;
        fRcvBufSize = rcvBufSize;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateRcvBufSize: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateRateLogging(const int rateLogging)
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        fIsValid = false;
        fRateLogging = rateLogging;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateRateLogging: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

bool FairMQChannel::IsValid() const
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);
        return fIsValid;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::IsValid: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

bool FairMQChannel::ValidateChannel()
{
    try
    {
        boost::unique_lock<boost::mutex> scoped_lock(fChannelMutex);

        stringstream ss;
        ss << "Validating channel \"" << fChannelName << "\"... ";

        if (fIsValid)
        {
            ss << "ALREADY VALID";
            LOG(DEBUG) << ss.str();
            return true;
        }

        // validate socket type
        const string socketTypeNames[] = { "sub", "pub", "pull", "push", "req", "rep", "xsub", "xpub", "dealer", "router", "pair" };
        const set<string> socketTypes(socketTypeNames, socketTypeNames + sizeof(socketTypeNames) / sizeof(string));
        if (socketTypes.find(fType) == socketTypes.end())
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(DEBUG) << "Invalid channel type: \"" << fType << "\"";
            return false;
        }

        // validate socket method
        const string socketMethodNames[] = { "bind", "connect" };
        const set<string> socketMethods(socketMethodNames, socketMethodNames + sizeof(socketMethodNames) / sizeof(string));
        if (socketMethods.find(fMethod) == socketMethods.end())
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(DEBUG) << "Invalid channel method: \"" << fMethod << "\"";
            return false;
        }

        // validate socket address
        if (fAddress == "unspecified" || fAddress == "")
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(DEBUG) << "invalid channel address: \"" << fAddress << "\"";
            return false;
        }
        else
        {
            // check if address is a tcp or ipc address
            if (fAddress.compare(0, 6, "tcp://") == 0)
            {
                // check if TCP address contains port delimiter
                string addressString = fAddress.substr(6);
                if (addressString.find(":") == string::npos)
                {
                    ss << "INVALID";
                    LOG(DEBUG) << ss.str();
                    LOG(DEBUG) << "invalid channel address: \"" << fAddress << "\" (missing port?)";
                    return false;
                }
            }
            else if (fAddress.compare(0, 6, "ipc://") == 0)
            {
                // check if IPC address is not empty
                string addressString = fAddress.substr(6);
                if (addressString == "")
                {
                    ss << "INVALID";
                    LOG(DEBUG) << ss.str();
                    LOG(DEBUG) << "invalid channel address: \"" << fAddress << "\" (empty IPC address?)";
                    return false;
                }
            }
            else
            {
                // if neither TCP or IPC is specified, return invalid
                ss << "INVALID";
                LOG(DEBUG) << ss.str();
                LOG(DEBUG) << "invalid channel address: \"" << fAddress << "\" (missing protocol specifier?)";
                return false;
            }
        }

        // validate socket buffer size for sending
        if (fSndBufSize < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(DEBUG) << "invalid channel send buffer size: \"" << fSndBufSize << "\"";
            return false;
        }

        // validate socket buffer size for receiving
        if (fRcvBufSize < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(DEBUG) << "invalid channel receive buffer size: \"" << fRcvBufSize << "\"";
            return false;
        }

        fIsValid = true;
        ss << "VALID";
        LOG(DEBUG) << ss.str();
        return true;
    }
    catch (boost::exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::ValidateChannel: " << boost::diagnostic_information(e);
        exit(EXIT_FAILURE);
    }
}

bool FairMQChannel::InitCommandInterface(FairMQTransportFactory* factory, int numIoThreads)
{
    fTransportFactory = factory;

    fCmdSocket = fTransportFactory->CreateSocket("sub", "device-commands", numIoThreads);
    if (fCmdSocket)
    {
        fCmdSocket->Connect("inproc://commands");

        fNoBlockFlag = fCmdSocket->NOBLOCK;
        fSndMoreFlag = fCmdSocket->SNDMORE;

        fPoller = fTransportFactory->CreatePoller(*fCmdSocket, *fSocket);

        return true;
    }
    else
    {
        return false;
    }
}

void FairMQChannel::ResetChannel()
{
    fIsValid = false;
    // TODO: implement channel resetting
}

int FairMQChannel::Send(const unique_ptr<FairMQMessage>& msg) const
{
    fPoller->Poll(fSndTimeoutInMs);

    if (fPoller->CheckInput(0))
    {
        HandleUnblock();
        return -2;
    }

    if (fPoller->CheckOutput(1))
    {
        return fSocket->Send(msg.get(), 0);
    }

    return -2;
}

int FairMQChannel::SendAsync(const unique_ptr<FairMQMessage>& msg) const
{
    return fSocket->Send(msg.get(), fNoBlockFlag);
}

int FairMQChannel::SendPart(const unique_ptr<FairMQMessage>& msg) const
{
    return fSocket->Send(msg.get(), fSndMoreFlag);
}

int FairMQChannel::SendPartAsync(const unique_ptr<FairMQMessage>& msg) const
{
    return fSocket->Send(msg.get(), fSndMoreFlag|fNoBlockFlag);
}

// int FairMQChannel::SendParts(initializer_list<unique_ptr<FairMQMessage>> partsList) const
// {
//     int totalSize = 0;
//     initializer_list<unique_ptr<FairMQMessage>>::iterator it = partsList.end();
//     auto &last = --it;
//     for (auto &p : partsList)
//     {
//         if (&p != last)
//         {
//             int nbytes = SendPart(p);
//             if (nbytes >= 0)
//             {
//                 totalSize += nbytes;
//             }
//             else
//             {
//                 return nbytes;
//             }
//         }
//         else
//         {
//             int nbytes = Send(p);
//             if (nbytes >= 0)
//             {
//                 totalSize += nbytes;
//             }
//             else
//             {
//                 return nbytes;
//             }
//         }
//     }
//     return totalSize;
// }

int FairMQChannel::Receive(const unique_ptr<FairMQMessage>& msg) const
{
    fPoller->Poll(fRcvTimeoutInMs);

    if (fPoller->CheckInput(0))
    {
        HandleUnblock();
        return -2;
    }

    if (fPoller->CheckInput(1))
    {
        return fSocket->Receive(msg.get(), 0);
    }

    return -2;
}

int FairMQChannel::ReceiveAsync(const unique_ptr<FairMQMessage>& msg) const
{
    return fSocket->Receive(msg.get(), fNoBlockFlag);
}

int FairMQChannel::Send(FairMQMessage* msg, const string& flag) const
{
    if (flag == "")
    {
        fPoller->Poll(fSndTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            return -2;
        }

        if (fPoller->CheckOutput(1))
        {
            return fSocket->Send(msg, flag);
        }

        return -2;
    }
    else
    {
        return fSocket->Send(msg, flag);
    }
}

int FairMQChannel::Send(FairMQMessage* msg, const int flags) const
{
    if (flags == 0)
    {
        fPoller->Poll(fSndTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            return -2;
        }

        if (fPoller->CheckOutput(1))
        {
            return fSocket->Send(msg, flags);
        }

        return -2;
    }
    else
    {
        return fSocket->Send(msg, flags);
    }
}

int FairMQChannel::Receive(FairMQMessage* msg, const string& flag) const
{
    if (flag == "")
    {
        fPoller->Poll(fRcvTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            return -2;
        }

        if (fPoller->CheckInput(1))
        {
            return fSocket->Receive(msg, flag);
        }

        return -2;
    }
    else
    {
        return fSocket->Receive(msg, flag);
    }
}

int FairMQChannel::Receive(FairMQMessage* msg, const int flags) const
{
    if (flags == 0)
    {
        fPoller->Poll(fRcvTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            return -2;
        }

        if (fPoller->CheckInput(1))
        {
            return fSocket->Receive(msg, flags);
        }

        return -2;
    }
    else
    {
        return fSocket->Receive(msg, flags);
    }
}

void FairMQChannel::SetSendTimeout(const int timeout)
{
    // if (fSocket)
    // {
    //     if (fSocket->SetSendTimeout(timeout, fAddress, fMethod))
    //     {
            fSndTimeoutInMs = timeout;
    //         return true;
    //     }
    // }

    // LOG(ERROR) << "SetSendTimeout() failed - socket is not initialized!";
    // return false;
}

int FairMQChannel::GetSendTimeout() const
{
    return fSndTimeoutInMs;
    // if (fSocket)
    // {
    //     return fSocket->GetSendTimeout();
    // }
    // else
    // {
    //     LOG(ERROR) << "GetSendTimeout() failed - socket is not initialized!";
    //     return -1;
    // }
}

void FairMQChannel::SetReceiveTimeout(const int timeout)
{
    // if (fSocket)
    // {
    //     if (fSocket->SetReceiveTimeout(timeout, fAddress, fMethod))
    //     {
            fRcvTimeoutInMs = timeout;
    //         return true;
    //     }
    // }

    // LOG(ERROR) << "SetReceiveTimeout() failed - socket is not initialized!";
    // return false;
}

int FairMQChannel::GetReceiveTimeout() const
{
    return fRcvTimeoutInMs;
    // if (fSocket)
    // {
    //     return fSocket->GetReceiveTimeout();
    // }
    // else
    // {
    //     LOG(ERROR) << "GetReceiveTimeout() failed - socket is not initialized!";
    //     return -1;
    // }
}

bool FairMQChannel::ExpectsAnotherPart() const
{
    int64_t more = 0;
    size_t more_size = sizeof more;

    if (fSocket)
    {
        fSocket->GetOption("rcv-more", &more, &more_size);
        if (more)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

inline bool FairMQChannel::HandleUnblock() const
{
    FairMQMessage* cmd = fTransportFactory->CreateMessage();
    if (fCmdSocket->Receive(cmd, 0) >= 0)
    {
        LOG(DEBUG) << "unblocked";
    }
    delete cmd;
    return true;
}

FairMQChannel::~FairMQChannel()
{
    delete fCmdSocket;
    delete fPoller;
}
