// -------------------------------------------------------------------------
// -----                        FairMCPointDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairMCPointDraw.h"
#include "CbmMCPoint.h"
#include "TEveQuadSet.h"
#include "CbmRootManager.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "FairEventManager.h"
#include "TEveManager.h"
#include "TEvePointSet.h"
#include <iostream>
#include "TEveTreeTools.h"
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairMCPointDraw::FairMCPointDraw() 
  :fVerbose(0),
   fPointList(0),
   fEventManager(0),
   fq(0)
{
 }
// -------------------------------------------------------------------------

                                      

// -----   Standard constructor   ------------------------------------------
FairMCPointDraw::FairMCPointDraw(const char* name, Color_t color ,Style_t mstyle,Int_t iVerbose) 
  : CbmTask(name, iVerbose),
    fVerbose(iVerbose),
    fPointList(0),
    fEventManager(0),
    fq(0),
	fColor(color),
	fStyle(mstyle)
{
 
}
// -------------------------------------------------------------------------
InitStatus FairMCPointDraw::Init()
{
  if(fVerbose>1) cout<<  "FairMCPointDraw::Init()" << endl;
   CbmRootManager* fManager = CbmRootManager::Instance();
   fPointList = (TClonesArray *)fManager->GetObject(GetName());
   if(fPointList==0){
      cout << "FairMCPointDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl; 
      SetActive(kFALSE);
    }
   if(fVerbose>2)  cout<<  "FairMCPointDraw::Init() get track list" <<  fPointList<< endl;
   fEventManager =FairEventManager::Instance();
   if(fVerbose>2) cout<<  "FairMCPointDraw::Init() get instance of FairEventManager " << endl;
   fq =0;
      
  // gEve->AddElement(fq, fEventManager ); 
   return kSUCCESS;
}
// -------------------------------------------------------------------------  
void FairMCPointDraw::Exec(Option_t* option)
{
   if (IsActive()){
   CbmMCPoint *p=0;
  // Reset();
//   TEveQuadSet* q = new TEveQuadSet(GetName());
//   TEvePointSet* q = new TEvePointSet();
  // gEve->RemoveElement(fq, fEventManager );
   Int_t npoints=fPointList->GetEntriesFast();
   Reset();
   TEvePointSet *q = new TEvePointSet(GetName(),npoints,  TEvePointSelectorConsumer::kTVT_XYZ);
   q->SetOwnIds(kTRUE);
   q->SetMarkerColor(fColor);
   q->SetMarkerSize(1.5);
   q->SetMarkerStyle(fStyle);

   for (Int_t i=0; i<npoints; ++i) {   
      p=(CbmMCPoint *)fPointList->At(i);
      //fq->AddQad(p->GetX(),p->GetY(),p->GetZ(),1.5, 1.5);
	  if(p!=0) {
		q->SetNextPoint(p->GetX(),p->GetY(),p->GetZ());
        q->SetPointId(new TNamed(Form("Point %d", i), ""));
	  }
	//  TVector3 fMom; 
    //  p->Momentum(fMom); 
    //  fq->QuadValue(fMom.Mag());
    //  if(fVerbose>2) cout<<  "FairMCPointDraw::Init() Add point " <<p->GetX()<< " "<<p->GetY()<< " "<< p->GetZ()<< " " << endl; 

    }
	gEve->AddElement(q);
	gEve->Redraw3D(kFALSE); 
	fq=q;
  }

}
// -----   Destructor   ----------------------------------------------------
FairMCPointDraw::~FairMCPointDraw() 
{ 
}
// -------------------------------------------------------------------------
void FairMCPointDraw::SetParContainers()
{ 

}
// -------------------------------------------------------------------------
  /** Action after each event**/
void FairMCPointDraw::Finish()
{
}
// -------------------------------------------------------------------------
void FairMCPointDraw::Reset()
{
     if(fq!=0){
	   fq->Reset();
       gEve->RemoveElement(fq, fEventManager );
	 }
}


ClassImp(FairMCPointDraw)


