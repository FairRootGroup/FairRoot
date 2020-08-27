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

#include <TGedFrame.h>
#include "FairEveCut.h"
#include "FairEveRecoTracksExample.h"

class FairEveRecoTracksExampleEditor :public TGedFrame {
    FairEveMinMaxCut *fPtCut;
    FairEveMinMaxCut *fEtaCut;
    FairEveMinMaxCut *fEnergyCut;
    FairEveRecoTracksExample *fRecoTracks;
    FairEveBoolCut *fDrawMC;
public:
    FairEveRecoTracksExampleEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30, UInt_t options=kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual void SetModel(TObject* obj);
    void SwapTracks();
    void Repaint();
    virtual ~FairEveRecoTracksExampleEditor();
    ClassDef(FairEveRecoTracksExampleEditor,0);
};
#endif /* FAIREVERECOTRACKSEXAMPLEEDITOR_H_ */
