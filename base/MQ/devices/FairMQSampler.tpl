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
    , fTimer(nullptr)
    , fInputFile()
    , fParFile()
    , fBranch()
    , fNumEvents(0)
    , fChainInput(0)
    , fEventRate(1)
    , fEventCounter(0)
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
    LOG(INFO) << "Initializing Task...";

    fSamplerTask->SetBranch(fBranch);
    fSamplerTask->SetTransport(fTransportFactory);

    FairFileSource* source = new FairFileSource(TString(fInputFile));
    // Adds the same file to the input. The output will still be a single file.
    for (int i = 0; i < fChainInput; ++i)
    {
        source->AddFile(fInputFile);
    }

    fFairRunAna->SetSource(source);

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
    // fFairRunAna->Run(0, 0);
    FairRootManager *ioman = FairRootManager::Instance();
    fNumEvents = int((ioman->GetInChain())->GetEntries());

    LOG(INFO) << "Task initialized.";
}

template <typename Loader>
void FairMQSampler<Loader>::Run()
{
    boost::thread ackListener(boost::bind(&FairMQSampler::ListenForAcks, this));

    int sentMsgs = 0;

    LOG(INFO) << "Number of events to process: " << fNumEvents;

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataOutChannel = fChannels.at("data-out").at(0);

    fTimer = new boost::timer::auto_cpu_timer();

    for (Long64_t eventNr = 0; eventNr < fNumEvents; ++eventNr)
    {
        fSamplerTask->SetEventIndex(eventNr);
        fFairRunAna->RunMQ(eventNr);

        dataOutChannel.Send(fSamplerTask->GetOutput());
        ++sentMsgs;

        fSamplerTask->ClearOutput();

        if (!CheckCurrentState(RUNNING))
        {
            break;
        }
    }

    try
    {
        ackListener.join();
    }
    catch(boost::thread_resource_error& e)
    {
        LOG(ERROR) << e.what();
        exit(EXIT_FAILURE);
    }
}

template <typename Loader>
void FairMQSampler<Loader>::ListenForAcks()
{
    for (Long64_t eventNr = 0; eventNr < fNumEvents; ++eventNr)
    {
        std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
        fChannels.at("ack-in").at(0).Receive(ack);

        if (!CheckCurrentState(RUNNING))
        {
            break;
        }
    }

    boost::timer::cpu_times const elapsedTime(fTimer->elapsed());
    LOG(INFO) << "Acknowledged " << fNumEvents << " messages in:";
    delete fTimer;
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
        case ChainInput:
            fChainInput = value;
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
        case ChainInput:
            return fChainInput;
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
        case ChainInput:
            return "ChainInput: Adds the same file to the input <value> times. The output is still a single file.";
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
