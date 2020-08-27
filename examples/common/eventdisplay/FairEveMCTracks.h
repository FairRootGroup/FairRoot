/*
 * FairMCTracks.h
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVEMCTRACKS_H_
#define FAIREVEMCTRACKS_H_

#include "FairEveTracks.h"
#include "FairMCTrack.h"

#include <TDatabasePDG.h>
#include <FairRKPropagator.h>

class FairEveMCTracks : public FairEveTracks{
    TClonesArray *fContainer;
    Bool_t fShowPrimary;
    Bool_t fShowSecondary;
    Bool_t fUsePdg;
    Int_t fPdgCut;
    FairRKPropagator *fRK;
    TDatabasePDG *fPDG;
protected:
    Bool_t CheckCuts(FairMCTrack *tr);
    void DrawTrack(Int_t id);
    TEveTrackList *GetTrackGroup(void *tr);
public:
    FairEveMCTracks();
    void Repaint();
    void SetPdgCut(Int_t pdg, Bool_t use){fPdgCut = pdg; fUsePdg = use;};
    void SetShowPrimSec(Bool_t prim, Bool_t sec){fShowPrimary = prim;
    fShowSecondary = sec;}
    virtual InitStatus Init();
    virtual ~FairEveMCTracks();
    ClassDef(FairEveMCTracks,0)
};

#endif /* FAIREVEMCTRACKS_H_ */
