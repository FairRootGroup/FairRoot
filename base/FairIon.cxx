// -------------------------------------------------------------------------
// -----                         FairIon source file                    -----
// -----                 Created 27/08/04  by  V. Friese               -----
// -------------------------------------------------------------------------

#include "FairIon.h"

#include <iostream>

using std::cout;
using std::endl;

const Double_t kProtonMass = 0.92827231;


// -----   Default constructor   -------------------------------------------
FairIon::FairIon() 
 :fZ(0),
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
  if (mass == 0.) fMass = kProtonMass * Double_t(a);
  else fMass = mass;
  cout << "-I- FairIon: New ion " << name << ", z = " <<  z << ", a = "
       << a << ", charge = " << q << ", mass = " << fMass << " GeV "
       << endl;     
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairIon::~FairIon() {};
// -------------------------------------------------------------------------



ClassImp(FairIon)
