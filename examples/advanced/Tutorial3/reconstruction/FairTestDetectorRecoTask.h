/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORRECOTASK_H_
#define FAIRTESTDETECTORRECOTASK_H_

#include "FairTask.h"   // for FairTask, InitStatus

class TClonesArray;

class FairTestDetectorRecoTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorRecoTask();
    FairTestDetectorRecoTask(Int_t verbose);

    /** Destructor **/
    ~FairTestDetectorRecoTask() override;

    /** Virtual method Init **/
    InitStatus Init() override;

    /** Virtual method Exec **/
    void Exec(Option_t* opt) override;

    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

  private:
    FairTestDetectorRecoTask(const FairTestDetectorRecoTask&);
    FairTestDetectorRecoTask& operator=(const FairTestDetectorRecoTask&);

    ClassDefOverride(FairTestDetectorRecoTask, 1);
};

#endif /* FAIRTESTDETECTORRECOTASK_H_ */
