#ifndef FairGetEventTimeTask_H_
#define FairGetEventTimeTask_H_

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
    virtual void SetParContainers();
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
    bool fRunOnce;

    void Register();
    void Reset();
    void ProduceHits();

    ClassDef(FairGetEventTimeTask, 1);
};

#endif /*PndGetEventTimeTask_H_*/
