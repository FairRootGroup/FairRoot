/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 FAIRMCMATCHSELECTORTASK header file             -----
// -----                  Created 18/01/10  by T.Stockmanns             -----
// -------------------------------------------------------------------------

/** FAIRMCMATCHSELECTORTASK.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/

#ifndef FAIRMCMATCHSELECTORTASK_H
#define FAIRMCMATCHSELECTORTASK_H

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>    // for Int_t, Float_t, etc
#include <TString.h>   // for TString
#include <utility>     // for pair
#include <vector>      // for vector

class FairMCMatch;

class FairMCMatchSelectorTask : public FairTask
{
  public:
    /** Default constructor **/
    FairMCMatchSelectorTask();

    FairMCMatchSelectorTask(TString start, TString stop);

    FairMCMatchSelectorTask(Int_t start, Int_t stop);

    /** Destructor **/
    virtual ~FairMCMatchSelectorTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void SetStart(Int_t type) { fStart = type; }
    virtual void SetStop(Int_t type) { fStop = type; }

    virtual void SetAllWeights(Float_t weight) { fCommonWeight = weight; }
    virtual void SetWeightStage(Int_t type, Float_t weight)
    {
        fStageWeights.push_back(std::pair<Int_t, Float_t>(static_cast<Int_t>(type), weight));
    }

    virtual void SetWeights();

  private:
    FairMCMatch* fMCMatch;
    Int_t fStart;
    Int_t fStop;

    TString fStartString;
    TString fStopString;

    std::vector<std::pair<Int_t, Float_t>> fStageWeights;
    Float_t fCommonWeight;

    void Register();

    void Reset();

    void ProduceHits();

    FairMCMatchSelectorTask(const FairMCMatchSelectorTask&);
    FairMCMatchSelectorTask& operator=(const FairMCMatchSelectorTask&);

    ClassDef(FairMCMatchSelectorTask, 1);
};

#endif
