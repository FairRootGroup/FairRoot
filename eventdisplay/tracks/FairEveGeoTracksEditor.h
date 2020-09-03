/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveGeoTracksEditor.h
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVEGEOTRACKSEDITOR_H_
#define FAIREVEGEOTRACKSEDITOR_H_

#include <GuiTypes.h>
#include <TGFrame.h>
#include <TGedFrame.h>   // for TGedFrame
#include <memory>

class FairEveBoolCut;
class FairEveGeoTracks;
class FairEveIntCut;
class FairEveMinMaxCut;

/**
 * editor of TGeoTracks in event display
 */

class FairEveGeoTracksEditor : public TGedFrame
{
    std::unique_ptr<FairEveMinMaxCut> fPtCut;
    std::unique_ptr<FairEveMinMaxCut> fEtaCut;
    std::unique_ptr<FairEveMinMaxCut> fEnergyCut;
    std::unique_ptr<FairEveBoolCut> fPrimary;
    std::unique_ptr<FairEveBoolCut> fSecondary;
    std::unique_ptr<FairEveIntCut> fPdgCut;
    FairEveGeoTracks* fGeoTracks;   //!

  public:
    FairEveGeoTracksEditor(const TGWindow* p = 0,
                           Int_t width = 170,
                           Int_t height = 30,
                           UInt_t options = kChildFrame,
                           Pixel_t back = GetDefaultFrameBackground());
    virtual void SetModel(TObject* obj);
    void ToggleTracks();
    void ToggleGroups();
    void Repaint();
    virtual ~FairEveGeoTracksEditor();
    ClassDef(FairEveGeoTracksEditor, 1)
};

#endif /* FAIREVEGEOTRACKSEDITOR_H_ */
