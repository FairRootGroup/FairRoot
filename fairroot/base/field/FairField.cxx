/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairField source file                    -----
// -----                Created 06/01/04  by M. Al/Turany              -----
// -----                Redesign 13/02/06  by V. Friese                -----
// -------------------------------------------------------------------------

#include "FairField.h"

FairField::FairField()
    : TVirtualMagField("FAIR Magnetic Field")
    , fType(0)
{}

FairField::FairField(const char* name, const char*)
    : TVirtualMagField(name)
    , fType(0)
{}

FairField::~FairField() {}

Bool_t FairField::IsConst()
{
    return fType == 1;
}

Bool_t FairField::IsMap()
{
    return fType == 2;
}

void FairField::GetFieldValue(const Double_t point[3], Double_t* bField)
{
    bField[0] = GetBx(point[0], point[1], point[2]);
    bField[1] = GetBy(point[0], point[1], point[2]);
    bField[2] = GetBz(point[0], point[1], point[2]);
}
