// -------------------------------------------------------------------------
// -----                        FairTask source file                   -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------

#include "FairTask.h"
#include "FairLogger.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTask::FairTask()
  : TTask(),
    fVerbose(0),
    fInputPersistance(-1),
    fLogger(FairLogger::GetLogger())
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairTask::FairTask(const char* name, Int_t iVerbose)
  : TTask(name, "FairTask"),
    fVerbose(iVerbose),
    fInputPersistance(-1),
    fLogger(FairLogger::GetLogger())
{

}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairTask::~FairTask() { }
// -------------------------------------------------------------------------



// -----   Public method InitTask   ----------------------------------------
void FairTask::InitTask()
{
  if ( ! fActive ) { return; }
  InitStatus tStat = Init();
  if ( tStat == kFATAL ) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Initialization of Task %s failed fatally", fName.Data());
  }
  if ( tStat == kERROR ) { fActive = kFALSE; }
  InitTasks();
}
// -------------------------------------------------------------------------



// -----   Public method ReInitTask   --------------------------------------
void FairTask::ReInitTask()
{
  if ( ! fActive ) { return; }
  InitStatus tStat = ReInit();
  if ( tStat == kFATAL ) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Reinitialization of Task %s failed fatally", fName.Data());
  }
  if ( tStat == kERROR ) { fActive = kFALSE; }
  ReInitTasks();
}
// -------------------------------------------------------------------------



// -----   Public method SetParTask   --------------------------------------
void FairTask::SetParTask()
{
  if ( ! fActive ) { return; }
  SetParContainers();
  SetParTasks();
}
// -------------------------------------------------------------------------

// -----    Public method FinishEvent -------------------------------------
void FairTask::FinishEvent()
{
  if ( ! fActive ) { return; }
  FinishEvents();
  //  FinishTasks();
}

// -----    Public method FinishTask   -------------------------------------
void FairTask::FinishTask()
{
  if ( ! fActive ) { return; }
  Finish();
  FinishTasks();
}
// -------------------------------------------------------------------------



// -----   Public method SetVerbose   --------------------------------------
void FairTask::SetVerbose(Int_t iVerbose)
{
  fVerbose = iVerbose;
  TIter next(GetListOfTasks());
  FairTask* task;
  while((task=dynamic_cast <FairTask*> (next()))) { task->SetVerbose(iVerbose); }
}
// -------------------------------------------------------------------------




// -----   Protected method InitTasks   ------------------------------------
void FairTask::InitTasks()
{
  TIter next(GetListOfTasks());
  FairTask* task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) { task->InitTask(); }
}
// -------------------------------------------------------------------------



// -----   Protected method ReInitTasks   ----------------------------------
void FairTask::ReInitTasks()
{
  TIter next(GetListOfTasks());
  FairTask* task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) { task->ReInitTask(); }
}
// -------------------------------------------------------------------------



// -----   Protected method SetParTasks   ----------------------------------
void FairTask::SetParTasks()
{
  TIter next(GetListOfTasks());
  FairTask* task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) { task->SetParTask(); }
}
// -------------------------------------------------------------------------



// -----   Protected method FinishTasks   ----------------------------------
void FairTask::FinishTasks()
{
  TIter next(GetListOfTasks());
  FairTask* task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) { task->FinishTask(); }
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) { task->Finish(); }
}
// -------------------------------------------------------------------------

// -----   Protected method FinishEvents   ----------------------------------
void FairTask::FinishEvents()
{
  TIter next(GetListOfTasks());
  FairTask* task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) { task->FinishEvent(); }
}
// -------------------------------------------------------------------------


ClassImp(FairTask)
