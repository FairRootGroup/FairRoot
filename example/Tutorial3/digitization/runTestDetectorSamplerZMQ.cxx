/**
 * runTestDetectorSampler.cxx
 *
 *  @since 2013-04-29
 *  @author: A. Rybalchenko
 */

#include <iostream>
#include <csignal>

#include "FairMQLogger.h"
#include "FairMQSampler.h"
#include "zeromq/FairMQTransportFactoryZMQ.h"

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;


FairMQSampler sampler;

static void s_signal_handler (int signal)
{
  cout << endl << "Caught signal " << signal << endl;

  sampler.ChangeState(FairMQSampler::STOP);
  sampler.ChangeState(FairMQSampler::END);

  cout << "Shutdown complete. Bye!" << endl;
  exit(1);
}

static void s_catch_signals (void)
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
  if ( argc != 11 ) {
    cout << "Usage: testDetectorSampler \tID inputFile parameterFile\n"
              << "\t\tbranch eventRate numIoTreads\n"
              << "\t\toutputSocketType outputSndBufSize outputMethod outputAddress\n" << endl;
    return 1;
  }

  s_catch_signals();

  
  stringstream logmsg;
  logmsg << "PID: " << getpid();
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, logmsg.str());

  
  FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
  sampler.SetTransport(transportFactory);

  int i = 1;

  sampler.SetProperty(FairMQSampler::Id, argv[i]);
  ++i;

  sampler.SetProperty(FairMQSampler::InputFile, argv[i]);
  ++i;

  sampler.SetProperty(FairMQSampler::ParFile, argv[i]);
  ++i;

  sampler.SetProperty(FairMQSampler::Branch, argv[i]);
  ++i;

  int eventRate;
  stringstream(argv[i]) >> eventRate;
  sampler.SetProperty(FairMQSampler::EventRate, eventRate);
  ++i;

  int numIoThreads;
  stringstream(argv[i]) >> numIoThreads;
  sampler.SetProperty(FairMQSampler::NumIoThreads, numIoThreads);
  ++i;

  sampler.SetProperty(FairMQSampler::NumInputs, 0);
  sampler.SetProperty(FairMQSampler::NumOutputs, 1);

  sampler.ChangeState(FairMQSampler::INIT);

  // INPUT: 0 - command
  //sampler.SetProperty(FairMQSampler::InputSocketType, ZMQ_SUB, 0);
  //sampler.SetProperty(FairMQSampler::InputRcvBufSize, 1000, 0);
  //sampler.SetProperty(FairMQSampler::InputAddress, "tcp://localhost:5560", 0);

  // OUTPUT: 0 - data
  sampler.SetProperty(FairMQSampler::OutputSocketType, argv[i], 0);
  ++i;
  int outputSndBufSize;
  stringstream(argv[i]) >> outputSndBufSize;
  sampler.SetProperty(FairMQSampler::OutputSndBufSize, outputSndBufSize, 0);
  ++i;
  sampler.SetProperty(FairMQSampler::OutputMethod, argv[i], 0);
  ++i;
  sampler.SetProperty(FairMQSampler::OutputAddress, argv[i], 0);
  ++i;

  // OUTPUT: 1 - logger
  //sampler.SetProperty(FairMQSampler::OutputSocketType, ZMQ_PUB, 1);
  //sampler.SetProperty(FairMQSampler::OutputSndBufSize, 1000, 1);
  //sampler.SetProperty(FairMQSampler::OutputAddress, "tcp://*:5561", 1);

  sampler.ChangeState(FairMQSampler::SETOUTPUT);
  sampler.ChangeState(FairMQSampler::SETINPUT);
  sampler.ChangeState(FairMQSampler::RUN);

  //TODO: get rid of this hack!
  char ch;
  cin.get(ch);

  sampler.ChangeState(FairMQSampler::STOP);
  sampler.ChangeState(FairMQSampler::END);

  return 0;
}

