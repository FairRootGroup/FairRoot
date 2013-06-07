/*
 * runTestDetectorProcessor.cxx
 *
 *  Created on: Oct 26, 2012
 *      Author: dklein
 */

#include "FairMQProcessor.h"
#include "FairTestDetectorMQRecoTask.h"
#include "FairMQLogger.h"
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <zmq.hpp>
#include <stdio.h>
#include <iostream>
#include <csignal>

FairMQProcessor* processor;

void signal_handler(int s)
{

  delete processor;

  std::cout << "Caught signal " << s << std::endl;
  exit(1);

}


int main(int argc, char** argv)
{
  if( argc != 10 ) {
    std::cout << "Usage: testDetectorProcessor \tID processorTask numIoTreads\n" <<
              "\t\tconnectSocketType connectRcvBufferSize ConnectAddress\n" <<
              "\t\tbindSocketType bindSndBufferSize BindAddress\n" << std::endl;
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

  processor = new FairMQProcessor();
  processor->SetProperty(FairMQProcessor::Id, argv[i]);
  ++i;

  if (std::string(argv[i]) == "FairTestDetectorMQRecoTask") {
    FairMQProcessorTask* task = new FairTestDetectorMQRecoTask();
    processor->SetTask(task);
  } else {
    FairMQLogger::GetInstance()->Log(FairMQLogger::ERROR, "task not supported.");
    exit(1);
  }
  ++i;

  int numIoThreads;
  std::stringstream(argv[i]) >> numIoThreads;
  processor->SetProperty(FairMQProcessor::NumIoThreads, numIoThreads);
  ++i;

  int numInputs = 1;
  processor->SetProperty(FairMQProcessor::NumInputs, numInputs);

  int numOutputs = 1;
  processor->SetProperty(FairMQProcessor::NumOutputs, numOutputs);

  processor->Init();

  int connectSocketType = ZMQ_SUB;
  if (strcmp(argv[i], "pull") == 0) {
    connectSocketType = ZMQ_PULL;
  }
  processor->SetProperty(FairMQProcessor::ConnectSocketType, connectSocketType, 0);
  ++i;

  int connectRcvBufferSize;
  std::stringstream(argv[i]) >> connectRcvBufferSize;
  processor->SetProperty(FairMQProcessor::ConnectRcvBufferSize, connectRcvBufferSize, 0);
  ++i;

  processor->SetProperty(FairMQProcessor::ConnectAddress, argv[i], 0);
  ++i;

  int bindSocketType = ZMQ_PUB;
  if (strcmp(argv[i], "push") == 0) {
    bindSocketType = ZMQ_PUSH;
  }
  processor->SetProperty(FairMQProcessor::BindSocketType, bindSocketType, 0);
  ++i;

  int bindSndBufferSize;
  std::stringstream(argv[i]) >> bindSndBufferSize;
  processor->SetProperty(FairMQProcessor::BindSndBufferSize, bindSndBufferSize, 0);
  ++i;

  processor->SetProperty(FairMQProcessor::BindAddress, argv[i], 0);
  ++i;


  processor->Bind();
  processor->Connect();
  processor->Run();


  exit(0);
}

