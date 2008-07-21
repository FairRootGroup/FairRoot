// -------------------------------------------------------------------------
// -----                       CbmGenericStack source file                    -----
// -----             Created 10/08/04  by D. Bertini                   -----
// -------------------------------------------------------------------------
#include "CbmGenericStack.h"

#include "CbmDetector.h"
#include "CbmRootManager.h"
#include "CbmMCPoint.h"

#include "TError.h"
#include "TLorentzVector.h"
#include "TParticle.h"
#include "TRefArray.h"
//#include "TClonesArray.h"

//#include <map>
//#include <stack>
//#include <iostream>


// -----   Default constructor   -------------------------------------------
CbmGenericStack::CbmGenericStack() {
}
// -------------------------------------------------------------------------
// -----   Constructor with estimated array dimension   --------------------
CbmGenericStack::CbmGenericStack(Int_t size) {
}
// -------------------------------------------------------------------------
// -----   Destructor   ----------------------------------------------------
CbmGenericStack::~CbmGenericStack() {
}
// -------------------------------------------------------------------------
// -----   Virtual method PushTrack   --------------------------------------
void CbmGenericStack::PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
			 Double_t px, Double_t py, Double_t pz,
			 Double_t e, Double_t vx, Double_t vy, Double_t vz, 
			 Double_t time, Double_t polx, Double_t poly,
			 Double_t polz, TMCProcess proc, Int_t& ntr, 
			 Double_t weight, Int_t is) {

}

// -----   Virtual method PopNextTrack   -----------------------------------
TParticle* CbmGenericStack::PopNextTrack(Int_t& iTrack) {
  return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method PopPrimaryForTracking   --------------------------
TParticle* CbmGenericStack::PopPrimaryForTracking(Int_t iPrim) {
  return 0;
}
// -------------------------------------------------------------------------
// -----   Public method AddParticle   -------------------------------------
void CbmGenericStack::AddParticle(TParticle* oldPart) {
}
// -------------------------------------------------------------------------
// -----   Public method FillTrackArray   ----------------------------------
void CbmGenericStack::FillTrackArray() {
}
// -------------------------------------------------------------------------
// -----   Public method UpdateTrackIndex   --------------------------------
void CbmGenericStack::UpdateTrackIndex(TRefArray* detList) {

}
// -------------------------------------------------------------------------
// -----   Public method Reset   -------------------------------------------
void CbmGenericStack::Reset() {
}
// -------------------------------------------------------------------------
// -----   Public method Register   ----------------------------------------
void CbmGenericStack::Register() {
}
// -------------------------------------------------------------------------
// -----   Public method Print  --------------------------------------------
void CbmGenericStack::Print(Int_t iVerbose) const {
}
// -------------------------------------------------------------------------
// -----   Virtual method SetCurrentTrack   --------------------------------
void CbmGenericStack::SetCurrentTrack(Int_t iTrack) {
}
// -------------------------------------------------------------------------
// -----   Virtual method GetNtrack   --------------------------------------
Int_t CbmGenericStack::GetNtrack() const {
return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetNprimary   ------------------------------------
Int_t CbmGenericStack::GetNprimary() const {
return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetCurrentTrack   --------------------------------
TParticle* CbmGenericStack::GetCurrentTrack() const {
return NULL;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetCurrentTrackNumber   --------------------------
Int_t CbmGenericStack::GetCurrentTrackNumber() const {
return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetCurrentParentTrackNumber   --------------------
Int_t CbmGenericStack::GetCurrentParentTrackNumber() const {
return 0;
}
// -------------------------------------------------------------------------
ClassImp(CbmGenericStack)
