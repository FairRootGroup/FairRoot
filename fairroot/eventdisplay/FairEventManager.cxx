/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//______________________________________________________________________________
/** FairEventManager
 *  class for event management and navigation.
 *  M. Al-Turany 06.12.2007
 **/
#include "FairEventManager.h"

#include "FairRootManager.h"   // for FairRootManager
#include "FairRunAna.h"        // for FairRunAna
#include "FairXMLNode.h"

#include <TDatabasePDG.h>   // for TDatabasePDG
#include <TEveBrowser.h>
#include <TEveGeoNode.h>   // for TEveGeoTopNode
#include <TEveManager.h>   // for TEveManager, gEve
#include <TEveProjectionManager.h>
#include <TEveProjections.h>   // for TEveProjection, TEveProjection::k...
#include <TEveScene.h>
#include <TEveText.h>
#include <TEveTrans.h>
#include <TEveViewer.h>
#include <TEveWindow.h>   // for TEveWindowPack, TEveWindowSlot
#include <TGFileDialog.h>
#include <TGLCameraOverlay.h>
#include <TGLClip.h>   // for TGLClip, TGLClip::kClipPlane, TGL...
#include <TGLFontManager.h>
#include <TGLLightSet.h>
#include <TGLViewer.h>
#include <TGeoBBox.h>
#include <TGeoManager.h>   // for gGeoManager, TGeoManager
#include <TGeoNode.h>
#include <TGeoVolume.h>   // for TGeoVolume
#include <TVector3.h>

FairEventManager* FairEventManager::fgRinstance = nullptr;

FairEventManager* FairEventManager::Instance()
{
    return fgRinstance;
}

FairEventManager::FairEventManager()
    : TEveEventManager("FairEventManager", "")
    , fRunAna(FairRunAna::Instance())
    , fRootManager(fRunAna->GetRootManager())
    , fEntry(0)
    , fWorldSizeX(2000)
    , fWorldSizeY(2000)
    , fWorldSizeZ(2000)
    , fTimeMin(0)
    , fTimeMax(DBL_MAX)
    , fUseTimeOfEvent(kTRUE)
    , fTimeEvent(-1.)
    , fAnimatedTracks(kFALSE)
    , fClearHandler(kTRUE)
    , fRPhiPlane{0, 0, 10, 0}
    , fRhoZPlane{-1, 0, 0, 0}
    , fRphiCam(TGLViewer::kCameraOrthoXOY)
    , fRhoCam(TGLViewer::kCameraOrthoZOY)
    , fXMLConfig("")
{
    fgRinstance = this;
    AddParticlesToPdgDataBase();
}

