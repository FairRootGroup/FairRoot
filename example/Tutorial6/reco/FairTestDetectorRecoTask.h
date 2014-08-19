/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORRECOTASK_H_
#define FAIRTESTDETECTORRECOTASK_H_

#include "FairTask.h" // for FairTask, InitStatus
#include "FairRuntimeDb.h"

class TClonesArray;


class FairEventHeader;
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

    /** Init with Id*/
    virtual void InitWithId(Int_t rid); 
        
    /** Get RTDB */ 
    FairRuntimeDb* GetRtdb(){return (FairRuntimeDb::instance());}

 public: 
    FairEventHeader* fEvtHeader; 
    TClonesArray*    fDigiArray;
    TClonesArray*    fHitArray;
    Int_t fRunId;


  private:
    FairTestDetectorRecoTask(const FairTestDetectorRecoTask&);
    FairTestDetectorRecoTask& operator=(const FairTestDetectorRecoTask&);

    ClassDef(FairTestDetectorRecoTask, 1);
};

#endif /* FAIRTESTDETECTORRECOTASK_H_ */
