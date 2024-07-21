/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include "FairEveTracks.h"     // for FairEveTracks
#include "FairTask.h"          // for InitStatus
#include "FairXMLPdgColor.h"   //for pdg color

#include <FairRKPropagator.h>
#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Bool_t, Int_t
#include <memory>         // for std::unique_ptr

class FairMCTrack;
class TBuffer;
class TClass;
class TClonesArray;
class TDatabasePDG;

class FairEveMCTracks : public FairEveTracks
{
    TClonesArray* fContainer{nullptr};
    Bool_t fShowPrimary;
    Bool_t fShowSecondary;
    Bool_t fUsePdg;
    Int_t fPdgCut;
    FairXMLPdgColor fPdgColor;
    std::unique_ptr<FairRKPropagator> fRK{};
    TDatabasePDG* fPDG{nullptr};

  protected:
    Bool_t CheckCuts(FairMCTrack* tr);
    void DrawTrack(Int_t id);

  public:
    FairEveMCTracks();
    void Repaint() override;
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
    InitStatus Init() override;
    ~FairEveMCTracks() override;
    ClassDefOverride(FairEveMCTracks, 0)
};

#endif /* FAIREVEMCTRACKS_H_ */
