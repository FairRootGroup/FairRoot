/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORRECOTASK_H_
#define FAIRTESTDETECTORRECOTASK_H_

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Int_t, Option_t

class TClonesArray;
class TBuffer;
class TClass;
class TMemberInspector;

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

    ClassDef(FairTestDetectorRecoTask, 1);
};

#endif /* FAIRTESTDETECTORRECOTASK_H_ */
