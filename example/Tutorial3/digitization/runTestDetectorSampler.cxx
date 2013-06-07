/**
 * runTestDetectorSampler.cxx
 *
 *  @since 2013-04-29
 *  @author: A. Rybalchenko
 */

#include "TestDetectorMQSampler.h"
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include "FairMQLogger.h"
#include <zmq.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv)
{
  if( argc != 10 ) {
    std::cout << "Usage: testDetectorSampler \tID inputFile parameterFile\n" <<
              "\t\tbranch eventRate numIoTreads\n" <<
              "\t\tbindSocketType bindSndBufferSize BindAddress\n" << std::endl;
    return 1;
  }

  pid_t pid = getpid();
  std::stringstream logmsg;
  logmsg << "PID: " << pid;
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, logmsg.str());

  int i = 1;

  TestDetectorMQSampler* sampler = new TestDetectorMQSampler();

  sampler->SetProperty(TestDetectorMQSampler::Id, argv[i]);
  ++i;

  sampler->SetProperty(TestDetectorMQSampler::InputFile, argv[i]);
  ++i;

  sampler->SetProperty(TestDetectorMQSampler::ParFile, argv[i]);
  ++i;

  sampler->SetProperty(TestDetectorMQSampler::Branch, argv[i]);
  ++i;

  int eventRate;
  std::stringstream(argv[i]) >> eventRate;
  sampler->SetProperty(TestDetectorMQSampler::EventRate, eventRate);
  ++i;

  int numIoThreads;
  std::stringstream(argv[i]) >> numIoThreads;
  sampler->SetProperty(TestDetectorMQSampler::NumIoThreads, numIoThreads);
  ++i;

  int numInputs = 0;
  sampler->SetProperty(TestDetectorMQSampler::NumInputs, numInputs);

  int numOutputs = 1;
  sampler->SetProperty(TestDetectorMQSampler::NumOutputs, numOutputs);

  sampler->Init();

  int bindSocketType = ZMQ_PUB;
  if (strcmp(argv[i], "push") == 0) {
    bindSocketType = ZMQ_PUSH;
  }
  sampler->SetProperty(TestDetectorMQSampler::BindSocketType, bindSocketType, 0);
  ++i;

  int bindSndBufferSize;
  std::stringstream(argv[i]) >> bindSndBufferSize;
  sampler->SetProperty(TestDetectorMQSampler::BindSndBufferSize, bindSndBufferSize, 0);
  ++i;

  sampler->SetProperty(TestDetectorMQSampler::BindAddress, argv[i], 0);
  ++i;


  sampler->Bind();
  sampler->Connect();
  sampler->Run();

  exit(0);
}

