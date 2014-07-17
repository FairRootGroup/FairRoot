/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4.h"

#include "FairDetectorList.h"           // for DetectorId::kTutDet
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairGeoVolume.h"              // for FairGeoVolume
#include "FairLogger.h"                 // for FairLogger, etc
#include "FairRootManager.h"            // for FairRootManager
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairStack.h"                  // for FairStack
#include "FairTutorialDet4Geo.h"        // for FairTutorialDet4Geo
#include "FairTutorialDet4GeoHandler.h"  // for FairTutorialDet4GeoHandler
#include "FairTutorialDet4GeoPar.h"     // for FairTutorialDet4GeoPar
#include "FairTutorialDet4MisalignPar.h"
#include "FairTutorialDet4Point.h"      // for FairTutorialDet4Point

#include "Riosfwd.h"                    // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TGeoMatrix.h"                 // for TGeoHMatrix, TGeoCombiTrans, etc
#include "TGeoNode.h"                   // for TGeoNode
#include "TGeoPhysicalNode.h"           // for TGeoPhysicalNode, etc
#include "TList.h"                      // for TListIter, TList (ptr only)
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString, operator<<, Form
#include "TVirtualMC.h"                 // for TVirtualMC, gMC
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include <stdio.h>                      // for NULL, printf
#include <iostream>                     // for operator<<, cout, endl, etc

using std::cout;
using std::endl;

FairTutorialDet4::FairTutorialDet4()
  : FairDetector("TutorialDet", kTRUE, kTutDet),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDet4PointCollection(new TClonesArray("FairTutorialDet4Point")),
    fGeoHandler(new FairTutorialDet4GeoHandler()),
    fMisalignPar(NULL),
    fNrOfDetectors(-1),
    fShiftX(),
    fShiftY(),
    fShiftZ(),
    fRotX(),
    fRotY(),
    fRotZ(),
    fModifyGeometry(kFALSE)
{
}

FairTutorialDet4::FairTutorialDet4(const char* name, Bool_t active)
  : FairDetector(name, active, kTutDet),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDet4PointCollection(new TClonesArray("FairTutorialDet4Point")),
    fGeoHandler(new FairTutorialDet4GeoHandler()),
    fMisalignPar(NULL),
    fNrOfDetectors(-1),
    fShiftX(),
    fShiftY(),
    fShiftZ(),
    fRotX(),
    fRotY(),
    fRotZ(),
    fModifyGeometry(kFALSE)
{
}

FairTutorialDet4::~FairTutorialDet4()
{
  LOG(DEBUG4)<<"Entering Destructor of FairTutorialDet4"<<FairLogger::endl;
  if (fFairTutorialDet4PointCollection) {
    fFairTutorialDet4PointCollection->Delete();
    delete fFairTutorialDet4PointCollection;
  }
  LOG(DEBUG4)<<"Leaving Destructor of FairTutorialDet4"<<FairLogger::endl;
}
void FairTutorialDet4::SetParContainers()
{

  LOG(INFO)<< "Set tutdet missallign parameters"<<FairLogger::endl;
  // Get Base Container
  FairRun* sim = FairRun::Instance();
  LOG_IF(FATAL, !sim) << "No run object"<<FairLogger::endl;
  FairRuntimeDb* rtdb=sim->GetRuntimeDb();
  LOG_IF(FATAL, !rtdb) << "No runtime database"<<FairLogger::endl;

  fMisalignPar = (FairTutorialDet4MisalignPar*)
                 (rtdb->getContainer("FairTutorialDet4MissallignPar"));

}

void FairTutorialDet4::Initialize()
{
  FairDetector::Initialize();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairTutorialDet4GeoPar* par=(FairTutorialDet4GeoPar*)(rtdb->getContainer("FairTutorialDet4GeoPar"));

  Bool_t isSimulation = kTRUE;
  fGeoHandler->Init(isSimulation);
}

void FairTutorialDet4::InitParContainers()
{
  LOG(INFO)<< "Initialize tutdet missallign parameters"<<FairLogger::endl;
  fNrOfDetectors=fMisalignPar->GetNrOfDetectors();
  fShiftX=fMisalignPar->GetShiftX();
  fShiftY=fMisalignPar->GetShiftY();
  fShiftZ=fMisalignPar->GetShiftZ();
  fRotX=fMisalignPar->GetRotX();
  fRotY=fMisalignPar->GetRotY();
  fRotZ=fMisalignPar->GetRotZ();

}

