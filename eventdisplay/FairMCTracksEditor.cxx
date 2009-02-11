#include "FairMCTracksEditor.h"
#include "TGedFrame.h"
#include <iostream>
#include "TStyle.h"

#include "TGLabel.h"
#include "TG3DLine.h"
#include "TGButton.h"
#include "TGNumberEntry.h"
#include "TGColorSelect.h"
#include "TGDoubleSlider.h"
#include "FairEventManager.h"
#include "FairRunAna.h"

//______________________________________________________________________________
// FairMCTracksEditor
//
// Specialization of TGedEditor for proper update propagation to
// TEveManager.

ClassImp(FairMCTracksEditor)


//______________________________________________________________________________
FairMCTracksEditor::FairMCTracksEditor(const TGWindow* p, Int_t width, Int_t height,
                      UInt_t options, Pixel_t back) :
   TGedFrame(p, width, height, options | kVerticalFrame, back)
{
  // Resize(width, height);
   fManager= FairEventManager::Instance();

   MakeTitle("FairEventManager  Editor");

   TGVerticalFrame      *fInfoFrame= CreateEditorTabSubFrame("Info");
   TGCompositeFrame *title1 = new TGCompositeFrame(fInfoFrame, 180, 10,
                                                   kVerticalFrame |
                                                   kLHintsExpandX   |
                                                   kFixedWidth      |
                                                   kOwnBackground);
   TString Infile= "Input File : ";
   TFile *file =FairRunAna::Instance()->GetInputFile();
   Infile+=file->GetName();
   TGLabel *TFName=new TGLabel(title1, Infile.Data());   
   title1->AddFrame(TFName);
 
   UInt_t RunId= FairRunAna::Instance()->getRunId();
   TString run= "Run Id : ";
   run += RunId; 
   TGLabel *TRunId=new TGLabel(title1, run.Data());
   title1->AddFrame( TRunId);

   fInfoFrame->AddFrame(title1, new TGLayoutHints(kLHintsTop, 0, 0, 2, 0));
}

//______________________________________________________________________________
void FairMCTracksEditor::SetModel( TObject* obj)
{
   fObject     = obj;
}
//______________________________________________________________________________



