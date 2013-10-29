/*
 * runTestDetectorProcessor.cxx
 *
 *  Created on: Oct 26, 2012
 *      Author: dklein
 */

#include <iostream>
#include <csignal>

#include "FairMQLogger.h"
#include "FairMQProcessor.h"
#include "FairTestDetectorMQRecoTask.h"

FairMQProcessor processor;

static void s_signal_handler (int signal)
{
  std::cout << std::endl << "Caught signal " << signal << std::endl;

  processor.ChangeState(FairMQProcessor::STOP);
  processor.ChangeState(FairMQProcessor::END);

  std::cout << "Shutdown complete. Bye!" << std::endl;
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
  if ( argc != 12 ) {
    std::cout << "Usage: testDetectorProcessor \tID processorTask numIoTreads\n"
              << "\t\tinputSocketType inputRcvBufSize inputMethod inputAddress\n"
              << "\t\toutputSocketType outputSndBufSize outputMethod outputAddress\n" << std::endl;
    return 1;
  }

  s_catch_signals();

  std::stringstream logmsg;
  logmsg << "PID: " << getpid();
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, logmsg.str());

  int i = 1;

  processor.SetProperty(FairMQProcessor::Id, argv[i]);
  ++i;

  if (strcmp(argv[i], "FairTestDetectorMQRecoTask") == 0) {
    FairMQProcessorTask* task = new FairTestDetectorMQRecoTask();
    processor.SetTask(task);
  } else {
    FairMQLogger::GetInstance()->Log(FairMQLogger::ERROR, "task not supported.");
    exit(1);
  }
  ++i;

  int numIoThreads;
  std::stringstream(argv[i]) >> numIoThreads;
  processor.SetProperty(FairMQProcessor::NumIoThreads, numIoThreads);
  ++i;

  processor.SetProperty(FairMQProcessor::NumInputs, 1);
  processor.SetProperty(FairMQProcessor::NumOutputs, 1);


  processor.ChangeState(FairMQProcessor::INIT);


  int inputSocketType = ZMQ_SUB;
  if (strcmp(argv[i], "pull") == 0) {
    inputSocketType = ZMQ_PULL;
  }
  processor.SetProperty(FairMQProcessor::InputSocketType, inputSocketType, 0);
  ++i;
  int inputRcvBufSize;
  std::stringstream(argv[i]) >> inputRcvBufSize;
  processor.SetProperty(FairMQProcessor::InputRcvBufSize, inputRcvBufSize, 0);
  ++i;
  processor.SetProperty(FairMQProcessor::InputMethod, argv[i], 0);
  ++i;
  processor.SetProperty(FairMQProcessor::InputAddress, argv[i], 0);
  ++i;

  int outputSocketType = ZMQ_PUB;
  if (strcmp(argv[i], "push") == 0) {
    outputSocketType = ZMQ_PUSH;
  }
  processor.SetProperty(FairMQProcessor::OutputSocketType, outputSocketType, 0);
  ++i;
  int outputSndBufSize;
  std::stringstream(argv[i]) >> outputSndBufSize;
  processor.SetProperty(FairMQProcessor::OutputSndBufSize, outputSndBufSize, 0);
  ++i;
  processor.SetProperty(FairMQProcessor::OutputMethod, argv[i], 0);
  ++i;
  processor.SetProperty(FairMQProcessor::OutputAddress, argv[i], 0);
  ++i;


  processor.ChangeState(FairMQProcessor::SETOUTPUT);
  processor.ChangeState(FairMQProcessor::SETINPUT);
  processor.ChangeState(FairMQProcessor::RUN);


  char ch;
  std::cin.get(ch);

  processor.ChangeState(FairMQProcessor::STOP);
  processor.ChangeState(FairMQProcessor::END);

  return 0;
}

