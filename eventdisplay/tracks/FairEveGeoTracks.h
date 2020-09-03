/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

#include "FairEveTracks.h"
#include "FairTask.h"

class TGeoTrack;

/**
 * draw TGeoTracks
 */

class FairEveGeoTracks : public FairEveTracks
{
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

  public:
    FairEveGeoTracks();
    void Repaint();
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
    virtual InitStatus Init();
    virtual ~FairEveGeoTracks();
    ClassDef(FairEveGeoTracks, 0)
};

#endif /* FAIREVEGEOTRACKS_H_ */
