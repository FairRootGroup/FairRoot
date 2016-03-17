/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef _FAIRTUT8_TASK_
#define _FAIRTUT8_TASK_

#include "FairTask.h"

class TClonesArray;
class TH1F;

/**
 * An example analysis task for demonstartion of THttpServer usage.
 * Loops over detector raw items in an event and fills the histogram.
 */
class FairTut8Task : public FairTask
{
  public:
    /** Standard Constructor. */
    FairTut8Task(const char* name, Int_t iVerbose);
    
    /** Destructor. */
    virtual ~FairTut8Task();

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

    FairTut8Task(const FairTut8Task&);
    FairTut8Task& operator=(const FairTut8Task&);

  public:
    ClassDef(FairTut8Task, 1)
};

#endif
