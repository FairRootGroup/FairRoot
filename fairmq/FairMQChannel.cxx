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

#include <boost/algorithm/string.hpp> // join/split

#include "FairMQChannel.h"
#include "FairMQLogger.h"

using namespace std;

mutex FairMQChannel::fChannelMutex;

atomic<bool> FairMQChannel::fInterrupted(false);

FairMQChannel::FairMQChannel()
    : fSocket(nullptr)
    , fType("unspecified")
    , fMethod("unspecified")
    , fAddress("unspecified")
    , fSndBufSize(1000)
    , fRcvBufSize(1000)
    , fSndKernelSize(0)
    , fRcvKernelSize(0)
    , fRateLogging(1)
    , fChannelName("")
    , fIsValid(false)
    , fPoller(nullptr)
    , fCmdSocket(nullptr)
    , fTransportFactory(nullptr)
    , fNoBlockFlag(0)
    , fSndMoreFlag(0)
{
}

FairMQChannel::FairMQChannel(const string& type, const string& method, const string& address)
    : fSocket(nullptr)
    , fType(type)
    , fMethod(method)
    , fAddress(address)
    , fSndBufSize(1000)
    , fRcvBufSize(1000)
    , fSndKernelSize(0)
    , fRcvKernelSize(0)
    , fRateLogging(1)
    , fChannelName("")
    , fIsValid(false)
    , fPoller(nullptr)
    , fCmdSocket(nullptr)
    , fTransportFactory(nullptr)
    , fNoBlockFlag(0)
    , fSndMoreFlag(0)
{
}

FairMQChannel::FairMQChannel(const FairMQChannel& chan)
    : fSocket(nullptr)
    , fType(chan.fType)
    , fMethod(chan.fMethod)
    , fAddress(chan.fAddress)
    , fSndBufSize(chan.fSndBufSize)
    , fRcvBufSize(chan.fRcvBufSize)
    , fSndKernelSize(chan.fSndKernelSize)
    , fRcvKernelSize(chan.fRcvKernelSize)
    , fRateLogging(chan.fRateLogging)
    , fChannelName(chan.fChannelName)
    , fIsValid(false)
    , fPoller(nullptr)
    , fCmdSocket(nullptr)
    , fTransportFactory(nullptr)
    , fNoBlockFlag(chan.fNoBlockFlag)
    , fSndMoreFlag(chan.fSndMoreFlag)
{}

FairMQChannel& FairMQChannel::operator=(const FairMQChannel& chan)
{
    fType = chan.fType;
    fMethod = chan.fMethod;
    fAddress = chan.fAddress;
    fSndBufSize = chan.fSndBufSize;
    fRcvBufSize = chan.fRcvBufSize;
    fSndKernelSize = chan.fSndKernelSize;
    fRcvKernelSize = chan.fRcvKernelSize;
    fRateLogging = chan.fRateLogging;
    fSocket = nullptr;
    fChannelName = chan.fChannelName;
    fIsValid = false;
    fPoller = nullptr;
    fCmdSocket = nullptr;
    fTransportFactory = nullptr;
    fNoBlockFlag = chan.fNoBlockFlag;
    fSndMoreFlag = chan.fSndMoreFlag;

    return *this;
}

string FairMQChannel::GetChannelName() const
{
    return fChannelName;
}

string FairMQChannel::GetChannelPrefix() const
{
    string prefix = fChannelName;
    return prefix.erase(fChannelName.rfind("["));
}

string FairMQChannel::GetType() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fType;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetType: " << e.what();
        exit(EXIT_FAILURE);
    }
}

string FairMQChannel::GetMethod() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fMethod;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetMethod: " << e.what();
        exit(EXIT_FAILURE);
    }
}

string FairMQChannel::GetAddress() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fAddress;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetAddress: " << e.what();
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetSndBufSize() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fSndBufSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetSndBufSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetRcvBufSize() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fRcvBufSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetRcvBufSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetSndKernelSize() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fSndKernelSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetSndKernelSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetRcvKernelSize() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fRcvKernelSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetRcvKernelSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

