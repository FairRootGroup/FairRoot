// -------------------------------------------------------------------------
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------


#include "FairFileHeader.h"
#include "FairRootManager.h"
#include "FairFileInfo.h"


// -----   Default constructor   -------------------------------------------
FairFileHeader::FairFileHeader()
  :TNamed(),
   fRunId(0),
   fTaskList(new TList()),
   fFileList(new TList())
{

}
// -------------------------------------------------------------------------
void FairFileHeader::AddTaskClassName(TString taskname)
{
  fTaskList->AddLast(new TObjString(taskname));
}
// -------------------------------------------------------------------------
void FairFileHeader::AddInputFile(TFile* f, UInt_t id,  UInt_t ChId)
{
  fFileList->AddLast(new FairFileInfo(f,id, ChId));
}
// -------------------------------------------------------------------------
FairFileInfo* FairFileHeader::GetFileInfo(UInt_t id, UInt_t ChId)
{
  TIterator* Iter=fFileList->MakeIterator();
  Iter->Reset();
  TObject* obj=0;
  FairFileInfo* info=0;
  while((obj=Iter->Next())) {
    info=dynamic_cast <FairFileInfo*> (obj);
    if(info->GetIdentifier() == id && info->GetOrderInChain()==ChId) {return info;}
  }
  return 0;

}
// -----   Destructor   ----------------------------------------------------
FairFileHeader::~FairFileHeader()
{
}
// -------------------------------------------------------------------------


ClassImp(FairFileHeader)
