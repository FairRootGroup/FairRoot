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
 #include <TGButton.h>          // for TGTextButton
 #include <TGLayout.h>          // for TGLayoutHints, kLHintsExpandX, kLHints...
 #include <TObject.h>           // for TObject
 #include "FairEveCut.h"        // for FairEveMinMaxCut, FairEveBoolCut, Fair...
 #include "FairEveGeoTracks.h"  // for FairEveGeoTracks
 class TGWindow;

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
    fPtCut = std::make_unique<FairEveMinMaxCut>(this, kinFrame, "Pt", width);
    fEtaCut = std::make_unique<FairEveMinMaxCut>(this, kinFrame, "Eta", width);
    fEnergyCut = std::make_unique<FairEveMinMaxCut>(this, kinFrame, "E", width);
    fPtCut->Init();
    fEtaCut->Init();
    fEnergyCut->Init();
    fPtCut->AddUpdateButton();

    TGVerticalFrame *statFrame = CreateEditorTabSubFrame("Status");

    fPrimary = std::make_unique<FairEveBoolCut>(this, statFrame, "Primary", width);
    fPrimary->UpdateWhenChanged();
    fPrimary->SetInitStatus(kTRUE);
    fSecondary = std::make_unique<FairEveBoolCut>(this, statFrame, "Secondary", width);
    fSecondary->SetInitStatus(kTRUE);
    fSecondary->UpdateWhenChanged();
    fPdgCut = std::make_unique<FairEveIntCut>(this, statFrame, "PDG", width);
    fPrimary->Init();
    fSecondary->Init();
    fPdgCut->Init();
    fPdgCut->AddUpdateButton();

    TGCompositeFrame *ToogleFrame = new TGCompositeFrame(statFrame, width, 20, kHorizontalFrame | kFixedWidth);
    TGTextButton *ToogleButton = new TGTextButton(ToogleFrame, "Toggle Tracks");
    ToogleButton->Connect("Clicked()", this->ClassName(), this, "ToggleTracks()");
    ToogleFrame->AddFrame(ToogleButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    statFrame->AddFrame(ToogleFrame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));

    TGCompositeFrame *ToogleGroupFrame = new TGCompositeFrame(statFrame, width, 20, kHorizontalFrame | kFixedWidth);
    TGTextButton *ToogleGroupButton = new TGTextButton(ToogleGroupFrame, "Toggle Groups");
    ToogleGroupButton->Connect("Clicked()", this->ClassName(), this, "ToggleGroups()");
    ToogleGroupFrame->AddFrame(ToogleGroupButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    statFrame->AddFrame(ToogleGroupFrame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));
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

void FairEveGeoTracksEditor::ToggleGroups() { fGeoTracks->ToggleGroups(); }

FairEveGeoTracksEditor::~FairEveGeoTracksEditor() {}