Bool_t  FairTutorialDet4::ProcessHits(FairVolume* vol)
{
  /** This method is called from the MC stepping */

  //Set parameters at entrance of volume. Reset ELoss.
  if ( gMC->IsTrackEntering() ) {
    fELoss  = 0.;
    fTime   = gMC->TrackTime() * 1.0e09;
    fLength = gMC->TrackLength();
    gMC->TrackPosition(fPos);
    gMC->TrackMomentum(fMom);
  }

  // Sum energy loss for all steps in the active volume
  fELoss += gMC->Edep();

  // Create FairTutorialDet4Point at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
//    fVolumeID = vol->getMCid();
    fVolumeID = fGeoHandler->GetUniqueDetectorId();
    if (fELoss == 0. ) { return kFALSE; }

    // Save positions in local coordinate system, so transform the
    // global coordinates into local ones.
    Double_t master[3] = {fPos.X(), fPos.Y(), fPos.Z()};
    Double_t local[3];

    gMC->Gmtod(master, local, 1);

//    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
    AddHit(fTrackID, fVolumeID, TVector3(local[0], local[1], local[2]),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of tutorial det points in TParticle
    FairStack* stack = (FairStack*) gMC->GetStack();
    stack->AddPoint(kTutDet);
  }

  return kTRUE;
}

void FairTutorialDet4::EndOfEvent()
{

  fFairTutorialDet4PointCollection->Clear();

}



