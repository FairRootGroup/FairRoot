/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveMCTracksEditor.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairEveMCTracksEditor.h"

#include "FairEveCut.h"
#include "FairEveMCTracks.h"
#include "FairEveTracks.h"

#include <TGButton.h>
#include <TGLayout.h>
#include <TGWindow.h>

FairEveMCTracksEditor::FairEveMCTracksEditor(const TGWindow *p, Int_t width, Int_t height, UInt_t options, Pixel_t back)
    : TGedFrame(p, width, height, options | kVerticalFrame, back)
    , fMCTracks(nullptr)
{

    MakeTitle("FairMCTracksEditor");
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
}

void FairEveMCTracksEditor::SetModel(TObject *obj) { fMCTracks = dynamic_cast<FairEveMCTracks *>(obj); }

void FairEveMCTracksEditor::ToggleTracks()
{
    if (fMCTracks)
        fMCTracks->ToggleTracks();
}

void FairEveMCTracksEditor::Repaint()
{
    Double_t min, max;
    Bool_t use = fPtCut->GetValues(min, max);
    fMCTracks->SetPtCut(min, max, use);
    use = fEtaCut->GetValues(min, max);
    fMCTracks->SetEtaCut(min, max, use);
    use = fEnergyCut->GetValues(min, max);
    fMCTracks->SetEnergyCut(min, max, use);
    Int_t pdg_code;
    use = fPdgCut->GetValue(pdg_code);
    fMCTracks->SetPdgCut(pdg_code, use);
    fMCTracks->SetShowPrimSec(fPrimary->GetValue(), fSecondary->GetValue());
    TGedFrame::Update();
    fMCTracks->Repaint();
}

FairEveMCTracksEditor::~FairEveMCTracksEditor() {}
