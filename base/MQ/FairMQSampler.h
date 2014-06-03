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
class FairMQSampler: public FairMQDevice
{
  public:
    enum {
      InputFile = FairMQDevice::Last,
      Branch,
      ParFile,
      EventRate
    };
    FairMQSampler();
    virtual ~FairMQSampler();

    void ResetEventCounter();
    virtual void ListenToCommands();
    virtual void SetProperty(const int key, const string& value, const int slot = 0);
    virtual string GetProperty(const int key, const string& default_ = "", const int slot = 0);
    virtual void SetProperty(const int key, const int value, const int slot = 0);
    virtual int GetProperty(const int key, const int default_ = 0, const int slot = 0);
  protected:
    FairRunAna* fFairRunAna;
    int fNumEvents;
    FairMQSamplerTask* fSamplerTask;
    string fInputFile; // Filename of a root file containing the simulated digis.
    string fParFile;
    string fBranch; // The name of the sub-detector branch to stream the digis from.
    int fEventRate;
    int fEventCounter;
    virtual void Init();
    virtual void Run();

};

/// Template implementation is in FairMQSampler.tpl :
#include "FairMQSampler.tpl"

#endif /* FAIRMQSAMPLER_H_ */
