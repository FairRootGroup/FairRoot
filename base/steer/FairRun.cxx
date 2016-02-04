/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRun source file                         -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRun.h"

#include "FairEventHeader.h"            // for FairEventHeader
#include "FairFileHeader.h"             // for FairFileHeader
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairRootManager.h"            // for FairRootManager
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairTask.h"                   // for FairTask
#include "FairLinkManager.h"            // for FairLinkManager

#include "TFile.h"                      // for TFile
#include "TList.h"                      // for TList
#include "TObject.h"                    // for TObject

#include <stddef.h>                     // for NULL

//_____________________________________________________________________________
TMCThreadLocal FairRun* FairRun::fRunInstance= 0;
//_____________________________________________________________________________
FairRun* FairRun::Instance()
{
  return fRunInstance;
}
//_____________________________________________________________________________
FairRun::FairRun(Bool_t isMaster)
  :TNamed(),
   fNTasks(0),
   fRtdb(FairRuntimeDb::instance()),
   fTask(new FairTask("FairTaskList")),
   fOutname(""),
   fRootManager(0),
   fOutFile(0),
   fRunId(0),
   fAna(kFALSE),
   fEvtHeader(NULL),
   fFileHeader(new FairFileHeader()),
   fGenerateRunInfo(kFALSE),
   fIsMaster(isMaster)
{
  if (fRunInstance) {
    Fatal("FairRun", "Singleton instance already exists.");
    return;
  }
  fRunInstance=this;

  if ( isMaster ) {
    fRootManager = new FairRootManager();
  }
  new FairLinkManager();
}
//_____________________________________________________________________________
FairRun::~FairRun()
{
  LOG(DEBUG) << "Enter Destructor of FairRun" << FairLogger::endl;
  if (fTask) {
    delete fTask;  // There is another tasklist in MCApplication,
  }
  // but this should be independent
  if (fRtdb) {
    delete fRtdb;  // who is responsible for the RuntimeDataBase
  }
  if (fRootManager) {
    delete fRootManager; // who is responsible
    fRootManager=0;
  }
  if (fEvtHeader) {
    delete fEvtHeader;
  }
  LOG(DEBUG) << "Leave Destructor of FairRun" << FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRun::SetOutputFile(const char* fname)
{
  fOutname=fname;
  if (fRootManager) fOutFile = fRootManager->OpenOutFile(fOutname);

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRun::SetOutputFile(TFile* f)
{
  if (! fRootManager) return;

  fOutname=f->GetName();
  fRootManager->OpenOutFile(f);
  fOutFile = f;

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRun::AddTask(FairTask* t)
{
  fTask->Add(t);
  fNTasks++;
  fFileHeader->AddTaskClassName(t->ClassName());
}
//_____________________________________________________________________________
void FairRun::SetTask(FairTask* t)
{
  if ( fTask ) { delete fTask; }
  fTask = t;
  fFileHeader->AddTaskClassName(t->ClassName());
}
//_____________________________________________________________________________
void FairRun::CreateGeometryFile(const char* geofile)
{
  fRootManager->CreateGeometryFile(geofile);
}
//_____________________________________________________________________________
FairTask* FairRun::GetTask(const char* taskName)
{
  TList* taskList = fTask->GetListOfTasks();
  TObject* task = taskList->FindObject(taskName);
  return dynamic_cast<FairTask*>(task);
}
//_____________________________________________________________________________
FairEventHeader*  FairRun::GetEventHeader()
{
  if ( NULL == fEvtHeader ) {
    fEvtHeader = new FairEventHeader();
  }
  return fEvtHeader;
}

void FairRun::SetUseFairLinks(Bool_t val)
{
        fRootManager->SetUseFairLinks(val);
}

//_____________________________________________________________________________
void FairRun::SetWriteRunInfoFile(Bool_t write)
{
  LOG(WARNING) << "Function FairRun::SetWriteRunInfoFile(Bool_t) is depcrecated and will vanish in future versions of FairRoot.\n";
  LOG(WARNING) << "Please use FairRun::SetGenerateRunInfo(Bool_t) instead." << FairLogger::endl;

  fGenerateRunInfo = write;
}

Bool_t FairRun::GetWriteRunInfoFile()
{
  LOG(WARNING) << "Function FairRun::GetWriteRunInfoFile() is depcrecated and will vanish in future versions of FairRoot.\n";
  LOG(WARNING) << "Please use FairRun::IsRunInfoGenerated() instead." << FairLogger::endl;

  return fGenerateRunInfo;
}



ClassImp(FairRun)


