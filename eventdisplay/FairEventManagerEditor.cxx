/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairEventManagerEditor.h"

#include "FairEventManager.h"   // for FairEventManager
#include "FairRootManager.h"    // for FairRootManager
#include "FairRun.h"
#include "FairRunAna.h"   // for FairRunAna
#include "FairTask.h"

#include <RtypesCore.h>
#include <TChain.h>   // for TChain
#include <TEveManager.h>
#include <TFile.h>           // for TFile
#include <TGButton.h>        // for TGCheckButton, TGTextButton
#include <TGLabel.h>         // for TGLabel
#include <TGLayout.h>        // for TGLayoutHints, etc
#include <TGNumberEntry.h>   // for TGNumberEntry, etc
#include <TGenericClassInfo.h>
#include <TGeoManager.h>   // for TGeoManager, gGeoManager
#include <TList.h>
#include <TNamed.h>
#include <TString.h>   // for TString
#include <TSystem.h>
#include <TTask.h>
#include <TTree.h>

class TGWindow;
class TObject;

#define MAXE 5000

// FairEventManagerEditor
//
// Specialization of TGedEditor for proper update propagation to
// TEveManager.

ClassImp(FairEventManagerEditor);

FairEventManagerEditor::FairEventManagerEditor(const TGWindow* p,
                                               Int_t width,
                                               Int_t height,
                                               UInt_t options,
                                               Pixel_t back)
    : TGedFrame(p, width, height, options | kVerticalFrame, back)
    , fObject(0)
    , fManager(FairEventManager::Instance())
    , fCurrentEvent(0)
    , fGlobalTransparency(nullptr)
    , fEventTime(nullptr)
    , fScreenshotOpt(nullptr)
{
    Init();
}

void FairEventManagerEditor::SwitchTransparency(Bool_t transparency)
{
    fManager->SwitchTransparency(transparency, fGlobalTransparency->GetIntNumber());
}

void FairEventManagerEditor::SwitchBackground(Bool_t light_background) { fManager->SwitchBackground(light_background); }

void FairEventManagerEditor::Init()
{
    FairRootManager* rootManager = FairRootManager::Instance();
    TChain* chain = rootManager->GetInChain();
    Int_t Entries = chain->GetEntriesFast();

    MakeTitle("FairEventManager  Editor");
    TGVerticalFrame* fInfoFrame = CreateEditorTabSubFrame("Info");
    TGCompositeFrame* title1 =
        new TGCompositeFrame(fInfoFrame, 250, 10, kVerticalFrame | kLHintsExpandX | kFixedWidth | kOwnBackground);

    TString Infile = "Input file : ";
    //  TFile* file =FairRunAna::Instance()->GetInputFile();
    TFile* file = FairRootManager::Instance()->GetInChain()->GetFile();
    Infile += file->GetName();
    TGLabel* TFName = new TGLabel(title1, Infile.Data());
    title1->AddFrame(TFName);

    UInt_t RunId = FairRunAna::Instance()->getRunId();
    TString run = "Run Id : ";
    run += RunId;
    TGLabel* TRunId = new TGLabel(title1, run.Data());
    title1->AddFrame(TRunId);

    TString nevent = "No of events : ";
    nevent += Entries;
    TGLabel* TEvent = new TGLabel(title1, nevent.Data());
    title1->AddFrame(TEvent);

    Int_t nodes = gGeoManager->GetNNodes();
    TString NNodes = "No. of Nodes : ";
    NNodes += nodes;
    TGLabel* NoNode = new TGLabel(title1, NNodes.Data());
    title1->AddFrame(NoNode);

    TGHorizontalFrame* f = new TGHorizontalFrame(title1);
    TGLabel* l = new TGLabel(f, "Current Event:");
    f->AddFrame(l, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 1, 2, 1, 1));
    fCurrentEvent = new TGNumberEntry(f,
                                      0.,
                                      6,
                                      -1,
                                      TGNumberFormat::kNESInteger,
                                      TGNumberFormat::kNEANonNegative,
                                      TGNumberFormat::kNELLimitMinMax,
                                      0,
                                      Entries);
    f->AddFrame(fCurrentEvent, new TGLayoutHints(kLHintsLeft, 1, 1, 1, 1));
    fCurrentEvent->Connect("ValueSet(Long_t)", "FairEventManagerEditor", this, "SelectEvent()");
    title1->AddFrame(f);

    TGHorizontalFrame* f2 = new TGHorizontalFrame(title1);
    TGLabel* EventTimeLabel = new TGLabel(f2, "Event Time: ");
    fEventTime = new TGLabel(f2, "");
    f2->AddFrame(EventTimeLabel);
    f2->AddFrame(fEventTime);
    title1->AddFrame(f2);

    TGTextButton* fUpdate = new TGTextButton(title1, "Update");
    title1->AddFrame(fUpdate, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 5, 5, 1, 1));
    fUpdate->Connect("Clicked()", "FairEventManagerEditor", this, "SelectEvent()");

    fInfoFrame->AddFrame(title1, new TGLayoutHints(kLHintsTop, 0, 0, 2, 0));

    fManager->SetMaxEnergy(MAXE);

    //=============== graphics =============================
    TGVerticalFrame* scene_conf = CreateEditorTabSubFrame("Graphics");
    TGHorizontalFrame* transparency_frame = new TGHorizontalFrame(scene_conf);
    TGCheckButton* Transparency = new TGCheckButton(transparency_frame, "Global transparency");
    transparency_frame->AddFrame(Transparency, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 5, 5, 1, 1));
    Transparency->Connect("Toggled(Bool_t)", this->ClassName(), this, "SwitchTransparency(Bool_t)");

    fGlobalTransparency = new TGNumberEntry(transparency_frame,
                                            0.,
                                            6,
                                            -1,
                                            TGNumberFormat::kNESInteger,
                                            TGNumberFormat::kNEANonNegative,
                                            TGNumberFormat::kNELLimitMinMax,
                                            0,
                                            100);
    fGlobalTransparency->SetIntNumber(80);
    transparency_frame->AddFrame(fGlobalTransparency, new TGLayoutHints(kLHintsRight, 1, 1, 1, 1));
    fGlobalTransparency->Connect("ValueSet(Long_t)", "FairEventManagerEditor", this, "SwitchTransparency(Bool_t)");
    scene_conf->AddFrame(transparency_frame);

    TGCheckButton* backgroundButton = new TGCheckButton(scene_conf, "Light background");
    scene_conf->AddFrame(backgroundButton, new TGLayoutHints(kLHintsRight | kLHintsExpandX, 5, 5, 1, 1));
    backgroundButton->Connect("Toggled(Bool_t)", this->ClassName(), this, "SwitchBackground(Bool_t)");

    TGGroupFrame* frame_screenshot = new TGGroupFrame(scene_conf, "Screenshot");
    frame_screenshot->SetTitlePos(TGGroupFrame::kCenter);

    frame_screenshot->SetLayoutManager(new TGHorizontalLayout(frame_screenshot));

    TGTextButton* Screen = new TGTextButton(frame_screenshot, "Make");
    frame_screenshot->AddFrame(Screen, new TGLayoutHints(kLHintsLeft | kLHintsExpandX, 20, 2, 2, 2));
    Screen->Connect("Clicked()", this->ClassName(), this, "MakeScreenshot()");

    fScreenshotOpt = new TGComboBox(frame_screenshot);
    fScreenshotOpt->AddEntry("3D", 0);
    fScreenshotOpt->AddEntry("RPhi", 1);
    fScreenshotOpt->AddEntry("RhoZ", 2);
    fScreenshotOpt->AddEntry("All", 3);
    fScreenshotOpt->Select(0);
    fScreenshotOpt->Resize(40, 30);
    frame_screenshot->AddFrame(fScreenshotOpt, new TGLayoutHints(kLHintsRight | kLHintsExpandX));
    scene_conf->AddFrame(frame_screenshot, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 1, 1, 2, 1));

    fAnimation = new FairEveAnimationButton(this, scene_conf, "Animation", fWidth, 2);
    fAnimation->SetMinMax(0, Entries);
    fAnimation->SetFunctionName("StartAnimation()");
    fAnimation->Init();

    //  scene_conf->AddFrame(online_screenshot,new TGLayoutHints(kLHintsRight|kLHintsExpandX));
}