void FairEventManager::Init(Int_t visopt, Int_t vislvl, Int_t maxvisnds)
{
    TEveManager::Create();
    fRunAna->Init();
    if (gGeoManager == nullptr)
        return;
    TGeoNode* N = gGeoManager->GetTopNode();
    auto TNod = new TEveGeoTopNode(gGeoManager, N, visopt, vislvl, maxvisnds);
    auto box = dynamic_cast<TGeoBBox*>(gGeoManager->GetTopNode()->GetVolume()->GetShape());
    if (box) {
        fWorldSizeX = box->GetDX();
        fWorldSizeY = box->GetDY();
        fWorldSizeZ = box->GetDZ();
    }
    if (!fXMLConfig.EqualTo(""))
        LoadXMLSettings();
    gEve->AddGlobalElement(TNod);
    gEve->FullRedraw3D(kTRUE);
    fEvent = gEve->AddEvent(this);

    fRPhiProjManager = new TEveProjectionManager(TEveProjection::kPT_RPhi);
    fRhoZProjManager = new TEveProjectionManager(TEveProjection::kPT_RhoZ);
    gEve->AddToListTree(fRPhiProjManager, kFALSE);
    gEve->AddToListTree(fRhoZProjManager, kFALSE);
    fAxesPhi = new TEveProjectionAxes(fRPhiProjManager);
    fAxesRho = new TEveProjectionAxes(fRhoZProjManager);

    fRPhiView = gEve->SpawnNewViewer("RPhi View", "");
    fRPhiScene = gEve->SpawnNewScene("RPhi", "Scene holding axis.");
    fRPhiScene->AddElement(fAxesPhi);

    fRhoZView = gEve->SpawnNewViewer("RhoZ View", "");
    fRhoZScene = gEve->SpawnNewScene("RhoZ", "Scene holding axis.");
    fRhoZScene->AddElement(fAxesRho);

    SetViewers(fRPhiView, fRhoZView);

    TEveWindowSlot* MultiSlot = TEveWindow::CreateWindowInTab(gEve->GetBrowser()->GetTabRight());
    TEveWindowPack* MultiPack = MultiSlot->MakePack();
    MultiPack->SetElementName("Multi View");
    MultiPack->SetHorizontal();
    MultiPack->SetShowTitleBar(kFALSE);
    MultiPack->NewSlot()->MakeCurrent();
    fMultiView = gEve->SpawnNewViewer("3D View (multi)", "");
    // switch off left and right light sources for 3D MultiView
    fMultiView->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightLeft, false);
    fMultiView->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightRight, false);
    // add 3D scenes (first tab) to 3D MultiView
    fMultiView->AddScene(gEve->GetGlobalScene());
    fMultiView->AddScene(gEve->GetEventScene());

    // add slot for RPhi projection on Multi View tab
    MultiPack = MultiPack->NewSlot()->MakePack();
    MultiPack->SetShowTitleBar(kFALSE);
    MultiPack->NewSlot()->MakeCurrent();
    fMultiRPhiView = gEve->SpawnNewViewer("RPhi View (multi)", "");
    MultiPack->NewSlot()->MakeCurrent();
    fMultiRhoZView = gEve->SpawnNewViewer("RhoZ View (multi)", "");

    SetViewers(fMultiRPhiView, fMultiRhoZView);

    // don't change reposition camera on each update
    fRPhiView->GetGLViewer()->SetResetCamerasOnUpdate(kFALSE);
    fRhoZView->GetGLViewer()->SetResetCamerasOnUpdate(kFALSE);
    fMultiView->GetGLViewer()->SetResetCamerasOnUpdate(kFALSE);
    fMultiRPhiView->GetGLViewer()->SetResetCamerasOnUpdate(kFALSE);
    fMultiRhoZView->GetGLViewer()->SetResetCamerasOnUpdate(kFALSE);
    fMultiView->GetEveFrame()->HideAllDecorations();
    fMultiRPhiView->GetEveFrame()->HideAllDecorations();
    fMultiRhoZView->GetEveFrame()->HideAllDecorations();

    fEventTimeText = new TEveText("Event Time: ");
    fEventTimeText->PtrMainTrans()->SetPos(-100, 80, 0);
    fEventTimeText->SetMainColor(kOrange - 2);
    fEventTimeText->SetFontFile("ariali");
    fEventTimeText->SetFontSize(20);
    fEventTimeText->SetFontMode(TGLFont::kPixmap);
    fEventTimeText->SetLighting(kTRUE);
    fEventTimeText->SetRnrState(kFALSE);
    gEve->AddElement(fEventTimeText);

    fEventNumberText = new TEveText("Event Number: ");
    fEventNumberText->PtrMainTrans()->SetPos(-100, 100, 0);
    fEventNumberText->SetMainColor(kOrange - 2);
    fEventNumberText->SetFontFile("ariali");
    fEventNumberText->SetFontSize(20);
    fEventNumberText->SetFontMode(TGLFont::kPixmap);
    fEventNumberText->SetLighting(kTRUE);
    fEventNumberText->SetRnrState(kFALSE);
    gEve->AddElement(fEventNumberText);
}

void FairEventManager::UpdateEditor() {}

FairEventManager::~FairEventManager()
{
    if (fgRinstance == this) {
        // Do not point to a destructed object!
        fgRinstance = nullptr;
    }
}

void FairEventManager::Open() {}

void FairEventManager::GotoEvent(Int_t event)
{
    fEntry = event;
    fTimeMin = 0;
    fTimeMax = DBL_MAX;
    fRunAna->Run(static_cast<Long64_t>(event));
}

void FairEventManager::NextEvent()
{
    fEntry += 1;
    fTimeMin = 0;
    fTimeMax = DBL_MAX;
    fRunAna->Run(static_cast<Long64_t>(fEntry));
}

