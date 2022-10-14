/********************************************************************************
 * Copyright (C) 2020-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairConstFieldCreator header file              -----
// -----                Created 12/11/2020  by R. Karabowicz           -----
// -------------------------------------------------------------------------

#include "FairConstFieldCreator.h"

#include "FairConstField.h"
#include "FairConstPar.h"
#include "FairField.h"
#include "FairLogger.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

static FairConstFieldCreator gFairConstFieldCreator;

FairConstFieldCreator::FairConstFieldCreator()
    : FairFieldFactory()
    , fFieldPar(nullptr)
{
}

FairConstFieldCreator::~FairConstFieldCreator() {}

void FairConstFieldCreator::SetParm()
{
    FairRunAna *Run = FairRunAna::Instance();
    FairRuntimeDb *RunDB = Run->GetRuntimeDb();
    fFieldPar = (FairConstPar *)RunDB->getContainer("FairConstPar");
}

FairField *FairConstFieldCreator::createFairField()
{
    FairField *fMagneticField = 0;

    if (!fFieldPar) {
        LOG(error) << "No field parameters available!";
    } else {
        // Instantiate correct field type
        Int_t fType = fFieldPar->GetType();
        if (fType == 0)
            fMagneticField = new FairConstField(fFieldPar);
        else
            LOG(warning) << "FairRunAna::GetField: Unknown field type " << fType;
        LOG(info) << "New field at " << fMagneticField << ", type " << fType;
        // Initialise field
        if (fMagneticField) {
            fMagneticField->Init();
            fMagneticField->Print("");
        }
    }
    return fMagneticField;
}

ClassImp(FairConstFieldCreator);