int FairMQChannel::GetRateLogging() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fRateLogging;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::GetRateLogging: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateType(const string& type)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fType = type;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateType: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateMethod(const string& method)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fMethod = method;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateMethod: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateAddress(const string& address)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fAddress = address;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateAddress: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateSndBufSize(const int sndBufSize)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fSndBufSize = sndBufSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateSndBufSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateRcvBufSize(const int rcvBufSize)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fRcvBufSize = rcvBufSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateRcvBufSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateSndKernelSize(const int sndKernelSize)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fSndKernelSize = sndKernelSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateSndKernelSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateRcvKernelSize(const int rcvKernelSize)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fRcvKernelSize = rcvKernelSize;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateRcvKernelSize: " << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQChannel::UpdateRateLogging(const int rateLogging)
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        fIsValid = false;
        fRateLogging = rateLogging;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::UpdateRateLogging: " << e.what();
        exit(EXIT_FAILURE);
    }
}

bool FairMQChannel::IsValid() const
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);
        return fIsValid;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::IsValid: " << e.what();
        exit(EXIT_FAILURE);
    }
}

bool FairMQChannel::ValidateChannel()
{
    try
    {
        unique_lock<mutex> lock(fChannelMutex);

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
            LOG(ERROR) << "Invalid channel type: \"" << fType << "\"";
            exit(EXIT_FAILURE);
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
            //TODO: maybe cache fEndpoints as a class member? not really needed as tokenizing is
            //fast, and only happens during (re-)configure
            vector<string> fEndpoints;
            Tokenize(fEndpoints, fAddress);
            for (const auto endpoint : fEndpoints)
            {
                string address;
                if (endpoint[0] == '@' || endpoint[0] == '+' || endpoint[0] == '>')
                {
                    address = endpoint.substr(1);
                }
                else
                {
                    // we don't have a method modifier, check if the default method is set
                    const string socketMethodNames[] = { "bind", "connect" };
                    const set<string> socketMethods(socketMethodNames, socketMethodNames + sizeof(socketMethodNames) / sizeof(string));
                    if (socketMethods.find(fMethod) == socketMethods.end())
                    {
                        ss << "INVALID";
                        LOG(DEBUG) << ss.str();
                        LOG(ERROR) << "Invalid endpoint connection method: \"" << fMethod << "\" for " << endpoint;
                        exit(EXIT_FAILURE);
                    }
                    address = endpoint;
                }
                // check if address is a tcp or ipc address
                if (address.compare(0, 6, "tcp://") == 0)
                {
                    // check if TCP address contains port delimiter
                    string addressString = address.substr(6);
                    if (addressString.find(":") == string::npos)
                    {
                        ss << "INVALID";
                        LOG(DEBUG) << ss.str();
                        LOG(ERROR) << "invalid channel address: \"" << address << "\" (missing port?)";
                        return false;
                    }
                }
                else if (address.compare(0, 6, "ipc://") == 0)
                {
                    // check if IPC address is not empty
                    string addressString = address.substr(6);
                    if (addressString == "")
                    {
                        ss << "INVALID";
                        LOG(DEBUG) << ss.str();
                        LOG(ERROR) << "invalid channel address: \"" << address << "\" (empty IPC address?)";
                        return false;
                    }
                }
                else
                {
                    // if neither TCP or IPC is specified, return invalid
                    ss << "INVALID";
                    LOG(DEBUG) << ss.str();
                    LOG(ERROR) << "invalid channel address: \"" << address << "\" (missing protocol specifier?)";
                    return false;
                }
            }
        }

        // validate socket buffer size for sending
        if (fSndBufSize < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(ERROR) << "invalid channel send buffer size (cannot be negative): \"" << fSndBufSize << "\"";
            exit(EXIT_FAILURE);
        }

        // validate socket buffer size for receiving
        if (fRcvBufSize < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(ERROR) << "invalid channel receive buffer size (cannot be negative): \"" << fRcvBufSize << "\"";
            exit(EXIT_FAILURE);
        }

        // validate socket kernel transmit size for sending
        if (fSndKernelSize < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(ERROR) << "invalid channel send kernel transmit size (cannot be negative): \"" << fSndKernelSize << "\"";
            exit(EXIT_FAILURE);
        }

        // validate socket kernel transmit size for receiving
        if (fRcvKernelSize < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(ERROR) << "invalid channel receive kernel transmit size (cannot be negative): \"" << fRcvKernelSize << "\"";
            exit(EXIT_FAILURE);
        }

        // validate socket rate logging interval
        if (fRateLogging < 0)
        {
            ss << "INVALID";
            LOG(DEBUG) << ss.str();
            LOG(ERROR) << "invalid socket rate logging interval (cannot be negative): \"" << fRateLogging << "\"";
            exit(EXIT_FAILURE);
        }

        fIsValid = true;
        ss << "VALID";
        LOG(DEBUG) << ss.str();
        return true;
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Exception caught in FairMQChannel::ValidateChannel: " << e.what();
        exit(EXIT_FAILURE);
    }
}

