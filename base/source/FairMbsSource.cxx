/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairMbsSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----              Copied from FairSource 01.11.2013 by F.Uhlig         -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#include <iostream>

#include "FairMbsSource.h"

FairMbsSource::FairMbsSource() : FairSource(), fUnpackers(new TObjArray()) {}

FairMbsSource::FairMbsSource(const FairMbsSource &source)
    : FairSource(source), fUnpackers(new TObjArray(*(source.GetUnpackers()))) {}

FairMbsSource::~FairMbsSource() {
  fUnpackers->Delete();
  delete fUnpackers;
}

Bool_t FairMbsSource::Init() {
  for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    if (!((FairUnpack *)fUnpackers->At(i))->Init()) {
      return kFALSE;
    }
  }
  return kTRUE;
}

void FairMbsSource::Reset() {
  for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    ((FairUnpack *)fUnpackers->At(i))->Reset();
  }
}

Bool_t FairMbsSource::Unpack(Int_t *data, Int_t size, Short_t type,
                             Short_t subType, Short_t procId, Short_t subCrate,
                             Short_t control) {
  FairUnpack *unpack;
  Bool_t seen = kFALSE;
  for (Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    unpack = (FairUnpack *)fUnpackers->At(i);

    if (unpack->GetSubCrate() < 0) { // All sub-crates
      if (type != unpack->GetType() || subType != unpack->GetSubType() ||
          procId != unpack->GetProcId() || control != unpack->GetControl()) {
        continue;
      }
    } else { // specified sub-crate
      if (type != unpack->GetType() || subType != unpack->GetSubType() ||
          procId != unpack->GetProcId() || subCrate != unpack->GetSubCrate() ||
          control != unpack->GetControl()) {
        continue;
      }
    }

    if (!unpack->DoUnpack(data, size)) {
      return kFALSE;
    }

    seen = kTRUE;
  }
  return seen;
}

ClassImp(FairMbsSource)
