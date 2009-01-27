#include "CbmTutorialDet.h"

#include "CbmTutorialDetPoint.h"
#include "CbmTutorialDetGeo.h"
#include "CbmTutorialDetGeoPar.h"

#include "CbmVolume.h"
#include "CbmGeoVolume.h"
#include "CbmGeoNode.h"
#include "CbmRootManager.h"
#include "CbmGeoLoader.h"
#include "CbmGeoInterface.h"
#include "CbmRun.h"
#include "CbmRuntimeDb.h"
#include "CbmDetectorList.h"
#include "CbmStack.h"

#include "TClonesArray.h"
#include "TVirtualMC.h"

#include <iostream>
using std::cout;
using std::endl;

CbmTutorialDet::CbmTutorialDet() :
  CbmDetector("TutorialDet", kTRUE, kTutDet) {
  /** create your collection for data points */
  fCbmTutorialDetPointCollection = new TClonesArray("CbmTutorialDetPoint");
  
}

CbmTutorialDet::CbmTutorialDet(const char* name, Bool_t active)
  : CbmDetector(name, active, kTutDet) {
  fCbmTutorialDetPointCollection = new TClonesArray("CbmTutorialDetPoint");
  
}
 
CbmTutorialDet::~CbmTutorialDet() {
   if (fCbmTutorialDetPointCollection) {
     fCbmTutorialDetPointCollection->Delete();
     delete fCbmTutorialDetPointCollection;
   }
}

void CbmTutorialDet::Initialize()
{
  CbmDetector::Initialize();
  CbmRuntimeDb *rtdb= CbmRun::Instance()->GetRuntimeDb();
  CbmTutorialDetGeoPar* par=(CbmTutorialDetGeoPar*)(rtdb->getContainer("CbmTutorialDetGeoPar"));
}
 
Bool_t  CbmTutorialDet::ProcessHits(CbmVolume* vol)
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
  
  // Create CbmTutorialDetPoint at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) return kFALSE;
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
	   TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
	   fELoss);
    
    // Increment number of tutorial det points in TParticle
    CbmStack* stack = (CbmStack*) gMC->GetStack();
    stack->AddPoint(kTutDet);
  }
  
  return kTRUE;
}
 
void CbmTutorialDet::EndOfEvent() {
  
  fCbmTutorialDetPointCollection->Clear();
  
}



void CbmTutorialDet::Register() {

/** This will create a branch in the output tree called  
    CbmTutorialDetPoint, setting the last parameter to kFALSE means:
    this collection will not be written to the file, it will exist 
    only during the simulation. 
*/
 
  CbmRootManager::Instance()->Register("TutorialDetPoint", "TutorialDet",
				       fCbmTutorialDetPointCollection, kTRUE);
 
}


TClonesArray* CbmTutorialDet::GetCollection(Int_t iColl) const {
  if (iColl == 0) return fCbmTutorialDetPointCollection;
  else return NULL;
}

void CbmTutorialDet::Reset() {
  fCbmTutorialDetPointCollection->Clear();
}

void CbmTutorialDet::ConstructGeometry() {
  /** If you are using the standard ASCII input for the geometry 
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */
  
  CbmGeoLoader*    geoLoad = CbmGeoLoader::Instance();
  CbmGeoInterface* geoFace = geoLoad->getGeoInterface();
  CbmTutorialDetGeo*  Geo  = new CbmTutorialDetGeo();
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);
  
  Bool_t rc = geoFace->readSet(Geo);
  if (rc) Geo->create(geoLoad->getGeoBuilder());
  TList* volList = Geo->getListOfVolumes();
  
  // store geo parameter
  CbmRun *fRun = CbmRun::Instance();
  CbmRuntimeDb *rtdb= CbmRun::Instance()->GetRuntimeDb();
  CbmTutorialDetGeoPar* par=(CbmTutorialDetGeoPar*)(rtdb->getContainer("CbmTutorialDetGeoPar"));
  TObjArray *fSensNodes = par->GetGeoSensitiveNodes();
  TObjArray *fPassNodes = par->GetGeoPassiveNodes();
  
  TListIter iter(volList);
  CbmGeoNode* node   = NULL;
  CbmGeoVolume *aVol=NULL;
  
  while( (node = (CbmGeoNode*)iter.Next()) ) {
    aVol = dynamic_cast<CbmGeoVolume*> ( node );
    if ( node->isSensitive()  ) {
      fSensNodes->AddLast( aVol );
    }else{
      fPassNodes->AddLast( aVol );
    }
  }
  par->setChanged();
  par->setInputVersion(fRun->GetRunId(),1);
  
  ProcessNodes ( volList );
}

CbmTutorialDetPoint* CbmTutorialDet::AddHit(Int_t trackID, Int_t detID, 
					    TVector3 pos, TVector3 mom, 
					    Double_t time, Double_t length,
					    Double_t eLoss) {
  TClonesArray& clref = *fCbmTutorialDetPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) CbmTutorialDetPoint(trackID, detID, pos, mom,
					      time, length, eLoss);
}

ClassImp(CbmTutorialDet)
