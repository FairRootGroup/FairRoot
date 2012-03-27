#include "FairBoxSetEditor.h"

#include "FairRootManager.h"
#include "FairEventManager.h"
#include "FairRunAna.h"

#include "TGLabel.h"
#include "TGButton.h"
#include "TGNumberEntry.h"
#include "TGeoManager.h"
#include "TChain.h"
#include "TEveGValuators.h"
#include "FairEventManager.h"

//______________________________________________________________________________
// FairBoxSetEditor
//
// Specialization of TGedEditor for proper update propagation to
// TEveManager.

ClassImp(FairBoxSetEditor)


//______________________________________________________________________________
FairBoxSetEditor::FairBoxSetEditor(const TGWindow* p, Int_t width, Int_t height,
                                   UInt_t options, Pixel_t back)
  :TGedFrame(p, width, height, options | kVerticalFrame, back),
   fObject(0), fInfoFrame(0), fM(0)

{
  std::cout << "FairBoxSetEditor called!" << std::endl;
  Init();
}

void FairBoxSetEditor::Init()
{

  FairRootManager* fRootManager=FairRootManager::Instance();
  TChain* chain =fRootManager->GetInChain();
  Int_t Entries= chain->GetEntriesFast();

  MakeTitle("FairBoxSet  Editor");
  fInfoFrame= CreateEditorTabSubFrame("Time");
  TGCompositeFrame* title1 = new TGCompositeFrame(fInfoFrame, 250, 10,
      kVerticalFrame | kLHintsExpandX |
      kFixedWidth    | kOwnBackground);

  TString EventTime = "Event Time BoxSetEditor : ";
//  TFile* file =FairRunAna::Instance()->GetInputFile();
  EventTime+=FairRootManager::Instance()->GetEventTime();
  TGLabel* TFName=new TGLabel(title1, EventTime.Data());
  title1->AddFrame(TFName);

  UInt_t RunId= FairRunAna::Instance()->getRunId();
  TString run= "Run Id : ";
  run += RunId;
  TGLabel* TRunId=new TGLabel(title1, run.Data());
  title1->AddFrame( TRunId);

  fTimeWindow = new TEveGValuator(title1, "Time Window:", 90, 0);
  fTimeWindow->SetNELength(5);
  fTimeWindow->SetLabelWidth(80);
  fTimeWindow->Build();
// fTimeWindow->SetLimits(0, MAXE, 2501, TGNumberFormat::kNESRealOne);
  fTimeWindow->SetToolTip("Time window in ns for which points are shown");
  fTimeWindow->Connect("ValueSet(Double_t)", "FairBoxSetEditor",this, "TimeWindow()");
  title1->AddFrame(fTimeWindow, new TGLayoutHints(kLHintsTop, 1, 1, 1, 0));

  fInfoFrame->AddFrame(title1);

  std::cout << EventTime.Data() << std::endl;

}

void FairBoxSetEditor::TimeWindow()
{
  std::cout << "FairBoxSetEditor::TimeWindow " << fTimeWindow->GetValue() << std::endl;
  fM->SetTimeWindow(fTimeWindow->GetValue());
  FairEventManager* man = FairEventManager::Instance();
  man->GotoEvent(man->GetCurrentEvent());
  Update();
}


//______________________________________________________________________________



