/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewTask.h"

// ---- Default constructor -------------------------------------------
NewTask::NewTask()
  :FairTask("NewTask")
{
  fLogger->Debug(MESSAGE_ORIGIN,"Defaul Constructor of NewTask");
}

// ---- Destructor ----------------------------------------------------
NewTask::~NewTask()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Destructor of NewTask");
}

// ----  Initialisation  ----------------------------------------------
void NewTask::SetParContainers()
{
  fLogger->Debug(MESSAGE_ORIGIN,"SetParContainers of NewTask");
  // Load all necessary parameter containers from the runtime data base
  /*
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  <NewTaskDataMember> = (<ClassPointer>*)
    (rtdb->getContainer("<ContainerName>"));
  */
}

// ---- Init ----------------------------------------------------------
InitStatus NewTask::Init()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Initilization of NewTask");

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();

  // Get a pointer to the previous already existing data level
  /*
    <InputDataLevel> = (TClonesArray*) ioman->GetObject("InputDataLevelName");
    if ( ! <InputLevel> ) {
    fLogger->Error(MESSAGE_ORIGIN,"No InputDataLevelName array!\n NewTask will be inactive");
    return kERROR;
    }
  */

  // Create the TClonesArray for the output data and register
  // it in the IO manager
  /*
    <OutputDataLevel> = new TClonesArray("OutputDataLevelName", 100);
    ioman->Register("OutputDataLevelName","OutputDataLevelName",<OutputDataLevel>,kTRUE);
  */

  // Do whatever else is needed at the initilization stage
  // Create histograms to be filled
  // initialize variables

  return kSUCCESS;

}

// ---- ReInit  -------------------------------------------------------
InitStatus NewTask::ReInit()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Initilization of NewTask");
  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void NewTask::Exec(Option_t* option)
{
  fLogger->Debug(MESSAGE_ORIGIN,"Exec of NewTask");
}

// ---- Finish --------------------------------------------------------
void NewTask::Finish()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Finish of NewTask");
}

ClassImp(NewTask)
