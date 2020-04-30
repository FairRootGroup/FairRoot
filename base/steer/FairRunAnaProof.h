/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNANAPROOF_H
#define FAIRRUNANAPROOF_H

/**
 * Configure and manage the  Analysis on proof
 * @author R. Karabowicz
 * @version 0.1
 * @since 30.04.2013
 */

#include "FairFileSource.h"   // FairRunAnaProof can only accept FairFileSource as source
#include "FairRunAna.h"

#include <Rtypes.h>
#include <TProof.h>

class FairRunAnaProof : public FairRunAna
{
  public:
    static FairRunAnaProof* Instance();
    virtual ~FairRunAnaProof();
    FairRunAnaProof(const char* proofName = "");

    /**initialize the run manager*/
    void Init();

    /** Init containers executed on PROOF, which is part of Init when running locally*/
    void InitContainers();

    /**
     * Set the output file name for analysis or simulation
     */
    //    virtual void    SetOutputFile(const char* fname);
    /**
     * Set the output file for analysis or simulation
     */
    //    virtual void    SetOutputFile(TFile* f);

    /**Run from event number NStart to event number NStop */
    void Run(Int_t NStart = 0, Int_t NStop = 0);
    /**Run for one event, used on PROOF nodes*/
    void RunOneEvent(Long64_t entry);
    /**Run on proof from event NStart to event NStop*/
    void RunOnProof(Int_t NStart, Int_t NStop);

    /** set the input tree of fRootManager when running on PROOF worker*/
    /* void        SetInTree (TTree* tempTree)   { */
    /*   fRootManager->SetInTree (tempTree); */
    /* } */

    /** GetProof */
    TProof* GetProof() { return fProof; }

    /** To be set to kTRUE only when running on PROOF worker, only by TSelector */
    void SetRunOnProofWorker(Bool_t tb = kTRUE) { fRunOnProofWorker = tb; }
    /** Set PROOF ARchive (PAR) file name*/
    void SetProofParName(TString parName) { fProofParName = parName; }
    /** Set directory for storing output files*/
    void SetOutputDirectory(TString dirName) { fOutputDirectory = dirName; }
    /** Set PROOF output status, possibilities: "copy","merge"*/
    void SetProofOutputStatus(TString outStat) { fProofOutputStatus = outStat; }

    virtual void SetSource(FairSource* tempSource);

  protected:
    static FairRunAnaProof* fRAPInstance;

    /** PROOF **/
    TProof* fProof;
    /** executing on PROOF worker*/
    Bool_t fRunOnProofWorker;   //!
    /** PROOF server name*/
    TString fProofServerName;   //!
    /** PROOF ARchive (PAR) file name*/
    TString fProofParName;   //!
    /** Output directory*/
    TString fOutputDirectory;   //!
    /** Output status indicator: "copy","merge","dataset"*/
    TString fProofOutputStatus;

  private:
    FairRunAnaProof(const FairRunAnaProof&);
    FairRunAnaProof operator=(const FairRunAnaProof&);

    FairFileSource* fProofFileSource;

    ClassDef(FairRunAnaProof, 1);
};

#endif   // FAIRRUNANAPROOF_H
