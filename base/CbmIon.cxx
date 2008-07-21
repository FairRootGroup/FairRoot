// -------------------------------------------------------------------------
// -----                         CbmIon source file                    -----
// -----                 Created 27/08/04  by  V. Friese               -----
// -------------------------------------------------------------------------

#include "CbmIon.h"

#include <iostream>

using std::cout;
using std::endl;

const Double_t kProtonMass = 0.92827231;


// -----   Default constructor   -------------------------------------------
CbmIon::CbmIon() 
 :fZ(0),
  fA(0),
  fQ(0),
  fExcEnergy(0), 
  fMass(0)
{
 
}
// -------------------------------------------------------------------------


// -----   Standard constructor   ------------------------------------------
CbmIon::CbmIon(const char* name, Int_t z, Int_t a, Int_t q, Double_t e,
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
  cout << "-I- CbmIon: New ion " << name << ", z = " <<  z << ", a = "
       << a << ", charge = " << q << ", mass = " << fMass << " GeV "
       << endl;     
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
CbmIon::~CbmIon() {};
// -------------------------------------------------------------------------



ClassImp(CbmIon)
