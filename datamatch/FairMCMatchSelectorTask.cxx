// -------------------------------------------------------------------------
// -----                FairMCMatchSelectorTask source file             -----
// -----                  Created 18/07/08  by T.Stockmanns        -----
// -------------------------------------------------------------------------
// libc includes
#include <iostream>

// Root includes
#include "TROOT.h"
#include "TClonesArray.h"

// framework includes
#include "FairRootManager.h"
#include "FairMCMatchSelectorTask.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairHit.h"
#include "FairMultiLinkedData.h"
#include "FairRootManager.h"

#include "FairMCEntry.h"


// -----   Default constructor   -------------------------------------------
FairMCMatchSelectorTask::FairMCMatchSelectorTask()
  : FairTask("Creates FairMCMatch"), 
    fStart(-1), 
    fStop(-1)
    //    fStart(kUnknown), 
    //    fStop(kUnknown)
{
}
// -------------------------------------------------------------------------

FairMCMatchSelectorTask::FairMCMatchSelectorTask(TString start, TString stop)
  : FairTask("Creates FairMCMatch"), 
    fStartString(start), 
    fStopString(stop), 
    fStart(-1), 
    fStop(-1)
{
}

FairMCMatchSelectorTask::FairMCMatchSelectorTask(Int_t start, Int_t stop)
  : FairTask("Creates FairMCMatch"), 
    fStart(start), 
    fStop(stop), 
    fStartString(""), 
    fStopString("")
{
}

// -----   Destructor   ----------------------------------------------------
FairMCMatchSelectorTask::~FairMCMatchSelectorTask()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus FairMCMatchSelectorTask::Init()
{

  FairRootManager* ioman = FairRootManager::Instance();
  if (!ioman) {
    std::cout << "-E- FairMCMatchSelectorTask::Init: "
	      << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }
  
  fMCMatch = (FairMCMatch*)ioman->GetObject("MCMatch");
  if (fStart < 0 && fStop < 0){
    fStart = ioman->GetBranchId(fStartString);
    fStop = ioman->GetBranchId(fStopString);
    std::cout << fStartString << ": " << fStart << " / " << fStopString << ": " << fStop << std::endl;
  }
  
  std::cout << "-I- FairMCMatchSelectorTask::Init: Initialization successfull" << std::endl;
  
  
  return kSUCCESS;
}


// -------------------------------------------------------------------------
void FairMCMatchSelectorTask::SetParContainers()
{
}


// -----   Public method Exec   --------------------------------------------
void FairMCMatchSelectorTask::Exec(Option_t* opt)
{
  std::cout << "Output Selector: " << std::endl;
  SetWeights();
  fMCMatch->CreateArtificialStage("MCTrack");
  std::cout << fMCMatch->GetMCInfo(fStart, fStop);
  std::cout << std::endl;
}

void FairMCMatchSelectorTask::SetWeights()
{
  fMCMatch->SetCommonWeightStages(fCommonWeight);
  for (int i = 0; i < fStageWeights.size();i++){
    fMCMatch->GetMCStageType(fStageWeights[i].first)->SetWeight(fStageWeights[i].second);
  }
}

void FairMCMatchSelectorTask::Finish()
{
}


ClassImp(FairMCMatchSelectorTask);
