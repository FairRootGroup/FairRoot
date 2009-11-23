#include "FairRun.h"
#include "FairTask.h"
#include "FairRootManager.h"
#include "FairRuntimeDb.h"

//_____________________________________________________________________________
FairRun * FairRun::fRunInstance= 0;
//_____________________________________________________________________________
FairRun * FairRun::Instance(){

        return fRunInstance;
}
//_____________________________________________________________________________
FairRun::FairRun()
  :TNamed(),
   fRtdb(FairRuntimeDb::instance()),
   fTask(new FairTask("FairTask List")),
   Outfname(""),
   fRootManager(FairRootManager::Instance()),
   fOutFile(0),
   fRunId(0),
   fAna(kFALSE)
{
  if (fRunInstance) {
      Fatal("FairRun", "Singleton instance already exists.");
      return;
  } 
  fRunInstance=this;
  if(fRootManager==0) fRootManager= new FairRootManager();
}
//_____________________________________________________________________________
FairRun::~FairRun()
{
	if (fTask) delete fTask;
	if (fRtdb) delete fRtdb;
}
//_____________________________________________________________________________

void FairRun::SetOutputFile(const char *fname)
{
	Outfname=fname;
}
//_____________________________________________________________________________

void FairRun::AddTask(FairTask *t)
{
  fTask->Add(t);
}
//_____________________________________________________________________________
FairTask* FairRun::GetTask(const char* taskName) {
    TList* taskList = fTask->GetListOfTasks();
    TObject* task = taskList->FindObject(taskName);
    return dynamic_cast<FairTask*>(task);
}
ClassImp(FairRun)



