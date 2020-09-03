/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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

#include <TGFrame.h>
#include <TGedFrame.h>
#include <memory>

class FairEveBoolCut;
class FairEveIntCut;
class FairEveMCTracks;
class FairEveMinMaxCut;

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
