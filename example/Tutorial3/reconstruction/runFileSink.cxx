/*
 * runFileSink.cxx
 *
 *  Created on: Jan 21, 2013
 *      Author: dklein
 */

#include "FairMQFileSink.h"
#include <sys/types.h>
#include <unistd.h>
#include "FairMQLogger.h"
#include <zmq.hpp>
#include <stdio.h>
#include <iostream>
#include <csignal>

FairMQFileSink* filesink;

void signal_handler(int s)
{

  delete filesink;

  std::cout << "Caught signal " << s << std::endl;
  exit(1);

}

int main(int argc, char** argv)
{
  if( argc != 6 ) {
    std::cout << "Usage: fileSink \tID numIoTreads\n" <<
              "\t\tconnectSocketType connectRcvBufferSize ConnectAddress\n" << std::endl;
    return 1;
  }

  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler = signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  pid_t pid = getpid();
  std::stringstream logmsg;
  logmsg << "PID: " << pid;
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, logmsg.str());

  int i = 1;

  filesink = new FairMQFileSink();
  filesink->SetProperty(FairMQFileSink::Id, argv[i]);
  ++i;

  int numIoThreads;
  std::stringstream(argv[i]) >> numIoThreads;
  filesink->SetProperty(FairMQFileSink::NumIoThreads, numIoThreads);
  ++i;

  int numInputs = 1;
  filesink->SetProperty(FairMQFileSink::NumInputs, numInputs);

  int numOutputs = 0;
  filesink->SetProperty(FairMQFileSink::NumOutputs, numOutputs);

  filesink->Init();
  filesink->InitOutput();

  int connectSocketType = ZMQ_SUB;
  if (strcmp(argv[i], "pull") == 0) {
    connectSocketType = ZMQ_PULL;
  }
  filesink->SetProperty(FairMQFileSink::ConnectSocketType, connectSocketType, 0);
  ++i;

  int connectRcvBufferSize;
  std::stringstream(argv[i]) >> connectRcvBufferSize;
  filesink->SetProperty(FairMQFileSink::ConnectRcvBufferSize, connectRcvBufferSize, 0);
  ++i;

  filesink->SetProperty(FairMQFileSink::ConnectAddress, argv[i], 0);
  ++i;


  filesink->Bind();
  filesink->Connect();
  filesink->Run();

  exit(0);
}

