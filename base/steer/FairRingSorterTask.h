/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** FairRingSorterTask.h
 **
 **/

#ifndef FairRingSorterTask_H
#define FairRingSorterTask_H

#include "FairRingSorter.h"   // for FairRingSorter
#include "FairTask.h"         // for FairTask, InitStatus

#include <Rtypes.h>    // for Bool_t, Int_t, kTRUE, etc
#include <TString.h>   // for TString

class FairTimeStamp;
class TClonesArray;

class FairRingSorterTask : public FairTask
{
  public:
    /** Default constructor **/
    FairRingSorterTask()
        : FairTask("SorterTask")
        , fSorter(0)
        , fPersistance(kTRUE)
        , fDigiPixelMCInfo(kFALSE)
        , fNumberOfCells(1000)
        , fWidthOfCells(10)
        , fInputBranch()
        , fInputArray(0)
        , fOutputBranch()
        , fFolder()
        , fOutputArray(0)
        , fEntryNr(0)
    {
        SetVerbose(0);
    }

    /** Named constructor **/
    FairRingSorterTask(const char* name)
        : FairTask(name)
        , fSorter(0)
        , fPersistance(kTRUE)
        , fDigiPixelMCInfo(kFALSE)
        , fNumberOfCells(1000)
        , fWidthOfCells(10)
        , fInputBranch()
        , fInputArray(0)
        , fOutputBranch()
        , fFolder()
        , fOutputArray(0)
        , fEntryNr(0)
    {
        SetVerbose(0);
    }

    FairRingSorterTask(Int_t numberOfCells,
                       Double_t widthOfCells,
                       TString inputBranch,
                       TString outputBranch,
                       TString folderName)
        : FairTask("Sorter")
        , fSorter(0)
        , fPersistance(kTRUE)
        , fDigiPixelMCInfo(kFALSE)
        , fNumberOfCells(numberOfCells)
        , fWidthOfCells(widthOfCells)
        , fInputBranch(inputBranch)
        , fInputArray(0)
        , fOutputBranch(outputBranch)
        , fFolder(folderName)
        , fOutputArray(0)
        , fEntryNr(0)
    {
        SetVerbose(0);
    }

    /** Destructor **/
    ~FairRingSorterTask() override { delete fSorter; }

    /** Virtual method Init **/
    InitStatus Init() override;
    InitStatus ReInit() override;

    /** Virtual method Exec **/
    void Exec(Option_t* opt) override;
    void FinishEvent() override;
    void FinishTask() override;

    void SetPersistance(Bool_t p = kTRUE) { fPersistance = p; };
    Bool_t GetPersistance() { return fPersistance; };

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

  protected:
    FairRingSorter* fSorter;
    /** switch to turn on/off storing the arrays to a file*/
    Bool_t fPersistance;
    /** switch to turn on/off storing additional MC Info of Digis*/
    Bool_t fDigiPixelMCInfo;
    Int_t fNumberOfCells;
    Double_t fWidthOfCells;   // in ns
    /** Input array of PndSdsPixelDigis **/
    TString fInputBranch;
    TClonesArray* fInputArray;
    /** Output array of sorted PndSdsDigis **/
    TString fOutputBranch;
    TString fFolder;
    TClonesArray* fOutputArray;
    Int_t fEntryNr;
    FairRingSorterTask(const FairRingSorterTask&);
    FairRingSorterTask& operator=(const FairRingSorterTask&);

    ClassDefOverride(FairRingSorterTask, 2);
};

#endif
