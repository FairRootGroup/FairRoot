// -------------------------------------------------------------------------
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------


#include "FairFileHeader.h"
#include "FairRootManager.h"

// -----   Default constructor   -------------------------------------------
FairFileHeader::FairFileHeader()
  :fRunId(0)
{

}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairFileHeader::~FairFileHeader() { }
// -------------------------------------------------------------------------

//void FairFileHeader::Register()
//{
//  FairRootManager::Instance()->Register("EventHeader.", "EvtHeader", this, kTRUE);
//}


ClassImp(FairFileHeader)
