/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * class for event management and navigation.
 * 06.12.07 M.Al-Turany
 */
#ifndef FairEventManager_H
#define FairEventManager_H

#include "FairEveAnimationControl.h"
#include "FairRunAna.h"   // for FairRunAna
#include "FairXMLPdgColor.h"

#include <Rtypes.h>             // for Float_t, Int_t, Bool_t, etc
#include <TEveEventManager.h>   // for TEveEventManager
#include <TEveProjectionAxes.h>
#include <TGLViewer.h>
#include <map>

class TVector3;

class FairRootManager;   // does not work with streamer, reason unclear
class FairTask;
class FairXMLNode;

class TEveProjectionManager;
class TEveScene;
class TEveViewer;
class TEveText;
class TGeoNode;
class TGListTreeItem;

/**
 * \ingroup eventdisplay fairroot_singleton
 */
class FairEventManager : public TEveEventManager
{
  public:
    static FairEventManager* Instance();
    FairEventManager();
    virtual ~FairEventManager();
    virtual void SetXMLConfig(TString xml_config) { fXMLConfig = xml_config; };
    virtual void Open();
    virtual void GotoEvent(Int_t event);   // *MENU*
    virtual void NextEvent();              // *MENU*
    virtual void PrevEvent();              // *MENU*
    virtual void Close();
    virtual void DisplaySettings();   //  *Menu*
    virtual Int_t Color(Int_t pdg) { return fPDGColor.GetColor(pdg); }
    void AddTask(FairTask* t) { fRunAna->AddTask(t); }
    virtual void Init(Int_t visopt = 1, Int_t vislvl = 3, Int_t maxvisnds = 10000);
    virtual Int_t GetCurrentEvent() { return fEntry; }
    /**
     * set plane  on RPhi-view, first parameters describe plane equation Ax+By+Cz+D=0
     * @param a
     * @param b
     * @param c
     * @param d
     * @param camtype camera type
     */
    virtual void SetRPhiPlane(Double_t a, Double_t b, Double_t c, Double_t d, TGLViewer::ECameraType camtype);
    /**
     * set plane  on RhoZ-view, first parameters describe plane equation Ax+By+Cz+D=0
     * @param a
     * @param b
     * @param c
     * @param d
     * @param camtype camera type
     */
    virtual void SetRhoZPlane(Double_t a, Double_t b, Double_t c, Double_t d, TGLViewer::ECameraType camtype);
    void UpdateEditor();
    /**
     * set time limits (used in timeslice animations)
     * @param min
     * @param max
     */
    void SetTimeLimits(Double_t min, Double_t max)
    {
        fTimeMin = min;
        fTimeMax = max;
    };
    void GetTimeLimits(Double_t& min, Double_t& max)
    {
        min = fTimeMin;
        max = fTimeMax;
    };
    virtual void AddParticlesToPdgDataBase(Int_t pdg = 0);
    /**
     * set detector's transparency
     * @param use_xml use xml colors if available
     * @param trans transparency for detector (if xml not used)
     */
    virtual void SetTransparency(Bool_t use_xml, Int_t trans);
    /**
     * switch background color
     * @param light use white if true
     */
    virtual void SwitchBackground(Bool_t light);
    /* functions below are obsolete  **/
    virtual void SetPriOnly(Bool_t Pri) {}
    virtual Bool_t IsPriOnly() { return kFALSE; }
    virtual void SelectPDG(Int_t PDG) {}
    virtual Int_t GetCurrentPDG() { return 0; }
    virtual void SetMaxEnergy(Float_t max) {}
    virtual void SetMinEnergy(Float_t min) {}
    virtual void SetEvtMaxEnergy(Float_t max) {}
    virtual void SetEvtMinEnergy(Float_t min) {}
    virtual void SetEvtTime(Float_t time) { fTimeEvent = time; }
    virtual void SetEvtTimeText(Double_t time);
    virtual void SetEvtNumberText(Int_t evtNumber);
    void SetUseTimeOfEvent(Bool_t val) { fUseTimeOfEvent = val; }
    void SetAnimatedTracks(Bool_t val) { fAnimatedTracks = val; }
    void SetClearHandler(Bool_t val) { fClearHandler = val; }
    virtual Float_t GetEvtMaxEnergy() { return 1E+9; }
    virtual Float_t GetEvtMinEnergy() { return 0; }
    virtual Float_t GetMaxEnergy() { return 1E+9; }
    virtual Float_t GetMinEnergy() { return 0; }
    TVector3 GetWorldSize() const;
    Float_t GetEvtTime();   ///< current time in ns to display in the event display. Either set value or event time
                            ///< taken from FairRootManager. Controlled via fUseTimeOfEvent
    Bool_t GetUseTimeOfEvent() const { return fUseTimeOfEvent; }
    Bool_t GetDrawAnimatedTracks() const { return fAnimatedTracks; }
    Bool_t GetClearHandler() const { return fClearHandler; }
    FairRootManager& GetRootManager() { return fRootManager; }
    FairRootManager const& GetRootManager() const { return fRootManager; }

