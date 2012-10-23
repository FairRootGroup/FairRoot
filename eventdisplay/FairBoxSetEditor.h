// -------------------------------------------------------------------------
// -----              FairBoxSetEditor header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSetEditor
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *   to place the points.
 *   If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *   an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FairBoxSetEditor_H
#define FairBoxSetEditor_H

#include "FairBoxSet.h"

#include "TGedFrame.h"
#include "TEveDigitSetEditor.h"
#include "TGFrame.h"
#include "TEveGValuators.h"

class TGNumberEntry;
//class TGVerticalFrame;
//class TEveGValuator;

class FairBoxSetEditor : public TGedFrame
{

  public:

    FairBoxSetEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30,
                     UInt_t options = kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual ~FairBoxSetEditor() {};

    virtual void Init();

    virtual void SetModel(TObject* obj) {
      fM = dynamic_cast<FairBoxSet*>(obj);
      fTimeWindowPlus->SetNumber(fM->GetTimeWindowPlus());
      fTimeWindowMinus->SetNumber(fM->GetTimeWindowMinus());
    }

    virtual void TimeWindow();

    TGVerticalFrame* fInfoFrame;
    TGNumberEntry* fTimeWindowPlus;
    TGNumberEntry* fTimeWindowMinus;


  protected:
    TObject* fObject;
    FairBoxSet* fM;



  private:
    FairBoxSetEditor(const FairBoxSetEditor&);
    FairBoxSetEditor& operator=(const FairBoxSetEditor&);


    ClassDef(FairBoxSetEditor,2);

};


#endif
