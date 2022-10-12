/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORDIGITASK_H_
#define FAIRTESTDETECTORDIGITASK_H_

#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Double_t, Int_t, Option_t
#include "FairTask.h"    // for FairTask, InitStatus
class TBuffer;
class TClass;
class TClonesArray;  // lines 15-15
class TMemberInspector;

class FairTestDetectorDigiTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorDigiTask();

    /** Destructor **/
    ~FairTestDetectorDigiTask() override;

    /** Virtual method Init **/
    InitStatus Init() override;

    /** Virtual method Exec **/
    void Exec(Option_t* opt) override;

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

    ClassDefOverride(FairTestDetectorDigiTask, 1);
};

#endif /* FAIRTESTDETECTORDIGITASK_H_ */
