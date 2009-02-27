// -------------------------------------------------------------------------
// -----                        FairTask source file                    -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------

#include "FairTask.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTask::FairTask()
: fVerbose(0)
{ 
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairTask::FairTask(const char* name, Int_t iVerbose) 
  : TTask(name, "FairTask"), 
    fVerbose(iVerbose)
{
  
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairTask::~FairTask() { }
// -------------------------------------------------------------------------



// -----   Public method InitTask   ----------------------------------------
void FairTask::InitTask() {
  if ( ! fActive ) return;
  InitStatus tStat = Init();
  if ( tStat == kFATAL ) {
    cout << "-E- FairTask::InitTask: Intialisation of task "
	 << fName << " failed fatally! " << endl;
    Fatal("InitTask", "Init failed");
  }
  if ( tStat == kERROR ) fActive = kFALSE;
  InitTasks();
}
// -------------------------------------------------------------------------



// -----   Public method ReInitTask   --------------------------------------
void FairTask::ReInitTask() {
  if ( ! fActive ) return;
  InitStatus tStat = ReInit();
  if ( tStat == kFATAL ) {
    cout << "-E- FairTask::ReInitTask: Reintialisation of task "
	 << fName << " failed fatally! " << endl;
    Fatal("ReInitTask", "Init failed");
  }
  if ( tStat == kERROR ) fActive = kFALSE;
  ReInitTasks();
}
// -------------------------------------------------------------------------



// -----   Public method SetParTask   --------------------------------------
void FairTask::SetParTask() {
  if ( ! fActive ) return;
  SetParContainers();
  SetParTasks();
}
// -------------------------------------------------------------------------

// -----    Public method FinishEvent -------------------------------------
void FairTask::FinishEvent() {
  if ( ! fActive ) return;
  FinishEvents();
  //  FinishTasks();
}

// -----    Public method FinishTask   -------------------------------------
void FairTask::FinishTask() {
  if ( ! fActive ) return;
  //  Finish();
  FinishTasks();
}
// -------------------------------------------------------------------------



// -----   Public method SetVerbose   --------------------------------------
void FairTask::SetVerbose(Int_t iVerbose) {
  fVerbose = iVerbose;
  TIter next(GetListOfTasks());
  FairTask *task;
  while((task=dynamic_cast <FairTask*> (next()))) task->SetVerbose(iVerbose);
}
// -------------------------------------------------------------------------




// -----   Protected method InitTasks   ------------------------------------
void FairTask::InitTasks() {
  TIter next(GetListOfTasks());
  FairTask *task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) task->InitTask();
}
// -------------------------------------------------------------------------



// -----   Protected method ReInitTasks   ----------------------------------
void FairTask::ReInitTasks() {
  TIter next(GetListOfTasks());
  FairTask *task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) task->ReInitTask();
}
// -------------------------------------------------------------------------



// -----   Protected method SetParTasks   ----------------------------------
void FairTask::SetParTasks() {
  TIter next(GetListOfTasks());
  FairTask *task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) task->SetParTask();
}
// -------------------------------------------------------------------------



// -----   Protected method FinishTasks   ----------------------------------
void FairTask::FinishTasks() {
  TIter next(GetListOfTasks());
  FairTask *task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) task->FinishTask();
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) task->Finish();
}
// -------------------------------------------------------------------------

// -----   Protected method FinishEvents   ----------------------------------
void FairTask::FinishEvents() {
  TIter next(GetListOfTasks());
  FairTask *task;
  while( ( task=dynamic_cast<FairTask*>(next()) ) ) task->FinishEvent();
}
// -------------------------------------------------------------------------


ClassImp(FairTask)
