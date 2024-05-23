/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveMCTracksEditor.h
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVEMCTRACKSEDITOR_H_
#define FAIREVEMCTRACKSEDITOR_H_
#include <GuiTypes.h>    // for Pixel_t
#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Int_t, UInt_t
#include <TGFrame.h>     // for kChildFrame
#include <TGedFrame.h>   // for TGedFrame
#include <memory>        // for unique_ptr
class FairEveBoolCut;  // lines 23-23
class FairEveIntCut;  // lines 24-24
class FairEveMCTracks;  // lines 25-25
class FairEveMinMaxCut;  // lines 26-26
class TBuffer;
class TClass;
class TGWindow;
class TObject;

class FairEveMCTracksEditor : public TGedFrame
{
    std::unique_ptr<FairEveMinMaxCut> fPtCut;
    std::unique_ptr<FairEveMinMaxCut> fEtaCut;
    std::unique_ptr<FairEveMinMaxCut> fEnergyCut;
    std::unique_ptr<FairEveBoolCut> fPrimary;
    std::unique_ptr<FairEveBoolCut> fSecondary;
    std::unique_ptr<FairEveIntCut> fPdgCut;
    FairEveMCTracks *fMCTracks;   //!

  public:
    FairEveMCTracksEditor(const TGWindow *p = 0,
                          Int_t width = 170,
                          Int_t height = 30,
                          UInt_t options = kChildFrame,
                          Pixel_t back = GetDefaultFrameBackground());
    virtual void SetModel(TObject *obj);
    void ToggleTracks();
    void Repaint();
    virtual ~FairEveMCTracksEditor();
    ClassDef(FairEveMCTracksEditor, 0)
};

#endif /* FAIREVEMCTRACKSEDITOR_H_ */
