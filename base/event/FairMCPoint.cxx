#include "FairMCPoint.h"
#include "FairLogger.h"

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

FairMCPoint::FairMCPoint(const FairMCPoint &MCPoint) :
  FairMultiLinkedData(), 
  fTrackID(MCPoint.fTrackID), fEventId(MCPoint.fEventId), fDetectorID(MCPoint.fDetectorID),
  fTime(MCPoint.fTime), fLength(MCPoint.fLength), fELoss(MCPoint.fELoss), 
  fPx(MCPoint.fPx), fPy(MCPoint.fPy), fPz(MCPoint.fPz),
  fX(MCPoint.fX), fY(MCPoint.fY), fZ(MCPoint.fZ)
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairMCPoint::~FairMCPoint() { }
// -------------------------------------------------------------------------
void FairMCPoint::Print(const Option_t* opt) const
{
  LOG(DEBUG) << "FairMC point for track " << fTrackID
             << " in detector " << fDetectorID << FairLogger::endl;
  LOG(DEBUG) << "Position (" << fX << ", " << fY << ", " << fZ
             << ") cm" << FairLogger::endl;
  LOG(DEBUG) << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
             << ") GeV" << FairLogger::endl;
  LOG(DEBUG) << "    Time " << fTime << " ns,  Length " << fLength
             << " cm,  Energy loss " << fELoss*1.0e06 << " keV" << FairLogger::endl;
}



ClassImp(FairMCPoint)

