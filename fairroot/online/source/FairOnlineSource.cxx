/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairOnlineSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----              Copied from FairSource 01.11.2013 by F.Uhlig         -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#include "FairOnlineSource.h"

#include "FairLogger.h"

FairOnlineSource::FairOnlineSource()
    : FairSource()
    , fUnpackers(new TObjArray())
{
}

FairOnlineSource::FairOnlineSource(const FairOnlineSource &source)
    : FairSource(source)
    , fUnpackers(new TObjArray(*(source.GetUnpackers())))
{
}

FairOnlineSource::~FairOnlineSource()
{
    fUnpackers->Delete();
    delete fUnpackers;
}

Bool_t FairOnlineSource::InitUnpackers()
{
    for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
        if (!((FairUnpack *)fUnpackers->At(i))->Init()) {
            return kFALSE;
        }
    }
    return kTRUE;
}

Bool_t FairOnlineSource::ReInitUnpackers()
{
    for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
        if (!((FairUnpack *)fUnpackers->At(i))->ReInit()) {
            return kFALSE;
        }
    }
    return kTRUE;
}

void FairOnlineSource::SetParUnpackers()
{
    for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
        ((FairUnpack *)fUnpackers->At(i))->SetParContainers();
    }
}

void FairOnlineSource::Reset()
{
    for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
        ((FairUnpack *)fUnpackers->At(i))->Reset();
    }
}

ClassImp(FairOnlineSource);
