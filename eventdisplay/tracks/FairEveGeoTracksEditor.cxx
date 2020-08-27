/*
 * FairGeoTracksEditor.cxx
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include <iostream>

#include "FairEveGeoTracksEditor.h"

FairEveGeoTracksEditor::FairEveGeoTracksEditor(const TGWindow *p, Int_t width,
        Int_t height, UInt_t options, Pixel_t back) :
        TGedFrame(p, width, height, options | kVerticalFrame, back),fGeoTracks(nullptr){

    MakeTitle("FairGeoTracksEditor");
    SetName("MCtracksEditor");

    TGVerticalFrame *kinFrame = CreateEditorTabSubFrame("Kin");
    fPtCut .reset(new FairEveMinMaxCut(this,kinFrame,"Pt",width));
    fEtaCut.reset(new FairEveMinMaxCut(this,kinFrame,"Eta",width));
    fEnergyCut.reset(new FairEveMinMaxCut(this,kinFrame,"E",width));
    fPtCut->Init();
    fEtaCut->Init();
    fEnergyCut->Init();
    fPtCut->AddUpdateButton();

    TGVerticalFrame *statFrame = CreateEditorTabSubFrame("Status");

    fPrimary.reset(new FairEveBoolCut(this,statFrame,"Primary",width));
    fPrimary->UpdateWhenChanged();
    fPrimary->SetInitStatus(kTRUE);
    fSecondary.reset(new FairEveBoolCut(this,statFrame,"Secondary",width));
    fSecondary->SetInitStatus(kTRUE);
    fSecondary->UpdateWhenChanged();
    fPdgCut .reset(new FairEveIntCut(this,statFrame,"PDG",width));
    fPrimary->Init();
    fSecondary->Init();
    fPdgCut->Init();
    fPdgCut->AddUpdateButton();
}

void FairEveGeoTracksEditor::SetModel(TObject *obj) {
    fGeoTracks = dynamic_cast<FairEveGeoTracks*>(obj);
}

void FairEveGeoTracksEditor::SwapTracks() {
    if(fGeoTracks)
        fGeoTracks->SwapTracks();
}

void FairEveGeoTracksEditor::Repaint() {
    Double_t min,max;
    Bool_t use = fPtCut->GetValues(min, max);
    fGeoTracks->SetPtCut(min, max, use);
    use = fEtaCut->GetValues(min, max);
    fGeoTracks->SetEtaCut(min, max, use);
    use = fEnergyCut->GetValues(min, max);
    fGeoTracks->SetEnergyCut(min,max,use);
    Int_t pdg_code;
    use = fPdgCut->GetValue(pdg_code);
    fGeoTracks->SetPdgCut(pdg_code,use);
    fGeoTracks->SetShowPrimSec(fPrimary->GetValue(), fSecondary->GetValue());
    TGedFrame::Update();
    fGeoTracks->Repaint();
}

FairEveGeoTracksEditor::~FairEveGeoTracksEditor() {
}

