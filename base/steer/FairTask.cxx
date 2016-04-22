/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                        FairTask source file                   -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------

#include "FairTask.h"

#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairMonitor.h"                // for FairMonitor

#include "TCollection.h"                // for TIter
#include "TList.h"                      // for TList
#include "TObject.h"                    // for TObject

#include <iostream>                     // for cout, endl

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTask::FairTask()
  : TTask(),
    fVerbose(0),
    fInputPersistance(-1),
    fLogger(FairLogger::GetLogger()),
    fOutputPersistance()
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairTask::FairTask(const char* name, Int_t iVerbose)
  : TTask(name, "FairTask"),
    fVerbose(iVerbose),
    fInputPersistance(-1),
    fLogger(FairLogger::GetLogger()),
    fOutputPersistance()
{

}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairTask::~FairTask() { }
// -------------------------------------------------------------------------



// -----   Public method InitTask   ----------------------------------------
void FairTask::InitTask()
{
  FairMonitor::GetMonitor()->SetCurrentTask(this);
  if ( ! fActive ) { return; }
  InitStatus tStat = Init();
  if ( tStat == kFATAL ) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Initialization of Task %s failed fatally", fName.Data());
  }
  if ( tStat == kERROR ) { fActive = kFALSE; }
  FairMonitor::GetMonitor()->SetCurrentTask(0);
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

//______________________________________________________________________________
void FairTask::ExecuteTask(Option_t *option)
{
   // Execute main task and its subtasks.
   // When calling this function, the Exec function of the corresponding class
   // is invoked, then the list of its subtasks is executed calling recursively
   // all the subtasks, etc.
   //
   // The option parameter may be used to select different execution steps
   // within a task. This parameter is passed also to all the subtasks.

   if (fgBeginTask) {
      Error("ExecuteTask","Cannot execute task:%s, already running task: %s",GetName(),fgBeginTask->GetName());
      return;
   }
   if (!IsActive()) return;

   fOption = option;
   fgBeginTask = this;
   fgBreakPoint = 0;

   if (fBreakin) return;
   if (gDebug > 1) {
     LOG(INFO)<<"Execute task:"<<GetName()<<" : "<<GetTitle()<<FairLogger::endl;
   }
   FairMonitor::GetMonitor()->StartMonitoring(this,"EXEC");
   Exec(option);
   FairMonitor::GetMonitor()->StopMonitoring(this,"EXEC");


   fHasExecuted = kTRUE;
   ExecuteTasks(option);

   if (fBreakout) return;

   if (!fgBreakPoint) {
      fgBeginTask->CleanTasks();
      fgBeginTask = 0;
   }
}
// -------------------------------------------------------------------------

//______________________________________________________________________________
void FairTask::ExecuteTasks(Option_t *option)
{
   // Execute all the subtasks of a task.

   TIter next(fTasks);
   FairTask *task;
   while((task=static_cast<FairTask*>(next()))) {
      if (fgBreakPoint) return;
      if (!task->IsActive()) continue;
      if (task->fHasExecuted) {
         task->ExecuteTasks(option);
         continue;
      }
      if (task->fBreakin == 1) {
         printf("Break at entry of task: %s\n",task->GetName());
         fgBreakPoint = this;
         task->fBreakin++;
         return;
      }

      if (gDebug > 1) {
	LOG(INFO)<<"Execute task:"<<task->GetName()<<" : "<<task->GetTitle()<<FairLogger::endl;
      }
      FairMonitor::GetMonitor()->StartMonitoring(task,"EXEC");
      task->Exec(option);
      FairMonitor::GetMonitor()->StopMonitoring(task,"EXEC");

      task->fHasExecuted = kTRUE;
      task->ExecuteTasks(option);
      if (task->fBreakout == 1) {
	printf("Break at exit of task: %s\n",task->GetName());
	fgBreakPoint = this;
	task->fBreakout++;
	return;
      }
   }
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

void FairTask::SetOutputBranchPersistent(TString branchName, Bool_t persistence)
{
  fOutputPersistance.insert ( std::pair<TString,Bool_t>(branchName, persistence) );
}

Bool_t FairTask::IsOutputBranchPersistent(TString branchName)
{  
  std::map<TString, Bool_t>::iterator it = fOutputPersistance.find(branchName);
  if (it != fOutputPersistance.end()) {
    return it->second;
  } else {
    return kTRUE;
  }
}

ClassImp(FairTask)
