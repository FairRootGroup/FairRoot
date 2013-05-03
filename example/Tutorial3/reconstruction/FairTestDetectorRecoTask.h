#ifndef PNDTORINODETECTORRECOTASK_H
#define PNDTORINODETECTORRECOTASK_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for ClassDef

class TClonesArray;

class FairTestDetectorRecoTask : public FairTask
{
  public:

    /** Default constructor **/
    FairTestDetectorRecoTask();
    FairTestDetectorRecoTask(Int_t verbose);


    /** Destructor **/
    ~FairTestDetectorRecoTask();


    /** Virtual method Init **/
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

  private:


    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

    FairTestDetectorRecoTask(const FairTestDetectorRecoTask&);
    FairTestDetectorRecoTask& operator=(const FairTestDetectorRecoTask&);

    ClassDef(FairTestDetectorRecoTask,1);

};

#endif
