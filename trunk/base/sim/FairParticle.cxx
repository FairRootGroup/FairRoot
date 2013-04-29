// -------------------------------------------------------------------------
// -----                   FairParticle source file                    -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------


// Extended TParticle with pointers to mother and daughters
// particles

#include "FairParticle.h"

#include "TParticle.h"
#include "TMCParticleType.h"
#include <iostream>
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
using std::cout;
using std::endl;

ClassImp(FairParticle)
//_____________________________________________________________________________
FairParticle::FairParticle(Int_t id, TParticle* particle)
  : TObject(),
    fpdg(id),
    fParticle(particle),
    fMother(0),
    fDaughters(0),
    fname(particle->GetName()),
    fmcType(kPTIon),
    fmass(particle->GetMass()),
    fcharge(particle->GetPDG()->Charge()),
    fDecayTime(particle->GetPDG()->Lifetime()),
    fpType("Ion"),
    fwidth(particle->GetPDG()->Width()),
    fiSpin((Int_t)particle->GetPDG()->Spin()),
    fiParity(particle->GetPDG()->Parity()),
    fiConjugation(0),
    fiIsospin((Int_t)particle->GetPDG()->Isospin()),
    fiIsospinZ(0),
    fgParity(0),
    flepton(0),
    fbaryon(0),
    fstable(particle->GetPDG()->Stable())
{
}
//_____________________________________________________________________________

FairParticle::FairParticle(const char* name, Int_t z, Int_t a, Int_t s,Double_t mass ,Int_t q, Bool_t stable, Double_t decaytime)
  :  TObject(),
     fpdg(1000000000+10000000*s+10000* z +10 * a),
     fParticle(0),
     fMother(0),
     fDaughters(0),
     fname(name),
     fmcType(kPTIon),
     fmass(0),
     fcharge(0),
     fDecayTime(decaytime),
     fpType("Ion"),
     fwidth(0),
     fiSpin(0),
     fiParity(0),
     fiConjugation(0),
     fiIsospin(0),
     fiIsospinZ(0),
     fgParity(0),
     flepton(0),
     fbaryon(0),
     fstable(stable)
{

  TDatabasePDG* pdgDB = TDatabasePDG::Instance();
  if (!pdgDB->GetParticle(fpdg)) {
    if(mass == 0 ) {
      TParticlePDG* kProton = pdgDB->GetParticle(2212);
      Double_t kProtonMass=kProton->Mass();
      mass = a*kProtonMass;
    }
    pdgDB->AddParticle(name, name, mass, stable, 0, q, "kPTHadron", fpdg);

  }

  fParticle = new TParticle();
  fParticle->SetPdgCode(fpdg);

  fmcType= kPTHadron;
  fmass= mass;
  fcharge= fParticle->GetPDG()->Charge();
  fDecayTime=decaytime ;
  fwidth=   fParticle->GetPDG()->Width();
  fiSpin=   (Int_t)fParticle->GetPDG()->Spin();
  fiParity=  fParticle->GetPDG()->Parity();
  fiConjugation= 0;
  fiIsospin= (Int_t) fParticle->GetPDG()->Isospin();
  fiIsospinZ= 0;
  fgParity= 0;
  flepton=  0;
  fbaryon=  0;
  fstable= fParticle->GetPDG()->Stable();


}
//_____________________________________________________________________________

FairParticle::FairParticle(const char* name, Int_t z, Int_t a, Double_t mass ,Int_t q, Bool_t stable, Double_t decaytime)
  :  TObject(),
     fpdg(10000000+10000* z +10 * a),
     fParticle(0),
     fMother(0),
     fDaughters(0),
     fname(name),
     fmcType(kPTIon),
     fmass(0),
     fcharge(0),
     fDecayTime(decaytime),
     fpType("Ion"),
     fwidth(0),
     fiSpin(0),
     fiParity(0),
     fiConjugation(0),
     fiIsospin(0),
     fiIsospinZ(0),
     fgParity(0),
     flepton(0),
     fbaryon(0),
     fstable(stable)
{
  //  fpdg= 10000000+10000* z +10 * a;

  //  fDecayTime= decaytime;
  TDatabasePDG* pdgDB = TDatabasePDG::Instance();

  if (!pdgDB->GetParticle(fpdg)) {
    if(mass == 0 ) {
      TParticlePDG* kProton = pdgDB->GetParticle(2212);
      Double_t kProtonMass=kProton->Mass();
      mass = a*kProtonMass;
    }
    pdgDB->AddParticle(name, name, mass, stable, 0, q, "kPTHadron", fpdg);

  }

  fParticle = new TParticle();
  fParticle->SetPdgCode(fpdg);

  fmcType= kPTHadron;
  fmass= mass;
  fcharge= fParticle->GetPDG()->Charge();
  fDecayTime=decaytime ;
  fwidth=   fParticle->GetPDG()->Width();
  fiSpin=   (Int_t)fParticle->GetPDG()->Spin();
  fiParity=  fParticle->GetPDG()->Parity();
  fiConjugation= 0;
  fiIsospin= (Int_t) fParticle->GetPDG()->Isospin();
  fiIsospinZ= 0;
  fgParity= 0;
  flepton=  0;
  fbaryon=  0;
  fstable= fParticle->GetPDG()->Stable();


}

