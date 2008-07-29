#include "CbmRun.h"
#include "CbmTask.h"
#include "CbmRootManager.h"
#include "CbmRuntimeDb.h"

//_____________________________________________________________________________
CbmRun * CbmRun::fRunInstance= 0;
//_____________________________________________________________________________
CbmRun * CbmRun::Instance(){

        return fRunInstance;
}
//_____________________________________________________________________________
CbmRun::CbmRun()
  :TNamed(),
   rtdb(CbmRuntimeDb::instance()),
   fTask(new CbmTask("CbmTask List")),
   Outfname(""),
   fRootManager(CbmRootManager::Instance()),
   fOutFile(0),
   fRunId(0),
   fAna(kFALSE)
{
  if (fRunInstance) {
      Fatal("CbmRun", "Singleton instance already exists.");
      return;
  } 
  fRunInstance=this;
  if(fRootManager==0) fRootManager= new CbmRootManager();
}
//_____________________________________________________________________________
CbmRun::~CbmRun()
{
	delete fTask;
        delete rtdb;
}
//_____________________________________________________________________________

void CbmRun::SetOutputFile(const char *fname)
{
	Outfname=fname;
}
//_____________________________________________________________________________

void CbmRun::AddTask(CbmTask *t)
{
  fTask->Add(t);
}
//_____________________________________________________________________________

void CbmRun::Run(Int_t NStart,Int_t NStop)
{
}
//_____________________________________________________________________________

void CbmRun::Init()
{
}
//_____________________________________________________________________________
CbmTask* CbmRun::GetTask(const char* taskName) {
    TList* taskList = fTask->GetListOfTasks();
    TObject* task = taskList->FindObject(taskName);
    return dynamic_cast<CbmTask*>(task);
}
ClassImp(CbmRun)



