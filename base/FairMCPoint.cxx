#include "FairMCPoint.h"

// -----   Default constructor   -------------------------------------------
FairMCPoint::FairMCPoint() 
 : fTrackID    (-1),
   fEventId(0),
   fPx(0.),         
   fPy(0.), 
   fPz(0.),
   fTime (0.),
   fLength(0.),
   fELoss(0.)
   
{
  
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairMCPoint::FairMCPoint(Int_t trackID, Int_t detID, TVector3 pos, 
			TVector3 mom, Double_t tof, Double_t length, 
			Double_t eLoss, UInt_t EventId) 
  :FairBasePoint(detID, pos),
   fTrackID    ( trackID),
   fEventId    (EventId),
   fPx         ( mom.Px()),
   fPy         ( mom.Py()),
   fPz         ( mom.Pz()),
   fTime       ( tof),
   fLength     ( length),
   fELoss      ( eLoss)
   
{
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairMCPoint::~FairMCPoint() { }
// -------------------------------------------------------------------------



ClassImp(FairMCPoint)

