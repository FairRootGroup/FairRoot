/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairTestDetectorTimeDigiTask_H
#define FairTestDetectorTimeDigiTask_H

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>   // for Double_t, etc

class TClonesArray;
class FairTestDetectorDigiWriteoutBuffer;

class FairTestDetectorTimeDigiTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorTimeDigiTask();

    /** Destructor **/
    ~FairTestDetectorTimeDigiTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void SetTimeResolution(Double_t timeInNs) { fTimeResolution = timeInNs; }
    Double_t GetTimeResolution() { return fTimeResolution; }

    void RunTimeBased() { fTimeOrderedDigi = kTRUE; }

  private:
    Int_t CalcPad(Double_t posIn, Double_t posOut);
    Double_t CalcTimeStamp(Double_t timeOfFlight);

    Double_t fTimeResolution;

    TClonesArray* fPointArray;
    TClonesArray* fDigiArray;

    FairTestDetectorDigiWriteoutBuffer* fDataBuffer;

    Bool_t fTimeOrderedDigi;

    FairTestDetectorTimeDigiTask(const FairTestDetectorTimeDigiTask&);
    FairTestDetectorTimeDigiTask& operator=(const FairTestDetectorTimeDigiTask&);

    ClassDef(FairTestDetectorTimeDigiTask, 1);
};

#endif
