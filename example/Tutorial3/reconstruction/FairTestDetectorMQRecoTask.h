#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include "FairTestDetectorRecoTask.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"
#include "TestDetectorPayload.h"
class TFile;
class TTree;
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

    TFile* fOutFile;
    TTree* fTree;
    TClonesArray* fHitA;

    //ClassDef(FairTestDetectorMQRecoTask,1);
};

#endif //FAIRTESTDETECTORMQRECOTASK_H
