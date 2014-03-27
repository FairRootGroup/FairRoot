#include "FairHit.h"


// -----   Default constructor   -------------------------------------------
FairHit::FairHit()
  : FairTimeStamp(),
    fDx(0),
    fDy(0),
    fDz(0),
    fRefIndex(-1),
    fDetectorID(-1),
    fX(0),
    fY(0),
    fZ(0)


{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairHit::FairHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index)
  :FairTimeStamp(),
   fDx          (dpos.X()),
   fDy          (dpos.Y()),
   fDz          (dpos.Z()),
   fRefIndex    (index),
   fDetectorID  (detID),
   fX           (pos.X()),
   fY           (pos.Y()),
   fZ           (pos.Z())
{
}
// -------------------------------------------------------------------------


FairHit::FairHit(const FairHit &Hit) :
  FairTimeStamp(Hit), 
  fX(Hit.fX), fY(Hit.fY), fZ(Hit.fZ),
  fDx(Hit.fDx), fDy(Hit.fDy), fDz(Hit.fDz),
  fRefIndex(Hit.fRefIndex), fDetectorID(Hit.fDetectorID)
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairHit::~FairHit() { }
// -------------------------------------------------------------------------



ClassImp(FairHit)
