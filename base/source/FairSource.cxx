// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#include "FairSource.h"


FairSource::FairSource()
  : TObject(),
    fUnpackers(new TObjArray())
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
                          Int_t type, Int_t subType)
{
  Reset();

  FairUnpack* unpack;
  for(Int_t i = 0; i < fUnpackers->GetEntriesFast(); i++) {
    unpack = (FairUnpack*)fUnpackers->At(i);

    if(type != unpack->GetType() || subType != unpack->GetSubType()) {
      continue;
    }

    if(! unpack->DoUnpack(data, size)) {
      return kFALSE;
    }
  }
  return kTRUE;
}


ClassImp(FairSource)

