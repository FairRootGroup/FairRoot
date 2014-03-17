#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include "FairTestDetectorRecoTask.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"

class TClonesArray;

template <typename T1, typename T2>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    /** Default constructor **/
    FairTestDetectorMQRecoTask();
    FairTestDetectorMQRecoTask(Int_t verbose);


    /** Destructor **/
    virtual ~FairTestDetectorMQRecoTask();


    /** Virtual method Init **/
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(FairMQMessage* msg, Option_t* opt);

  private:
    FairTestDetectorRecoTask* fRecoTask;
};

#include "FairTestDetectorMQRecoTask.tpl"

#endif /* FAIRTESTDETECTORMQRECOTASK_H */
