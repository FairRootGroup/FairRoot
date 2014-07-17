/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBTUTACCESSRTDBTASK_H
#define FAIRDBTUTACCESSRTDBTASK_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for ClassDef

#include <stddef.h>                     // for NULL

class FairDbTutPar;

class FairDbTutAccessRtdbTask : public FairTask
{
  public:

    /** Default constructor **/
    FairDbTutAccessRtdbTask() : FairTask(), fTutParDef(NULL), fTutParAlt(NULL) {};

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

    FairDbTutAccessRtdbTask(const FairDbTutAccessRtdbTask&);
    FairDbTutAccessRtdbTask& operator=(const FairDbTutAccessRtdbTask&);

    ClassDef(FairDbTutAccessRtdbTask,0);
};

#endif
