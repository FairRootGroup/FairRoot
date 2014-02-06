/*
 * runFileSink.cxx
 *
 * @since: Jan 21, 2013
 * @author: A. Rybalchenko
 */

#include <iostream>
#include <csignal>

#include "FairMQLogger.h"
#include "FairMQFileSink.h"
#include "zeromq/FairMQTransportFactoryZMQ.h"

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;


FairMQFileSink filesink;

static void s_signal_handler (int signal)
{
  cout << endl << "Caught signal " << signal << endl;

  filesink.ChangeState(FairMQFileSink::STOP);
  filesink.ChangeState(FairMQFileSink::END);

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
  if ( argc != 7 ) {
    cout << "Usage: fileSink \tID numIoTreads\n"
              << "\t\tinputSocketType inputRcvBufHSize inputMethod inputAddress\n"
              << endl;
    return 1;
  }

  s_catch_signals();

  stringstream logmsg;
  logmsg << "PID: " << getpid();
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, logmsg.str());

  FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
  filesink.SetTransport(transportFactory);

  int i = 1;

  filesink.SetProperty(FairMQFileSink::Id, argv[i]);
  ++i;

  int numIoThreads;
  stringstream(argv[i]) >> numIoThreads;
  filesink.SetProperty(FairMQFileSink::NumIoThreads, numIoThreads);
  ++i;

  filesink.SetProperty(FairMQFileSink::NumInputs, 1);
  filesink.SetProperty(FairMQFileSink::NumOutputs, 0);

  filesink.ChangeState(FairMQFileSink::INIT);
  filesink.InitOutputFile(argv[1]);


  filesink.SetProperty(FairMQFileSink::InputSocketType, argv[i], 0);
  ++i;
  int inputRcvBufSize;
  stringstream(argv[i]) >> inputRcvBufSize;
  filesink.SetProperty(FairMQFileSink::InputRcvBufSize, inputRcvBufSize, 0);
  ++i;
  filesink.SetProperty(FairMQFileSink::InputMethod, argv[i], 0);
  ++i;
  filesink.SetProperty(FairMQFileSink::InputAddress, argv[i], 0);
  ++i;


  filesink.ChangeState(FairMQFileSink::SETOUTPUT);
  filesink.ChangeState(FairMQFileSink::SETINPUT);
  filesink.ChangeState(FairMQFileSink::RUN);

  char ch;
  cin.get(ch);

  filesink.ChangeState(FairMQFileSink::STOP);
  filesink.ChangeState(FairMQFileSink::END);

  return 0;
}

