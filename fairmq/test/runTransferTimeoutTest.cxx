/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runTransferTimeoutTester.cxx
 *
 * @since 2015-09-05
 * @author A. Rybalchenko
 */

#include "FairMQLogger.h"
#include "FairMQDevice.h"

#ifdef NANOMSG
#include "FairMQTransportFactoryNN.h"
#else
#include "FairMQTransportFactoryZMQ.h"
#endif

class TransferTimeoutTester : public FairMQDevice
{
  public:
    TransferTimeoutTester() {}
    virtual ~TransferTimeoutTester() {}

  protected:
    virtual void Run()
    {
        bool setSndOK = false;
        bool setRcvOK = false;
        bool getSndOK = false;
        bool getRcvOK = false;
        bool sendCanceling = false;
        bool receiveCanceling = false;

        if (fChannels.at("data-out").at(0).SetSendTimeout(1000))
        {
            setSndOK = true;
            LOG(INFO) << "set send timeout OK";
        }
        else
        {
            LOG(ERROR) << "set send timeout failed";
        }

        if (fChannels.at("data-in").at(0).SetReceiveTimeout(1000))
        {
            setRcvOK = true;
            LOG(INFO) << "set receive timeout OK";
        }
        else
        {
            LOG(ERROR) << "set receive timeout failed";
        }

        if (setSndOK && setRcvOK)
        {
            if (fChannels.at("data-out").at(0).GetSendTimeout() == 1000)
            {
                getSndOK = true;
                LOG(INFO) << "get send timeout OK: " << fChannels.at("data-out").at(0).GetSendTimeout();
            }
            else
            {
                LOG(ERROR) << "get send timeout failed";
            }

            if (fChannels.at("data-in").at(0).GetReceiveTimeout() == 1000)
            {
                getRcvOK = true;
                LOG(INFO) << "get receive timeout OK: " << fChannels.at("data-in").at(0).GetReceiveTimeout();
            }
            else
            {
                LOG(ERROR) << "get receive timeout failed";
            }
        }

        if (getSndOK && getRcvOK)
        {
            void* buffer = operator new[](1000);
            std::unique_ptr<FairMQMessage> msg1(fTransportFactory->CreateMessage(buffer, 1000));
            std::unique_ptr<FairMQMessage> msg2(fTransportFactory->CreateMessage());

            if (fChannels.at("data-out").at(0).Send(msg1) == -2)
            {
                LOG(INFO) << "send canceled";
                sendCanceling = true;
            }
            else
            {
                LOG(ERROR) << "send did not cancel";
            }

            if (fChannels.at("data-in").at(0).Receive(msg2) == -2)
            {
                LOG(INFO) << "receive canceled";
                receiveCanceling = true;
            }
            else
            {
                LOG(ERROR) << "receive did not cancel";
            }

            if (sendCanceling && receiveCanceling)
            {
                LOG(INFO) << "Transfer timeout test successfull";
            }
        }
    }
};

int main(int argc, char** argv)
{
    TransferTimeoutTester timeoutTester;
    timeoutTester.CatchSignals();

#ifdef NANOMSG
    timeoutTester.SetTransport(new FairMQTransportFactoryNN());
#else
    timeoutTester.SetTransport(new FairMQTransportFactoryZMQ());
#endif

    timeoutTester.SetProperty(TransferTimeoutTester::Id, "timeoutTester");

    FairMQChannel dataOutChannel;
    dataOutChannel.UpdateType("push");
    dataOutChannel.UpdateMethod("bind");
    dataOutChannel.UpdateAddress("tcp://127.0.0.1:5559");
    dataOutChannel.UpdateSndBufSize(1000);
    dataOutChannel.UpdateRcvBufSize(1000);
    dataOutChannel.UpdateRateLogging(0);
    timeoutTester.fChannels["data-out"].push_back(dataOutChannel);

    FairMQChannel dataInChannel;
    dataInChannel.UpdateType("pull");
    dataInChannel.UpdateMethod("bind");
    dataInChannel.UpdateAddress("tcp://127.0.0.1:5560");
    dataInChannel.UpdateSndBufSize(1000);
    dataInChannel.UpdateRcvBufSize(1000);
    dataInChannel.UpdateRateLogging(0);
    timeoutTester.fChannels["data-in"].push_back(dataInChannel);

    timeoutTester.ChangeState(TransferTimeoutTester::INIT_DEVICE);
    timeoutTester.WaitForEndOfState(TransferTimeoutTester::INIT_DEVICE);

    timeoutTester.ChangeState(TransferTimeoutTester::INIT_TASK);
    timeoutTester.WaitForEndOfState(TransferTimeoutTester::INIT_TASK);

    timeoutTester.ChangeState(TransferTimeoutTester::RUN);
    timeoutTester.WaitForEndOfState(TransferTimeoutTester::RUN);

    timeoutTester.ChangeState(TransferTimeoutTester::RESET_TASK);
    timeoutTester.WaitForEndOfState(TransferTimeoutTester::RESET_TASK);

    timeoutTester.ChangeState(TransferTimeoutTester::RESET_DEVICE);
    timeoutTester.WaitForEndOfState(TransferTimeoutTester::RESET_DEVICE);

    timeoutTester.ChangeState(TransferTimeoutTester::END);

    return 0;
}
