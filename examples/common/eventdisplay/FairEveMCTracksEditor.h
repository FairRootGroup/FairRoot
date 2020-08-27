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

#include "FairEveCut.h"
#include "FairEveMCTracks.h"

#include <TGedFrame.h>

class FairEveMCTracksEditor : public TGedFrame
{
    FairEveMinMaxCut *fPtCut;
    FairEveMinMaxCut *fEtaCut;
    FairEveMinMaxCut *fEnergyCut;
    FairEveBoolCut *fPrimary;
    FairEveBoolCut *fSecondary;
    FairEveIntCut *fPdgCut;
    FairEveMCTracks *fMCTracks;

  public:
    FairEveMCTracksEditor(const TGWindow *p = 0,
                          Int_t width = 170,
                          Int_t height = 30,
                          UInt_t options = kChildFrame,
                          Pixel_t back = GetDefaultFrameBackground());
    virtual void SetModel(TObject *obj);
    void SwapTracks();
    void Repaint();
    virtual ~FairEveMCTracksEditor();
    ClassDef(FairEveMCTracksEditor, 0)
};

#endif /* FAIREVEMCTRACKSEDITOR_H_ */
