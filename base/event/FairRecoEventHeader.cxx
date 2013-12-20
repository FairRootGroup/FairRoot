// -------------------------------------------------------------------------
// -----            FairRecoEventHeader source file                    -----
// -----            Created 20/09/13                 R.Karabowicz      -----
// -------------------------------------------------------------------------


#include "FairRecoEventHeader.h"

// -----   Default constructor   -------------------------------------------
FairRecoEventHeader::FairRecoEventHeader()
  :fRunId(0),
   fIdentifier(0),
   fEventTime(-1.),
   fEventTimeError(-1.)
{

}
// -----   Destructor   ----------------------------------------------------
FairRecoEventHeader::~FairRecoEventHeader() { }
// -------------------------------------------------------------------------

ClassImp(FairRecoEventHeader)
