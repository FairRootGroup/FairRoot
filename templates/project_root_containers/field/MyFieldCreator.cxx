/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    MyConstField header file                  -----
// -----                Created 25/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------

#include "MyFieldCreator.h"

#include "FairField.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "MyConstField.h"
#include "MyFieldPar.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

static MyFieldCreator gMyFieldCreator;

MyFieldCreator::MyFieldCreator()
    : FairFieldFactory()
    , fFieldPar(nullptr)
{
}

MyFieldCreator::~MyFieldCreator() {}

void MyFieldCreator::SetParm()
{
    FairRunAna *Run = FairRunAna::Instance();
    FairRuntimeDb *RunDB = Run->GetRuntimeDb();
    fFieldPar = (MyFieldPar *)RunDB->getContainer("MyFieldPar");
}

FairField *MyFieldCreator::createFairField()
{
    FairField *fMagneticField = 0;

    if (!fFieldPar) {
        cerr << "-E-  No field parameters available!" << endl;
    } else {
        // Instantiate correct field type
        Int_t fType = fFieldPar->GetType();
        if (fType == 0)
            fMagneticField = new MyConstField(fFieldPar);
        else
            cerr << "-W- FairRunAna::GetField: Unknown field type " << fType << endl;
        cout << "New field at " << fMagneticField << ", type " << fType << endl;
        // Initialise field
        if (fMagneticField) {
            fMagneticField->Init();
            fMagneticField->Print("");
        }
    }
    return fMagneticField;
}
