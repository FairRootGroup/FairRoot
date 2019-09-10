/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef _FAIRMBS_TASK_
#define _FAIRMBS_TASK_

#include "FairTask.h"

class TClonesArray;
class TH1F;

/**
 * An example analysis task for demonstartion of THttpServer usage.
 * Loops over detector raw items in an event and fills the histogram.
 */
class FairMBSTask : public FairTask
{
  public:
    /** Standard Constructor. */
    FairMBSTask(const char* name, Int_t iVerbose);
    
    /** Destructor. */
    virtual ~FairMBSTask();

    /** Initialization of the task. */
    virtual InitStatus Init();

    /** Process an event. */
    virtual void Exec(Option_t*);

    /** Called at the end of each event. */
    virtual void FinishEvent();

    /** Called at the end of task. */
    virtual void FinishTask();

  private:
    TClonesArray* fRawData; /**< Array with input data. */
    TH1F* fhQdc;            /**< Histogram object which is registered on http server. */
    TH1F* fhTac;
    TH1F* fhClock;
    TH1F* fhTacCh;

    FairMBSTask(const FairMBSTask&);
    FairMBSTask& operator=(const FairMBSTask&);

  public:
    ClassDef(FairMBSTask, 1)
};

#endif
