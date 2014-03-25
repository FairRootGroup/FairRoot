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
#include "FairTestDetectorHit.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

//typedef TestDetectorPayload::TestDetectorHit TPayloadIn;
typedef boost::archive::binary_iarchive TPayloadIn;   // binary format
//typedef boost::archive::text_iarchive TPayloadIn;       // text format
typedef FairTestDetectorHit THit;
typedef FairMQFileSink<THit,TPayloadIn> TMQFileSink;

//FairMQFileSink filesink;
TMQFileSink filesink;

static void s_signal_handler (int signal)
{
  cout << endl << "Caught signal " << signal << endl;

  filesink.ChangeState(TMQFileSink::STOP);
  filesink.ChangeState(TMQFileSink::END);

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

  LOG(INFO) << "PID: " << getpid();

  FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
  filesink.SetTransport(transportFactory);

  int i = 1;

  filesink.SetProperty(TMQFileSink::Id, argv[i]);
  ++i;

  int numIoThreads;
  stringstream(argv[i]) >> numIoThreads;
  filesink.SetProperty(TMQFileSink::NumIoThreads, numIoThreads);
  ++i;

  filesink.SetProperty(TMQFileSink::NumInputs, 1);
  filesink.SetProperty(TMQFileSink::NumOutputs, 0);

  filesink.ChangeState(TMQFileSink::INIT);
  filesink.InitOutputFile(argv[1]);


  filesink.SetProperty(TMQFileSink::InputSocketType, argv[i], 0);
  ++i;
  int inputRcvBufSize;
  stringstream(argv[i]) >> inputRcvBufSize;
  filesink.SetProperty(TMQFileSink::InputRcvBufSize, inputRcvBufSize, 0);
  ++i;
  filesink.SetProperty(TMQFileSink::InputMethod, argv[i], 0);
  ++i;
  filesink.SetProperty(TMQFileSink::InputAddress, argv[i], 0);
  ++i;


  filesink.ChangeState(TMQFileSink::SETOUTPUT);
  filesink.ChangeState(TMQFileSink::SETINPUT);
  filesink.ChangeState(TMQFileSink::RUN);

  char ch;
  cin.get(ch);

  filesink.ChangeState(TMQFileSink::STOP);
  filesink.ChangeState(TMQFileSink::END);

  return 0;
}

