// -------------------------------------------------------------------------
// -----                         FairEventHeader source file           -----
// -----            Created 08/09/04                 D. Bertini        -----
// -------------------------------------------------------------------------


#include "FairEventHeader.h"
#include "FairRootManager.h"

// -----   Default constructor   -------------------------------------------
FairEventHeader::FairEventHeader()
  :fRunId(0),
   fEventTime(-1.),
   fInputFileId(0),
   fMCEntryNo(0)
{

}
// -----   Destructor   ----------------------------------------------------
FairEventHeader::~FairEventHeader() { }
// -------------------------------------------------------------------------

void FairEventHeader::Register()
{
  FairRootManager::Instance()->Register("EventHeader.", "EvtHeader", this, kTRUE);
}


ClassImp(FairEventHeader)
