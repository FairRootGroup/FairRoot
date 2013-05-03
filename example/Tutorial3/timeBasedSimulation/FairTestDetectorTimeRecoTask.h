#ifndef FairTestDetectorTimeRecoTask_H
#define FairTestDetectorTimeRecoTask_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for ClassDef

class BinaryFunctor;
class TClonesArray;

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
