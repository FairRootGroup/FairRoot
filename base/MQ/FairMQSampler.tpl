/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSampler.tpl
 *
 * @since 2012-09-27
 * @author D. Klein, A. Rybalchenko, N. Winckler
 */

template <typename Loader>
FairMQSampler<Loader>::FairMQSampler() :
  fFairRunAna(new FairRunAna()),
  fSamplerTask(new Loader()),
  fNumEvents(0),
  fEventRate(1),
  fEventCounter(0),
  fContinuous(false)
{
}


template <typename Loader>
FairMQSampler<Loader>::~FairMQSampler()
{
  if(fFairRunAna) fFairRunAna->TerminateRun();
  delete fSamplerTask;
}

template <typename Loader>
void FairMQSampler<Loader>::Init()
{
  FairMQDevice::Init();

  fSamplerTask->SetBranch(fBranch);
  fSamplerTask->SetTransport(fTransportFactory);
  // Set the callback for the Sampler Task for sending multipart messages.
  fSamplerTask->SetSendPart(boost::bind(&FairMQSampler::SendPart, this));

  fFairRunAna->SetInputFile(TString(fInputFile));
  // This loop can be used to duplicate input file to get more data. The output will still be a single file.
  for (int i = 0; i < 0; ++i) {
    fFairRunAna->AddFile(fInputFile);
  }

  TString output = fInputFile;
  output.Append(".out.root");
  fFairRunAna->SetOutputFile(output.Data());

  fFairRunAna->AddTask(fSamplerTask);

  FairRuntimeDb *rtdb = fFairRunAna->GetRuntimeDb();
  FairParRootFileIo *parInput1 = new FairParRootFileIo();
  parInput1->open(TString(fParFile).Data());
  rtdb->setFirstInput(parInput1);
  rtdb->print();

  fFairRunAna->Init();
  // fFairRunAna->Run(0, 0);
  FairRootManager *ioman = FairRootManager::Instance();
  fNumEvents = int((ioman->GetInChain())->GetEntries());
}

template <typename Loader>
void FairMQSampler<Loader>::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));
  // boost::thread resetEventCounter(boost::bind(&FairMQSampler::ResetEventCounter, this));
  // boost::thread commandListener(boost::bind(&FairMQSampler::ListenToCommands, this));

  int sentMsgs = 0;

  boost::timer::auto_cpu_timer timer;

  LOG(INFO) << "Number of events to process: " << fNumEvents;

//  while ( fState == RUNNING ) {

  do {
    for ( Long64_t eventNr = 0 ; eventNr < fNumEvents; ++eventNr ) {
      fSamplerTask->SetEventIndex(eventNr);
      fFairRunAna->RunMQ(eventNr);

      fPayloadOutputs->at(0)->Send(fSamplerTask->GetOutput());
      ++sentMsgs;

      fSamplerTask->GetOutput()->CloseMessage();

      // Optional event rate limiting
      // --fEventCounter;
      // while (fEventCounter == 0) {
      //   boost::this_thread::sleep(boost::posix_time::milliseconds(1));
      // }

      if( fState != RUNNING ) { break; }
    }
  } while ( fState == RUNNING && fContinuous );

//  }

  boost::timer::cpu_times const elapsed_time(timer.elapsed());
  LOG(INFO) << "Sent everything in:\n" << boost::timer::format(elapsed_time, 2);
  LOG(INFO) << "Sent " << sentMsgs << " messages!";

  try {
    rateLogger.interrupt();
    rateLogger.join();
    // resetEventCounter.interrupt();
    // resetEventCounter.join();
    // commandListener.interrupt();
    // commandListener.join();
  }
  catch (boost::thread_resource_error &e) {
    LOG(ERROR) << e.what();
  }

  FairMQDevice::Shutdown();

  // notify parent thread about end of processing.
  boost::lock_guard<boost::mutex> lock(fRunningMutex);
  fRunningFinished = true;
  fRunningCondition.notify_one();
}

template <typename Loader>
void FairMQSampler<Loader>::SendPart()
{
  fPayloadOutputs->at(0)->Send(fSamplerTask->GetOutput(), "snd-more");
  fSamplerTask->GetOutput()->CloseMessage();
}

template <typename Loader>
void FairMQSampler<Loader>::ResetEventCounter()
{
  while (true) {
    try {
      fEventCounter = fEventRate / 100;
      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    }
    catch (boost::thread_interrupted &) {
      LOG(DEBUG) << "resetEventCounter interrupted";
      break;
    }
  }
  LOG(DEBUG) << ">>>>>>> stopping resetEventCounter <<<<<<<";
}

template <typename Loader>
void FairMQSampler<Loader>::ListenToCommands()
{
  LOG(INFO) << ">>>>>>> ListenToCommands <<<<<<<";

  int received = 0;

  while (true) {
    try {
      FairMQMessage *msg = fTransportFactory->CreateMessage();

      received = fPayloadInputs->at(0)->Receive(msg);

      if (received > 0) {
        // command handling goes here.
        LOG(INFO) << "> received command <";
        received = 0;
      }

      delete msg;

      boost::this_thread::interruption_point();
    }
    catch (boost::thread_interrupted &) {
      LOG(DEBUG) << "commandListener interrupted";
      break;
    }
  }
  LOG(DEBUG) << ">>>>>>> stopping commandListener <<<<<<<";
}

template <typename Loader>
void FairMQSampler<Loader>::SetProperty(const int key, const string& value, const int slot/*= 0*/)
{
  switch (key)
  {
    case InputFile:
      fInputFile = value;
      break;
    case ParFile:
      fParFile = value;
      break;
    case Branch:
      fBranch = value;
      break;
    default:
      FairMQDevice::SetProperty(key, value, slot);
      break;
  }
}

template <typename Loader>
string FairMQSampler<Loader>::GetProperty(const int key, const string& default_/*= ""*/, const int slot/*= 0*/)
{
  switch (key)
  {
    case InputFile:
      return fInputFile;
    case ParFile:
      return fParFile;
    case Branch:
      return fBranch;
    default:
      return FairMQDevice::GetProperty(key, default_, slot);
  }
}

template <typename Loader>
void FairMQSampler<Loader>::SetProperty(const int key, const int value, const int slot/*= 0*/)
{
  switch (key)
  {
    case EventRate:
      fEventRate = value;
      break;
    default:
      FairMQDevice::SetProperty(key, value, slot);
      break;
  }
}

template <typename Loader>
int FairMQSampler<Loader>::GetProperty(const int key, const int default_/*= 0*/, const int slot/*= 0*/)
{
  switch (key)
  {
    case EventRate:
      return fEventRate;
    default:
      return FairMQDevice::GetProperty(key, default_, slot);
  }
}
