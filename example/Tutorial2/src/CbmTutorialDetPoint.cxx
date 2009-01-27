#include "CbmTutorialDetPoint.h"

#include <iostream>
using std::cout;
using std::endl;


// -----   Default constructor   -------------------------------------------
CbmTutorialDetPoint::CbmTutorialDetPoint() : CbmMCPoint() { }
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
CbmTutorialDetPoint::CbmTutorialDetPoint(Int_t trackID, Int_t detID, 
					 TVector3 pos, TVector3 mom, 
					 Double_t tof, Double_t length,
					 Double_t eLoss)
  : CbmMCPoint(trackID, detID, pos, mom, tof, length, eLoss) { }
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
CbmTutorialDetPoint::~CbmTutorialDetPoint() { }
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void CbmTutorialDetPoint::Print(const Option_t* opt) const {
  cout << "-I- CbmTutorialDetPoint: TutorialDet point for track " << fTrackID
       << " in detector " << fDetectorID << endl;
  cout << "    Position (" << fX << ", " << fY << ", " << fZ
       << ") cm" << endl;
  cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
       << ") GeV" << endl;
  cout << "    Time " << fTime << " ns,  Length " << fLength
       << " cm,  Energy loss " << fELoss*1.0e06 << " keV" << endl;
}
// -------------------------------------------------------------------------

ClassImp(CbmTutorialDetPoint)
  