void FairEventManager::PrevEvent()
{
    fEntry -= 1;
    fTimeMin = 0;
    fTimeMax = DBL_MAX;
    fRunAna->Run(static_cast<Long64_t>(fEntry));
}

void FairEventManager::Close() {}

void FairEventManager::DisplaySettings() {}

void FairEventManager::AddParticlesToPdgDataBase(Int_t /*pdg*/)
{
    // Add particles to the PDG data base

    TDatabasePDG* pdgDB = TDatabasePDG::Instance();

    const Double_t kAu2Gev = 0.9314943228;
    const Double_t khSlash = 1.0545726663e-27;
    const Double_t kErg2Gev = 1 / 1.6021773349e-3;
    const Double_t khShGev = khSlash * kErg2Gev;
    const Double_t kYear2Sec = 3600 * 24 * 365.25;

    // Ions

    if (!pdgDB->GetParticle(1000010020))
        pdgDB->AddParticle("Deuteron", "Deuteron", 2 * kAu2Gev + 8.071e-3, kTRUE, 0, 3, "Ion", 1000010020);

    if (!pdgDB->GetParticle(1000010030))
        pdgDB->AddParticle(
            "Triton", "Triton", 3 * kAu2Gev + 14.931e-3, kFALSE, khShGev / (12.33 * kYear2Sec), 3, "Ion", 1000010030);

    if (!pdgDB->GetParticle(1000020040))
        pdgDB->AddParticle(
            "Alpha", "Alpha", 4 * kAu2Gev + 2.424e-3, kTRUE, khShGev / (12.33 * kYear2Sec), 6, "Ion", 1000020040);

    if (!pdgDB->GetParticle(1000020030))
        pdgDB->AddParticle("HE3", "HE3", 3 * kAu2Gev + 14.931e-3, kFALSE, 0, 6, "Ion", 1000020030);

    // Special particles
    //
    if (!pdgDB->GetParticle(50000050))
        pdgDB->AddParticle("Cherenkov", "Cherenkov", 0, kFALSE, 0, 0, "Special", 50000050);

    if (!pdgDB->GetParticle(50000051))
        pdgDB->AddParticle("FeedbackPhoton", "FeedbackPhoton", 0, kFALSE, 0, 0, "Special", 50000051);
}

TVector3 FairEventManager::GetWorldSize() const
{
    return TVector3(fWorldSizeX, fWorldSizeY, fWorldSizeZ);
}

void FairEventManager::SetViewers(TEveViewer* RPhi, TEveViewer* RhoZ)
{
    RPhi->GetGLViewer()->SetCurrentCamera(fRphiCam);
    // set clip plane and camera parameters
    // RPhi->GetGLViewer()->GetClipSet()->SetClipType(TGLClip::kClipPlane);
    // RPhi->GetGLViewer()->GetClipSet()->SetClipState(TGLClip::kClipPlane, fRPhiPlane);
    RPhi->GetGLViewer()->GetCameraOverlay()->SetOrthographicMode(TGLCameraOverlay::kAxis);
    RPhi->GetGLViewer()->GetCameraOverlay()->SetShowOrthographic(kTRUE);
    // switch off left, right, top and bottom light sources
    RPhi->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightLeft, false);
    RPhi->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightRight, false);
    RPhi->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightTop, false);
    RPhi->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightBottom, false);

    RhoZ->GetGLViewer()->SetCurrentCamera(fRhoCam);
    // set clip plane and camera parameters
    // RhoZ->GetGLViewer()->GetClipSet()->SetClipType(TGLClip::kClipPlane);
    // RhoZ->GetGLViewer()->GetClipSet()->SetClipState(TGLClip::kClipPlane, fRhoZPlane);
    RhoZ->GetGLViewer()->GetCameraOverlay()->SetOrthographicMode(TGLCameraOverlay::kAxis);
    RhoZ->GetGLViewer()->GetCameraOverlay()->SetShowOrthographic(kTRUE);
    // switch off left, right and front light sources
    RhoZ->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightLeft, false);
    RhoZ->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightRight, false);
    RhoZ->GetGLViewer()->GetLightSet()->SetLight(TGLLightSet::kLightFront, false);

    RPhi->AddScene(fRPhiScene);
    RPhi->AddScene(gEve->GetGlobalScene());
    RPhi->AddScene(gEve->GetEventScene());
    RhoZ->AddScene(fRhoZScene);
    RhoZ->AddScene(gEve->GetGlobalScene());
    RhoZ->AddScene(gEve->GetEventScene());
}

