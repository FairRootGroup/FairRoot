/* 
 * File:   FairMQSampler.tpl
 * Author: winckler
 *
 * Created on February 7, 2014, 6:21 PM
 */



template <typename Loader>
FairMQSampler<Loader>::FairMQSampler() :
  fFairRunAna(new FairRunAna()),
  fSamplerTask(new Loader()),
  fInputFile(""),
  fParFile(""),
  fBranch(""),
  fNumEvents(0),
  fEventRate(1),
  fEventCounter(0)
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

  fFairRunAna->SetInputFile(TString(fInputFile));
  // This loop can be used to duplicate input file to get more data. The output will still be a single file.
  for (int i = 0; i < 4; ++i)
  {
    fFairRunAna->AddFile(fInputFile);
  }

  TString output = fInputFile;
  output.Append(".out.root");
  fFairRunAna->SetOutputFile(output.Data());

  fFairRunAna->AddTask(fSamplerTask);

  FairRuntimeDb* rtdb = fFairRunAna->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(TString(fParFile).Data());
  rtdb->setFirstInput(parInput1);
  rtdb->print();

  fFairRunAna->Init();
  //fFairRunAna->Run(0, 0);
  FairRootManager* ioman = FairRootManager::Instance();
  fNumEvents = int((ioman->GetInChain())->GetEntries());
}

template <typename Loader>
void FairMQSampler<Loader>::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));
  boost::thread resetEventCounter(boost::bind(&FairMQSampler::ResetEventCounter, this));
  //boost::thread commandListener(boost::bind(&FairMQSampler::ListenToCommands, this));

  int sentMsgs = 0;

  boost::timer::auto_cpu_timer timer;

  LOG(INFO) << "Number of events to process: " << fNumEvents;

  Long64_t eventNr = 0;

//  while ( fState == RUNNING ) {

  for ( /* eventNr */ ; eventNr < fNumEvents; eventNr++ ) {
    fSamplerTask->SetEventIndex(eventNr);
    fFairRunAna->RunMQ(eventNr);

    fPayloadOutputs->at(0)->Send(fSamplerTask->GetOutput());
    sentMsgs++;

    --fEventCounter;

    while (fEventCounter == 0) {
      boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }

    if( fState != RUNNING ) { break; }
  }

  boost::this_thread::interruption_point();
//  }

  boost::timer::cpu_times const elapsed_time(timer.elapsed());

  LOG(INFO) << "Sent everything in:\n" << boost::timer::format(elapsed_time, 2);
  LOG(INFO) << "Sent " << sentMsgs << " messages!";

  try {
    rateLogger.interrupt();
    rateLogger.join();
    resetEventCounter.interrupt();
    resetEventCounter.join();
    //commandListener.interrupt();
    //commandListener.join();
  } catch(boost::thread_resource_error& e) {
    LOG(ERROR) << e.what();
  }
}

template <typename Loader>
void FairMQSampler<Loader>::ResetEventCounter()
{
  while ( true ) {
    try {
      fEventCounter = fEventRate / 100;
      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    } catch (boost::thread_interrupted&) {
      cout << "resetEventCounter interrupted" << endl;
      break;
    }
  }
  LOG(DEBUG) << ">>>>>>> stopping resetEventCounter <<<<<<<";
}

template <typename Loader>
void FairMQSampler<Loader>::ListenToCommands()
{
  LOG(INFO) << ">>>>>>> ListenToCommands <<<<<<<";

  bool received = false;

  while ( true ) {
    try {
      FairMQMessage* msg = fTransportFactory->CreateMessage();

      received = fPayloadInputs->at(0)->Receive(msg);

      if (received) {
        //command handling goes here.
        LOG(INFO) << "> received command <";
        received = false;
      }

      delete msg;

      boost::this_thread::interruption_point();
    } catch (boost::thread_interrupted&) {
      cout << "commandListener interrupted" << endl;
      break;
    }
  }
  LOG(DEBUG) << ">>>>>>> stopping commandListener <<<<<<<";
}

template <typename Loader>
void FairMQSampler<Loader>::SetProperty(const int key, const string& value, const int slot/*= 0*/)
{
  switch (key) {
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
  switch (key) {
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
  switch (key) {
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
  switch (key) {
  case EventRate:
    return fEventRate;
  default:
    return FairMQDevice::GetProperty(key, default_, slot);
  }
}


