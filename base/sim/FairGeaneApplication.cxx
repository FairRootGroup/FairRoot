/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairGeaneApplication source file           -----
// -----                   Created 10/11/10  by M. Al-Turany           -----
// -------------------------------------------------------------------------

#include "FairGeaneApplication.h"

#include "FairField.h"   // for FairField

#include <TVirtualMC.h>   // for  TVirtualMC
#include <stdio.h>        // for printf

FairGeaneApplication::FairGeaneApplication()
    : TVirtualMCApplication()
    , fxField(0)
    , fMcVersion(-1)
    , fDebug(kFALSE)
    , fTrkPos(TLorentzVector(0, 0, 0, 0))
{}

FairGeaneApplication::FairGeaneApplication(Bool_t Debug)
    : TVirtualMCApplication()
    , fxField(0)
    , fMcVersion(-1)
    , fDebug(Debug)
    , fTrkPos(TLorentzVector(0, 0, 0, 0))
{
    // constructur used by Geane track propagation
}

FairGeaneApplication::~FairGeaneApplication() {}

void FairGeaneApplication::ConstructGeometry()
{
    TVirtualMC::GetMC()->SetRootGeometry();   // notify VMC about Root geometry
}

void FairGeaneApplication::InitMC(const char*, const char*)
{
    // Initialize MC.

    TVirtualMC::GetMC()->Init();
    TVirtualMC::GetMC()->BuildPhysics();
    fMcVersion = 3;   // Geane

    TVirtualMC::GetMC()->SetMagField(fxField);
}

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

void FairGeaneApplication::SetField(FairField* field)
{
    fxField = field;
}
