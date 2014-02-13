/**
 * runSplitter.cxx
 *
 * @since 2012-12-06
 * @author D. Klein, A. Rybalchenko
 */

#include <iostream>
#include <csignal>

#include "FairMQLogger.h"
#include "FairMQSplitter.h"
#include "FairMQTransportFactoryZMQ.h"

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;


FairMQSplitter splitter;

static void s_signal_handler (int signal)
{
  cout << endl << "Caught signal " << signal << endl;

  splitter.ChangeState(FairMQSplitter::STOP);
  splitter.ChangeState(FairMQSplitter::END);

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
  if ( argc != 15 ) {
    cout << "Usage: splitter \tID numIoTreads\n"
              << "\t\tinputSocketType inputRcvBufSize inputMethod inputAddress\n"
              << "\t\toutputSocketType outputSndBufSize outputMethod outputAddress\n"
              << "\t\toutputSocketType outputSndBufSize outputMethod outputAddress\n" << endl;
    return 1;
  }

  s_catch_signals();

  LOG(INFO) << "PID: " << getpid();

  FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
  splitter.SetTransport(transportFactory);

  int i = 1;

  splitter.SetProperty(FairMQSplitter::Id, argv[i]);
  ++i;

  int numIoThreads;
  stringstream(argv[i]) >> numIoThreads;
  splitter.SetProperty(FairMQSplitter::NumIoThreads, numIoThreads);
  ++i;

  splitter.SetProperty(FairMQSplitter::NumInputs, 1);
  splitter.SetProperty(FairMQSplitter::NumOutputs, 2);


  splitter.ChangeState(FairMQSplitter::INIT);


  splitter.SetProperty(FairMQSplitter::InputSocketType, argv[i], 0);
  ++i;
  int inputRcvBufSize;
  stringstream(argv[i]) >> inputRcvBufSize;
  splitter.SetProperty(FairMQSplitter::InputRcvBufSize, inputRcvBufSize, 0);
  ++i;
  splitter.SetProperty(FairMQSplitter::InputMethod, argv[i], 0);
  ++i;
  splitter.SetProperty(FairMQSplitter::InputAddress, argv[i], 0);
  ++i;

  splitter.SetProperty(FairMQSplitter::OutputSocketType, argv[i], 0);
  ++i;
  int outputSndBufSize;
  stringstream(argv[i]) >> outputSndBufSize;
  splitter.SetProperty(FairMQSplitter::OutputSndBufSize, outputSndBufSize, 0);
  ++i;
  splitter.SetProperty(FairMQSplitter::OutputMethod, argv[i], 0);
  ++i;
  splitter.SetProperty(FairMQSplitter::OutputAddress, argv[i], 0);
  ++i;

  splitter.SetProperty(FairMQSplitter::OutputSocketType, argv[i], 1);
  ++i;
  stringstream(argv[i]) >> outputSndBufSize;
  splitter.SetProperty(FairMQSplitter::OutputSndBufSize, outputSndBufSize, 1);
  ++i;
  splitter.SetProperty(FairMQSplitter::OutputMethod, argv[i], 1);
  ++i;
  splitter.SetProperty(FairMQSplitter::OutputAddress, argv[i], 1);
  ++i;


  splitter.ChangeState(FairMQSplitter::SETOUTPUT);
  splitter.ChangeState(FairMQSplitter::SETINPUT);
  splitter.ChangeState(FairMQSplitter::RUN);


  char ch;
  cin.get(ch);

  splitter.ChangeState(FairMQSplitter::STOP);
  splitter.ChangeState(FairMQSplitter::END);

  return 0;
}

