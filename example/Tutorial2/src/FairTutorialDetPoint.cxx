#include "FairTutorialDetPoint.h"

#include <iostream>
using std::cout;
using std::endl;


// -----   Default constructor   -------------------------------------------
FairTutorialDetPoint::FairTutorialDetPoint() : FairMCPoint() { }
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTutorialDetPoint::FairTutorialDetPoint(Int_t trackID, Int_t detID, 
					 TVector3 pos, TVector3 mom, 
					 Double_t tof, Double_t length,
					 Double_t eLoss)
  : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss) { }
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutorialDetPoint::~FairTutorialDetPoint() { }
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTutorialDetPoint::Print(const Option_t*) const {
  cout << "-I- FairTutorialDetPoint: TutorialDet point for track " << fTrackID
       << " in detector " << fDetectorID << endl;
  cout << "    Position (" << fX << ", " << fY << ", " << fZ
       << ") cm" << endl;
  cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
       << ") GeV" << endl;
  cout << "    Time " << fTime << " ns,  Length " << fLength
       << " cm,  Energy loss " << fELoss*1.0e06 << " keV" << endl;
}
// -------------------------------------------------------------------------

ClassImp(FairTutorialDetPoint)
  
