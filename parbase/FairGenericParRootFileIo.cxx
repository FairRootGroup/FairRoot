/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

//////////////////////////////////////////////////////////////////////////////
// FairGenericParRootFileIo
//
// Interface class to ROOT file for input/output of parameters derived
// from FairParGenericSet
//////////////////////////////////////////////////////////////////////////////

#include "FairGenericParRootFileIo.h"

#include <TString.h>   // for TString

class FairParSet;

ClassImp(FairGenericParRootFileIo);

FairGenericParRootFileIo::FairGenericParRootFileIo(FairParRootFile* f)
    : FairDetParRootFileIo(f)
{
    // constructor
    // sets the name of the I/O class "FairGenericParIo"
    // gets the pointer to the ROOT file
    fName = "FairGenericParIo";
}

Bool_t FairGenericParRootFileIo::init(FairParSet* pPar)
{
    // calls FairDetParRootFileIo"::read(FairParSet*)
    if (!pFile) {
        return kFALSE;
    }
    return FairDetParRootFileIo::read(pPar);
}
