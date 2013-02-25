// -------------------------------------------------------------------------
// -----                FairRingSorterTaskT source file             -----
// -------------------------------------------------------------------------

#include "FairRingSorterTask.h"
#include "FairRootManager.h"




InitStatus FairRingSorterTask::ReInit()
{
  return kSUCCESS;
}

// -----   Public method Init   --------------------------------------------
InitStatus FairRingSorterTask::Init()
{

  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) {
    std::cout << "-E- FairRingSorterTaskT::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  fSorter = InitSorter(fNumberOfCells, fWidthOfCells);

  // Create and register output array
  fInputArray = FairRootManager::Instance()->GetTClonesArray(fInputBranch);

  if(fVerbose>1) { Info("Init","Registering this branch: %s/%s",fFolder.Data(),fOutputBranch.Data()); }
  fOutputArray = ioman->Register(fOutputBranch, fInputArray->GetClass()->GetName(), fFolder, fPersistance);


  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void FairRingSorterTask::Exec(Option_t* opt)
{



  fInputArray = FairRootManager::Instance()->GetTClonesArray(fInputBranch);
  if (fVerbose > 1) {
    std::cout << "-I- FairRingSorterTask: Size PixelArray: " << fInputArray->GetEntriesFast() << std::endl;
  }
  for (int i = 0; i < fInputArray->GetEntriesFast(); i++) {
    FairTimeStamp* myData = (FairTimeStamp*)fInputArray->At(i);
    myData->SetEntryNr(FairLink(0, fEntryNr, fInputBranch, i));
    if (fVerbose > 1) {
      std::cout << "Sorter filled with: ";
      myData->Print();
      std::cout<< std::endl;
    }
    fSorter->AddElement(myData, myData->GetTimeStamp());
  }
  if (fVerbose > 2) { fSorter->Print(); }

  std::vector<FairTimeStamp*> sortedData = fSorter->GetOutputData();


  fOutputArray = FairRootManager::Instance()->GetEmptyTClonesArray(fOutputBranch);
  for (int i = 0; i < sortedData.size(); i++) {
    AddNewDataToTClonesArray(sortedData[i]);
  }
  fSorter->DeleteOutputData();
  fEntryNr++;
}

// -------------------------------------------------------------------------

void FairRingSorterTask::FinishEvent()
{
  fOutputArray->Delete();
}

void FairRingSorterTask::FinishTask()
{
  fInputArray = FairRootManager::Instance()->GetTClonesArray(fInputBranch);
  if (fVerbose > 2) { std::cout << "-I- FairRingSorterTaskT::FinishTask Size InputArray: " << fInputArray->GetEntriesFast() << std::endl; }
  for (int i = 0; i < fInputArray->GetEntriesFast(); i++) {
    FairTimeStamp* myDigi = (FairTimeStamp*) fInputArray->At(i);
    fSorter->AddElement(myDigi, ((FairTimeStamp*)myDigi)->GetTimeStamp());
  }
  fSorter->Print();
  fSorter->WriteOutAll();
  std::vector<FairTimeStamp*> sortedData = fSorter->GetOutputData();

  FairRootManager* ioman = FairRootManager::Instance();
  fOutputArray = ioman->GetEmptyTClonesArray(fOutputBranch);
  for (int i = 0; i < sortedData.size(); i++) {
    if (fVerbose > 2) {
      std::cout << i << " FinishTask : ";
      sortedData[i]->Print();
      std::cout << std::endl;
    }

    AddNewDataToTClonesArray(sortedData[i]);
  }
  fSorter->DeleteOutputData();
  if (fVerbose > 1) {
    fSorter->Print();
  }
  ioman->SetLastFill();
}

ClassImp(FairRingSorterTask);
