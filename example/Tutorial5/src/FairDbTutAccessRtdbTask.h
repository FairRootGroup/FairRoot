#ifndef FAIRDBTUTACCESSRTDBTASK_H
#define FAIRDBTUTACCESSRTDBTASK_H


#include "FairTask.h"
#include "FairDbTutPar.h"

#include <string>
#include <vector>

class TClonesArray;

class FairDbTutAccessRtdbTask : public FairTask
{
  public:

    /** Default constructor **/
    FairDbTutAccessRtdbTask() {};

    /** Destructor **/
    virtual ~FairDbTutAccessRtdbTask() {};


    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();
    virtual InitStatus ReInit();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
    /** Virtual method Finish **/
    virtual void Finish();

    FairDbTutPar* fTutParDef;
    FairDbTutPar* fTutParAlt;

    ClassDef(FairDbTutAccessRtdbTask,0);
};

#endif
