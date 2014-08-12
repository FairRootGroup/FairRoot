/**
 * runBenchmarkflp.cxx
 *
 * @since 2013-04-23
 * @author D. Klein, A. Rybalchenko
 */

#include <iostream>
#include <csignal>

#include "FairMQLogger.h"
#include "O2FLPex.h"

#ifdef NANOMSG
  #include "FairMQTransportFactoryNN.h"
#else
  #include "FairMQTransportFactoryZMQ.h"
#endif

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;


O2FLPex flp;

static void s_signal_handler (int signal)
{
  cout << endl << "Caught signal " << signal << endl;

  flp.ChangeState(O2FLPex::STOP);
  flp.ChangeState(O2FLPex::END);

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
  LOG(INFO) << "-> " << argc;
  
  if ( argc < 15 ) {
    cout << "Usage: testFLP ID eventSize eventRate numIoTreads numOutputs heartbeatTimeoutInMs\n"
              << "\t\tinputSocketType inputSndBufSize inputMethod inputAddress\n"
              << "\t\toutputSocketType outputSndBufSize outputMethod outputAddress\n"
              << "\t\t...\n"
              << endl;
    return 1;
  }

  s_catch_signals();

  LOG(INFO) << "PID: " << getpid();

#ifdef NANOMSG
  FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
  FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

  flp.SetTransport(transportFactory);

  int i = 1;

  flp.SetProperty(O2FLPex::Id, argv[i]);
  ++i;

  int eventSize;
  stringstream(argv[i]) >> eventSize;
  flp.SetProperty(O2FLPex::EventSize, eventSize);
  ++i;

  int eventRate;
  stringstream(argv[i]) >> eventRate;
  flp.SetProperty(O2FLPex::EventRate, eventRate);
  ++i;

  int numIoThreads;
  stringstream(argv[i]) >> numIoThreads;
  flp.SetProperty(O2FLPex::NumIoThreads, numIoThreads);
  ++i;
  
  flp.SetProperty(O2FLPex::NumInputs, 1);
  
  int numOutputs;
  stringstream(argv[i]) >> numOutputs;
  flp.SetProperty(O2FLPex::NumOutputs, numOutputs);
  ++i;

  int heartbeatTimeoutInMs;
  stringstream(argv[i]) >> heartbeatTimeoutInMs;
  flp.SetProperty(O2FLPex::HeartbeatTimeoutInMs, heartbeatTimeoutInMs);
  ++i;

  flp.ChangeState(O2FLPex::INIT);
  
  flp.SetProperty(O2FLPex::InputSocketType, argv[i], 0);
  ++i;
  int inputSndBufSize;
  stringstream(argv[i]) >> inputSndBufSize;
  flp.SetProperty(O2FLPex::InputSndBufSize, inputSndBufSize, 0);
  ++i;
  flp.SetProperty(O2FLPex::InputMethod, argv[i], 0);
  ++i;
  flp.SetProperty(O2FLPex::InputAddress, argv[i], 0);
  ++i;

  for (int iOutput = 0; iOutput < numOutputs; iOutput++ ) {
    flp.SetProperty(O2FLPex::OutputSocketType, argv[i], iOutput);
    ++i;
    int outputSndBufSize;
    stringstream(argv[i]) >> outputSndBufSize;
    flp.SetProperty(O2FLPex::OutputSndBufSize, outputSndBufSize, iOutput);
    ++i;
    flp.SetProperty(O2FLPex::OutputMethod, argv[i], iOutput);
    ++i;
    flp.SetProperty(O2FLPex::OutputAddress, argv[i], iOutput);
    ++i;
  }

  flp.ChangeState(O2FLPex::SETOUTPUT);
  flp.ChangeState(O2FLPex::SETINPUT);
  flp.ChangeState(O2FLPex::RUN);

  char ch;
  cin.get(ch);

  flp.ChangeState(O2FLPex::STOP);
  flp.ChangeState(O2FLPex::END);

  return 0;
}
