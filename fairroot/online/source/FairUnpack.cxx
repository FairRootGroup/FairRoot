/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairUnpack                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#include "FairUnpack.h"

FairUnpack::FairUnpack(Short_t type, Short_t subType, Short_t procId, Short_t subCrate, Short_t control)
    : TObject()
    , fType(type)
    , fSubType(subType)
    , fProcId(procId)
    , fSubCrate(subCrate)
    , fControl(control)
{
}

FairUnpack::~FairUnpack() {}

ClassImp(FairUnpack);
