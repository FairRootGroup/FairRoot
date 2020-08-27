/*
 * FairEveRecoTracksExampleEditor.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveRecoTracksExampleEditor.h"

FairEveRecoTracksExampleEditor::FairEveRecoTracksExampleEditor(const TGWindow *p,
                                                               Int_t width,
                                                               Int_t height,
                                                               UInt_t options,
                                                               Pixel_t back)
    : TGedFrame(p, width, height, options | kVerticalFrame, back)
    , fRecoTracks(nullptr)
{
    MakeTitle("FairRecoTracksEditor");
    SetName("RecoTracksEditor");

    TGVerticalFrame *kinFrame = CreateEditorTabSubFrame("Kin");
    fPtCut = new FairEveMinMaxCut(this, kinFrame, "Pt", width);
    fEtaCut = new FairEveMinMaxCut(this, kinFrame, "Eta", width);
    fEnergyCut = new FairEveMinMaxCut(this, kinFrame, "E", width);
    fPtCut->Init();
    fEtaCut->Init();
    fEnergyCut->Init();
    fPtCut->AddUpdateButton();

    TGVerticalFrame *statFrame = CreateEditorTabSubFrame("Status");

    fDrawMC = new FairEveBoolCut(this, statFrame, "Draw MC", 1);
    fDrawMC->UpdateWhenChanged();
    fDrawMC->Init();

    TGCompositeFrame *Frame = new TGCompositeFrame(statFrame, width, 20, kHorizontalFrame | kFixedWidth);
    TGTextButton *UpdateButton = new TGTextButton(Frame, "Swap Tracks");
    UpdateButton->Connect("Clicked()", this->ClassName(), this, "SwapTracks()");
    Frame->AddFrame(UpdateButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    statFrame->AddFrame(Frame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));
}

void FairEveRecoTracksExampleEditor::SetModel(TObject *obj)
{
    fRecoTracks = dynamic_cast<FairEveRecoTracksExample *>(obj);
}

void FairEveRecoTracksExampleEditor::SwapTracks()
{
    if (fRecoTracks)
        fRecoTracks->SwapTracks();
}

void FairEveRecoTracksExampleEditor::Repaint()
{
    Double_t min, max;
    Bool_t use = fPtCut->GetValues(min, max);
    fRecoTracks->SetPtCut(min, max, use);
    use = fEtaCut->GetValues(min, max);
    fRecoTracks->SetEtaCut(min, max, use);
    use = fEnergyCut->GetValues(min, max);
    fRecoTracks->SetEnergyCut(min, max, use);
    fRecoTracks->SetDrawMC(fDrawMC->GetValue());
    TGedFrame::Update();
    fRecoTracks->Repaint();
}

FairEveRecoTracksExampleEditor::~FairEveRecoTracksExampleEditor()
{
    delete fPtCut;
    delete fEtaCut;
    delete fEnergyCut;
    delete fDrawMC;
}
