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
FairMQSampler<Loader>::FairMQSampler()
    : fFairRunAna(new FairRunAna())
    , fSamplerTask(new Loader())
    , fInputFile()
    , fParFile()
    , fBranch()
    , fNumEvents(0)
    , fEventRate(1)
    , fEventCounter(0)
    , fContinuous(false)
{
}

template <typename Loader>
FairMQSampler<Loader>::~FairMQSampler()
{
    if (fFairRunAna)
    {
        fFairRunAna->TerminateRun();
    }
    delete fSamplerTask;
}

template <typename Loader>
void FairMQSampler<Loader>::InitTask()
{
    LOG(INFO) << "Starting task initialization";
    fSamplerTask->SetBranch(fBranch);
    fSamplerTask->SetTransport(fTransportFactory);

    // Set the callback for the Sampler Task for sending multipart messages.
    fSamplerTask->SetSendPart(boost::bind(&FairMQSampler::SendPart, this));

    fFairRunAna->SetInputFile(TString(fInputFile));
    // This loop can be used to duplicate input file to get more data. The output will still be a single file.
    for (int i = 0; i < 10; ++i) {
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
    LOG(INFO) << "Finished task initialization";
}

template <typename Loader>
void FairMQSampler<Loader>::Run()
{
    // boost::thread resetEventCounter(boost::bind(&FairMQSampler::ResetEventCounter, this));

    int sentMsgs = 0;

    boost::timer::auto_cpu_timer timer;

    LOG(INFO) << "Number of events to process: " << fNumEvents;

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataOutChannel = fChannels.at("data-out").at(0);

    do
    {
        for (Long64_t eventNr = 0; eventNr < fNumEvents; ++eventNr)
        {
            fSamplerTask->SetEventIndex(eventNr);
            fFairRunAna->RunMQ(eventNr);

            dataOutChannel.Send(fSamplerTask->GetOutput());
            ++sentMsgs;

            fSamplerTask->GetOutput()->CloseMessage();

            // Optional event rate limiting
            // --fEventCounter;
            // while (fEventCounter == 0) {
            //   boost::this_thread::sleep(boost::posix_time::milliseconds(1));
            // }

            if (!CheckCurrentState(RUNNING))
            {
                break;
            }
        }
    } while (CheckCurrentState(RUNNING) && fContinuous);

    boost::timer::cpu_times const elapsedTime(timer.elapsed());
    LOG(INFO) << "Sent everything in:\n" << boost::timer::format(elapsedTime, 2);
    LOG(INFO) << "Sent " << sentMsgs << " messages!";
}

template <typename Loader>
void FairMQSampler<Loader>::SendPart()
{
    fChannels.at("data-out").at(0).Send(fSamplerTask->GetOutput(), "snd-more");
    fSamplerTask->GetOutput()->CloseMessage();
}

template <typename Loader>
void FairMQSampler<Loader>::SetContinuous(bool flag)
{
    fContinuous = flag;
}

template <typename Loader>
void FairMQSampler<Loader>::ResetEventCounter()
{
    while (true)
    {
        try
        {
            fEventCounter = fEventRate / 100;
            boost::this_thread::sleep(boost::posix_time::milliseconds(10));
        }
        catch (boost::thread_interrupted &)
        {
            LOG(DEBUG) << "resetEventCounter interrupted";
            break;
        }
    }
    LOG(DEBUG) << ">>>>>>> stopping resetEventCounter <<<<<<<";
}

template <typename Loader>
void FairMQSampler<Loader>::SetProperty(const int key, const std::string& value)
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
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

template <typename Loader>
std::string FairMQSampler<Loader>::GetProperty(const int key, const std::string& default_/*= ""*/)
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
            return FairMQDevice::GetProperty(key, default_);
    }
}

template <typename Loader>
void FairMQSampler<Loader>::SetProperty(const int key, const int value)
{
    switch (key)
    {
        case EventRate:
            fEventRate = value;
            break;
        default:
            FairMQDevice::SetProperty(key, value);
            break;
  }
}

template <typename Loader>
int FairMQSampler<Loader>::GetProperty(const int key, const int default_/*= 0*/)
{
    switch (key)
    {
        case EventRate:
            return fEventRate;
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

template <typename Loader>
std::string FairMQSampler<Loader>::GetPropertyDescription(const int key)
{
    switch (key)
    {
        case InputFile:
            return "InputFile: Input ROOT file.";
        case ParFile:
            return "ParFile: Input Parameter file.";
        case Branch:
            return "Branch: Name of the Branch (e.g. FairTestDetectorDigi).";
        case EventRate:
            return "EventRate: Upper limit for the message rate.";
        default:
            return FairMQDevice::GetPropertyDescription(key);
    }
}

template <typename Loader>
void FairMQSampler<Loader>::ListProperties()
{
    LOG(INFO) << "Properties of FairMQSampler:";
    for (int p = FairMQConfigurable::Last; p < FairMQSampler::Last; ++p)
    {
        LOG(INFO) << " " << GetPropertyDescription(p);
    }
    LOG(INFO) << "---------------------------";
}
