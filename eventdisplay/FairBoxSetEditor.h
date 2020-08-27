/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----              FairBoxSetEditor header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------

/** FairBoxSetEditor
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an
 *input to place the points. If one wants to change the color of the points one has to overwrite the method GetValue.
 *This method takes a TObject and an integer and translates this into an integer as input for the EveBoxSet method
 *DigitValue
 **
 **/

#ifndef FairBoxSetEditor_H
#define FairBoxSetEditor_H

#include "FairBoxSet.h"   // for FairBoxSet

#include <GuiTypes.h>        // for Pixel_t
#include <Rtypes.h>          // for FairBoxSetEditor::Class, etc
#include <TGFrame.h>         // for EFrameType::kChildFrame, etc
#include <TGNumberEntry.h>   // for TGNumberEntry
#include <TGedFrame.h>       // for TGedFrame
#include <TObject.h>         // for TObject

class TGWindow;

class FairBoxSetEditor : public TGedFrame
{
  public:
    FairBoxSetEditor(const TGWindow* p = 0,
                     Int_t width = 170,
                     Int_t height = 30,
                     UInt_t options = kChildFrame,
                     Pixel_t back = GetDefaultFrameBackground());
    virtual ~FairBoxSetEditor(){};

    virtual void Init();

    virtual void SetModel(TObject* obj)
    {
        fM = dynamic_cast<FairBoxSet*>(obj);
        if (fM) {
            fTimeWindowPlus->SetNumber(fM->GetTimeWindowPlus());
            fTimeWindowMinus->SetNumber(fM->GetTimeWindowMinus());
        }
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

    ClassDef(FairBoxSetEditor, 2);
};

#endif