void FairEventManagerEditor::SelectEvent()
{
    fManager->GotoEvent(fCurrentEvent->GetIntNumber());
    TString time;
    time.Form("%.2f", FairRootManager::Instance()->GetEventTime());
    time += " ns";
    fEventTime->SetText(time.Data());
    Update();
}

void FairEventManagerEditor::SetModel(TObject* obj) { fObject = obj; }

void FairEventManagerEditor::StartAnimation()
{
    switch (fAnimation->GetAnimationType()) {
        case FairEveAnimationButton::eAnimationType::kEventByEvent: {   // event by event
            gSystem->mkdir("event_animations");
            FairEventManager::Instance()->SetTimeLimits(0, -1);   // disable drawing by timeslice
            Int_t start = (Int_t)fAnimation->GetMin();
            Int_t end = (Int_t)fAnimation->GetMax();
            FairEveAnimationButton::eScreenshotType screen = fAnimation->GetScreenshotType();
            gSystem->mkdir("event_animations");
            for (int i = start; i < end; i++) {
                fCurrentEvent->SetIntNumber(i);
                SelectEvent();
                gEve->FullRedraw3D();
                fManager->MakeScreenshot(screen, Form("event_animations/event_%i.png", i));
            }
        } break;
        case FairEveAnimationButton::eAnimationType::kTimeSlice: {   // timeslice
            gSystem->mkdir("timeslice_animations");
            SelectEvent();
            Double_t start = (Double_t)fAnimation->GetMin();
            Double_t end = (Double_t)fAnimation->GetMax();
            Double_t step = (Double_t)fAnimation->GetStep();
            if (step == 0) {
                step = 1;
            }
            Int_t no = 0;
            FairEveAnimationButton::eScreenshotType screen = fAnimation->GetScreenshotType();
            FairRunAna* ana = FairRunAna::Instance();
            FairTask* pMainTask = ana->GetMainTask();
            TList* taskList = pMainTask->GetListOfTasks();

            Int_t ntask = ana->GetNTasks();
            for (Double_t i = start; i < end; i += step) {
                FairEventManager::Instance()->SetTimeLimits(start, i);
                TObjLink* lnk = taskList->FirstLink();
                while (lnk) {
                    FairTask* pCurTask = (FairTask*)lnk->GetObject();
                    pCurTask->ExecuteTask("");
                    lnk = lnk->Next();
                }
                gEve->FullRedraw3D();
                fManager->MakeScreenshot(screen, Form("timeslice_animations/event_%i.png", no++));
            }
        } break;
    }
}

void FairEventManagerEditor::MakeScreenshot()
{
    fManager->MakeScreenshot(static_cast<FairEveAnimationButton::eScreenshotType>(fScreenshotOpt->GetSelected()));
}
