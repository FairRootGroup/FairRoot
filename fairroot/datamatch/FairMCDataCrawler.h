/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCDataCrawler.h
 *
 *  Created on: Jul 5, 2011
 *      Author: stockman
 */

#ifndef FAIRMCDATACRAWLER_H_
#define FAIRMCDATACRAWLER_H_

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairMultiLinkedData.h"   // for FairMultiLinkedData

#include <Rtypes.h>    // for Int_t, Bool_t, etc
#include <TObject.h>   // for TObject
#include <TString.h>   // for TString

class FairLink;
class FairRootManager;

class FairMCDataCrawler : public TObject
{
  public:
    FairMCDataCrawler();
    virtual ~FairMCDataCrawler();

    FairMultiLinkedData GetInfo(FairMultiLinkedData startLink, TString stopStage);
    FairMultiLinkedData GetInfo(FairMultiLinkedData startLink, Int_t stopStageId);

    FairMultiLinkedData* GetEntry(Int_t fileId, Int_t eventNr, Int_t type, Int_t index);
    FairMultiLinkedData* GetEntry(FairLink link);

    void SetStoreIntermediate(Bool_t val = kTRUE) { fStoreIntermediate = val; }
    void SetStoreAllEndpoints(Bool_t val = kTRUE) { fStoreAllEndpoints = val; }

    void Init();

    void SetVerbose(Int_t val) { fVerbose = val; };

    virtual void InitDataObjects() = 0;

  protected:
    FairRootManager* fIoman;

  private:
    FairMultiLinkedData fFinalStage;
    Int_t fUltimateStage;   ///< last stage in link chain. Here all recursive operations must stop.

    Int_t fVerbose;
    Bool_t fStoreAllEndpoints;   ///< true if non-stop-stage data is stored in results
    Bool_t fStoreIntermediate;   ///< true if all intermediate steps should be stored

    void GetNextStage(FairMultiLinkedData& startEntry, Int_t stopStage);
    void AddToFinalStage(FairLink link, Float_t mult);
    void ClearFinalStage();

    FairMCDataCrawler(const FairMCDataCrawler&);
    FairMCDataCrawler& operator=(const FairMCDataCrawler&);

    ClassDef(FairMCDataCrawler, 1);
};

#endif /* FAIRMCDATACRAWLER_H_ */
