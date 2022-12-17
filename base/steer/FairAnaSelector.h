/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----            FairAnaSelector header file                        -----
// -----            Created 14/10/11  by R. Karabowicz                 -----
// -----            Updated 01/02/12  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#ifndef FAIRANASELECTOR_H
#define FAIRANASELECTOR_H

#include "FairLogger.h"   // for FairLogger, MESSAGE_ORIGIN

#include <Rtypes.h>          // for Int_t, Bool_t, etc
#include <TSelector.h>       // for TSelector
#include <TSelectorList.h>   // for TSelectorList
#include <TString.h>         // for TString
#include <TTree.h>           // for TTree

class FairFileSource;
class FairRunAnaProof;

class TFile;
class TList;
class TObject;
class TProofOutputFile;

class FairAnaSelector : public TSelector
{
  public:
    TProofOutputFile* fProofFile;
    TFile* fFile;
    TTree* fChain;   //! pointer to the analyzed TTree or TChain
    FairRunAnaProof* fRunAna;

    FairAnaSelector(TTree* /*tree*/ = 0)
        : fProofFile(0)
        , fFile(0)
        , fChain(0)
        , fRunAna(nullptr)
        , fProofSource(0)
        , fCurrentDirectory("")
    {}

    ~FairAnaSelector() override {}
    Int_t Version() const override { return 1; }
    void Begin(TTree* tree) override;
    void SlaveBegin(TTree* tree) override;
    void Init(TTree* tree) override;
    Bool_t Notify() override;
    Bool_t Process(Long64_t entry) override;
    Int_t GetEntry(Long64_t entry, Int_t getall = 0) override
    {
        return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
    }
    void SetOption(const char* option) override { fOption = option; }
    void SetObject(TObject* obj) override { fObject = obj; }
    void SetInputList(TList* input) override { fInput = input; }
    TList* GetOutputList() const override { return fOutput; }
    void SlaveTerminate() override;
    void Terminate() override;

    void SetFairRunAnaProof(FairRunAnaProof* runAna) { fRunAna = runAna; }

  private:
    FairAnaSelector(const FairAnaSelector&);
    FairAnaSelector operator=(const FairAnaSelector&);

    FairFileSource* fProofSource;

    TString fCurrentDirectory;

    ClassDefOverride(FairAnaSelector, 0);
};

#endif   // FAIRANASELECTOR_H
