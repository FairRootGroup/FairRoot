#ifndef FAIRTESTDETECTORRECOTASK_H
#define FAIRTESTDETECTORRECOTASK_H

#include "FairTask.h"                   // for FairTask, InitStatus

class TClonesArray;

class FairTestDetectorPoint;


class FairTestDetectorRecoTask : public FairTask
{
  public:

    /** Default constructor **/
    FairTestDetectorRecoTask();
    FairTestDetectorRecoTask(Int_t verbose);


    /** Destructor **/
    virtual ~FairTestDetectorRecoTask();


    /** Virtual method Init **/
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);


    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

  private:
    FairTestDetectorRecoTask(const FairTestDetectorRecoTask&);
    FairTestDetectorRecoTask& operator=(const FairTestDetectorRecoTask&);


    ClassDef(FairTestDetectorRecoTask,1);

};

#endif //FAIRTESTDETECTORRECOTASK_H
