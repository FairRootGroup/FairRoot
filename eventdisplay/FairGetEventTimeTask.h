#ifndef FairGetEventTimeTask_H_
#define FairGetEventTimeTask_H_

/**
 * FairTimebasedMCSource.h
 *
 * \brief Reads in the event times stored in the event headers of each event in the Init() of the task and provides this
 * data as a transient vector
 *
 *  Created on: 07.12.2020
 *
 *      Author: tstockmanns
 */

#include "FairEventHeader.h"
#include "FairTask.h"
#include "TClonesArray.h"

#include <vector>

class FairGetEventTimeTask : public FairTask
{
  public:
    FairGetEventTimeTask();
    virtual ~FairGetEventTimeTask();

    /** Virtual method Init **/
    virtual InitStatus Init();
    virtual InitStatus ReInit();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
    virtual void FinishEvent();

  private:
    FairEventHeader* fHeader = nullptr;
    TBranch* fBranch = nullptr;

    std::vector<double>* fEventTime = nullptr;
    std::vector<double> fEventTimeCopy;

    void Register();
    void Reset();
    void ProduceHits();

    ClassDef(FairGetEventTimeTask, 1);
};

#endif /*PndGetEventTimeTask_H_*/
