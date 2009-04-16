// -------------------------------------------------------------------------
// -----                        FairBoxSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairBoxSetDraw.h"
#include "FairHit.h"
#include "TEveBoxSet.h"
#include "FairRootManager.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "FairEventManager.h"
#include "TEveManager.h"
#include "TVector3.h"
#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairBoxSetDraw::FairBoxSetDraw() { }
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairBoxSetDraw::FairBoxSetDraw(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose), fX(1), fY(1), fZ(1){

}
// -------------------------------------------------------------------------
InitStatus FairBoxSetDraw::Init()
{
	if(fVerbose>1)
	  cout<<  "FairBoxSetDraw::Init()" << endl;
   FairRootManager* fManager = FairRootManager::Instance();
   fList = (TClonesArray *)fManager->GetObject(GetName());
   if(fVerbose>2)
	   cout<<  "FairBoxSetDraw::Init() get track list" <<  fList<< endl;
   fEventManager =FairEventManager::Instance();
   if(fVerbose>2)
	   cout<<  "FairBoxSetDraw::Init() get instance of FairEventManager " << endl;
   fq=0;
}
// -------------------------------------------------------------------------
void FairBoxSetDraw::Exec(Option_t* option)
{
   TObject *p;
   Reset();
 //  cout<<  "FairBoxSetDraw::Init() Exec! " << fList->GetEntriesFast() << endl;
   fq = new TEveBoxSet(GetName());
   fq->Reset(TEveBoxSet::kBT_AABoxFixedDim, kFALSE, 32);
   fq->SetDefWidth(1);
   fq->SetDefHeight(1);
   fq->SetDefDepth(1);

   for (Int_t i=0; i<fList->GetEntriesFast(); ++i) {
      p=fList->At(i);
      AddBoxes(fq, p, i);
    }
    gEve->AddElement(fq, fEventManager );
    gEve->Redraw3D(kFALSE);
}

void FairBoxSetDraw::AddBoxes(TEveBoxSet* set, TObject* obj, Int_t i)
{
	TVector3 point = GetVector(obj);
	set->AddBox(point.X(),point.Y(),point.Z());
	set->DigitValue(GetValue(obj, i));
	if(fVerbose>2)
		cout<<  "FairBoxSetDraw::Init() Add point " << i << ": " <<point.X()<< " "<<point.Y()<< " "<< point.Z()<< " " << endl;
}


Int_t FairBoxSetDraw::GetValue(TObject* obj, Int_t i)
{
	return i;
}
// -----   Destructor   ----------------------------------------------------
FairBoxSetDraw::~FairBoxSetDraw()
{
}
// -------------------------------------------------------------------------
void FairBoxSetDraw::SetParContainers()
{

}
// -------------------------------------------------------------------------
  /** Action after each event**/
void FairBoxSetDraw::Finish()
{
}
// -------------------------------------------------------------------------
void FairBoxSetDraw::Reset()
{
    if(fq!=0){
//	   fq->Reset();
      gEve->RemoveElement(fq, fEventManager );
	 }
}


ClassImp(FairBoxSetDraw)


