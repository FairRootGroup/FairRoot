/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairGeoTracksEditor.cxx
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveGeoTracksEditor.h"

#include <iostream>

FairEveGeoTracksEditor::FairEveGeoTracksEditor(const TGWindow *p,
                                               Int_t width,
                                               Int_t height,
                                               UInt_t options,
                                               Pixel_t back)
    : TGedFrame(p, width, height, options | kVerticalFrame, back)
    , fGeoTracks(nullptr)
{

    MakeTitle("FairGeoTracksEditor");
    SetName("MCtracksEditor");

    TGVerticalFrame *kinFrame = CreateEditorTabSubFrame("Kin");
    fPtCut.reset(new FairEveMinMaxCut(this, kinFrame, "Pt", width));
    fEtaCut.reset(new FairEveMinMaxCut(this, kinFrame, "Eta", width));
    fEnergyCut.reset(new FairEveMinMaxCut(this, kinFrame, "E", width));
    fPtCut->Init();
    fEtaCut->Init();
    fEnergyCut->Init();
    fPtCut->AddUpdateButton();

    TGVerticalFrame *statFrame = CreateEditorTabSubFrame("Status");

    fPrimary.reset(new FairEveBoolCut(this, statFrame, "Primary", width));
    fPrimary->UpdateWhenChanged();
    fPrimary->SetInitStatus(kTRUE);
    fSecondary.reset(new FairEveBoolCut(this, statFrame, "Secondary", width));
    fSecondary->SetInitStatus(kTRUE);
    fSecondary->UpdateWhenChanged();
    fPdgCut.reset(new FairEveIntCut(this, statFrame, "PDG", width));
    fPrimary->Init();
    fSecondary->Init();
    fPdgCut->Init();
    fPdgCut->AddUpdateButton();

    TGCompositeFrame *Frame = new TGCompositeFrame(statFrame, width, 20, kHorizontalFrame | kFixedWidth);
    TGTextButton *UpdateButton = new TGTextButton(Frame, "Toggle Tracks");
    UpdateButton->Connect("Clicked()", this->ClassName(), this, "ToggleTracks()");
    Frame->AddFrame(UpdateButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    statFrame->AddFrame(Frame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));
}

void FairEveGeoTracksEditor::SetModel(TObject *obj) { fGeoTracks = dynamic_cast<FairEveGeoTracks *>(obj); }

void FairEveGeoTracksEditor::ToggleTracks()
{
    if (fGeoTracks)
        fGeoTracks->ToggleTracks();
}

void FairEveGeoTracksEditor::Repaint()
{
    Double_t min, max;
    Bool_t use = fPtCut->GetValues(min, max);
    fGeoTracks->SetPtCut(min, max, use);
    use = fEtaCut->GetValues(min, max);
    fGeoTracks->SetEtaCut(min, max, use);
    use = fEnergyCut->GetValues(min, max);
    fGeoTracks->SetEnergyCut(min, max, use);
    Int_t pdg_code;
    use = fPdgCut->GetValue(pdg_code);
    fGeoTracks->SetPdgCut(pdg_code, use);
    fGeoTracks->SetShowPrimSec(fPrimary->GetValue(), fSecondary->GetValue());
    TGedFrame::Update();
    fGeoTracks->Repaint();
}

FairEveGeoTracksEditor::~FairEveGeoTracksEditor() {}
