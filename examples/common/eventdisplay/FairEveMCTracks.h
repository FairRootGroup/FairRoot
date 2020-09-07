/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
#include "FairTask.h"

class FairMCTrack;
class FairRKPropagator;
class TDatabasePDG;

class FairEveMCTracks : public FairEveTracks
{
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

  public:
    FairEveMCTracks();
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
    virtual ~FairEveMCTracks();
    ClassDef(FairEveMCTracks, 0)
};

#endif /* FAIREVEMCTRACKS_H_ */
