// -------------------------------------------------------------------------
// -----                         FairIon source file                    -----
// -------------------------------------------------------------------------
#include "FairIon.h"

#include <iostream>
#include "TDatabasePDG.h"
#include "TParticlePDG.h"

using std::cout;
using std::endl;

const Double_t FairIon::amu=0.931494028 ; // Gev/c**2


// -----   Default constructor   -------------------------------------------
FairIon::FairIon()
  :TNamed(),
   fZ(0),
   fA(0),
   fQ(0),
   fExcEnergy(0),
   fMass(0)
{

}
// -------------------------------------------------------------------------


// -----   Standard constructor   ------------------------------------------
FairIon::FairIon(const char* name, Int_t z, Int_t a, Int_t q, Double_t e,
                 Double_t mass)
  : TNamed(name, "User defined ion"),
    fZ(z),
    fA(a),
    fQ(q),
    fExcEnergy(e),
    fMass(0)
{

  TDatabasePDG* pdgDB = TDatabasePDG::Instance();
  TParticlePDG* kProton = pdgDB->GetParticle(2212);
  Double_t kProtonMass=kProton->Mass();

  if (mass == 0.) { fMass = kProtonMass * Double_t(a); }
  else { fMass = mass; }
  cout << "-I- FairIon: New ion " << name << ", z = " <<  z << ", a = "
       << a << ", charge = " << q << ", mass = " << fMass << " GeV "
       << endl;
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairIon::~FairIon() {};
// -------------------------------------------------------------------------



ClassImp(FairIon)
