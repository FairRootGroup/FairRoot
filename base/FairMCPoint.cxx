#include "FairMCPoint.h"

// -----   Default constructor   -------------------------------------------
FairMCPoint::FairMCPoint()
  : FairMultiLinkedData(),
    fTrackID(-1),
    fEventId(0),
    fPx(0.),
    fPy(0.),
    fPz(0.),
    fTime (0.),
    fLength(0.),
    fELoss(0.),
    fDetectorID (-1),
    fX(0),
    fY (0),
    fZ(0)


{

}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairMCPoint::FairMCPoint(Int_t trackID, Int_t detID, TVector3 pos,
                         TVector3 mom, Double_t tof, Double_t length,
                         Double_t eLoss, UInt_t EventId)
  :FairMultiLinkedData(),
   fTrackID    ( trackID),
   fEventId    (EventId),
   fPx         ( mom.Px()),
   fPy         ( mom.Py()),
   fPz         ( mom.Pz()),
   fTime       ( tof),
   fLength     ( length),
   fELoss      ( eLoss),
   fDetectorID (detID),
   fX(pos.X()),
   fY(pos.Y()),
   fZ(pos.Z())
{
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairMCPoint::~FairMCPoint() { }
// -------------------------------------------------------------------------



ClassImp(FairMCPoint)

