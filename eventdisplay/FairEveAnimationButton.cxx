/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairAnimationButton.cxx
 *
 *  Created on: 26 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveAnimationButton.h"

FairEveAnimationButton::FairEveAnimationButton(TGedFrame *frame,
                                               TGCompositeFrame *tab,
                                               TString name,
                                               Int_t width,
                                               Int_t buttons)
    : fWidth(width)
    , fValMin(0)
    , fValMax(10)
    , fFunctionName("")
    , fParent(frame)
    , fTab(tab)
    , fMin(nullptr)
    , fMax(nullptr)
    , fStep(nullptr)
    , fComboOpt(nullptr)
    , fTypeOpt(nullptr)
{
    SetName(name);
}

void FairEveAnimationButton::Init()
{
    TGGroupFrame *cuts = new TGGroupFrame(fTab, GetName());
    cuts->SetTitlePos(TGGroupFrame::kCenter);
    // cuts->SetLayoutManager(new TGMatrixLayout(cuts,6,2));
    TGTextButton *start_button = new TGTextButton(cuts, "Start");
    start_button->Resize(80, 25);
    cuts->AddFrame(start_button, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 5, 5, 5, 5));
    start_button->Connect("Clicked()", fParent->ClassName(), fParent, fFunctionName);

    TGCompositeFrame *frame1 = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gAnimType = new TGLabel(frame1, "Animation type:");
    frame1->AddFrame(gAnimType, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 1, 1));
    fTypeOpt = new TGComboBox(frame1);
    fTypeOpt->AddEntry("Event by Event", kEventByEvent);
    fTypeOpt->AddEntry("Timeslice", kTimeSlice);
    fTypeOpt->Select(kEventByEvent);
    fTypeOpt->Resize(100, 20);
    frame1->AddFrame(fTypeOpt, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));
    cuts->AddFrame(frame1, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    TGCompositeFrame *frame2 = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gLabelType = new TGLabel(frame2, "Scene type:");
    frame2->AddFrame(gLabelType, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fComboOpt = new TGComboBox(frame2);
    fComboOpt->AddEntry("3D", k3D);
    fComboOpt->AddEntry("RPhi", kXY);
    fComboOpt->AddEntry("RhoZ", kZ);
    fComboOpt->AddEntry("All", kAll);
    fComboOpt->Select(0);
    fComboOpt->Resize(100, 20);
    frame2->AddFrame(fComboOpt, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));
    cuts->AddFrame(frame2, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    TGCompositeFrame *frame3 = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gLabelMin = new TGLabel(frame3, "Min:");
    frame3->AddFrame(gLabelMin, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fMin = new TGNumberEntry(frame3, 0, 6, -1, TGNumberFormat::kNESRealTwo);
    fMin->SetNumber(fValMin);
    frame3->AddFrame(fMin, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    cuts->AddFrame(frame3, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    TGCompositeFrame *frame4 = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gLabelMax = new TGLabel(frame4, "Max:");
    frame4->AddFrame(gLabelMax, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fMax = new TGNumberEntry(frame4, 10, 6, -1, TGNumberFormat::kNESRealTwo);
    fMax->SetNumber(fValMax);
    frame4->AddFrame(fMax, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    cuts->AddFrame(frame4, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    TGCompositeFrame *frame5 = new TGCompositeFrame(cuts, fWidth, 30, kHorizontalFrame | kFixedWidth);
    TGLabel *gLabelStep = new TGLabel(frame5, "Step:");
    frame5->AddFrame(gLabelStep, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 1, 1, 2, 1));
    fStep = new TGNumberEntry(frame5, 0, 6, -1, TGNumberFormat::kNESRealTwo);
    frame5->AddFrame(fStep, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    cuts->AddFrame(frame5, new TGLayoutHints(kLHintsLeft | kLHintsExpandX));

    fTab->AddFrame(cuts, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 1, 1, 2, 1));
}

Double_t FairEveAnimationButton::GetMin() { return fMin->GetNumber(); }

Double_t FairEveAnimationButton::GetMax() { return fMax->GetNumber(); }

Double_t FairEveAnimationButton::GetStep()
{
    if (fStep)
        return fStep->GetNumber();
    return 1;
}

FairEveAnimationButton::eScreenshotType FairEveAnimationButton::GetScreenshotType()
{
    return static_cast<eScreenshotType>(fComboOpt->GetSelected());
}

FairEveAnimationButton::eAnimationType FairEveAnimationButton::GetAnimationType()
{
    return static_cast<eAnimationType>(fTypeOpt->GetSelected());
}

FairEveAnimationButton::~FairEveAnimationButton()
{
    // TODO Auto-generated destructor stub
}
