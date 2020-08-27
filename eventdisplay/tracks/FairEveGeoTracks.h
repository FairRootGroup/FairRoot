/*
 * FairEveGeoTracks.h
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVEGEOTRACKS_H_
#define FAIREVEGEOTRACKS_H_

#include <Rtypes.h>
#include <RtypesCore.h>
#include <TEveElement.h>
#include <TNamed.h>
#include <TEveTrackPropagator.h>
#include <TEveTrack.h>
#include <TGeoTrack.h>
#include <TClonesArray.h>

#include "FairTask.h"
#include "FairEventManager.h"
#include "FairEveTracks.h"

/**
 * draw TGeoTracks
 */

class FairEveGeoTracks :  public FairEveTracks{
    TClonesArray *fContainer;
    Bool_t fShowPrimary;
    Bool_t fShowSecondary;
    Bool_t fUsePdg;
    Int_t fPdgCut;
    Double_t fTMin, fTMax;
protected:
    Bool_t CheckCuts(TGeoTrack *tr);
    void DrawTrack(Int_t id);
    void DrawAnimatedTrack(Int_t id);
    TEveTrackList *GetTrackGroup(void *tr);
public:
    FairEveGeoTracks();
    void Repaint();
    void SetPdgCut(Int_t pdg, Bool_t use){fPdgCut = pdg; fUsePdg = use;};
    void SetShowPrimSec(Bool_t prim, Bool_t sec){fShowPrimary = prim;
    fShowSecondary = sec;}
    virtual InitStatus Init();
    virtual ~FairEveGeoTracks();
    ClassDef(FairEveGeoTracks,0)
};

#endif /* FAIREVEGEOTRACKS_H_ */
