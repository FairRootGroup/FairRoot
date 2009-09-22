// -------------------------------------------------------------------------
// -----                        FairBoxSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairBoxSetDraw.h"
#include "FairHit.h"
#include "FairRootManager.h"
#include "TObjArray.h"
#include "TEveManager.h"
#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairBoxSetDraw::FairBoxSetDraw() : fVerbose(0), fq(0),fX(1), fY(1), fZ(1){ }
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairBoxSetDraw::FairBoxSetDraw(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose),  fVerbose(iVerbose), fq(0), fX(1), fY(1), fZ(1)
{
}
// -------------------------------------------------------------------------
InitStatus FairBoxSetDraw::Init()
{
	if(fVerbose>1)
	  cout<<  "FairBoxSetDraw::Init()" << endl;
   fManager = FairRootManager::Instance();
   fList = (TClonesArray *)fManager->GetObject(GetName());
   //std::cout << fList << std::endl;
   if (fList==0){
	   cout << "FairBoxSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
	   SetActive(kFALSE);
	   return kERROR;
   }
   if(fVerbose>2)
	   cout<<  "FairBoxSetDraw::Init() get track list" <<  fList<< endl;
   fEventManager =FairEventManager::Instance();
   if(fVerbose>2)
	   cout<<  "FairBoxSetDraw::Init() get instance of FairEventManager " << endl;
   fq=0;
	return kSUCCESS;	
}
// -------------------------------------------------------------------------
void FairBoxSetDraw::Exec(Option_t* option)
{
	if(IsActive()){
	   TObject *p;
	   Reset();
	 //  cout<<  "FairBoxSetDraw::Init() Exec! " << fList->GetEntriesFast() << endl;
	   fq = new TEveBoxSet(GetName());
	   fq->Reset(TEveBoxSet::kBT_AABoxFixedDim, kFALSE, 32);
	   fq->SetDefWidth(1);
	   fq->SetDefHeight(1);
	   fq->SetDefDepth(1);

	   //fList = (TClonesArray *)fManager->GetObject(GetName());
	   //std::cout << "fList: " << fList << " " << fList->GetEntries() << std::endl;
	   for (Int_t i=0; i<fList->GetEntriesFast(); ++i) {
		  p=fList->At(i);
		  AddBoxes(fq, p, i);
		}
		gEve->AddElement(fq, fEventManager );
		gEve->Redraw3D(kFALSE);
	}
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
    	fq->Reset();
    	gEve->RemoveElement(fq, fEventManager );
	 }
}


ClassImp(FairBoxSetDraw)


