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

FairFieldFactory::FairFieldFactory()
    : fCreator(0)
{
    fgRinstance = this;
}

FairFieldFactory::~FairFieldFactory()
{
    if (fgRinstance == this) {
        // Do not point to a destructed object!
        fgRinstance = nullptr;
    }
}

FairFieldFactory* FairFieldFactory::Instance() { return fgRinstance; }

ClassImp(FairFieldFactory);
