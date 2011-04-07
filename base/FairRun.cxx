// -------------------------------------------------------------------------
// -----                   FairRun source file                         -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------


#include "FairRun.h"
#include "FairTask.h"
#include "FairRootManager.h"
#include "FairRuntimeDb.h"
#include "FairEventHeader.h"
#include <iostream>


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
   fLogger(FairLogger::GetLogger()),
   fNTasks(0),
   fRtdb(FairRuntimeDb::instance()),
   fTask(new FairTask("FairTask List")),
   Outfname(""),
   //   fRootManager(FairRootManager::Instance()),
   fRootManager(new FairRootManager()),
   fOutFile(0),
   fRunId(0),
   fAna(kFALSE),
   fEvHead(NULL)
{
  if (fRunInstance) {
    Fatal("FairRun", "Singleton instance already exists.");
    return;
  }
  fRunInstance=this;
}
//_____________________________________________________________________________
FairRun::~FairRun()
{
  fLogger->Debug(MESSAGE_ORIGIN," Enter Destructor of FairRun ");
  if (fTask) { delete fTask; } // There is another tasklist in MCApplication,
  // but this should be independent
  if (fRtdb) { delete fRtdb; } // who is responsible for the RuntimeDataBase
  if (fRootManager) {
    delete fRootManager; // who is responsible
    fRootManager=0;
  }
  if (fEvHead) { delete fEvHead; }
}
//_____________________________________________________________________________

void FairRun::SetOutputFile(const char* fname)
{
  Outfname=fname;
}
//_____________________________________________________________________________

void FairRun::AddTask(FairTask* t)
{
  fTask->Add(t);
  fNTasks++;
}

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

FairEventHeader*  FairRun::GetEventHeader()
{
  if ( NULL == fEvHead ) { fEvHead = new FairEventHeader(); }
  return fEvHead;
}


ClassImp(FairRun)


