// -------------------------------------------------------------------------
// -----                FairParticleGenerator source file               -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairParticleGenerator.h"

#include "FairPrimaryGenerator.h"

#include <iostream>

// -----   Default constructor   ------------------------------------------
FairParticleGenerator::FairParticleGenerator()
  : FairGenerator(),
    fPDGType(-1),
    fMult(0),
    fPx(0),
    fPy(0),
    fPz(0),
    fVx(0),
    fVy(0),
    fVz(0)

{
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
FairParticleGenerator::FairParticleGenerator(Int_t pdgid, Int_t mult,
    Double32_t px, Double32_t py,
    Double32_t pz, Double32_t vx,
    Double32_t vy, Double32_t vz)
  : FairGenerator(),
    fPDGType(pdgid),
    fMult(mult),
    fPx(px),
    fPy(py),
    fPz(pz),
    fVx(vx),
    fVy(vy),
    fVz(vz)

{
}
// ------------------------------------------------------------------------



// -----   Public method SetM<omentum   -----------------------------------
void FairParticleGenerator::SetMomentum(Double32_t px, Double32_t py,
                                        Double32_t pz)
{
  fPx = px;
  fPy = py;
  fPz = pz;
}
// ------------------------------------------------------------------------



// -----   Public method SetVertex   --------------------------------------
void FairParticleGenerator::SetVertex(Double32_t vx, Double32_t vy,
                                      Double32_t vz)
{
  fVx = vx;
  fVy = vy;
  fVz = vz;
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairParticleGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

  // Check for particle type
  if ( fPDGType == -1 ) {
    Fatal("FairParticleGenerator","PDG code not defined.");
  }

  // Generate particles
  for (Int_t k = 0; k < fMult; k++) {
    primGen->AddTrack(fPDGType, fPx, fPy, fPz, fVx, fVy, fVz);
  }

  return kTRUE;

}
// ------------------------------------------------------------------------


ClassImp(FairParticleGenerator)

