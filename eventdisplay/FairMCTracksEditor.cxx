/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairMCTracksEditor.h"

#include "FairEventManager.h"           // for FairEventManager
#include "FairRootManager.h"            // for FairRootManager
#include "FairRunAna.h"                 // for FairRunAna

#include "TChain.h"                     // for TChain
#include "TFile.h"                      // for TFile
#include "TGLabel.h"                    // for TGLabel
#include "TGLayout.h"
#include "TString.h"                    // for TString

#include <stddef.h>                     // for NULL

class TGWindow;
class TObject;

//______________________________________________________________________________
// FairMCTracksEditor
//
// Specialization of TGedEditor for proper update propagation to
// TEveManager.

ClassImp(FairMCTracksEditor)


//______________________________________________________________________________
FairMCTracksEditor::FairMCTracksEditor(const TGWindow* p, Int_t width, Int_t height,
                                       UInt_t options, Pixel_t back)
  : TGedFrame(p, width, height, options | kVerticalFrame, back),
    fObject(NULL),
    fManager(FairEventManager::Instance())
{
  // Resize(width, height);
  //  fManager= FairEventManager::Instance();

  MakeTitle("FairEventManager  Editor");

  TGVerticalFrame*      fInfoFrame= CreateEditorTabSubFrame("Info");
  TGCompositeFrame* title1 = new TGCompositeFrame(fInfoFrame, 180, 10,
      kVerticalFrame |
      kLHintsExpandX   |
      kFixedWidth      |
      kOwnBackground);
  TString Infile= "Input File : ";
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

  fInfoFrame->AddFrame(title1, new TGLayoutHints(kLHintsTop, 0, 0, 2, 0));
}

//______________________________________________________________________________
void FairMCTracksEditor::SetModel( TObject* obj)
{
  fObject     = obj;
}
//______________________________________________________________________________



