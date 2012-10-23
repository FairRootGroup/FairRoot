#include "FairEventManagerEditor.h"

#include "FairRootManager.h"
#include "FairEventManager.h"
#include "FairRunAna.h"

#include "TGLabel.h"
#include "TGButton.h"
#include "TGNumberEntry.h"
#include "TGeoManager.h"
#include "TChain.h"

#define MAXE 5000

//______________________________________________________________________________
// FairEventManagerEditor
//
// Specialization of TGedEditor for proper update propagation to
// TEveManager.

ClassImp(FairEventManagerEditor)


//______________________________________________________________________________
FairEventManagerEditor::FairEventManagerEditor(const TGWindow* p, Int_t width, Int_t height,
    UInt_t options, Pixel_t back)
  :TGedFrame(p, width, height, options | kVerticalFrame, back),
   fObject(0),
   fManager(FairEventManager::Instance()),
   fCurrentEvent(0),
   fCurrentPDG(0),
   fVizPri(0),
   fMinEnergy(0),
   fMaxEnergy(0),
   fEventTime(NULL)
{
  Init();
}

void FairEventManagerEditor::Init()
{

  FairRootManager* fRootManager=FairRootManager::Instance();
  TChain* chain =fRootManager->GetInChain();
  Int_t Entries= chain->GetEntriesFast();

  MakeTitle("FairEventManager  Editor");
  TGVerticalFrame*      fInfoFrame= CreateEditorTabSubFrame("Info");
  TGCompositeFrame* title1 = new TGCompositeFrame(fInfoFrame, 250, 10,
      kVerticalFrame | kLHintsExpandX |
      kFixedWidth    | kOwnBackground);

  TString Infile= "Input file : ";
//  TFile* file =FairRunAna::Instance()->GetInputFile();
  TFile* file =FairRootManager::Instance()->GetInChain()->GetFile();
  Infile+=file->GetName();
  TGLabel* TFName=new TGLabel(title1, Infile.Data());
  title1->AddFrame(TFName);

  UInt_t RunId= FairRunAna::Instance()->getRunId();
  TString run= "Run Id : ";
  run += RunId;
  TGLabel* TRunId=new TGLabel(title1, run.Data());
  title1->AddFrame( TRunId);

  TString nevent= "No of events : ";
  nevent +=Entries ;
  TGLabel* TEvent=new TGLabel(title1, nevent.Data());
  title1->AddFrame(TEvent);

  Int_t nodes= gGeoManager->GetNNodes();
  TString NNodes= "No. of Nodes : ";
  NNodes += nodes;
  TGLabel* NoNode=new TGLabel(title1, NNodes.Data());
  title1->AddFrame( NoNode);

  TGHorizontalFrame* f = new TGHorizontalFrame(title1);
  TGLabel* l = new TGLabel(f, "Current Event:");
  f->AddFrame(l, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 1, 2, 1, 1));
  fCurrentEvent = new TGNumberEntry(f, 0., 6, -1,
                                    TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
                                    TGNumberFormat::kNELLimitMinMax, 0, Entries);
  f->AddFrame(fCurrentEvent, new TGLayoutHints(kLHintsLeft, 1, 1, 1, 1));
  fCurrentEvent->Connect("ValueSet(Long_t)","FairEventManagerEditor", this, "SelectEvent()");
  title1->AddFrame(f);

  TGHorizontalFrame* f2 = new TGHorizontalFrame(title1);
  TGLabel* EventTimeLabel = new TGLabel(f2, "Event Time: ");
  fEventTime = new TGLabel(f2,"");
  f2->AddFrame(EventTimeLabel);
  f2->AddFrame(fEventTime);
  title1->AddFrame(f2);

  fVizPri = new TGCheckButton(title1, "Primary Only");
  AddFrame(fVizPri, new TGLayoutHints(kLHintsTop, 3, 1, 1, 0));
  fVizPri->Connect("Toggled(Bool_t)", "FairEventManagerEditor", this, "DoVizPri()");

  title1->AddFrame(fVizPri);

  TGHorizontalFrame* f1 = new TGHorizontalFrame(title1);
  TGLabel* L1 = new TGLabel(f1, "Select PDG :");
  f1->AddFrame(L1, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 1, 2, 1, 1));
  fCurrentPDG = new TGNumberEntry(f1, 0., 12, -1,
                                  TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber,
                                  TGNumberFormat::kNELNoLimits, 0, 1);
  f1->AddFrame(fCurrentPDG, new TGLayoutHints(kLHintsLeft, 1, 1, 1, 1));
  fCurrentPDG->Connect("ValueSet(Long_t)","FairEventManagerEditor", this, "SelectPDG()");
  title1->AddFrame(f1);


  fMinEnergy = new TEveGValuator(title1, "Min Energy:", 90, 0);
  fMinEnergy->SetNELength(5);
  fMinEnergy->SetLabelWidth(80);
  fMinEnergy->Build();
  fMinEnergy->SetLimits(0, MAXE, 2501, TGNumberFormat::kNESRealOne);
  fMinEnergy->SetToolTip("Minimum energy of displayed track.");
  fMinEnergy->Connect("ValueSet(Double_t)", "FairEventManagerEditor",this, "MinEnergy()");
  title1->AddFrame(fMinEnergy, new TGLayoutHints(kLHintsTop, 1, 1, 1, 0));


  fMaxEnergy = new TEveGValuator(title1, "Max Energy:", 90, 0);
  fMaxEnergy->SetNELength(5);
  fMaxEnergy->SetLabelWidth(80);
  fMaxEnergy->Build();
  fMaxEnergy->SetLimits(0, MAXE, 2501, TGNumberFormat::kNESRealOne);
  fMaxEnergy->SetToolTip("Maximum energy of displayed track.");
  fMaxEnergy->SetValue(MAXE);
  fMaxEnergy->Connect("ValueSet(Double_t)", "FairEventManagerEditor",this, "MaxEnergy()");
  title1->AddFrame(fMaxEnergy, new TGLayoutHints(kLHintsTop, 1, 1, 1, 0));

  TGTextButton* fUpdate = new TGTextButton(title1, "Update");
  title1->AddFrame(fUpdate, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 5,5,1,1));
  fUpdate->Connect("Clicked()", "FairEventManagerEditor", this, "SelectEvent()");

  fInfoFrame->AddFrame(title1, new TGLayoutHints(kLHintsTop, 0, 0, 2, 0));

  fManager->SetMaxEnergy(MAXE);
}


