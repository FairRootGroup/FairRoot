/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairEventManagerEditor                  -----
// -----                  Created 16/12/07  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#ifndef ROOT_FAIREVENTMANAGEREDITOR
#define ROOT_FAIREVENTMANAGEREDITOR

#include "TGedFrame.h"                  // for TGedFrame

#include "GuiTypes.h"                   // for Pixel_t
#include "Rtypes.h"                     // for ClassDef
#include "TGFrame.h"                    // for EFrameType::kChildFrame

class FairEventManager;
class TEveGValuator;
class TGCheckButton;
class TGLabel;
class TGNumberEntry;
class TGWindow;
class TObject;

class FairEventManagerEditor : public TGedFrame
{
    FairEventManagerEditor(const FairEventManagerEditor&);            // Not implemented
    FairEventManagerEditor& operator=(const FairEventManagerEditor&); // Not implemented

  protected:
    TObject* fObject;
    FairEventManager*  fManager;
    TGNumberEntry*  fCurrentEvent, *fCurrentPDG;
    TGCheckButton*  fVizPri;
    TEveGValuator* fMinEnergy ,*fMaxEnergy;
    TGLabel* fEventTime;
  public:
    FairEventManagerEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30,
                           UInt_t options = kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual ~FairEventManagerEditor() {}
    void SetModel( TObject* obj);
    virtual void SelectEvent();
    virtual void SelectPDG();
    void DoVizPri();
    virtual void MaxEnergy();
    virtual void MinEnergy();
    virtual void Init();

    ClassDef(FairEventManagerEditor, 0); // Specialization of TGedEditor for proper update propagation to TEveManager.
};

#endif
