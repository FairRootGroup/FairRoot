/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef ROOT_FAIREMCTRACKSEDITOR
#define ROOT_FAIREMCTRACKSEDITOR

#include "TGedFrame.h"                  // for TGedFrame

#include "GuiTypes.h"                   // for Pixel_t
#include "Rtypes.h"                     // for FairMCTracksEditor::Class, etc
#include "TGFrame.h"                    // for EFrameType::kChildFrame

class FairEventManager;
class TGWindow;
class TObject;

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
