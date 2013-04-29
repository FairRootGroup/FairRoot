#include "FairMockVirtualMC.h"

#include "TGeoNode.h"
#include "TGeoManager.h"

FairMockVirtualMC::FairMockVirtualMC()
  : TVirtualMC(),
    fMCGeo(new TGeoMCGeometry("MCGeo", "TGeo Implementation of VirtualMCGeometry")),
    fLogger(FairLogger::GetLogger())
{
}

FairMockVirtualMC::FairMockVirtualMC(const char* title, Int_t nwgeant)
  : TVirtualMC("FairMockVirtualMC",title, kFALSE),
    fMCGeo(new TGeoMCGeometry("MCGeo", "TGeo Implementation of VirtualMCGeometry")),
    fLogger(FairLogger::GetLogger())
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

Int_t FairMockVirtualMC::CurrentVolID(Int_t& copy) const
{
  //
  // Returns the current volume ID and copy number
  //
  if (gGeoManager->IsOutside()) { return 0; }
  TGeoNode* node = gGeoManager->GetCurrentNode();
  copy = node->GetNumber();
  Int_t id = node->GetVolume()->GetNumber();
  return id;
}

//_____________________________________________________________________________
Int_t FairMockVirtualMC::CurrentVolOffID(Int_t off, Int_t& copy) const
{
  //
  // Return the current volume "off" upward in the geometrical tree
  // ID and copy number
  //
  if (off<0 || off>gGeoManager->GetLevel()) { return 0; }
  if (off==0) { return CurrentVolID(copy); }
  TGeoNode* node = gGeoManager->GetMother(off);
  if (!node) { return 0; }
  copy = node->GetNumber();
  return node->GetVolume()->GetNumber();
}

void FairMockVirtualMC::StopExecution() const
{
  fLogger->Fatal(MESSAGE_ORIGIN,"This function is not yet implemented.");
}

