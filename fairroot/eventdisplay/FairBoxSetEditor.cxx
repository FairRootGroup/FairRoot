/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairBoxSetEditor.h"

#include "FairEventManager.h"   // for FairEventManager

#include <TGLabel.h>         // for TGLabel
#include <TGLayout.h>        // for TGLayoutHints, etc
#include <TGNumberEntry.h>   // for TGNumberEntry, etc
#include <fairlogger/Logger.h>

class TGWindow;

#include <iostream>   // for operator<<, basic_ostream, etc

// FairBoxSetEditor
//
// Specialization of TGedEditor for proper update propagation to
// TEveManager.

ClassImp(FairBoxSetEditor);

FairBoxSetEditor::FairBoxSetEditor(const TGWindow* p, Int_t width, Int_t height, UInt_t options, Pixel_t back)
    : TGedFrame(p, width, height, options | kVerticalFrame, back)
    , fInfoFrame(nullptr)
    , fTimeWindowPlus(nullptr)
    , fTimeWindowMinus(nullptr)
    , fObject(nullptr)
    , fM(nullptr)
{
    LOG(info) << "FairBoxSetEditor called!";
    Init();
}

void FairBoxSetEditor::Init()
{
    //  FairRootManager* fRootManager=FairRootManager::Instance();
    //  TChain* chain =fRootManager->GetInChain();
    //  Int_t Entries= chain->GetEntriesFast();

    MakeTitle("FairBoxSet  Editor");
    fInfoFrame = CreateEditorTabSubFrame("Time");

    TGCompositeFrame* title1 =
        new TGCompositeFrame(fInfoFrame, 250, 10, kVerticalFrame | kLHintsExpandX | kFixedWidth | kOwnBackground);

    TGLabel* label1 = new TGLabel(title1, "Time window after event time [ns]: ");
    title1->AddFrame(label1, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 1, 2, 1, 1));

    fTimeWindowPlus =
        new TGNumberEntry(title1);   //, 0, 5, -1, TGNumberFormat::kNESRealTwo); //, TGNumberFormat::kNEANonNegative);
                                     // fTimeWindow->SetLimits(0, MAXE, 2501, TGNumberFormat::kNESRealOne);
    fTimeWindowPlus->GetNumberEntry()->SetToolTipText("Time window in ns for which points are shown");
    fTimeWindowPlus->Connect("ValueSet(Long_t)", "FairBoxSetEditor", this, "TimeWindow()");
    title1->AddFrame(fTimeWindowPlus, new TGLayoutHints(kLHintsTop, 1, 1, 1, 0));

    fInfoFrame->AddFrame(title1);

    TGCompositeFrame* title2 =
        new TGCompositeFrame(fInfoFrame, 250, 10, kVerticalFrame | kLHintsExpandX | kFixedWidth | kOwnBackground);

    TGLabel* label2 = new TGLabel(title2, "Time window before event time [ns]: ");
    title2->AddFrame(label2, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 1, 2, 1, 1));
    fTimeWindowMinus = new TGNumberEntry(
        title2,
        0.,
        6,
        -1,
        TGNumberFormat::kNESInteger,
        TGNumberFormat::kNEANonNegative);   //, 1, 5, -1, TGNumberFormat::kNESRealTwo, TGNumberFormat::kNEANonNegative);
                                            // fTimeWindow->SetLimits(0, MAXE, 2501, TGNumberFormat::kNESRealOne);
    fTimeWindowMinus->GetNumberEntry()->SetToolTipText("Time window in ns for which points are shown");
    fTimeWindowMinus->Connect("ValueSet(Long_t)", "FairBoxSetEditor", this, "TimeWindow()");
    title2->AddFrame(fTimeWindowMinus, new TGLayoutHints(kLHintsTop, 1, 1, 1, 0));

    fInfoFrame->AddFrame(title2);
}

void FairBoxSetEditor::TimeWindow()
{
    LOG(debug) << "FairBoxSetEditor::TimeWindowPlus " << fTimeWindowPlus->GetNumber();
    LOG(debug) << "FairBoxSetEditor::TimeWindowMinus " << fTimeWindowMinus->GetNumber();
    fM->SetTimeWindowPlus(fTimeWindowPlus->GetNumber());
    fM->SetTimeWindowMinus(fTimeWindowMinus->GetNumber());
    FairEventManager* man = FairEventManager::Instance();
    man->GotoEvent(man->GetCurrentEvent());
    Update();
}
