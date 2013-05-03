#ifndef PNDTORINODETECTORDIGITASK_H
#define PNDTORINODETECTORDIGITASK_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for Double_t, etc

class TClonesArray;

class FairTestDetectorDigiTask : public FairTask
{
  public:

    /** Default constructor **/
    FairTestDetectorDigiTask();


    /** Destructor **/
    ~FairTestDetectorDigiTask();


    /** Virtual method Init **/
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void SetTimeResolution(Double_t timeInNs) { fTimeResolution = timeInNs; }
    Double_t GetTimeResolution() { return fTimeResolution; }

  private:

    Int_t CalcPad(Double_t posIn, Double_t posOut);
    Double_t CalcTimeStamp(Double_t timeOfFlight);

    Double_t fTimeResolution;

    TClonesArray* fPointArray;
    TClonesArray* fDigiArray;

    FairTestDetectorDigiTask(const FairTestDetectorDigiTask&);
    FairTestDetectorDigiTask& operator=(const FairTestDetectorDigiTask&);

    ClassDef(FairTestDetectorDigiTask,1);

};

#endif
