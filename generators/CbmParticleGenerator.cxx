// -------------------------------------------------------------------------
// -----                CbmParticleGenerator source file               -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "CbmParticleGenerator.h"

#include "CbmPrimaryGenerator.h"

#include <iostream>

// -----   Default constructor   ------------------------------------------
CbmParticleGenerator::CbmParticleGenerator() {
  fPDGType =  -1;
  fMult    =   0;
  fPx = fPy = fPz = 0.;
  fVx = fVy = fVz = 0.;
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
CbmParticleGenerator::CbmParticleGenerator(Int_t pdgid, Int_t mult, 
					   Double32_t px, Double32_t py, 
					   Double32_t pz, Double32_t vx, 
					   Double32_t vy, Double32_t vz) {
  fPDGType = pdgid;
  fMult    = mult;
  fPx      = px;
  fPy      = py;
  fPz      = pz;
  fVx      = vx;
  fVy      = vy;
  fVz      = vz;
}
// ------------------------------------------------------------------------



// -----   Public method SetM<omentum   -----------------------------------
void CbmParticleGenerator::SetMomentum(Double32_t px, Double32_t py, 
				       Double32_t pz) {
   fPx = px;
   fPy = py;
   fPz = pz;
}
// ------------------------------------------------------------------------



// -----   Public method SetVertex   --------------------------------------
void CbmParticleGenerator::SetVertex(Double32_t vx, Double32_t vy, 
				     Double32_t vz) {
   fVx = vx;
   fVy = vy;
   fVz = vz;
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t CbmParticleGenerator::ReadEvent(CbmPrimaryGenerator* primGen) {

  // Check for particle type
  if ( fPDGType == -1 ) 
    Fatal("CbmParticleGenerator","PDG code not defined.");

  // Generate particles
  for (Int_t k = 0; k < fMult; k++) 
    primGen->AddTrack(fPDGType, fPx, fPy, fPz, fVx, fVy, fVz);

  return kTRUE;

}
// ------------------------------------------------------------------------


ClassImp(CbmParticleGenerator)

