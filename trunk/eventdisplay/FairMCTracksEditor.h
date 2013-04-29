#ifndef ROOT_FAIREMCTRACKSEDITOR
#define ROOT_FAIREMCTRACKSEDITOR

#include "TGedFrame.h"
class FairEventManager;

class FairMCTracksEditor : public TGedFrame
{
    FairMCTracksEditor(const FairMCTracksEditor&);            // Not implemented
    FairMCTracksEditor& operator=(const FairMCTracksEditor&); // Not implemented

  protected:
    TObject* fObject;
    FairEventManager*  fManager;
  public:
    FairMCTracksEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30,
                       UInt_t options = kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual ~FairMCTracksEditor() {}

    virtual void SetModel( TObject* obj);


    ClassDef(FairMCTracksEditor, 0); // Specialization of TGedEditor for proper update propagation to TEveManager.
};

#endif
