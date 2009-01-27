// -------------------------------------------------------------------------
// -----                         FairHit source file                    -----
// -----            Created 08/09/04  by V. Friese / D. Bertini        -----
// -------------------------------------------------------------------------


#include "FairHit.h"


// -----   Default constructor   -------------------------------------------
FairHit::FairHit() 
: fDetectorID (-1),
  fX(0), 
  fY (0), 
  fZ(0),
  fDx(0), 
  fDy(0),
  fDz(0),
  fRefIndex(-1)

{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairHit::FairHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index) 
  :fDetectorID  (detID),
   fX           (pos.X()),
   fY           (pos.Y()),
   fZ           (pos.Z()),
   fDx          (dpos.X()),
   fDy          (dpos.Y()),
   fDz          (dpos.Z()),
   fRefIndex    (index)
{
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairHit::~FairHit() { }
// -------------------------------------------------------------------------



ClassImp(FairHit)
