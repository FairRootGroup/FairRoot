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

#include "TVirtualMC.h"                 // for gMC, TVirtualMC

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

  gMC->SetMagField(fxField);
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
//_____________________________________________________________________________
void FairGeaneApplication::SetField(FairField* field)
{
  fxField=field;
}

ClassImp(FairGeaneApplication)


