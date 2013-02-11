#include "FairTutorialDet.h"

#include "FairTutorialDetPoint.h"
#include "FairTutorialDetGeo.h"
#include "FairTutorialDetGeoPar.h"

#include "FairVolume.h"
#include "FairGeoVolume.h"
#include "FairGeoNode.h"
#include "FairRootManager.h"
#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairDetectorList.h"
#include "FairStack.h"

#include "TClonesArray.h"
#include "TVirtualMC.h"

#include <iostream>
using std::cout;
using std::endl;

FairTutorialDet::FairTutorialDet()
  : FairDetector("TutorialDet", kTRUE, kTutDet),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDetPointCollection(new TClonesArray("FairTutorialDetPoint"))
{
}

FairTutorialDet::FairTutorialDet(const char* name, Bool_t active)
  : FairDetector(name, active, kTutDet),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDetPointCollection(new TClonesArray("FairTutorialDetPoint"))
{
}

FairTutorialDet::~FairTutorialDet()
{
  if (fFairTutorialDetPointCollection) {
    fFairTutorialDetPointCollection->Delete();
    delete fFairTutorialDetPointCollection;
  }
}

void FairTutorialDet::Initialize()
{
  FairDetector::Initialize();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairTutorialDetGeoPar* par=(FairTutorialDetGeoPar*)(rtdb->getContainer("FairTutorialDetGeoPar"));
}

Bool_t  FairTutorialDet::ProcessHits(FairVolume* vol)
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

  // Create FairTutorialDetPoint at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) { return kFALSE; }
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of tutorial det points in TParticle
    FairStack* stack = (FairStack*) gMC->GetStack();
    stack->AddPoint(kTutDet);
  }

  return kTRUE;
}

void FairTutorialDet::EndOfEvent()
{

  fFairTutorialDetPointCollection->Clear();

}



void FairTutorialDet::Register()
{

  /** This will create a branch in the output tree called
      FairTutorialDetPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  FairRootManager::Instance()->Register("TutorialDetPoint", "TutorialDet",
                                        fFairTutorialDetPointCollection, kTRUE);

}


TClonesArray* FairTutorialDet::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fFairTutorialDetPointCollection; }
  else { return NULL; }
}

void FairTutorialDet::Reset()
{
  fFairTutorialDetPointCollection->Clear();
}

void FairTutorialDet::ConstructGeometry()
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

Bool_t FairTutorialDet::CheckIfSensitive(std::string name)
{
  TString tsname = name;
  if (tsname.Contains("tut4")) {
    return kTRUE;
  }
  return kFALSE;
}

void FairTutorialDet::ConstructASCIIGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  FairTutorialDetGeo*  Geo  = new FairTutorialDetGeo();
  LOG(DEBUG)<<"Read Geo file "<<GetGeometryFileName()<<FairLogger::endl;
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);

  Bool_t rc = geoFace->readSet(Geo);
  if (rc) { Geo->create(geoLoad->getGeoBuilder()); }
  TList* volList = Geo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairTutorialDetGeoPar* par=(FairTutorialDetGeoPar*)(rtdb->getContainer("FairTutorialDetGeoPar"));
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

FairTutorialDetPoint* FairTutorialDet::AddHit(Int_t trackID, Int_t detID,
    TVector3 pos, TVector3 mom,
    Double_t time, Double_t length,
    Double_t eLoss)
{
  TClonesArray& clref = *fFairTutorialDetPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) FairTutorialDetPoint(trackID, detID, pos, mom,
         time, length, eLoss);
}

ClassImp(FairTutorialDet)
