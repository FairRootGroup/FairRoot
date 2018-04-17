// -------------------------------------------------------------------------
// -----                FairPrintFairLinks source file             -----
// -----                  Created 18/07/08  by T.Stockmanns        -----
// -------------------------------------------------------------------------
// libc includes
#include <FairPrintFairLinks.h>
#include <iostream>
#include <exception>

// Root includes
#include "TROOT.h"
#include "TClonesArray.h"
#include "TChain.h"
#include "TChainElement.h"

// framework includes
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairHit.h"
#include "FairMultiLinkedData_Interface.h"
#include "FairLogger.h"

//#include "PndDetectorList.h"


// -----   Default constructor   -------------------------------------------
FairPrintFairLinks::FairPrintFairLinks() : FairTask("Creates PndMCMatch"), fSelectedBranches(new TList())
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairPrintFairLinks::~FairPrintFairLinks()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus FairPrintFairLinks::Init()
{
	  FairRootManager* ioman = FairRootManager::Instance();
	  	if (!ioman) {
	  		LOG(ERROR) << "-E- FairPrintFairLinks::Init: "
	  				<< "RootManager not instantiated!";
	  		return kFATAL;
	  	}

	  	TList* branchNames;
	  	if (fSelectedBranches->GetEntries() > 0){
	  		branchNames = fSelectedBranches;
	  	} else {
	  		branchNames = ioman->GetBranchNameList();
	  	}

	  	InitBranchList(branchNames);

	  	PrintBranchNameList(ioman->GetBranchNameList());

  return kSUCCESS;
}


void FairPrintFairLinks::InitBranchList(TList* branches)
{
	FairRootManager* ioman = FairRootManager::Instance();
	for (int i = 0; i < branches->GetEntries(); i++) {				//removes branches which do not contain objects derived from FairMultiLinkedData_Interface
		TObjString* branchName = (TObjString*) branches->At(i);
		if (branchName->String().Contains("_link")) continue;
		if (branchName->String().Contains("MCTrack")) continue;
		if (branchName->String().Contains(".")) continue;
		if (branchName->String().Contains("GeoTracks")) continue;
		if (branchName->String().Contains("Header")) continue;
		if (branchName->String().Contains("Info")) continue;
		if (branchName->String().Contains("ID")) continue;
		if (branchName->String().Contains("PidAlgo")) continue;
		if (branchName->String().Contains("Riemann")) continue;

		LOG(DEBUG) << "FairPrintFairLinks::Init() branches: " << branchName->String();
		if ((TClonesArray*)ioman->GetObject(branchName->String()) != 0){
			fBranches[ioman->GetBranchId(branchName->String())] = (TClonesArray*)ioman->GetObject(branchName->String());
		} else {
			LOG(WARNING) << "-E- FairPrintFairLinks " << branchName->String().Data() << " is not a valid branch name!";
		}
	}
}


void FairPrintFairLinks::PrintBranchNameList(TList* branches)
{
	LOG(INFO) << "-I- FairPrintFairLinks Branches:";

	for (int i = 0; i < branches->GetEntries(); i++) {
		TObjString* branchName = (TObjString*) branches->At(i);
		LOG(INFO) << i << " : " << branchName->String().Data() << std::endl;
	}
	LOG(INFO) << std::endl;
}

// -------------------------------------------------------------------------
void FairPrintFairLinks::SetParContainers()
{
  // Get Base Container
//  FairRun* ana = FairRun::Instance();
//  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

}


// -----   Public method Exec   --------------------------------------------
void FairPrintFairLinks::Exec(Option_t*)
{
	LOG(INFO) << std::endl << "--------------------- Event " << FairRootManager::Instance()->GetEntryNr() <<
			" at " << FairRootManager::Instance()->GetEventTime() << " ns ----------------------";
	for (std::map<Int_t, TClonesArray*>::iterator iter = fBranches.begin(); iter != fBranches.end(); iter++){
		LOG(INFO) << std::endl << iter->first << " : " << FairRootManager::Instance()->GetBranchName(iter->first) << " Entries: " << iter->second->GetEntriesFast();
		for (int i = 0; i < iter->second->GetEntriesFast(); i++){
			FairMultiLinkedData_Interface* myLinks = (FairMultiLinkedData_Interface*)iter->second->At(i);
			if (myLinks->GetPointerToLinks() != 0){
				LOG(INFO) << i << " : " << *myLinks << std::endl;
			}
		}
	}
}

void FairPrintFairLinks::Finish()
{
}


ClassImp(FairPrintFairLinks);
