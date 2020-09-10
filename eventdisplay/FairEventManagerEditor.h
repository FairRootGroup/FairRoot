/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairEventManagerEditor                  -----
// -----                  Created 16/12/07  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#ifndef ROOT_FAIREVENTMANAGEREDITOR
#define ROOT_FAIREVENTMANAGEREDITOR

#include <GuiTypes.h>   // for Pixel_t
#include <Rtypes.h>     // for ClassDef
#include <RtypesCore.h>
#include <TGFrame.h>     // for EFrameType::kChildFrame
#include <TGedFrame.h>   // for TGedFrame

class FairEveAnimationControl;
class TGComboBox;

class FairEventManager;
class TEveGValuator;
class TGCheckButton;
class TGLabel;
class TGNumberEntry;
class TGWindow;
class TObject;

class FairEventManagerEditor : public TGedFrame
{
    FairEventManagerEditor(const FairEventManagerEditor&);              // Not implemented
    FairEventManagerEditor& operator=(const FairEventManagerEditor&);   // Not implemented

  protected:
    TObject* fObject;
    FairEventManager* fManager;
    TGNumberEntry* fCurrentEvent;
    TGNumberEntry* fGlobalTransparency;
    TGLabel* fEventTime;
    TGComboBox* fScreenshotOpt;
    FairEveAnimationControl* fAnimation;

    void SetEventTimeLabel(Double_t time);

  public:
    FairEventManagerEditor(const TGWindow* p = 0,
                           Int_t width = 170,
                           Int_t height = 30,
                           UInt_t options = kChildFrame,
                           Pixel_t back = GetDefaultFrameBackground());
    virtual ~FairEventManagerEditor() {}
    void SetModel(TObject* obj);
    virtual void SelectEvent();
    virtual void StartAnimation();
    virtual void Init();
    /**
     *
     * @param light_background true if use white background
     */
    void SwitchBackground(Bool_t light_background);
    /**
     * make screenshot
     */
    void MakeScreenshot();
    ;
    // Specialization of TGedEditor for proper update propagation to TEveManager.
    ClassDef(FairEventManagerEditor, 0);
};

#endif
