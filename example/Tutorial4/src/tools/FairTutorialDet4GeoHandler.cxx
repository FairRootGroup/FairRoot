/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 CbmTrdGeoHandler source file                  -----
// -----                 Created 13/08/10  by F. Uhlig                 -----
// -------------------------------------------------------------------------

#include "FairTutorialDet4GeoHandler.h"

#include "FairLogger.h"                 // for FairLogger, etc

#include "TGeoBBox.h"                   // for TGeoBBox
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TGeoNode.h"                   // for TGeoNode
#include "TGeoVolume.h"                 // for TGeoVolume
#include "TVirtualMC.h"                 // for TVirtualMC, gMC

#include <stdio.h>                      // for printf
#include <string.h>                     // for NULL, strlen, strncpy
#include <iostream>                     // for cout, endl
#include <map>                          // for map
#include <utility>                      // for pair

using std::map;
using std::pair;
using std::cout;
using std::endl;

FairTutorialDet4GeoHandler::FairTutorialDet4GeoHandler()
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

Int_t FairTutorialDet4GeoHandler::Init(Bool_t isSimulation)
{
//  Int_t geoVersion = CheckGeometryVersion();

  fIsSimulation=isSimulation;

  return 1;
}

void FairTutorialDet4GeoHandler::LocalToGlobal(Double_t* local, Double_t* global, Int_t detID)
{
  TString path=ConstructFullPathFromDetID(detID);
  NavigateTo(path);
  gGeoManager->LocalToMaster(local, global);
}

TString FairTutorialDet4GeoHandler::ConstructFullPathFromDetID(Int_t detID)
{
  TString volStr   = "/cave_1/tutorial4_0/tut4_det_";
  TString volPath = volStr;
  volPath += detID;
  return volPath;
}

Int_t FairTutorialDet4GeoHandler::GetUniqueDetectorId(TString volName)
{
  if (fGeoPathHash != volName.Hash()) {
    NavigateTo(volName);
  }
  return GetUniqueDetectorId();
}


Int_t FairTutorialDet4GeoHandler::GetUniqueDetectorId()
{

  Int_t detectorNr=0;

  CurrentVolOffID(0, detectorNr);

  return detectorNr;


}


Int_t FairTutorialDet4GeoHandler::VolIdGeo(const char* name) const
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

Int_t FairTutorialDet4GeoHandler::VolId(const Text_t* name) const
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

Int_t FairTutorialDet4GeoHandler::CurrentVolID(Int_t& copy) const
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
Int_t FairTutorialDet4GeoHandler::CurrentVolOffID(Int_t off, Int_t& copy) const
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
const char* FairTutorialDet4GeoHandler::CurrentVolName() const
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
const char* FairTutorialDet4GeoHandler::CurrentVolOffName(Int_t off) const
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


void FairTutorialDet4GeoHandler::NavigateTo(TString volName)
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


ClassImp(FairTutorialDet4GeoHandler)
