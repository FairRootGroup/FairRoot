// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#include <iostream>

#include "FairSource.h"


FairSource::FairSource()
  : TObject(),
    fUnpackers(new TObjArray())
{
}


FairSource::FairSource(const FairSource& source)
  :fUnpackers(new TObjArray(*(source.GetUnpackers())))
{
}


FairSource::~FairSource()
{
  fUnpackers->Delete();
  delete fUnpackers;
}


Bool_t FairSource::Init()
{
  for(Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    if(! ((FairUnpack*)fUnpackers->At(i))->Init()) {
      return kFALSE;
    }
  }
  return kTRUE;
}


void FairSource::Reset()
{
  for(Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    ((FairUnpack*)fUnpackers->At(i))->Reset();
  }
}


Bool_t FairSource::Unpack(Int_t* data, Int_t size,
                          Short_t type, Short_t subType,
                          Short_t procId, Short_t subCrate, Short_t control)
{
  FairUnpack* unpack;
  for(Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    unpack = (FairUnpack*)fUnpackers->At(i);

    if(unpack->GetSubCrate() < 0) { // All sub-crates
      if(type != unpack->GetType() || subType != unpack->GetSubType() ||
          procId != unpack->GetProcId() ||
          control != unpack->GetControl()) {
        continue;
      }
    } else { // specified sub-crate
      if(type != unpack->GetType() || subType != unpack->GetSubType() ||
          procId != unpack->GetProcId() || subCrate != unpack->GetSubCrate() ||
          control != unpack->GetControl()) {
        continue;
      }
    }

    if(! unpack->DoUnpack(data, size)) {
      return kFALSE;
    }
  }
  return kTRUE;
}


ClassImp(FairSource)
