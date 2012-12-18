// -------------------------------------------------------------------------
// -----                        FairBoxSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairBoxSetDraw.h"

#include "FairRootManager.h"
#include "FairEventManager.h"

#include "TEveManager.h"
#include "FairBoxSet.h"
#include "TClonesArray.h"
#include "TVector3.h"

#include <iostream>
using std::cout;
using std::endl;

FairBoxSet* fq;    //!
Double_t fX, fY, fZ;

// -----   Default constructor   -------------------------------------------
FairBoxSetDraw::FairBoxSetDraw()
  : FairTask("FairBoxSetDraw",0),
    fVerbose(0),
    fList(NULL),
    fEventManager(NULL),
    fManager(NULL),
    fq(NULL),
    fX(1.),
    fY(1.),
    fZ(1.),
    fTimeWindowPlus(0.),
    fTimeWindowMinus(0.),
    fStartTime(0.),
    fUseEventTime(kTRUE),
    fStartFunctor(),
    fStopFunctor()
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairBoxSetDraw::FairBoxSetDraw(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose),
    fVerbose(iVerbose),
    fList(NULL),
    fEventManager(NULL),
    fManager(NULL),
    fq(NULL),
    fX(1.),
    fY(1.),
    fZ(1.),
    fTimeWindowPlus(0.),
    fTimeWindowMinus(0.),
    fStartTime(0.),
    fUseEventTime(kTRUE),
    fStartFunctor(),
    fStopFunctor()
{
}
// -------------------------------------------------------------------------
InitStatus FairBoxSetDraw::Init()
{
  if(fVerbose>1) {
    cout<<  "FairBoxSetDraw::Init()" << endl;
  }
  fManager = FairRootManager::Instance();

  fList = (TClonesArray*)FairRootManager::Instance()->GetObject(GetName());
  //std::cout << fList << std::endl;
  if (fList==0) {
    cout << "FairBoxSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
    SetActive(kFALSE);
    return kERROR;
  }
  if(fVerbose>2) {
    cout<<  "FairBoxSetDraw::Init() get track list" <<  fList<< endl;
  }
  fEventManager =FairEventManager::Instance();
  if(fVerbose>2) {
    cout<<  "FairBoxSetDraw::Init() get instance of FairEventManager " << endl;
  }
  fq=0;

  fStartFunctor = new StopTime();
  fStopFunctor = new StopTime();

  return kSUCCESS;
}
// -------------------------------------------------------------------------
void FairBoxSetDraw::Exec(Option_t* option)
{
  if(IsActive()) {
    TObject* p;
    Reset();
    //  cout<<  "FairBoxSetDraw::Init() Exec! " << fList->GetEntriesFast() << endl;
    CreateBoxSet();
    if (FairRunAna::Instance()->IsTimeStamp()) {
      fList->Clear();
      Double_t eventTime = FairRootManager::Instance()->GetEventTime();
      if (fUseEventTime) { fStartTime = eventTime - fTimeWindowMinus; }
      cout << "EventTime: " << eventTime << " TimeWindow: " << fStartTime << " - " << eventTime + fTimeWindowPlus << std::endl;

      fList = FairRootManager::Instance()->GetData(GetName(), fStartFunctor, fStartTime, fStopFunctor, eventTime + fTimeWindowPlus); //FairRootManager::Instance()->GetEventTime() +

    }

    //fList = (TClonesArray *)fManager->GetObject(GetName());
    if (fVerbose > 1) {
      std::cout << GetName() << " fList: " << fList->GetEntries() << std::endl;
    }
    for (Int_t i=0; i<fList->GetEntriesFast(); ++i) {
      p=fList->At(i);
      if (fVerbose > 2) {
        FairTimeStamp* data = (FairTimeStamp*)p;
//        cout << "TimeStamp: " <<  data->GetTimeStamp() << std::endl;
      }
      AddBoxes(fq, p, i);
    }
    gEve->AddElement(fq, fEventManager );
    gEve->Redraw3D(kFALSE);
  }
}

void FairBoxSetDraw::AddBoxes(FairBoxSet* set, TObject* obj, Int_t i)
{
  TVector3 point = GetVector(obj);
  set->AddBox(point.X(),point.Y(),point.Z());
  set->DigitValue(GetValue(obj, i));
  if(fVerbose>2) {
    cout<<  "FairBoxSetDraw::Init() Add point " << i << ": " <<point.X()<< " "<<point.Y()<< " "<< point.Z()<< " " << endl;
  }
}


Int_t FairBoxSetDraw::GetValue(TObject* obj, Int_t i)
{
  return i;
}

FairBoxSet* FairBoxSetDraw::CreateBoxSet()
{
  FairBoxSet* aBoxSet = new FairBoxSet(this, GetName());
  aBoxSet->Reset(FairBoxSet::kBT_AABoxFixedDim, kFALSE, 32);
  aBoxSet->SetDefWidth(0.3);
  aBoxSet->SetDefHeight(0.3);
  aBoxSet->SetDefDepth(0.3);
  fq = aBoxSet;

  return aBoxSet;
}

void FairBoxSetDraw::SetTimeWindowMinus(Double_t val)
{
  fTimeWindowMinus = val;
}

void FairBoxSetDraw::SetTimeWindowPlus(Double_t val)
{
  fTimeWindowPlus = val;
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
  if(fq!=0) {
    fq->Reset();
    gEve->RemoveElement(fq, fEventManager );
  }
}


ClassImp(FairBoxSetDraw)


