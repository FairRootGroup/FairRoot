/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----              FairFieldFactory source file                     -----
// -----          Created 12/01/04  by   M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairFieldFactory.h"

FairFieldFactory* FairFieldFactory::fgRinstance = nullptr;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
FairFieldFactory::FairFieldFactory()
    : fCreator(nullptr)
{
    fgRinstance = this;
}
#pragma GCC diagnostic pop

FairFieldFactory::~FairFieldFactory()
{
    if (fgRinstance == this) {
        // Do not point to a destructed object!
        fgRinstance = nullptr;
    }
}

FairFieldFactory* FairFieldFactory::Instance() { return fgRinstance; }

ClassImp(FairFieldFactory);