//______________________________________________________________________________
void FairEventManagerEditor::MaxEnergy()
{
  fManager->SetMaxEnergy(fMaxEnergy->GetValue());

}
//______________________________________________________________________________
void FairEventManagerEditor::MinEnergy()
{
  fManager->SetMinEnergy(fMinEnergy->GetValue());

}

//______________________________________________________________________________
void FairEventManagerEditor::DoVizPri()
{
  if (fVizPri->IsOn()) { fManager->SetPriOnly(kTRUE); }
  else { fManager->SetPriOnly(kFALSE); }
}
//______________________________________________________________________________
void FairEventManagerEditor::SelectPDG()
{
  fManager->SelectPDG(fCurrentPDG->GetIntNumber());
}

//______________________________________________________________________________
void FairEventManagerEditor::SelectEvent()
{
  fManager->GotoEvent(fCurrentEvent->GetIntNumber());

  TString time;
// time+=(FairRootManager::Instance()->GetEventTime());
  time.Form("%.2f", FairRootManager::Instance()->GetEventTime());
  time += " ns";
  fEventTime->SetText(time.Data());

  fMinEnergy->SetLimits(fManager->GetEvtMinEnergy(), fManager->GetEvtMaxEnergy(), 100);
  fMinEnergy->SetValue(fManager->GetEvtMinEnergy());
  fMaxEnergy->SetLimits(fManager->GetEvtMinEnergy(), fManager->GetEvtMaxEnergy(), 100);
  fMaxEnergy->SetValue( fManager->GetEvtMaxEnergy());
  Update();

}
//______________________________________________________________________________
void FairEventManagerEditor::SetModel( TObject* obj)
{
  fObject     = obj;

}
//______________________________________________________________________________



