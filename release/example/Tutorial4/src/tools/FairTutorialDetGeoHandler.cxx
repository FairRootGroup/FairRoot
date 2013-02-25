// -------------------------------------------------------------------------
// -----                 CbmTrdGeoHandler source file                  -----
// -----                 Created 13/08/10  by F. Uhlig                 -----
// -------------------------------------------------------------------------


#include "FairTutorialDetGeoHandler.h"

#include "FairLogger.h"

#include "TGeoVolume.h"
#include "TGeoBBox.h"
#include "TGeoNode.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TVirtualMC.h"

#include <iostream>
#include <vector>
#include <map>
using std::map;
using std::pair;
using std::cout;
using std::endl;

FairTutorialDetGeoHandler::FairTutorialDetGeoHandler()
  : TObject(),
    fIsSimulation(kFALSE),
    fLastUsedDetectorID(0),
    fGeoPathHash(0),
    fCurrentVolume(NULL),
    fVolumeShape(NULL),
    fGlobal(),
    fGlobalMatrix(NULL)
{
}

Int_t FairTutorialDetGeoHandler::Init(Bool_t isSimulation)
{
//  Int_t geoVersion = CheckGeometryVersion();

  fIsSimulation=isSimulation;

  return 1;
}

Int_t FairTutorialDetGeoHandler::GetUniqueDetectorId(TString volName)
{
  if (fGeoPathHash != volName.Hash()) {
    NavigateTo(volName);
  }
  return GetUniqueDetectorId();
}


Int_t FairTutorialDetGeoHandler::GetUniqueDetectorId()
{

  Int_t detectorNr=0;

  CurrentVolOffID(0, detectorNr);

  return detectorNr;


}


Int_t FairTutorialDetGeoHandler::VolIdGeo(const char* name) const
{
  //
  // Return the unique numeric identifier for volume name
  //

  Int_t uid = gGeoManager->GetUID(name);
  if (uid<0) {
    printf("VolId: Volume %s not found\n",name);
    return 0;
  }
  return uid;
}

Int_t FairTutorialDetGeoHandler::VolId(const Text_t* name) const
{
  if (fIsSimulation) {
    return gMC->VolId(name);
  } else {
    //
    // Return the unique numeric identifier for volume name
    //
    char sname[20];
    Int_t len = strlen(name)-1;
    if (name[len] != ' ') { return VolIdGeo(name); }
    strncpy(sname, name, len);
    sname[len] = 0;
    return VolIdGeo(sname);
  }
}

Int_t FairTutorialDetGeoHandler::CurrentVolID(Int_t& copy) const
{
  if (fIsSimulation) {
    return gMC->CurrentVolID(copy);
  } else {
    //
    // Returns the current volume ID and copy number
    //
    if (gGeoManager->IsOutside()) { return 0; }
    TGeoNode* node = gGeoManager->GetCurrentNode();
    copy = node->GetNumber();
    Int_t id = node->GetVolume()->GetNumber();
    return id;
  }
}

//_____________________________________________________________________________
Int_t FairTutorialDetGeoHandler::CurrentVolOffID(Int_t off, Int_t& copy) const
{
  if (fIsSimulation) {
    return gMC->CurrentVolOffID(off, copy);
  } else {
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
}

//_____________________________________________________________________________
const char* FairTutorialDetGeoHandler::CurrentVolName() const
{
  if (fIsSimulation) {
    return gMC->CurrentVolName();
  } else {
    //
    // Returns the current volume name
    //
    if (gGeoManager->IsOutside()) { return gGeoManager->GetTopVolume()->GetName(); }
    return gGeoManager->GetCurrentVolume()->GetName();
  }
}

//_____________________________________________________________________________
const char* FairTutorialDetGeoHandler::CurrentVolOffName(Int_t off) const
{
  if (fIsSimulation) {
    return gMC->CurrentVolOffName(off);
  } else {
    //
    // Return the current volume "off" upward in the geometrical tree
    // ID, name and copy number
    // if name=0 no name is returned
    //
    if (off<0 || off>gGeoManager->GetLevel()) { return 0; }
    if (off==0) { return CurrentVolName(); }
    TGeoNode* node = gGeoManager->GetMother(off);
    if (!node) { return 0; }
    return node->GetVolume()->GetName();
  }
}


void FairTutorialDetGeoHandler::NavigateTo(TString volName)
{
  if (fIsSimulation) {
    LOG(FATAL)<<"This methode is not supported in simulation mode"<<FairLogger::endl;
  } else {
    gGeoManager->cd(volName.Data());
    fGeoPathHash = volName.Hash();
    fCurrentVolume = gGeoManager->GetCurrentVolume();
    fVolumeShape = (TGeoBBox*)fCurrentVolume->GetShape();
    Double_t local[3] = {0., 0., 0.};  // Local centre of volume
    gGeoManager->LocalToMaster(local, fGlobal);
    LOG(DEBUG2)<<"Pos: "<<fGlobal[0]<<" , "<<fGlobal[1]<<" , "<<fGlobal[2]<<FairLogger::endl;
//    fGlobalMatrix = gGeoManager->GetCurrentMatrix();
  }
}


ClassImp(FairTutorialDetGeoHandler)
