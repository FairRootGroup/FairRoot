/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairIonGenerator source file                 -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairIonGenerator.h"

#include "FairIon.h"                    // for FairIon
#include "FairParticle.h"               // for FairParticle
#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator
#include "FairRunSim.h"                 // for FairRunSim
#include "FairLogger.h"                 // for logging

#include <iosfwd>                       // for ostream
#include "TDatabasePDG.h"               // for TDatabasePDG
#include "TObjArray.h"                  // for TObjArray
#include "TParticle.h"                  // for TParticle
#include "TParticlePDG.h"               // for TParticlePDG

#include <stdio.h>                      // for NULL, sprintf

// -----   Initialsisation of static variables   --------------------------
Int_t FairIonGenerator::fgNIon = 0;
// ------------------------------------------------------------------------



// -----   Default constructor   ------------------------------------------
FairIonGenerator::FairIonGenerator()
  :FairGenerator(),
   fMult(0),
   fPx(0), fPy(0), fPz(0),
   fVx(0), fVy(0), fVz(0),
   fIon(NULL),  fQ(0)
{
//  LOG(warn) << "FairIonGenerator: "
//               << " Please do not use the default constructor! ";
}
// ------------------------------------------------------------------------

FairIonGenerator::FairIonGenerator(const Char_t* ionName, Int_t mult,
                                   Double_t px, Double_t py, Double_t pz,
                                   Double_t vx, Double_t vy, Double_t vz)
  :FairGenerator(),
   fMult(mult),
   fPx(px), fPy(py), fPz(pz),
   fVx(vx), fVy(vy), fVz(vz),
   fIon(NULL),  fQ(0)

{

  FairRunSim* fRun=FairRunSim::Instance();
  TObjArray* UserIons=fRun->GetUserDefIons();
  TObjArray* UserParticles=fRun->GetUserDefParticles();
  FairParticle* part=0;
  fIon =static_cast<FairIon*>(UserIons->FindObject(ionName));
  if(fIon) {
    fgNIon++;
    fMult = mult;
    fPx   = Double_t(fIon->GetA()) * px;
    fPy   = Double_t(fIon->GetA()) * py;
    fPz   = Double_t(fIon->GetA()) * pz;
    fVx   = vx;
    fVy   = vy;
    fVz   = vz;

  } else {
    part= static_cast<FairParticle*>(UserParticles->FindObject(ionName));
    if(part) {
      fgNIon++;
      TParticle* particle=part->GetParticle();
      fMult = mult;
      fPx   = Double_t(particle->GetMass()/0.92827231) * px;
      fPy   = Double_t(particle->GetMass()/0.92827231) * py;
      fPz   = Double_t(particle->GetMass()/0.92827231) * pz;
      fVx   = vx;
      fVy   = vy;
      fVz   = vz;
    }
  }
  if(fIon==0 && part==0 ) {
    LOG(fatal) << "Ion or Particle is not defined !";
  }

}
// ------------------------------------------------------------------------



// -----   Default constructor   ------------------------------------------
FairIonGenerator::FairIonGenerator(Int_t z, Int_t a, Int_t q, Int_t mult,
                                   Double_t px, Double_t py, Double_t pz,
                                   Double_t vx, Double_t vy, Double_t vz)
  :FairGenerator(),
   fMult(mult),
   fPx(Double_t(a)*px), fPy(Double_t(a)*py), fPz(Double_t(a)*pz),
   fVx(vx), fVy(vy), fVz(vz),
   fIon(NULL),  fQ(0)

{
  fgNIon++;
  /*
  fMult = mult;
  fPx   = Double_t(a) * px;
  fPy   = Double_t(a) * py;
  fPz   = Double_t(a) * pz;
  fVx   = vx;
  fVy   = vy;
  fVz   = vz;
  */
  char buffer[20];
  sprintf(buffer, "FairIon%d", fgNIon);
  fIon= new FairIon(buffer, z, a, q);
  FairRunSim* run = FairRunSim::Instance();
  if ( ! run ) {
    LOG(error) << "No FairRun instantised!";
  } else {
    run->AddNewIon(fIon);
  }
}
//_________________________________________________________________________

FairIonGenerator::FairIonGenerator(const FairIonGenerator& rhs)
  :FairGenerator(rhs),
   fMult(rhs.fMult),
   fPx(rhs.fPx), fPy(rhs.fPy), fPz(rhs.fPz),
   fVx(rhs.fVx), fVy(rhs.fVy), fVz(rhs.fVz),
   fIon(rhs.fIon), // CHECK
   fQ(0)
{
  // fIon= new FairIon(buffer, z, a, q);
  FairRunSim* run = FairRunSim::Instance();
  if ( ! run ) {
    LOG(error) << "No FairRun instantised!";
  } else {
    run->AddNewIon(fIon);
  }
}

// -----   Destructor   ---------------------------------------------------
FairIonGenerator::~FairIonGenerator()
{
// if (fIon) delete fIon;
}
//_________________________________________________________________________



// -----   Public method SetExcitationEnergy   ----------------------------
void FairIonGenerator::SetExcitationEnergy(Double_t eExc)
{
  fIon->SetExcEnergy(eExc);
}
//_________________________________________________________________________



// -----   Public method SetMass   ----------------------------------------
void FairIonGenerator::SetMass(Double_t mass)
{
  fIon->SetMass(mass);
}
//_________________________________________________________________________



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairIonGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

// if ( ! fIon ) {
//   LOG(warn) << "FairIonGenerator: No ion defined! ";
//   return kFALSE;
// }

  TParticlePDG* thisPart =
    TDatabasePDG::Instance()->GetParticle(fIon->GetName());
  if ( ! thisPart ) {
    LOG(warn) << "FairIonGenerator: Ion " << fIon->GetName()
		 << " not found in database!";
    return kFALSE;
  }

  int pdgType = thisPart->PdgCode();

  LOG(info) << "FairIonGenerator: Generating " << fMult << " ions of type "
	    << fIon->GetName() << " (PDG code " << pdgType << ")";
  LOG(info) << "    Momentum (" << fPx << ", " << fPy << ", " << fPz
	    << ") Gev from vertex (" << fVx << ", " << fVy
	    << ", " << fVz << ") cm";

  for(Int_t i=0; i<fMult; i++) {
    primGen->AddTrack(pdgType, fPx, fPy, fPz, fVx, fVy, fVz);
  }

  return kTRUE;

}

//_____________________________________________________________________________

// ------------------------------------------------------------------------
FairGenerator* FairIonGenerator::CloneGenerator() const
{
  // Clone for worker (used in MT mode only)

  return new FairIonGenerator(*this);
}

//_____________________________________________________________________________

ClassImp(FairIonGenerator)
