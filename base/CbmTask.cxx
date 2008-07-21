// -------------------------------------------------------------------------
// -----                        CbmTask source file                    -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------

#include "CbmTask.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
CbmTask::CbmTask()
: fVerbose(0)
{ 
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
CbmTask::CbmTask(const char* name, Int_t iVerbose) 
  : TTask(name, "CbmTask"), 
    fVerbose(iVerbose)
{
  
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
CbmTask::~CbmTask() { }
// -------------------------------------------------------------------------



// -----   Public method InitTask   ----------------------------------------
void CbmTask::InitTask() {
  if ( ! fActive ) return;
  InitStatus tStat = Init();
  if ( tStat == kFATAL ) {
    cout << "-E- CbmTask::InitTask: Intialisation of task "
	 << fName << " failed fatally! " << endl;
    Fatal("InitTask", "Init failed");
  }
  if ( tStat == kERROR ) fActive = kFALSE;
  InitTasks();
}
// -------------------------------------------------------------------------



// -----   Public method ReInitTask   --------------------------------------
void CbmTask::ReInitTask() {
  if ( ! fActive ) return;
  InitStatus tStat = ReInit();
  if ( tStat == kFATAL ) {
    cout << "-E- CbmTask::ReInitTask: Reintialisation of task "
	 << fName << " failed fatally! " << endl;
    Fatal("ReInitTask", "Init failed");
  }
  if ( tStat == kERROR ) fActive = kFALSE;
  ReInitTasks();
}
// -------------------------------------------------------------------------



// -----   Public method SetParTask   --------------------------------------
void CbmTask::SetParTask() {
  if ( ! fActive ) return;
  SetParContainers();
  SetParTasks();
}
// -------------------------------------------------------------------------



// -----    Public method FinishTask   -------------------------------------
void CbmTask::FinishTask() {
  if ( ! fActive ) return;
  Finish();
  FinishTasks();
}
// -------------------------------------------------------------------------



// -----   Public method SetVerbose   --------------------------------------
void CbmTask::SetVerbose(Int_t iVerbose) {
  fVerbose = iVerbose;
  TIter next(GetListOfTasks());
  CbmTask *task;
  while((task=dynamic_cast <CbmTask*> (next()))) task->SetVerbose(iVerbose);
}
// -------------------------------------------------------------------------




// -----   Protected method InitTasks   ------------------------------------
void CbmTask::InitTasks() {
  TIter next(GetListOfTasks());
  CbmTask *task;
  while( ( task=dynamic_cast<CbmTask*>(next()) ) ) task->InitTask();
}
// -------------------------------------------------------------------------



// -----   Protected method ReInitTasks   ----------------------------------
void CbmTask::ReInitTasks() {
  TIter next(GetListOfTasks());
  CbmTask *task;
  while( ( task=dynamic_cast<CbmTask*>(next()) ) ) task->ReInitTask();
}
// -------------------------------------------------------------------------



// -----   Protected method SetParTasks   ----------------------------------
void CbmTask::SetParTasks() {
  TIter next(GetListOfTasks());
  CbmTask *task;
  while( ( task=dynamic_cast<CbmTask*>(next()) ) ) task->SetParTask();
}
// -------------------------------------------------------------------------



// -----   Protected method FinishTasks   ----------------------------------
void CbmTask::FinishTasks() {
  TIter next(GetListOfTasks());
  CbmTask *task;
  while( ( task=dynamic_cast<CbmTask*>(next()) ) ) task->FinishTask();
}
// -------------------------------------------------------------------------



ClassImp(CbmTask)
