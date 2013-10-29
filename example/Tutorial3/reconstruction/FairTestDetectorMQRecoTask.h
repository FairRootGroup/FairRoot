#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include "FairTestDetectorRecoTask.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"
#include "FairTestDetectorPayload.h"
class TClonesArray;

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

#endif //FAIRTESTDETECTORMQRECOTASK_H
