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
#include <GuiTypes.h>    // for Pixel_t
#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Int_t, Bool_t, Double_t, UInt_t
#include <TGFrame.h>     // for kChildFrame
#include <TGedFrame.h>   // for TGedFrame
class FairEveAnimationControl;  // lines 21-21
class FairEventManager;  // lines 24-24
class TBuffer;
class TClass;
class TGComboBox;  // lines 22-22
class TGLabel;  // lines 27-27
class TGNumberEntry;  // lines 28-28
class TGWindow;  // lines 29-29
class TMemberInspector;
class TObject;  // lines 30-30

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
    virtual void SelectSingleEvent();
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
