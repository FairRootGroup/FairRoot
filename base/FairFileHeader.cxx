// -------------------------------------------------------------------------
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------


#include "FairFileHeader.h"
#include "FairRootManager.h"

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
void FairFileHeader::AddInputFileName(TString filename)
{
  printf("Add file name : %s \n", filename.Data());
  fFileList->AddLast(new TObjString(filename));
}

// -----   Destructor   ----------------------------------------------------
FairFileHeader::~FairFileHeader()
{
}
// -------------------------------------------------------------------------


ClassImp(FairFileHeader)
