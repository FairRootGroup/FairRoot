// -------------------------------------------------------------------------
// -----                        FairPointSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairPointSetDraw.h"

#include "FairRootManager.h"
#include "FairEventManager.h"

#include "TClonesArray.h"
#include "TEveManager.h"
#include "TEvePointSet.h"
#include "TEveTreeTools.h"
#include "TVector3.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairPointSetDraw::FairPointSetDraw()
  : FairTask("FairPointSetDraw", 0),
    fVerbose(0),
    fPointList(NULL),
    fEventManager(NULL),
    fq(NULL),
    fColor(0),
    fStyle(0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairPointSetDraw::FairPointSetDraw(const char* name, Color_t color ,Style_t mstyle,Int_t iVerbose)
  : FairTask(name, iVerbose),
    fVerbose(iVerbose),
    fPointList(NULL),
    fEventManager(NULL),
    fq(NULL),
    fColor(color),
    fStyle(mstyle)
{

}
// -------------------------------------------------------------------------
InitStatus FairPointSetDraw::Init()
{
  if(fVerbose>1) { cout<<  "FairPointSetDraw::Init()" << endl; }
  FairRootManager* fManager = FairRootManager::Instance();
  fPointList = (TClonesArray*)fManager->GetObject(GetName());
  if(fPointList==0) {
    cout << "FairPointSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
    SetActive(kFALSE);
  }
  if(fVerbose>2) { cout<<  "FairPointSetDraw::Init() get track list" <<  fPointList<< endl; }
  fEventManager =FairEventManager::Instance();
  if(fVerbose>2) { cout<<  "FairPointSetDraw::Init() get instance of FairEventManager " << endl; }
  fq =0;

  // gEve->AddElement(fq, fEventManager );
  return kSUCCESS;
}
// -------------------------------------------------------------------------
void FairPointSetDraw::Exec(Option_t* option)
{
  if (IsActive()) {
    Int_t npoints=fPointList->GetEntriesFast();
    Reset();
    TEvePointSet* q = new TEvePointSet(GetName(),npoints,  TEvePointSelectorConsumer::kTVT_XYZ);
    q->SetOwnIds(kTRUE);
    q->SetMarkerColor(fColor);
    q->SetMarkerSize(1.5);
    q->SetMarkerStyle(fStyle);
    //std::cout << "fPointList: " << fPointList << " " << fPointList->GetEntries() << std::endl;
    for (Int_t i=0; i<npoints; ++i) {
      TObject*  p=(TObject*)fPointList->At(i);
      if(p!=0) {
        TVector3 vec(GetVector(p));
        q->SetNextPoint(vec.X(),vec.Y(), vec.Z());
        q->SetPointId(GetValue(p, i));
      }
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
  if(fq!=0) {
    fq->Reset();
    gEve->RemoveElement(fq, fEventManager );
  }
}


ClassImp(FairPointSetDraw);


