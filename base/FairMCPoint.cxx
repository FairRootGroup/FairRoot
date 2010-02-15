// -------------------------------------------------------------------------
// -----                      FairMCPoint source file                   -----
// -----                  Created 26/07/04  by V. Friese               -----
// -------------------------------------------------------------------------


#include "FairMCPoint.h"


// -----   Default constructor   -------------------------------------------
FairMCPoint::FairMCPoint() 
 : TObject(),
   fTrackID    (-1),
   fDetectorID (-1),
   fX(0.),
   fY(0.),
   fZ(0.),
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
			Double_t eLoss) 
  :fTrackID    ( trackID),
   fDetectorID ( detID),
   fX          ( pos.X()),
   fY          ( pos.Y()),
   fZ          ( pos.Z()),
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

