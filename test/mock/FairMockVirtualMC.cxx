#include "FairMockVirtualMC.h"

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

void FairMockVirtualMC::StopExecution() const
{
  fLogger->Fatal(MESSAGE_ORIGIN,"This function is not yet implemented.");
}

const char* FairMockVirtualMC::VolName(Int_t) const
{
  StopExecution();
  return "NULL";
}

Int_t FairMockVirtualMC::MediumId(const char*) const
{
  StopExecution();
  return -1;
}

Int_t FairMockVirtualMC::NofVolumes() const
{
  StopExecution();
  return -1;
}

Int_t FairMockVirtualMC::VolId2Mate(Int_t) const
{
  StopExecution();
  return -1;
}

Int_t FairMockVirtualMC::NofVolDaughters(const char*) const
{
  StopExecution();
  return -1;
}

const char* FairMockVirtualMC::VolDaughterName(const char*, Int_t) const
{
  StopExecution();
  return "NULL";
}

Int_t FairMockVirtualMC::VolDaughterCopyNo(const char*, Int_t) const
{
  StopExecution();
  return -1;
}