bool FairMQChannel::InitCommandInterface(shared_ptr<FairMQTransportFactory> factory, int numIoThreads)
{
    fTransportFactory = factory;

    fCmdSocket = fTransportFactory->CreateSocket("sub", "device-commands", numIoThreads, "internal");
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
    unique_lock<mutex> lock(fChannelMutex);
    fIsValid = false;
    // TODO: implement channel resetting
}

int FairMQChannel::Send(const unique_ptr<FairMQMessage>& msg, int sndTimeoutInMs) const
{
    fPoller->Poll(sndTimeoutInMs);

    if (fPoller->CheckInput(0))
    {
        HandleUnblock();
        if (fInterrupted)
        {
            return -2;
        }
    }

    if (fPoller->CheckOutput(1))
    {
        return fSocket->Send(msg.get(), 0);
    }

    return -2;
}

int FairMQChannel::Receive(const unique_ptr<FairMQMessage>& msg, int rcvTimeoutInMs) const
{
    fPoller->Poll(rcvTimeoutInMs);

    if (fPoller->CheckInput(0))
    {
        HandleUnblock();
        if (fInterrupted)
        {
            return -2;
        }
    }

    if (fPoller->CheckInput(1))
    {
        return fSocket->Receive(msg.get(), 0);
    }

    return -2;
}

int64_t FairMQChannel::Send(const vector<unique_ptr<FairMQMessage>>& msgVec, int sndTimeoutInMs) const
{
    fPoller->Poll(sndTimeoutInMs);

    if (fPoller->CheckInput(0))
    {
        HandleUnblock();
        if (fInterrupted)
        {
            return -2;
        }
    }

    if (fPoller->CheckOutput(1))
    {
        return fSocket->Send(msgVec);
    }

    return -2;
}

int64_t FairMQChannel::Receive(vector<unique_ptr<FairMQMessage>>& msgVec, int rcvTimeoutInMs) const
{
    fPoller->Poll(rcvTimeoutInMs);

    if (fPoller->CheckInput(0))
    {
        HandleUnblock();
        if (fInterrupted)
        {
            return -2;
        }
    }

    if (fPoller->CheckInput(1))
    {
        return fSocket->Receive(msgVec);
    }

    return -2;
}

int FairMQChannel::Send(FairMQMessage* msg, const string& flag, int sndTimeoutInMs) const
{
    if (flag == "")
    {
        fPoller->Poll(sndTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            if (fInterrupted)
            {
                return -2;

            }
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

int FairMQChannel::Send(FairMQMessage* msg, const int flags, int sndTimeoutInMs) const
{
    if (flags == 0)
    {
        fPoller->Poll(sndTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            if (fInterrupted)
            {
                return -2;

            }
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

int FairMQChannel::Receive(FairMQMessage* msg, const string& flag, int rcvTimeoutInMs) const
{
    if (flag == "")
    {
        fPoller->Poll(rcvTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            if (fInterrupted)
            {
                return -2;

            }
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

int FairMQChannel::Receive(FairMQMessage* msg, const int flags, int rcvTimeoutInMs) const
{
    if (flags == 0)
    {
        fPoller->Poll(rcvTimeoutInMs);

        if (fPoller->CheckInput(0))
        {
            HandleUnblock();
            if (fInterrupted)
            {
                return -2;

            }
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
    FairMQMessagePtr cmd(fTransportFactory->CreateMessage());
    if (fCmdSocket->Receive(cmd.get(), 0) >= 0)
    {
        // LOG(DEBUG) << "unblocked";
    }
    return true;
}

FairMQChannel::~FairMQChannel()
{
}

void FairMQChannel::Tokenize(vector<string>& output, const string& input, const string delimiters)
{
    boost::algorithm::split(output, input, boost::algorithm::is_any_of(delimiters));
}
