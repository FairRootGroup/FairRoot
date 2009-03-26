// -------------------------------------------------------------------------
// -----                        FairTrackCandDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairTrackCandDraw.h"
#include "FairHit.h"
#include "TEveQuadSet.h"
#include "FairRootManager.h"
//#include "TClonesArray.h"
#include "TObjArray.h"
#include "FairEventManager.h"
#include "TEveManager.h"
#include "TrackCand.h"
#include "PndTpcCluster.h"
#include "PndTpcLheTrack.h"
#include "PndLhePidTrack.h"
#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairTrackCandDraw::FairTrackCandDraw() { }
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairTrackCandDraw::FairTrackCandDraw(const char* TrackCandName, Int_t iVerbose)
  : FairTask(TrackCandName, iVerbose) {
}
// -------------------------------------------------------------------------
InitStatus FairTrackCandDraw::Init()
{
   if(fVerbose>1)  cout<<  "FairTrackCandDraw::Init()" << endl;
   FairRootManager* fManager = CbmRootManager::Instance();
   fPixPointList = (TClonesArray *)fManager->GetObject("MVDHitsPixel");
   fStripPointList = (TClonesArray *)fManager->GetObject("MVDHitsStrip");
   fTpcClusterList = (TClonesArray *)fManager->GetObject("PndTpcCluster");
   if (fTpcClusterList == 0)
     fTpcClusterList = (TClonesArray*)fManager->GetObject("PndTpcClusterMerged");
   fTrackCandList = (TClonesArray *)fManager->GetObject(GetName());
   if(fPixPointList==0){
      cout << "FairTrackCandDraw::Init()  branch MVDHitsPixel Not found! Task will be deactivated "<< endl;
      SetActive(kFALSE);
    }
   if(fStripPointList==0){
      cout << "FairTrackCandDraw::Init()  branch MVDHitsStrip Not found! Task will be deactivated "<< endl;
      SetActive(kFALSE);
    }
   if(fTpcClusterList==0){
      cout << "FairTrackCandDraw::Init()  branch PndTpcCluster or PndTpcClusterMerged Not found! Task will be deactivated "<< endl;
      SetActive(kFALSE);
    }
   if(fTrackCandList==0){
      cout << "FairTrackCandDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
      SetActive(kFALSE);
    }
    if(fVerbose>2){
     cout<<  "FairTrackCandDraw::Init() get track list" <<  fTrackCandList<< endl;
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
void FairTrackCandDraw::Exec(Option_t* option)
{
   TrackCand *tc;
   PndLhePidTrack *pidtc;
   FairHit *p;
   Reset();
 //  cout<<  "FairTrackCandDraw::Exec() " << fPointList->GetEntriesFast() << endl;
   fq = new TEveQuadSet(GetName());
   fq->Reset(TEveQuadSet::kQT_RectangleXY, kFALSE, 256);

   for (Int_t i=0;  i<fTrackCandList->GetEntriesFast(); ++i) {
	  tc=0;

      if( 0 == strcmp(fTrackCandList->At(i)->ClassName() , "TrackCand") ) {
        tc=(TrackCand *)fTrackCandList->At(i);
        std::cout<<"fTrackCandList is full of TrackCands"<<std::endl;
      } else if ( 0 == strcmp(fTrackCandList->At(i)->ClassName() , "PndLhePidTrack") ) {
        pidtc=(PndLhePidTrack *)fTrackCandList->At(i);
        tc=pidtc->GetTrackCand();
        std::cout<<"fTrackCandList is full of PndLhePidTracks"<<std::endl;
      } else {
        std::cout<<"fTrackCandList is full of UNKNOWN "<<fTrackCandList->At(i)->ClassName()<<"?"<<std::endl;
      }
      if(0==tc) continue;

      for (Int_t j = 0; j < tc->getNHits(); j++){
        unsigned int detId, hitId;
        tc->getHit(j, detId, hitId);

        if (detId == 0){
                p = (FairHit *) fStripPointList->At(hitId);
        }
        else if (detId == 1){
            p=(FairHit *) fPixPointList->At(hitId);
        }
        else if (detId == 3){
          p = 0; // do it without CbmHit.. tpc package has none
          PndTpcCluster* myCluster = (PndTpcCluster*)fTpcClusterList->At(hitId);
          if(myCluster != 0){
            fq->AddQuad(myCluster->pos().X(),myCluster->pos().Y(),myCluster->pos().Z(),.5, .5);
            fq->QuadValue(i);
          }
        }
        else p = 0;
        if (p != 0){
          fq->AddQuad(p->GetX(),p->GetY(),p->GetZ(),.5, .5);
          fq->QuadValue(i);
          if(fVerbose>2)
            cout<<  "FairTrackCandDraw::Exec() Add point " << hitId << ": " <<p->GetX()<< " "<<p->GetY()<< " "<< p->GetZ()<< " for Track " << i << endl;
        }
      }
    }
   gEve->AddElement(fq, fEventManager );
   gEve->Redraw3D(kFALSE);
}
// -----   Destructor   ----------------------------------------------------
FairTrackCandDraw::~FairTrackCandDraw()
{
}
// -------------------------------------------------------------------------
void FairTrackCandDraw::SetParContainers()
{

}
// -------------------------------------------------------------------------
  /** Action after each event**/
void FairTrackCandDraw::Finish()
{
}
// -------------------------------------------------------------------------
void FairTrackCandDraw::Reset()
{
    if(fq!=0){
//	   fq->Reset();
      gEve->RemoveElement(fq, fEventManager );
	 }
}


ClassImp(FairTrackCandDraw)



