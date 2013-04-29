// -------------------------------------------------------------------------
// -----                       FairEventManagerEditor                  -----
// -----                  Created 16/12/07  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#ifndef ROOT_FAIREVENTMANAGEREDITOR
#define ROOT_FAIREVENTMANAGEREDITOR

#include "TGedFrame.h"

#include "TEveGValuators.h"

class FairEventManager;
class TGNumberEntry;
class TGCheckButton;
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
