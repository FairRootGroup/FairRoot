/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runTestDetectorSamplerBin.cxx
 *
 * @since 2013-04-29
 * @author A. Rybalchenko, N. Winckler
 */

#include <iostream>
#include <csignal>

#include "FairMQLogger.h"
#include "FairMQSampler.h"

#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif

#include "TestDetectorDigiLoader.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorDigi.h"

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

typedef FairTestDetectorDigi TDigi;            // class to serialize/deserialize
typedef TestDetectorPayload::Digi TPayloadOut; // binary payload
typedef TestDetectorDigiLoader<TDigi, TPayloadOut> TLoader;

FairMQSampler<TLoader> sampler;

static void s_signal_handler(int signal)
{
    cout << endl << "Caught signal " << signal << endl;

    sampler.ChangeState(FairMQSampler<TLoader>::STOP);
    sampler.ChangeState(FairMQSampler<TLoader>::END);

    cout << "Shutdown complete. Bye!" << endl;
    exit(1);
}

static void s_catch_signals(void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

int main(int argc, char** argv)
{
    if (argc != 11)
    {
        cout << "Usage: testDetectorSampler \tID inputFile parameterFile\n"
             << "\t\tbranch eventRate numIoTreads\n"
             << "\t\toutputSocketType outputSndBufSize outputMethod outputAddress\n" << endl;
        return 1;
    }

    s_catch_signals();

    LOG(INFO) << "PID: " << getpid();

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    sampler.SetTransport(transportFactory);

    int i = 1;

    sampler.SetProperty(FairMQSampler<TLoader>::Id, argv[i]);
    ++i;

    sampler.SetProperty(FairMQSampler<TLoader>::InputFile, argv[i]);
    ++i;

    sampler.SetProperty(FairMQSampler<TLoader>::ParFile, argv[i]);
    ++i;

    sampler.SetProperty(FairMQSampler<TLoader>::Branch, argv[i]);
    ++i;

    int eventRate;
    stringstream(argv[i]) >> eventRate;
    sampler.SetProperty(FairMQSampler<TLoader>::EventRate, eventRate);
    ++i;

    int numIoThreads;
    stringstream(argv[i]) >> numIoThreads;
    sampler.SetProperty(FairMQSampler<TLoader>::NumIoThreads, numIoThreads);
    ++i;

    sampler.SetProperty(FairMQSampler<TLoader>::NumInputs, 0);
    sampler.SetProperty(FairMQSampler<TLoader>::NumOutputs, 1);

    sampler.ChangeState(FairMQSampler<TLoader>::INIT);

    // INPUT: 0 - command
    // sampler.SetProperty(FairMQSampler::InputSocketType, ZMQ_SUB, 0);
    // sampler.SetProperty(FairMQSampler::InputRcvBufSize, 1000, 0);
    // sampler.SetProperty(FairMQSampler::InputAddress, "tcp://localhost:5560", 0);

    // OUTPUT: 0 - data
    sampler.SetProperty(FairMQSampler<TLoader>::OutputSocketType, argv[i], 0);
    ++i;
    int outputSndBufSize;
    stringstream(argv[i]) >> outputSndBufSize;
    sampler.SetProperty(FairMQSampler<TLoader>::OutputSndBufSize, outputSndBufSize, 0);
    ++i;
    sampler.SetProperty(FairMQSampler<TLoader>::OutputMethod, argv[i], 0);
    ++i;
    sampler.SetProperty(FairMQSampler<TLoader>::OutputAddress, argv[i], 0);
    ++i;

    // OUTPUT: 1 - logger
    // sampler.SetProperty(FairMQSampler::OutputSocketType, ZMQ_PUB, 1);
    // sampler.SetProperty(FairMQSampler::OutputSndBufSize, 1000, 1);
    // sampler.SetProperty(FairMQSampler::OutputAddress, "tcp://*:5561", 1);

    sampler.ChangeState(FairMQSampler<TLoader>::SETOUTPUT);
    sampler.ChangeState(FairMQSampler<TLoader>::SETINPUT);
    // sampler.ChangeState(FairMQSampler<TLoader>::RUN);

    try
    {
        sampler.ChangeState(FairMQSampler<TLoader>::RUN);
    }
    catch (boost::archive::archive_exception e)
    {
        LOG(ERROR) << e.what();
    }
    // TODO: get rid of this hack!
    char ch;
    cin.get(ch);

    sampler.ChangeState(FairMQSampler<TLoader>::STOP);
    sampler.ChangeState(FairMQSampler<TLoader>::END);

    return 0;
}
