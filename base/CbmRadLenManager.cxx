// -------------------------------------------------------------------------
// -----                      CbmRadLenManager source file                   -----
// -----                  Created 14/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

using namespace std;
#include <iostream>
#include "CbmRadLenPoint.h"
#include "CbmRadLenManager.h"
#include "CbmRootManager.h"
#include "TLorentzVector.h"
#include "TParticle.h"
#include "TVirtualMC.h"
			 
ClassImp(CbmRadLenManager)

CbmRadLenManager* CbmRadLenManager::fgInstance = NULL;

CbmRadLenManager* CbmRadLenManager::Instance()
{
  /**singelton instance*/
  return fgInstance;
}

CbmRadLenManager::CbmRadLenManager()
 : fPointCollection(new TClonesArray("CbmRadLenPoint")), 
   fTrackID(0),
   fVolumeID(0),
   fPosIn(TLorentzVector(0,0,0,0)),
   fPosOut(TLorentzVector(0,0,0,0)),
   fMomIn(TLorentzVector(0,0,0,0)),
   fMomOut(TLorentzVector(0,0,0,0)),
   fTime(0),
   fLength(0),
   fELoss(0),
   fA(0),
   fZmat(0),
   fDensity(0),
   fRadl(0),
   fAbsl(0)              
{
  /** radiation length default ctor */
   if(NULL == fgInstance) {
      fgInstance = this;
      fPointCollection=new TClonesArray("CbmRadLenPoint");
   }
}

CbmRadLenManager::~CbmRadLenManager()
{
   /** radiation length default dtor */
   fgInstance = NULL;
   fPointCollection->Delete();
   delete fPointCollection;
}

void CbmRadLenManager::Init()
{
	/**create the branch for output */
   CbmRootManager::Instance()->Register("RadLen","RadLenPoint", fPointCollection, kTRUE);
}

void CbmRadLenManager::Reset()
{
    /**We have to free the momeory, Clear() is faster but not enough! */
	fPointCollection->Delete();
}

void CbmRadLenManager::AddPoint()
{
 /**Add a point to the collection*/	
 if ( gMC->IsTrackEntering() ) {
    fELoss  = 0.;
    Int_t copyNo;
    fVolumeID = gMC->CurrentVolID(copyNo);
    fTime   = gMC->TrackTime() * 1.0e09;
    fLength = gMC->TrackLength();
    gMC->TrackPosition(fPosIn);
    gMC->TrackMomentum(fMomIn);
    //    Int_t MatId=  gMC->CurrentMaterial(fA, fZmat, fDensity, fRadl, fAbsl);
    gMC->CurrentMaterial(fA, fZmat, fDensity, fRadl, fAbsl);
 }
 /** Sum energy loss for all steps in the active volume */
    fELoss += gMC->Edep();
 /**  Create a point at exit of the volume */
    if ( gMC->IsTrackExiting()    ||
         gMC->IsTrackStop()       ||
         gMC->IsTrackDisappeared()   ) {
       
     fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
     gMC->TrackPosition(fPosOut);
     gMC->TrackMomentum(fMomOut);
     TClonesArray& clref = *fPointCollection;
     Int_t tsize = clref.GetEntriesFast();
     CbmRadLenPoint *p=new(clref[tsize]) CbmRadLenPoint(fTrackID, fVolumeID, 
			                               TVector3(fPosIn.X(),fPosIn.Y(),fPosIn.Z()),
	                                       TVector3(fMomIn.X(),fMomIn.Y(),fMomIn.Z()),
	                                       fTime,  fLength, fELoss,
					                       TVector3(fPosOut.X(),fPosOut.Y(),fPosOut.Z()),
	                                       TVector3(fMomOut.X(),fMomOut.Y(),fMomOut.Z()),
	                                       fA, fZmat, fDensity, fRadl);
  }

}


