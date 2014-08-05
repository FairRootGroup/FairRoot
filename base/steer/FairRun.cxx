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
#include "FairLinkManager.h"			// for FairLinkManager

#include "TFile.h"                      // for TFile
#include "TList.h"                      // for TList
#include "TObject.h"                    // for TObject

#include <stddef.h>                     // for NULL

//_____________________________________________________________________________
FairRun* FairRun::fRunInstance= 0;
//_____________________________________________________________________________
FairRun* FairRun::Instance()
{
  return fRunInstance;
}
//_____________________________________________________________________________
FairRun::FairRun()
  :TNamed(),
   fNTasks(0),
   fLogger(FairLogger::GetLogger()),
   fRtdb(FairRuntimeDb::instance()),
   fTask(new FairTask("FairTaskList")),
   fOutname(""),
   fRootManager(new FairRootManager()),
   fOutFile(0),
   fRunId(0),
   fAna(kFALSE),
   fEvHead(NULL),
   fFileHeader(new FairFileHeader()),
   fWriteRunInfo(kTRUE)
{
  if (fRunInstance) {
    Fatal("FairRun", "Singleton instance already exists.");
    return;
  }
  fRunInstance=this;
  fRootManager->SetFileHeader(fFileHeader);
  new FairLinkManager();
}
//_____________________________________________________________________________
FairRun::~FairRun()
{
  fLogger->Debug(MESSAGE_ORIGIN," Enter Destructor of FairRun ");
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
  if (fEvHead) {
    delete fEvHead;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRun::SetOutputFile(const char* fname)
{
  fOutname=fname;
  fOutFile = fRootManager->OpenOutFile(fOutname);

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRun::SetOutputFile(TFile* f)
{
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
  if ( NULL == fEvHead ) {
    fEvHead = new FairEventHeader();
  }
  return fEvHead;
}

void FairRun::SetUseFairLinks(Bool_t val)
{
        fRootManager->SetUseFairLinks(val);
}

//_____________________________________________________________________________
ClassImp(FairRun)


