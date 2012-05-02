#include "FairMockVirtualMC.h"

FairMockVirtualMC::FairMockVirtualMC()
  : TVirtualMC(),
    fMCGeo(new TGeoMCGeometry("MCGeo", "TGeo Implementation of VirtualMCGeometry"))
{
}

FairMockVirtualMC::FairMockVirtualMC(const char* title, Int_t nwgeant)
  : TVirtualMC("FairMockVirtualMC",title, kFALSE),
    fMCGeo(new TGeoMCGeometry("MCGeo", "TGeo Implementation of VirtualMCGeometry"))
{
}

FairMockVirtualMC::~FairMockVirtualMC()
{
}

void  FairMockVirtualMC::SetRootGeometry()
{
  // Notify Geant3 about use of TGeo geometry.
  // The materials and tracking medias will be imported from
  // TGeo at FinishGeometry().
  fImportRootGeometry = kTRUE;
}

Int_t FairMockVirtualMC::VolId(const Text_t* name) const
{
  //
  // Return the unique numeric identifier for volume name
  //
  char sname[20];
  Int_t len = strlen(name)-1;
  if (name[len] != ' ') { return fMCGeo->VolId(name); }
  strncpy(sname, name, len);
  sname[len] = 0;
  return fMCGeo->VolId(sname);
}
