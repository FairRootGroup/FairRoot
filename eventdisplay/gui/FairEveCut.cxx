/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEDTabEditor.cxx
 *
 *  Created on: 5 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

 #include "FairEveCut.h"
 #include <TGFrame.h>        // for TGGroupFrame, TGCompositeFrame, kFixedWidth
 #include <TGLabel.h>        // for TGLabel
 #include <TGLayout.h>       // for TGLayoutHints, kLHintsExpandX, kLHintsLeft
 #include <TGNumberEntry.h>  // for TGNumberEntry, TGNumberFormat, TGNumberFo...
 #include <TGedFrame.h>      // for TGedFrame


FairEveCut::FairEveCut(TGedFrame *frame, TGCompositeFrame *tab, TString name, Int_t width)
    : fWidth(width)
    , fName(name)
    , fParent(frame)
    , fTab(tab)
{}

void FairEveCut::AddUpdateButton()
{
    TGCompositeFrame *Frame = new TGCompositeFrame(fTab, fWidth, 20, kHorizontalFrame | kFixedWidth);
    TGTextButton *UpdateButton = new TGTextButton(Frame, "Update");
    UpdateButton->Connect("Clicked()", fParent->ClassName(), fParent, "Repaint()");
    Frame->AddFrame(UpdateButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
    fTab->AddFrame(Frame, new TGLayoutHints(kLHintsTop, 1, 1, 2, 1));
}

FairEveCut::~FairEveCut() {}

FairEveMinMaxCut::FairEveMinMaxCut(TGedFrame *frame, TGCompositeFrame *tab, TString name, Int_t width)
    : FairEveCut(frame, tab, name, width)
    , fUseCut(nullptr)
    , fLow(nullptr)
    , fHigh(nullptr)
{}

void FairEveMinMaxCut::Init()
{
    TGGroupFrame *cuts = new TGGroupFrame(fTab, Form("%s Cut", fName.Data()));
    cuts->SetTitlePos(TGGroupFrame::kCenter);

    TString label = Form("Use %s cut", fName.Data());
    TString labelMin = Form("%s min:", fName.Data());
    TString labelMax = Form("%s max:", fName.Data());

    TGCompositeFrame *frameUse = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *label_use = new TGLabel(frameUse, label);
    frameUse->AddFrame(label_use, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fUseCut = new TGCheckButton(frameUse);
    frameUse->AddFrame(fUseCut, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    cuts->AddFrame(frameUse, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    TGCompositeFrame *frameMin = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gLabelMin = new TGLabel(frameMin, labelMin);
    frameMin->AddFrame(gLabelMin, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fLow = new TGNumberEntry(frameMin, 0, 6, -1, TGNumberFormat::kNESRealTwo);
    frameMin->AddFrame(fLow, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    cuts->AddFrame(frameMin, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    TGCompositeFrame *frameMax = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gLabelMax = new TGLabel(frameMax, labelMax);
    frameMax->AddFrame(gLabelMax, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fHigh = new TGNumberEntry(frameMax, 10, 6, -1, TGNumberFormat::kNESRealTwo);
    frameMax->AddFrame(fHigh, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    cuts->AddFrame(frameMax, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    fTab->AddFrame(cuts, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 1, 1, 2, 1));
}

Bool_t FairEveMinMaxCut::GetValues(Double_t &min, Double_t &max) const
{
    min = fLow->GetNumber();
    max = fHigh->GetNumber();
    return fUseCut->IsOn();
}

FairEveMinMaxCut::~FairEveMinMaxCut() {}

FairEveBoolCut::FairEveBoolCut(TGedFrame *frame, TGCompositeFrame *tab, TString name, Int_t width)
    : FairEveCut(frame, tab, name, width)
    , fHasCut(nullptr)
    , fStatus(kTRUE)
    , fAutoUpdate(kFALSE)
{}

void FairEveBoolCut::Init()
{
    fHasCut = new TGCheckButton(fTab, fName, 1);
    if (fAutoUpdate) {
        fHasCut->Connect("Clicked()", fParent->ClassName(), fParent, "Repaint()");
    }
    if (fStatus) {
        fHasCut->SetState(kButtonDown);
    } else {
        fHasCut->SetState(kButtonUp);
    }
    fTab->AddFrame(fHasCut, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 1, 1, 2, 1));
}

FairEveBoolCut::~FairEveBoolCut() {}

FairEveIntCut::FairEveIntCut(TGedFrame *frame, TGCompositeFrame *tab, TString name, Int_t width)
    : FairEveCut(frame, tab, name, width)
    , fUseCut(nullptr)
    , fCut(nullptr)
{}

void FairEveIntCut::Init()
{
    TGGroupFrame *cuts = new TGGroupFrame(fTab, Form("%s Cut", fName.Data()));
    cuts->SetTitlePos(TGGroupFrame::kCenter);
    cuts->SetLayoutManager(new TGMatrixLayout(cuts, 3, 2));
    TString label = Form("Use %s cut", fName.Data());
    TString labelMin = Form("%s:", fName.Data());
    TGLabel *label_use = new TGLabel(cuts, label);
    cuts->AddFrame(label_use, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fUseCut = new TGCheckButton(cuts);
    cuts->AddFrame(fUseCut, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    TGLabel *gLabelMin = new TGLabel(cuts, labelMin);
    cuts->AddFrame(gLabelMin, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fCut = new TGNumberEntry(cuts, 0, 6, -1, TGNumberFormat::kNESInteger);
    cuts->AddFrame(fCut, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    fTab->AddFrame(cuts, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 1, 1, 2, 1));
}

Bool_t FairEveIntCut::GetValue(Int_t &val) const
{
    val = fCut->GetIntNumber();
    return fUseCut->IsOn();
}