    /**
     *
     * @param name name of file with screenshot
     * @param proj 0 - 3D view, 1 - RPhi, 2 RhoZ, 3 - all
     * @param def_path - default path to screenshot, if empty -user will be asked
     */
    void MakeScreenshot(FairEveAnimationControl::eScreenshotType screen, TString def_path = "");
    ClassDef(FairEventManager, 1);

  protected:
    TEveViewer* GetRPhiView() const { return fRPhiView; };
    TEveViewer* GetRhoZView() const { return fRhoZView; };
    TEveViewer* GetMultiView() const { return fMultiView; };
    TEveViewer* GetMultiRPhiView() const { return fMultiRPhiView; };
    TEveViewer* GetMultiRhoZView() const { return fMultiRhoZView; };
    TEveScene* GetRhoZScene() const { return fRhoZScene; };
    TEveScene* GetRPhiScene() const { return fRPhiScene; };
    TEveProjectionManager* GetRhoZProjManager() const { return fRhoZProjManager; };
    TEveProjectionManager* GetRPhiProjManager() const { return fRPhiProjManager; };
    TEveProjectionAxes* GetRPhiAxes() const { return fAxesPhi; };
    TEveProjectionAxes* GetRhoZAxes() const { return fAxesRho; };
    virtual void LoadXMLSettings();
    void LoadXMLDetector(TGeoNode* node, FairXMLNode* xml, Int_t depth = 0);
    [[deprecated("Use FairXMLPdgColor::StringToColor")]] Int_t StringToColor(const TString& color) const
    {
        return FairXMLPdgColor::StringToColor(color);
    }

  private:
    FairRunAna* fRunAna;                                //!
    FairRootManager& fRootManager;                      //!
    Int_t fEntry;                                       //!
    Double_t fWorldSizeX, fWorldSizeY, fWorldSizeZ;     //!
    Double_t fTimeMin, fTimeMax;                        //!
    Bool_t fUseTimeOfEvent;                             //!
    Double_t fTimeEvent;                                //!
    Bool_t fAnimatedTracks;                             //!
    Bool_t fClearHandler;                               //!
    TGListTreeItem* fEvent{nullptr};                    //!
    Double_t fRPhiPlane[4];                             //!
    Double_t fRhoZPlane[4];                             //!
    TGLViewer::ECameraType fRphiCam;                    //!
    TGLViewer::ECameraType fRhoCam;                     //!
    TEveViewer* fRPhiView{nullptr};                     //!
    TEveViewer* fRhoZView{nullptr};                     //!
    TEveViewer* fMultiView{nullptr};                    //!
    TEveViewer* fMultiRPhiView{nullptr};                //!
    TEveViewer* fMultiRhoZView{nullptr};                //!
    TEveScene* fRPhiScene{nullptr};                     //!
    TEveScene* fRhoZScene{nullptr};                     //!
    TEveProjectionManager* fRPhiProjManager{nullptr};   //!
    TEveProjectionManager* fRhoZProjManager{nullptr};   //!
    TEveProjectionAxes* fAxesPhi{nullptr};              //!
    TEveProjectionAxes* fAxesRho{nullptr};              //!
    TEveText* fEventTimeText{nullptr};                  //!
    TEveText* fEventNumberText{nullptr};                //!
    FairXMLPdgColor fPDGColor{};                        //!
    TString fXMLConfig;
    void SetTransparencyForLayer(TGeoNode* node, Int_t depth, Char_t transparency);
    static FairEventManager* fgRinstance;   //!
    FairEventManager(const FairEventManager&);
    FairEventManager& operator=(const FairEventManager&);
    void SetViewers(TEveViewer* RPhi, TEveViewer* RhoZ);
};

#endif
