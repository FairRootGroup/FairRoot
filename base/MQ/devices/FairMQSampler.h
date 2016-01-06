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

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/timer/timer.hpp>

#include "TList.h"
#include "TObjString.h"
#include "TClonesArray.h"
#include "TROOT.h"

#include "FairParRootFileIo.h"
#include "FairRuntimeDb.h"
#include "FairRunAna.h"
#include "FairTask.h"

#include "FairMQDevice.h"
#include "FairMQSamplerTask.h"
#include "FairMQLogger.h"

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

template <typename Loader>
class FairMQSampler : public FairMQDevice
{
  public:
    enum {
        InputFile = FairMQDevice::Last,
        ParFile,
        Branch,
        EventRate,
        ChainInput,
        Last
    };

    FairMQSampler();
    FairMQSampler(const FairMQSampler&) = delete;
    FairMQSampler operator=(const FairMQSampler&) = delete;

    virtual ~FairMQSampler();

    virtual void SetProperty(const int key, const std::string& value);
    virtual std::string GetProperty(const int key, const std::string& default_ = "");
    virtual void SetProperty(const int key, const int value);
    virtual int GetProperty(const int key, const int default_ = 0);

    virtual std::string GetPropertyDescription(const int key);
    virtual void ListProperties();

    void ListenForAcks();

    /**
     * Sends the currently available output of the Sampler Task as part of a multipart message
     * and reinitializes the message to be filled with the next part.
     * This method can be given as a callback to the SamplerTask.
     * The final message part must be sent with normal Send method.
     */
    void SendPart();

  protected:
    virtual void InitTask();
    virtual void Run();

    FairRunAna *fFairRunAna;
    FairMQSamplerTask *fSamplerTask;
    std::string fInputFile; // Filename of a root file containing the simulated digis.
    std::string fParFile;
    std::string fBranch; // The name of the sub-detector branch to stream the digis from.
    int fNumEvents;
    int fChainInput;
    int fEventRate;
    int fEventCounter;
};

// Template implementation is in FairMQSampler.tpl :
#include "FairMQSampler.tpl"

#endif /* FAIRMQSAMPLER_H_ */
