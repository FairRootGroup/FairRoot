/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveRecoTracksExampleEditor.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairEveRecoTracksExampleEditor.h"

#include "FairEveCut.h"
#include "FairEveRecoTracksExample.h"
#include "FairEveTracks.h"

#include <GuiTypes.h>
#include <RtypesCore.h>
#include <TGButton.h>
#include <TGLayout.h>
#include <TGWindow.h>

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
    fPtCut = std::make_unique<FairEveMinMaxCut>(this, kinFrame, "Pt", width);
    fEtaCut = std::make_unique<FairEveMinMaxCut>(this, kinFrame, "Eta", width);
    fEnergyCut = std::make_unique<FairEveMinMaxCut>(this, kinFrame, "E", width);
    fPtCut->Init();
    fEtaCut->Init();
    fEnergyCut->Init();
    fPtCut->AddUpdateButton();

    TGVerticalFrame *statFrame = CreateEditorTabSubFrame("Status");

    fDrawMC = std::make_unique<FairEveBoolCut>(this, statFrame, "Draw MC", 1);
    fDrawMC->UpdateWhenChanged();
    fDrawMC->Init();

    TGCompositeFrame *ToogleFrame = new TGCompositeFrame(statFrame, width, 20, kHorizontalFrame | kFixedWidth);
    TGTextButton *ToogleButton = new TGTextButton(ToogleFrame, "Toggle Tracks");
    ToogleButton->Connect("Clicked()", this->ClassName(), this, "ToggleTracks()");
    ToogleFrame->AddFrame(ToogleButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    statFrame->AddFrame(ToogleFrame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));
}

void FairEveRecoTracksExampleEditor::SetModel(TObject *obj)
{
    fRecoTracks = dynamic_cast<FairEveRecoTracksExample *>(obj);
}

void FairEveRecoTracksExampleEditor::ToggleTracks()
{
    if (fRecoTracks)
        fRecoTracks->ToggleTracks();
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

FairEveRecoTracksExampleEditor::~FairEveRecoTracksExampleEditor() {}