void FairTutorialDet4::Register()
{

  /** This will create a branch in the output tree called
      FairTutorialDet4Point, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  FairRootManager::Instance()->Register("TutorialDetPoint", "TutorialDet",
                                        fFairTutorialDet4PointCollection, kTRUE);

}


TClonesArray* FairTutorialDet4::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fFairTutorialDet4PointCollection; }
  else { return NULL; }
}

void FairTutorialDet4::Reset()
{
  fFairTutorialDet4PointCollection->Clear();
}

void FairTutorialDet4::ConstructGeometry()
{
  TString fileName=GetGeometryFileName();
  if (fileName.EndsWith(".geo")) {
    LOG(INFO)<<"Constructing Tutorial4 geometry from ASCII file "<<fileName<<FairLogger::endl;
    ConstructASCIIGeometry();
  } else if (fileName.EndsWith(".root")) {
    LOG(INFO)<<"Constructing Tutorial4 geometry from ROOT file "<<fileName<<FairLogger::endl;
    ConstructRootGeometry();
  } else {
    std::cout << "Geometry format not supported." << std::endl;
  }
}

Bool_t FairTutorialDet4::CheckIfSensitive(std::string name)
{
  TString tsname = name;
  if (tsname.Contains("tut4")) {
    return kTRUE;
  }
  return kFALSE;
}

void FairTutorialDet4::ConstructASCIIGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  FairTutorialDet4Geo*  Geo  = new FairTutorialDet4Geo();
  LOG(DEBUG)<<"Read Geo file "<<GetGeometryFileName()<<FairLogger::endl;
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);

  Bool_t rc = geoFace->readSet(Geo);
  if (rc) { Geo->create(geoLoad->getGeoBuilder()); }
  TList* volList = Geo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairTutorialDet4GeoPar* par=(FairTutorialDet4GeoPar*)(rtdb->getContainer("FairTutorialDet4GeoPar"));
  TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
  TObjArray* fPassNodes = par->GetGeoPassiveNodes();

  TListIter iter(volList);
  FairGeoNode* node   = NULL;
  FairGeoVolume* aVol=NULL;

  while( (node = (FairGeoNode*)iter.Next()) ) {
    aVol = dynamic_cast<FairGeoVolume*> ( node );
    if ( node->isSensitive()  ) {
      fSensNodes->AddLast( aVol );
    } else {
      fPassNodes->AddLast( aVol );
    }
  }
  par->setChanged();
  par->setInputVersion(fRun->GetRunId(),1);

  ProcessNodes ( volList );
}

void FairTutorialDet4::ModifyGeometry()
{
  // When saving the top volume of the geometry to a file the information
  // about the TGeoPNEntries is not saved. So the misalign procedure
  // which uses the TGeoPNEntry information can not be used.
  // The code is here to demonstrate how to use this feature.

  if (fModifyGeometry) {
    LOG(INFO)<<"Misalign the geometry for the tutorial detector."<<FairLogger::endl;

    TString detStr   = "Tutorial4/det00";

    TGeoPNEntry* entry = gGeoManager->GetAlignableEntry(detStr.Data());
    if (entry) {
      LOG(INFO)<<"Misalign using symlinks."<<FairLogger::endl;
      TGeoPhysicalNode* node = entry->GetPhysicalNode();
//    LOG(INFO)<<"Nr of alignable objects: "<<gGeoManager->GetNAlignable()<<FairLogger::endl;
      ModifyGeometryBySymlink();
    } else {
      LOG(INFO)<<"Misalign using full path."<<FairLogger::endl;
      ModifyGeometryByFullPath();
    }
  }
}

void FairTutorialDet4::ModifyGeometryByFullPath()
{

  TString volPath;
  TString volStr   = "/cave_1/tutorial4_0/tut4_det_";

  for (Int_t iDet = 0; iDet < fNrOfDetectors; ++iDet) {
    LOG(DEBUG)<<"Misalign detector nr "<<iDet<<FairLogger::endl;
    volPath  = volStr;
    volPath += iDet;

    cout<<"Path: "<<volPath<<endl;
    gGeoManager->cd(volPath);
    TGeoHMatrix* g3 = gGeoManager->GetCurrentMatrix();
//      g3->Print();
    TGeoNode* n3 = gGeoManager->GetCurrentNode();
    TGeoMatrix* l3 = n3->GetMatrix();
//      l3->Print();

    //we have to express the displacements as regards the old local RS (non misaligned BTOF)
    Double_t dx     = fShiftX[iDet];
    Double_t dy     = fShiftY[iDet];
    Double_t dz     = fShiftZ[iDet];
    Double_t dphi   = fRotX[iDet];
    Double_t dtheta = fRotY[iDet];
    Double_t dpsi   = fRotZ[iDet];

    TGeoRotation* rrot = new TGeoRotation("rot",dphi,dtheta,dpsi);
    TGeoCombiTrans localdelta = *(new TGeoCombiTrans(dx,dy,dz, rrot));
//      localdelta.Print();
    TGeoHMatrix nlocal = *l3 * localdelta;
    TGeoHMatrix* nl3 = new TGeoHMatrix(nlocal); // new matrix, representing real position (from new local mis RS to the global one)

    TGeoPhysicalNode* pn3 = gGeoManager->MakePhysicalNode(volPath);

    pn3->Align(nl3);

    TGeoHMatrix* ng3 = pn3->GetMatrix(); //"real" global matrix, what survey sees
    LOG(DEBUG)<<"*************  The Misaligned Matrix in GRS **************"<<FairLogger::endl;
//      ng3->Print();


  }
  LOG(DEBUG)<<"Align in total "<<fNrOfDetectors<<" detectors."<<FairLogger::endl;

}

void FairTutorialDet4::ModifyGeometryBySymlink()
{
  TString symName;
  TString detStr   = "Tutorial4/det";

  for (Int_t iDet = 0; iDet < fNrOfDetectors; ++iDet) {
    LOG(INFO)<<"Misalign detector nr "<<iDet<<FairLogger::endl;

    symName  = detStr;
    symName += Form("%02d",iDet);

    TGeoPhysicalNode* node = NULL;
    TGeoPNEntry* entry = gGeoManager->GetAlignableEntry(detStr);
    if (entry) {
      node = gGeoManager->MakeAlignablePN(entry);
    }
 
    TGeoMatrix* l3 = NULL;
    if (node) {
      l3 = node->GetMatrix();
    } else {
      continue;
    }

    //we have to express the displacements as regards the old local RS (non misaligned BTOF)
    Double_t dx     = fShiftX[iDet];
    Double_t dy     = fShiftY[iDet];
    Double_t dz     = fShiftZ[iDet];
    Double_t dphi   = fRotX[iDet];
    Double_t dtheta = fRotY[iDet];
    Double_t dpsi   = fRotZ[iDet];
    LOG(INFO)<<"Psi: "<<dpsi<<FairLogger::endl;

    TGeoRotation* rrot = new TGeoRotation("rot",dphi,dtheta,dpsi);
    TGeoCombiTrans localdelta = *(new TGeoCombiTrans(dx,dy,dz, rrot));
    localdelta.Print();
    TGeoHMatrix nlocal = *l3 * localdelta;
    TGeoHMatrix* nl3 = new TGeoHMatrix(nlocal); // new matrix, representing real position (from new local mis RS to the global one)

    node->Align(nl3);

    TGeoHMatrix* ng3 = node->GetMatrix(); //"real" global matrix, what survey sees
    printf("\n\n*************  The Misaligned Matrix in GRS **************\n");
    ng3->Print();


  }
  //do something
  LOG(INFO)<<"Total Nr of detectors: "<<fNrOfDetectors<<FairLogger::endl;





}
FairTutorialDet4Point* FairTutorialDet4::AddHit(Int_t trackID, Int_t detID,
    TVector3 pos, TVector3 mom,
    Double_t time, Double_t length,
    Double_t eLoss)
{
  TClonesArray& clref = *fFairTutorialDet4PointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) FairTutorialDet4Point(trackID, detID, pos, mom,
         time, length, eLoss);
}




ClassImp(FairTutorialDet4)
