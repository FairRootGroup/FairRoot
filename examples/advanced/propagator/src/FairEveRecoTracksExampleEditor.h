/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveRecoTracksExampleEditor.h
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVERECOTRACKSEXAMPLEEDITOR_H_
#define FAIREVERECOTRACKSEXAMPLEEDITOR_H_

#include <GuiTypes.h>     // for Pixel_t
#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Int_t, UInt_t
#include <TGFrame.h>      // for kChildFrame
#include <TGedFrame.h>    // for TGedFrame
#include <memory>         // for unique_ptr

class FairEveBoolCut;
class FairEveMinMaxCut;
class FairEveRecoTracksExample;
class TBuffer;
class TClass;
class TGWindow;
class TMemberInspector;
class TObject;

class FairEveRecoTracksExampleEditor : public TGedFrame
{
    std::unique_ptr<FairEveMinMaxCut> fPtCut;
    std::unique_ptr<FairEveMinMaxCut> fEtaCut;
    std::unique_ptr<FairEveMinMaxCut> fEnergyCut;
    FairEveRecoTracksExample *fRecoTracks;   //!
    std::unique_ptr<FairEveBoolCut> fDrawMC;

  public:
    FairEveRecoTracksExampleEditor(const TGWindow *p = 0,
                                   Int_t width = 170,
                                   Int_t height = 30,
                                   UInt_t options = kChildFrame,
                                   Pixel_t back = GetDefaultFrameBackground());
    virtual void SetModel(TObject *obj);
    void ToggleTracks();
    void Repaint();
    virtual ~FairEveRecoTracksExampleEditor();
    ClassDef(FairEveRecoTracksExampleEditor, 0);
};
#endif /* FAIREVERECOTRACKSEXAMPLEEDITOR_H_ */
