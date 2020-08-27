/*
 * FairEveMCTracksEditor.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveMCTracksEditor.h"

FairEveMCTracksEditor::FairEveMCTracksEditor(const TGWindow *p, Int_t width,
        Int_t height, UInt_t options, Pixel_t back) :
        TGedFrame(p, width, height, options | kVerticalFrame, back),fMCTracks(nullptr){

    MakeTitle("FairMCTracksEditor");
    SetName("MCtracksEditor");

    TGVerticalFrame *kinFrame = CreateEditorTabSubFrame("Kin");
    fPtCut = new FairEveMinMaxCut(this,kinFrame,"Pt",width);
    fEtaCut = new FairEveMinMaxCut(this,kinFrame,"Eta",width);
    fEnergyCut = new FairEveMinMaxCut(this,kinFrame,"E",width);
    fPtCut->Init();
    fEtaCut->Init();
    fEnergyCut->Init();
    fPtCut->AddUpdateButton();

    TGVerticalFrame *statFrame = CreateEditorTabSubFrame("Status");

    fPrimary = new FairEveBoolCut(this,statFrame,"Primary",width);
    fPrimary->UpdateWhenChanged();
    fPrimary->SetInitStatus(kTRUE);
    fSecondary = new FairEveBoolCut(this,statFrame,"Secondary",width);
    fSecondary->SetInitStatus(kTRUE);
    fSecondary->UpdateWhenChanged();
    fPdgCut = new FairEveIntCut(this,statFrame,"PDG",width);
    fPrimary->Init();
    fSecondary->Init();
    fPdgCut->Init();
    fPdgCut->AddUpdateButton();

    TGCompositeFrame *Frame = new TGCompositeFrame(statFrame, width, 20,
            kHorizontalFrame | kFixedWidth);
    TGTextButton *UpdateButton = new TGTextButton(Frame, "Swap Tracks");
    UpdateButton->Connect("Clicked()", this->ClassName(), this,
            "SwapTracks()");
    Frame->AddFrame(UpdateButton,
            new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    statFrame->AddFrame(Frame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));
}

void FairEveMCTracksEditor::SetModel(TObject *obj) {
    fMCTracks = dynamic_cast<FairEveMCTracks*>(obj);
}

void FairEveMCTracksEditor::SwapTracks() {
    if(fMCTracks)
        fMCTracks->SwapTracks();
}

void FairEveMCTracksEditor::Repaint() {
    Double_t min,max;
    Bool_t use = fPtCut->GetValues(min, max);
    fMCTracks->SetPtCut(min, max, use);
    use = fEtaCut->GetValues(min, max);
    fMCTracks->SetEtaCut(min, max, use);
    use = fEnergyCut->GetValues(min, max);
    fMCTracks->SetEnergyCut(min,max,use);
    Int_t pdg_code;
    use = fPdgCut->GetValue(pdg_code);
    fMCTracks->SetPdgCut(pdg_code,use);
    fMCTracks->SetShowPrimSec(fPrimary->GetValue(), fSecondary->GetValue());
    TGedFrame::Update();
    fMCTracks->Repaint();
}

FairEveMCTracksEditor::~FairEveMCTracksEditor() {
    // TODO Auto-generated destructor stub
}