void FairEventManager::SetRPhiPlane(Double_t a, Double_t b, Double_t c, Double_t d, TGLViewer::ECameraType camtype)
{
    fRPhiPlane[0] = a;
    fRPhiPlane[1] = b;
    fRPhiPlane[2] = c;
    fRPhiPlane[3] = d;
    fRphiCam = camtype;
}

void FairEventManager::SetRhoZPlane(Double_t a, Double_t b, Double_t c, Double_t d, TGLViewer::ECameraType camtype)
{
    fRhoZPlane[0] = a;
    fRhoZPlane[1] = b;
    fRhoZPlane[2] = c;
    fRhoZPlane[3] = d;
    fRhoCam = camtype;
}

void FairEventManager::LoadXMLSettings()
{
    FairXMLFile xmlfile(fXMLConfig, "read");
    FairXMLNode *xml = xmlfile.GetRootNode();
    for (int i = 0; i < xml->GetNChildren(); i++) {
        TString nodename = xml->GetChild(i)->GetName();
        if (nodename.EqualTo("Detectors")) {
            TGeoNode *top = gGeoManager->GetTopNode();
            FairXMLNode *top_xml = xml->GetChild(i)->GetChild(0);
            if (top_xml != nullptr)
                LoadXMLDetector(top, top_xml);
        } else if (nodename.EqualTo("MCTracksColors")) {
            FairXMLNode *colors = xml->GetChild(i);
            for (int j = 0; j < colors->GetNChildren(); j++) {
                FairXMLNode *color = colors->GetChild(j);
                TString pgd_code = color->GetAttrib("pdg")->GetValue();
                TString color_code = color->GetAttrib("color")->GetValue();
                fPDGColor.SetColor(pgd_code.Atoi(), FairXMLPdgColor::StringToColor(color_code));
            }
        }
    }
    gEve->Redraw3D();
}

void FairEventManager::LoadXMLDetector(TGeoNode* node, FairXMLNode* xml, Int_t depth)
{
    TString name = xml->GetAttrib("name")->GetValue();
    TString node_name = node->GetName();
    Bool_t recursive = (xml->GetAttrib("recursive")->GetValue().Length() != 0 && !name.EqualTo(node_name));
    if (recursive && depth == 0)
        return;
    TString transparency = xml->GetAttrib("transparency")->GetValue();
    TString color = xml->GetAttrib("color")->GetValue();
    if (!color.EqualTo("")) {
        node->GetVolume()->SetFillColor(FairXMLPdgColor::StringToColor(color));
        node->GetVolume()->SetLineColor(FairXMLPdgColor::StringToColor(color));
    }
    if (!transparency.EqualTo("")) {
        node->GetVolume()->SetTransparency((Char_t)(transparency.Atoi()));
    }
    if (xml->GetAttrib("recursive")->GetValue().Length() > 0) {
        TString val = xml->GetAttrib("recursive")->GetValue();
        Int_t xml_depth = val.Atoi();
        if (recursive) {
            xml_depth = depth - 1;
        }
        for (int i = 0; i < node->GetNdaughters(); i++) {
            TGeoNode *daughter_node = node->GetDaughter(i);
            LoadXMLDetector(daughter_node, xml, xml_depth);
        }
    }
    if (xml->GetNChildren() > 0 && !recursive) {
        for (int i = 0; i < node->GetNdaughters(); i++) {
            TString subdetector_name = node->GetDaughter(i)->GetName();
            for (int j = 0; j < xml->GetNChildren(); j++) {
                FairXMLNode *subnode = xml->GetChild(j);
                TString subnode_name = subnode->GetAttrib("name")->GetValue();
                if (subnode_name == subdetector_name) {
                    LoadXMLDetector(node->GetDaughter(i), subnode);
                }
            }
        }
    }
}

