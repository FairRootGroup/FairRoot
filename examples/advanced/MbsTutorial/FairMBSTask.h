/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef _FAIRMBS_TASK_
#define _FAIRMBS_TASK_

#include "FairRunOnline.h"
#include "FairTask.h"

#include <Rtypes.h>
#include <TClonesArray.h>
#include <TH1F.h>

/**
 * An example analysis task for demonstartion of THttpServer usage.
 * Loops over detector raw items in an event and fills the histogram.
 */
class FairMBSTask : public FairTask
{
  public:
    /** Standard Constructor. */
    explicit FairMBSTask(FairRunOnline& run)
        : FairTask("ExampleMBSTask")
        , fRunOnline(run)
    {}

    /** Destructor. */
    ~FairMBSTask() override = default;

    /** Initialization of the task. */
    InitStatus Init() override;

    /** Process an event. */
    void Exec(Option_t*) override;

  private:
    TClonesArray* fRawData{nullptr}; /**< Array with input data. */
    TH1F* fhQdc{nullptr};            /**< Histogram object which is registered on http server. */
    TH1F* fhTac{nullptr};
    TH1F* fhClock{nullptr};
    TH1F* fhTacCh{nullptr};
    FairRunOnline& fRunOnline;   //!

  public:
    ClassDefOverride(FairMBSTask, 1);
};

#endif
