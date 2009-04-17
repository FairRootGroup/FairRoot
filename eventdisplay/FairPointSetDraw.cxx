// -------------------------------------------------------------------------
// -----                        FairPointSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairPointSetDraw.h"
#include "TEveQuadSet.h"
#include "FairRootManager.h"
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
FairPointSetDraw::FairPointSetDraw()
  :fVerbose(0),
   fPointList(0),
   fEventManager(0),
   fq(0)
{
 }
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairPointSetDraw::FairPointSetDraw(const char* name, Color_t color ,Style_t mstyle,Int_t iVerbose)
  : FairTask(name, iVerbose),
    fVerbose(iVerbose),
    fPointList(0),
    fEventManager(0),
    fq(0),
	fColor(color),
	fStyle(mstyle)
{

}
// -------------------------------------------------------------------------
InitStatus FairPointSetDraw::Init()
{
  if(fVerbose>1) cout<<  "FairPointSetDraw::Init()" << endl;
   FairRootManager* fManager = FairRootManager::Instance();
   fPointList = (TClonesArray *)fManager->GetObject(GetName());
   if(fPointList==0){
      cout << "FairPointSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
      SetActive(kFALSE);
    }
   if(fVerbose>2)  cout<<  "FairPointSetDraw::Init() get track list" <<  fPointList<< endl;
   fEventManager =FairEventManager::Instance();
   if(fVerbose>2) cout<<  "FairPointSetDraw::Init() get instance of FairEventManager " << endl;
   fq =0;

  // gEve->AddElement(fq, fEventManager );
   return kSUCCESS;
}
// -------------------------------------------------------------------------
void FairPointSetDraw::Exec(Option_t* option)
{
   if (IsActive()){
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
      TObject*  p=(TObject *)fPointList->At(i);
      //fq->AddQad(p->GetX(),p->GetY(),p->GetZ(),1.5, 1.5);
	  if(p!=0) {
		  TVector3 vec(GetVector(p));
		q->SetNextPoint(vec.X(),vec.Y(), vec.Z());
        q->SetPointId(GetValue(p, i));
	  }
	//  TVector3 fMom;
    //  p->Momentum(fMom);
    //  fq->QuadValue(fMom.Mag());
    //  if(fVerbose>2) cout<<  "FairPointSetDraw::Init() Add point " <<p->GetX()<< " "<<p->GetY()<< " "<< p->GetZ()<< " " << endl;

    }
	gEve->AddElement(q);
	gEve->Redraw3D(kFALSE);
	fq=q;
  }

}

TObject* FairPointSetDraw::GetValue(TObject* obj,Int_t i)
{
	return new TNamed(Form("Point %d", i),"");
}

// -----   Destructor   ----------------------------------------------------
FairPointSetDraw::~FairPointSetDraw()
{
}
// -------------------------------------------------------------------------
void FairPointSetDraw::SetParContainers()
{

}
// -------------------------------------------------------------------------
  /** Action after each event**/
void FairPointSetDraw::Finish()
{
}
// -------------------------------------------------------------------------
void FairPointSetDraw::Reset()
{
     if(fq!=0){
	   fq->Reset();
       gEve->RemoveElement(fq, fEventManager );
	 }
}


ClassImp(FairPointSetDraw);