void FairEventManager::SetTransparency(Bool_t use_xml, Int_t trans)
{
    if (!use_xml) {   // high transparency
        Int_t vis_level = gGeoManager->GetVisLevel();
        TGeoNode* top = gGeoManager->GetTopNode();
        SetTransparencyForLayer(top, vis_level, trans);
    } else {   // normal transparency
        if (fXMLConfig != "") {
            LoadXMLSettings();
        } else {
            Int_t vis_level = gGeoManager->GetVisLevel();
            TGeoNode* top = gGeoManager->GetTopNode();
            SetTransparencyForLayer(top, vis_level, 0);
        }
    }
    if (gEve->GetGlobalScene()->GetRnrState()) {
        gEve->GetGlobalScene()->SetRnrState(kFALSE);
        gEve->GetGlobalScene()->SetRnrState(kTRUE);
        gEve->Redraw3D();
    }
}

void FairEventManager::SwitchBackground(Bool_t /*light*/)
{
    gEve->GetViewers()->SwitchColorSet();
}

void FairEventManager::SetTransparencyForLayer(TGeoNode* node, Int_t depth, Char_t transparency)
{
    node->GetVolume()->SetTransparency(transparency);
    if (depth <= 0)
        return;
    for (int i = 0; i < node->GetNdaughters(); i++) {
        TGeoNode* dau = node->GetDaughter(i);
        SetTransparencyForLayer(dau, depth - 1, transparency);
    }
}

void FairEventManager::MakeScreenshot(FairEveAnimationControl::eScreenshotType proj, TString path)
{
    TString filename;
    if (path == "") {
        const char* filetypes[] = {"PNG", "*.png", "JPG", "*.jpg", nullptr, nullptr};
        TGFileInfo fi;
        fi.fFileTypes = filetypes;
        fi.fIniDir = StrDup(".");
        new TGFileDialog(gClient->GetRoot(), gEve->GetMainWindow(), kFDSave, &fi);
        if (fi.fFilename == nullptr)
            return;
        filename = fi.fFilename;
    } else {
        filename = path;
    }
    switch (proj) {
        case FairEveAnimationControl::eScreenshotType::k3D: {
            gEve->GetDefaultGLViewer()->SavePicture(filename);
        } break;
        case FairEveAnimationControl::eScreenshotType::kXY: {
            TEveViewer* view = GetRPhiView();
            TGLViewer* gl = view->GetGLViewer();
            gl->SavePicture(filename);
        } break;
        case FairEveAnimationControl::eScreenshotType::kZ: {
            TEveViewer* view = GetRhoZView();
            TGLViewer* gl = view->GetGLViewer();
            gl->SavePicture(filename);
        } break;
        case FairEveAnimationControl::eScreenshotType::kAll: {
            TString filename_path = filename(0, filename.Last('.'));
            TString filename_ext = filename(filename.Last('.') + 1, 3);
            TString filename3d = Form("%s_3d.%s", filename_path.Data(), filename_ext.Data());
            TString filenameRphi = Form("%s_XY.%s", filename_path.Data(), filename_ext.Data());
            TString filenameRhoz = Form("%s_Z.%s", filename_path.Data(), filename_ext.Data());
            gEve->GetDefaultGLViewer()->SavePicture(filename3d);
            TEveViewer* view = GetRPhiView();
            TGLViewer* gl = view->GetGLViewer();
            gl->SavePicture(filenameRphi);
            view = GetRhoZView();
            gl = view->GetGLViewer();
            gl->SavePicture(filenameRhoz);
        } break;
    }
}

Float_t FairEventManager::GetEvtTime()
{
    if (fUseTimeOfEvent) {
        fTimeEvent = fRootManager.GetEventTime();
    }
    return fTimeEvent;
}

void FairEventManager::SetEvtTimeText(Double_t time)
{
    TString stime;
    stime.Form("%.2f", time);
    stime += " ns";
    fEventTimeText->SetText(stime);
}

void FairEventManager::SetEvtNumberText(Int_t evtNumber)
{
    TString text = "Event: ";
    text += evtNumber;
    fEventNumberText->SetText(text);
}
