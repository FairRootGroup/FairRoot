/*
 * FairEveRecoTracksExample.h
 *
 *  Created on: 16 cze 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVERECOTRACKS_H_
#define FAIREVERECOTRACKS_H_

#include "FairEveTracks.h"
#include "FairMCTrack.h"
#include "FairTask.h"
#include "FairTutPropTrack.h"

#include <FairRKPropagator.h>
#include <TDatabasePDG.h>

class FairEveRecoTracksExample : public FairEveTracks
{
    TClonesArray *fContainerReco;
    TClonesArray *fContainerSim;
    TClonesArray *fHits1, *fHits2;
    Bool_t fShowPrimary;
    Bool_t fShowSecondary;
    Bool_t fDrawMC;
    Bool_t fUsePdg;
    Int_t fPdgCut;
    FairRKPropagator *fRK;
    TDatabasePDG *fPDG;

  protected:
    Bool_t CheckCuts(FairTutPropTrack *tr);
    void DrawTrack(Int_t id);
    TEveTrackList *GetTrackGroup(void *tr);

  public:
    FairEveRecoTracksExample();
    void Repaint();
    void SetDrawMC(Bool_t draw);
    void SetPdgCut(Int_t pdg, Bool_t use)
    {
        fPdgCut = pdg;
        fUsePdg = use;
    };
    void SetShowPrimSec(Bool_t prim, Bool_t sec)
    {
        fShowPrimary = prim;
        fShowSecondary = sec;
    }
    virtual void SwapTracks();
    virtual InitStatus Init();
    virtual ~FairEveRecoTracksExample();
    ClassDef(FairEveRecoTracksExample, 0)
};

#endif /* FAIREVERECOTRACKS_H_ */
