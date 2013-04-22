#ifndef FairTestDetectorTimeRecoTask_H
#define FairTestDetectorTimeRecoTask_H

#include "FairTask.h"
#include "FairTSBufferFunctional.h"

class TClonesArray;

class FairTestDetectorPoint;


class FairTestDetectorTimeRecoTask : public FairTask
{
  public:

    /** Default constructor **/
    FairTestDetectorTimeRecoTask();
    FairTestDetectorTimeRecoTask(Int_t verbose);


    /** Destructor **/
    ~FairTestDetectorTimeRecoTask();


    /** Virtual method Init **/
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

  private:


    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

    BinaryFunctor* fFunctor; //!

    FairTestDetectorTimeRecoTask(const FairTestDetectorTimeRecoTask&);
    FairTestDetectorTimeRecoTask& operator=(const FairTestDetectorTimeRecoTask&);

    ClassDef(FairTestDetectorTimeRecoTask,1);

};

#endif