//_____________________________________________________________________________
FairParticle::FairParticle(Int_t id, TParticle* particle, FairParticle* mother)
  : TObject(),
    fpdg(id),
    fParticle(particle),
    fMother(mother),
    fDaughters(),
    fname(particle->GetName()),
    fmcType (kPTIon),
    fmass  (0),
    fcharge(0),
    fDecayTime(0),
    fpType("Ion"),
    fwidth(0),
    fiSpin(0),
    fiParity(0),
    fiConjugation(0),
    fiIsospin(0),
    fiIsospinZ(0),
    fgParity(0),
    flepton(0),
    fbaryon(0),
    fstable(kTRUE)

{
//
}

//_____________________________________________________________________________
FairParticle::FairParticle( Int_t pdg,
                            const TString name,
                            TMCParticleType mcType,
                            Double_t mass,
                            Double_t charge,
                            Double_t lifetime,
                            const TString pType,
                            Double_t width,
                            Int_t iSpin,
                            Int_t iParity,
                            Int_t iConjugation,
                            Int_t iIsospin,
                            Int_t iIsospinZ,
                            Int_t gParity,
                            Int_t lepton,
                            Int_t baryon,
                            Bool_t stable )
  : TObject(),
    fpdg  (pdg),
    fParticle( new TParticle()),
    fMother(0),
    fDaughters(0),
    fname(name),
    fmcType (mcType),
    fmass  (mass),
    fcharge( charge),
    fDecayTime( lifetime),
    fpType(   pType),
    fwidth(   width),
    fiSpin(  iSpin),
    fiParity(   iParity),
    fiConjugation( iConjugation),
    fiIsospin(   iIsospin),
    fiIsospinZ(  iIsospinZ),
    fgParity( gParity),
    flepton(  lepton),
    fbaryon(  baryon),
    fstable(  stable)
{

  if (!TDatabasePDG::Instance()->GetParticle(fpdg)) {
    TDatabasePDG::Instance()
    ->AddParticle(fname, fname, fmass, fstable, fwidth,fcharge ,pType, fpdg);

  }

  fParticle->SetPdgCode(fpdg);

}

//_____________________________________________________________________________
FairParticle::FairParticle()
  : TObject(),
    fpdg(0),
    fParticle(0),
    fMother(0),
    fDaughters(),
    fname("ion"),
    fmcType (kPTIon),
    fmass  (0),
    fcharge(0),
    fDecayTime(0),
    fpType("Ion"),
    fwidth(0),
    fiSpin(0),
    fiParity(0),
    fiConjugation(0),
    fiIsospin(0),
    fiIsospinZ(0),
    fgParity(0),
    flepton(0),
    fbaryon(0),
    fstable(kTRUE)
{
//
}

//_____________________________________________________________________________
FairParticle::~FairParticle()
{
//
  delete fParticle;
}

//
// public methods
//

//_____________________________________________________________________________
void FairParticle::SetMother(FairParticle* particle)
{
// Adds particles daughter
// ---

  fMother.SetObject(particle);
}

//_____________________________________________________________________________
void FairParticle::AddDaughter(FairParticle* particle)
{
// Adds particles daughter
// ---

  fDaughters.Add(particle);
}

//_____________________________________________________________________________
void FairParticle::Print(Option_t* option) const
{
// Prints particle properties.
// ---
//  return;

  cout << "Particle: " << fParticle->GetName()  << "  with ID:  " << fpdg << endl;

  // fParticle->Print();

  if (GetMother()) {
    cout << "Mother:    " << GetMother()->GetParticle()->GetName()
         << "  with ID: " << GetMother()->GetPDG() << endl;
  } else {
    cout << "Primary    " << endl;
  }

  cout << "Number of daughters: " << GetNofDaughters() << endl;
  cout << endl;
}

//_____________________________________________________________________________
void FairParticle::PrintDaughters() const
{
// Prints particles daughters.
// ---

  for (Int_t i=0; i<GetNofDaughters(); i++)  {
    cout << i << "th daughter: " << endl;
    GetDaughter(i)->Print();
  }
}

//_____________________________________________________________________________
Int_t  FairParticle::GetPDG() const
{
// Returs particle ID.
// ---

  return fpdg;
}


//_____________________________________________________________________________
TParticle*  FairParticle::GetParticle() const
{
// Returns particle definition (TParticle).
// ---

  return fParticle;
}

//_____________________________________________________________________________
FairParticle* FairParticle::GetMother() const
{
// Returns particle definition (TParticle).
// ---

  return (FairParticle*) fMother.GetObject();
}

//_____________________________________________________________________________
Int_t FairParticle::GetNofDaughters() const
{
// Returns number of daughters.
// ---

  return fDaughters.GetEntriesFast();
}

//_____________________________________________________________________________
FairParticle* FairParticle::GetDaughter(Int_t i) const
{
// Returns i-th daughter.
// ---

  if (i < 0 || i >= GetNofDaughters()) {
    Fatal("GetDaughter", "Index out of range");
  }

  return (FairParticle*) fDaughters.At(i);
}

