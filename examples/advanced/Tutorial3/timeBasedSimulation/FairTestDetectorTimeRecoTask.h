/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairTestDetectorTimeRecoTask_H
#define FairTestDetectorTimeRecoTask_H

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>   // for ClassDef

class BinaryFunctor;
class TClonesArray;

class FairTestDetectorTimeRecoTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorTimeRecoTask();
    FairTestDetectorTimeRecoTask(Int_t verbose);

    /** Destructor **/
    ~FairTestDetectorTimeRecoTask() override;

    /** Virtual method Init **/
    InitStatus Init() override;

    /** Virtual method Exec **/
    void Exec(Option_t* opt) override;

  private:
    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

    Double_t fTime;

    BinaryFunctor* fFunctor;   //!

    FairTestDetectorTimeRecoTask(const FairTestDetectorTimeRecoTask&);
    FairTestDetectorTimeRecoTask& operator=(const FairTestDetectorTimeRecoTask&);

    ClassDefOverride(FairTestDetectorTimeRecoTask, 1);
};

#endif
