// -------------------------------------------------------------------------
// -----                    FairGeaneApplication source file           -----
// -----                   Created 10/11/10  by M. Al-Turany           -----
// -------------------------------------------------------------------------


#include "FairGeaneApplication.h"
#include "FairField.h"

#include "TVirtualMC.h"
#include "TGeoManager.h"

#include <iostream>

using std::cout;
using std::endl;

//_____________________________________________________________________________
FairGeaneApplication::FairGeaneApplication()
  : TVirtualMCApplication(),
    fxField(0),
    fMcVersion(-1),
    fDebug(kFALSE),
    fTrkPos(TLorentzVector(0,0,0,0))
{
// Default constructor
}
//_____________________________________________________________________________
FairGeaneApplication::FairGeaneApplication(Bool_t Debug)
  : TVirtualMCApplication(),
    fxField(0),
    fMcVersion(-1),
    fDebug(Debug),
    fTrkPos(TLorentzVector(0,0,0,0))
{
  //constructur used by Geane track propagation
}

//_____________________________________________________________________________
FairGeaneApplication::~FairGeaneApplication()
{
// Destructor
  delete gMC;
  gMC=0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairGeaneApplication::ConstructGeometry()
{
  gMC->SetRootGeometry();  // notify VMC about Root geometry
}

void FairGeaneApplication::InitMC(const char* setup, const char* cuts)
{
// Initialize MC.

  gMC->Init();
  gMC->BuildPhysics();
  fMcVersion = 3;  //Geane

#if ROOT_VERSION_CODE >= 333824
  gMC->SetMagField(fxField);
#endif
}
//_____________________________________________________________________________
void FairGeaneApplication::GeaneStepping()
{
// User actions at each step
// ---
  if (fDebug) {
    printf(" FairGeaneApplication::GeaneStepping() \n");
    gMC->TrackPosition(fTrkPos);
    printf(" Track Position: x = %f   y= %f    z= %f \n  ", fTrkPos.X(), fTrkPos.Y(), fTrkPos.Z());
    printf(" Current Volume name: %s \n", gMC->CurrentVolName());
    Int_t copyNo;
    Int_t id = gMC->CurrentVolID(copyNo);
    printf(" Current Volume id = %i  , CopyNo = %i \n", id, copyNo);
  }
}

#if ROOT_VERSION_CODE < 333824
//_____________________________________________________________________________
void FairGeaneApplication::Field(const Double_t* x, Double_t* b) const
{
// put here a const magnetic field as 0th approx
// ---
// cout<< "FairGeaneApplication::Field" <<endl;
  b[0]=0;
  b[1]=0;
  b[2]=0;
  if(fxField) {
    fxField->GetFieldValue(x,b);
//     cout << " FairGeaneApplication::Field the old way of getting field " << endl;
  }
}
#endif
//_____________________________________________________________________________
void FairGeaneApplication::SetField(FairField* field)
{
  fxField=field;
}

ClassImp(FairGeaneApplication)


