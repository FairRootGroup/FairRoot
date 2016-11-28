/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSampler.h
 *
 * @since 2012-09-27
 * @author D. Klein, A. Rybalchenko, N. Winckler
 */

#ifndef FAIRMQSAMPLER_H_
#define FAIRMQSAMPLER_H_

#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <chrono>

#include "TList.h"
#include "TObjString.h"
#include "TClonesArray.h"
#include "TROOT.h"

#include "FairParRootFileIo.h"
#include "FairRuntimeDb.h"
#include "FairRunAna.h"
#include "FairTask.h"
#include "FairFileSource.h"

#include "FairMQDevice.h"
#include "FairMQSamplerTask.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"

/**
 * Reads simulated digis from a root file and samples the digi as a time-series UDP stream.
 * Must be initialized with the filename to the root file and the name of the sub-detector
 * branch, whose digis should be streamed.
 *
 * The purpose of this class is to provide a data source of digis very similar to the
 * future detector output at the point where the detector is connected to the online
 * computing farm. For the development of online analysis algorithms, it is very important
 * to simulate the future detector output as realistic as possible to evaluate the
 * feasibility and quality of the various possible online analysis features.
 */

template <typename Task>
class FairMQSampler : public FairMQDevice
{
  public:
    FairMQSampler()
        : fFairRunAna(new FairRunAna())
        , fSamplerTask(new Task())
        , fStart()
        , fEnd()
        , fInputFile()
        , fParFile()
        , fBranch()
        , fNumEvents(0)
        , fChainInput(0)
        , fSentMsgs(0)
        , fAckListener()
    {}

    FairMQSampler(const FairMQSampler&) = delete;
    FairMQSampler operator=(const FairMQSampler&) = delete;

    virtual ~FairMQSampler()
    {
        if (fFairRunAna)
        {
            fFairRunAna->TerminateRun();
        }
        delete fSamplerTask;
    }

  protected:
    virtual void InitTask()
    {
        LOG(INFO) << "Initializing Task...";

        fInputFile = fConfig->GetValue<std::string>("input-file");
        fParFile = fConfig->GetValue<std::string>("parameter-file");
        fBranch = fConfig->GetValue<std::string>("branch");
        fChainInput = fConfig->GetValue<int>("chain-input");

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

        if (fParFile != "")
        {
            FairRuntimeDb* rtdb = fFairRunAna->GetRuntimeDb();
            FairParRootFileIo* parInput = new FairParRootFileIo();
            parInput->open(TString(fParFile).Data());
            rtdb->setFirstInput(parInput);
            rtdb->print();
        }
        else
        {
            LOG(WARN) << "Parameter file not provided. Starting without RuntimeDB.";
        }

        fFairRunAna->Init();
        // fFairRunAna->Run(0, 0);
        FairRootManager* ioman = FairRootManager::Instance();
        fNumEvents = int((ioman->GetInChain())->GetEntries());

        LOG(INFO) << "Task initialized.";
        LOG(INFO) << "Number of events to process: " << fNumEvents;
    }

    virtual void PreRun()
    {
        fStart = std::chrono::high_resolution_clock::now();
        fAckListener = std::thread(&FairMQSampler::ListenForAcks, this);
    }

    virtual bool ConditionalRun()
    {
        FairMQMessagePtr msg;

        fSamplerTask->SetEventIndex(fSentMsgs);
        fFairRunAna->RunMQ(fSentMsgs);
        fSamplerTask->GetPayload(msg);

        if (fChannels.at("data1").at(0).Send(msg) >= 0)
        {
            ++fSentMsgs;
            if (fSentMsgs == fNumEvents)
            {
                return false;
            }
        }

        return true;
    }

    virtual void PostRun()
    {
        try
        {
            fAckListener.join();
        }
        catch (std::exception& e)
        {
            LOG(ERROR) << "Exception when ending AckListener thread: " << e.what();
            exit(EXIT_FAILURE);
        }
    }

    void ListenForAcks()
    {
        for (Long64_t eventNr = 0; eventNr < fNumEvents; ++eventNr)
        {
            std::unique_ptr<FairMQMessage> ack(fTransportFactory->CreateMessage());
            fChannels.at("ack").at(0).Receive(ack);

            if (!CheckCurrentState(RUNNING))
            {
                break;
            }
        }

        fEnd = std::chrono::high_resolution_clock::now();
        LOG(INFO) << "Acknowledged " << fNumEvents << " messages in: " << std::chrono::duration<double, std::milli>(fEnd - fStart).count() << "ms.";
    }

  private:
    FairRunAna* fFairRunAna;
    FairMQSamplerTask* fSamplerTask;
    std::chrono::high_resolution_clock::time_point fStart;
    std::chrono::high_resolution_clock::time_point fEnd;
    std::string fInputFile; // Filename of a root file containing the simulated digis.
    std::string fParFile;
    std::string fBranch; // The name of the sub-detector branch to stream the digis from.
    int fNumEvents;
    int fChainInput;
    int fSentMsgs;
    std::thread fAckListener;
};

#endif /* FAIRMQSAMPLER_H_ */
