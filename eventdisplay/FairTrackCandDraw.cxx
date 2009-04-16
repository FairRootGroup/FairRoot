// -------------------------------------------------------------------------
// -----                        FairTrackCandDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairTrackCandDraw.h"
#include "FairHit.h"
#include "FairRootManager.h"
//#include "TClonesArray.h"
#include "TObjArray.h"
#include "FairEventManager.h"
#include "TEveManager.h"
#include "TEveBoxSet.h"
#include "TrackCand.h"
#include "PndTpcCluster.h"
//#include "PndTpcLheTrack.h"
//#include "PndLhePidTrack.h"
#include <iostream>
using std::cout;
using std::endl;

// -----   Standard constructor   ------------------------------------------
FairTrackCandDraw::FairTrackCandDraw(const char* TrackCandName, Int_t iVerbose):FairHitDraw(TrackCandName, iVerbose)
{
}
// -------------------------------------------------------------------------
InitStatus FairTrackCandDraw::Init()
{
	FairBoxSetDraw::Init();

   if(fVerbose>1)  cout<<  "FairTrackCandDraw::Init()" << endl;
   FairRootManager* fManager = FairRootManager::Instance();
   fPixPointList = (TClonesArray *)fManager->GetObject("MVDHitsPixel");
   fStripPointList = (TClonesArray *)fManager->GetObject("MVDHitsStrip");
   fTpcClusterList = (TClonesArray *)fManager->GetObject("PndTpcCluster");
   if (fTpcClusterList == 0)
     fTpcClusterList = (TClonesArray*)fManager->GetObject("PndTpcClusterMerged");
   if(fPixPointList==0){
      cout << "FairTrackCandDraw::Init()  branch MVDHitsPixel Not found! Task will be deactivated "<< endl;
      //SetActive(kFALSE);
    }
   if(fStripPointList==0){
      cout << "FairTrackCandDraw::Init()  branch MVDHitsStrip Not found! Task will be deactivated "<< endl;
      //SetActive(kFALSE);
    }
   if(fTpcClusterList==0){
      cout << "FairTrackCandDraw::Init()  branch PndTpcCluster or PndTpcClusterMerged Not found! Task will be deactivated "<< endl;
      //SetActive(kFALSE);
    }
   if(fVerbose>2){
     cout<<  "FairTrackCandDraw::Init() get pix points list" <<  fPixPointList<< endl;
     cout<<  "FairTrackCandDraw::Init() get strip points list" <<  fStripPointList<< endl;
     cout<<  "FairTrackCandDraw::Init() get tpc cluster list" << fTpcClusterList<<endl;

   }
   fEventManager =FairEventManager::Instance();
   if(fVerbose>2)
     cout<<  "FairTrackCandDraw::Init() get instance of FairEventManager " << endl;
   fq=0;
}
// -------------------------------------------------------------------------


void FairTrackCandDraw::AddBoxes(TEveBoxSet* set, TObject* obj, Int_t i)
{
	   TrackCand *tc;
//	   PndLhePidTrack *pidtc;
//	   FairHit *p;
	//   Reset();
	 //  cout<<  "FairTrackCandDraw::Exec() " << fPointList->GetEntriesFast() << endl;
	      if( 0 == strcmp(obj->ClassName() , "TrackCand") ) {
	        tc=(TrackCand *)obj;
	        std::cout<<"fTrackCandList is full of TrackCands"<<std::endl;
//	      } else if ( 0 == strcmp(obj->ClassName() , "PndLhePidTrack") ) {
//	        pidtc=(PndLhePidTrack *)fTrackCandList->At(i);
//	        tc=pidtc->GetTrackCand();
//	        std::cout<<"fTrackCandList is full of PndLhePidTracks"<<std::endl;
	      } else {
	        std::cout<<"fTrackCandList is full of UNKNOWN "<<obj->ClassName()<<"?"<<std::endl;
	      }
	      if(0==tc) return;


	      for (Int_t j = 0; j < tc->getNHits(); j++){
	        unsigned int detId, hitId;
	        tc->getHit(j, detId, hitId);
	        TVector3 point = GetVector(detId, hitId);
	        set->AddBox(point.X(), point.Y(), point.Z());
	        set->DigitValue(i);
	      }
}


TVector3 FairTrackCandDraw::GetVector(Int_t detId, Int_t hitId)
{
	FairHit* p;

	if (detId == 4 || detId == 5){
		if (detId == 5){
				p = (FairHit *) fPixPointList->At(hitId);
		}
		else if (detId == 4){
			p=(FairHit *) fStripPointList->At(hitId);
		}
		return (TVector3(p->GetX(), p->GetY(), p->GetZ()));
	}
    else if (detId == 3){
      PndTpcCluster* myCluster = (PndTpcCluster*)fTpcClusterList->At(hitId);
      if(myCluster != 0){
        return (myCluster->pos());
      }
    }
    else std::cout << "-E- FairTrackCandDraw::GetVector : Unknown Detector with ID: " << detId << std::endl;
	return TVector3();
}

// -----   Destructor   ----------------------------------------------------
FairTrackCandDraw::~FairTrackCandDraw()
{
}
// -------------------------------------------------------------------------



ClassImp(FairTrackCandDraw)



