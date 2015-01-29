// -------------------------------------------------------------------------
// -----                   FairLinkManager source file                 -----
// -----            Created 05/06/14  by T.Stockmanns                  -----
// -------------------------------------------------------------------------


#include "FairLinkManager.h"

#include "FairLogger.h"
#include "FairRun.h"

using std::set;

#include <iostream>

TMCThreadLocal FairLinkManager* FairLinkManager::fgInstance = 0;
//_____________________________________________________________________________
FairLinkManager* FairLinkManager::Instance()
{
// Returns singleton instance.
// ---
  return fgInstance;
}
//_____________________________________________________________________________

FairLinkManager::FairLinkManager()
  : TObject(),
    fIgnoreTypes(),
    fIgnoreSetting(kTRUE),
    fLogger(0)
{
  if (fgInstance) {
    Fatal("FairLinkManager", "Singleton instance already exists.");
    return;
  }
//  std::cout << "-I- FairLinkManager::FairLinkManager created!" << std::endl;
  fgInstance = this;

  // Logger only on master - TO DO
  if ( FairRun::Instance()->GetIsMaster() ) {
    fLogger = FairLogger::GetLogger();
  }
}
//_____________________________________________________________________________
FairLinkManager::~FairLinkManager()
{
//
  fLogger->Debug(MESSAGE_ORIGIN,"Enter Destructor of FairLinkManager");
  fgInstance = 0;
  fLogger->Debug(MESSAGE_ORIGIN, "Leave Destructor of FairLinkManager");
}
//_____________________________________________________________________________

void FairLinkManager::AddIgnoreType(Int_t type)
{
	if (fIgnoreSetting == kFALSE){
		fLogger->Debug(MESSAGE_ORIGIN, "AddIgnoreType ignored because of IncludeType setting");
		return;
	}
	fLogger->Debug(MESSAGE_ORIGIN, "AddIgnoreType");
	fIgnoreTypes.insert(type);
}

void FairLinkManager::AddIncludeType(Int_t type)
{
	fLogger->Debug(MESSAGE_ORIGIN, "AddIgnoreType");
//	std::cout << "-I- FairLinkManager::AddIgnoreType: " << type << std::endl;
	if (fIgnoreSetting == kTRUE){
		fIgnoreSetting=kFALSE;
		fIgnoreTypes.clear();
	}
	fIgnoreTypes.insert(type);
}


Bool_t FairLinkManager::IsIgnoreType(Int_t type) const
{
	if (fIgnoreSetting)
		return fIgnoreTypes.count(type);
	else
		return !fIgnoreTypes.count(type);

}

ClassImp(FairLinkManager)
