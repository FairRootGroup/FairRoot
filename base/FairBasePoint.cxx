#include "FairBasePoint.h"


// -----   Default constructor   -------------------------------------------
FairBasePoint::FairBasePoint()
  : FairTimeStamp(),
    fDetectorID (-1),
    fX(0),
    fY (0),
    fZ(0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairBasePoint::FairBasePoint(Int_t detID, TVector3& pos)
  :FairTimeStamp(),
   fDetectorID  (detID),
   fX           (pos.X()),
   fY           (pos.Y()),
   fZ           (pos.Z())
{
  //AddLink(detID, index);
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairBasePoint::~FairBasePoint() { }
// -------------------------------------------------------------------------



ClassImp(FairBasePoint)
