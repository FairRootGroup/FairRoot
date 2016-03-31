/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairGeaneApplication source file           -----
// -----                   Created 10/11/10  by M. Al-Turany           -----
// -------------------------------------------------------------------------

#include "FairGeaneApplication.h"

#include "FairField.h"                  // for FairField

#include "TVirtualMC.h"                 // for  TVirtualMC

#include <stdio.h>                      // for printf
#include <iostream>                     // for cout, endl

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
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairGeaneApplication::ConstructGeometry()
{
  TVirtualMC::GetMC()->SetRootGeometry();  // notify VMC about Root geometry
}

void FairGeaneApplication::InitMC(const char*, const char*)
{
// Initialize MC.

  TVirtualMC::GetMC()->Init();
  TVirtualMC::GetMC()->BuildPhysics();
  fMcVersion = 3;  //Geane

  TVirtualMC::GetMC()->SetMagField(fxField);
}
//_____________________________________________________________________________
void FairGeaneApplication::GeaneStepping()
{
// User actions at each step
// ---
  if (fDebug) {
    printf(" FairGeaneApplication::GeaneStepping() \n");
    TVirtualMC::GetMC()->TrackPosition(fTrkPos);
    printf(" Track Position: x = %f   y= %f    z= %f \n  ", fTrkPos.X(), fTrkPos.Y(), fTrkPos.Z());
    printf(" Current Volume name: %s \n", TVirtualMC::GetMC()->CurrentVolName());
    Int_t copyNo;
    Int_t id = TVirtualMC::GetMC()->CurrentVolID(copyNo);
    printf(" Current Volume id = %i  , CopyNo = %i \n", id, copyNo);
  }
}
//_____________________________________________________________________________
void FairGeaneApplication::SetField(FairField* field)
{
  fxField=field;
}

ClassImp(FairGeaneApplication)


