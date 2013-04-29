
/** FairRingSorterTask.h
 **
 **/

#ifndef FairRingSorterTask_H
#define FairRingSorterTask_H

#include "FairTask.h"

#include "TClonesArray.h"

#include "FairRingSorter.h"


class TClonesArray;

class FairRingSorterTask : public FairTask
{
  public:

    /** Default constructor **/
    FairRingSorterTask():
      FairTask("SorterTask"),
      fSorter(0),
      fPersistance(kTRUE),
      fDigiPixelMCInfo(kFALSE),
      fNumberOfCells(1000),
      fWidthOfCells(10),
      fInputBranch(),
      fInputArray(0),
      fOutputBranch(),
      fFolder(),
      fOutputArray(0),
      fEntryNr(0) {
      SetVerbose(0);
    }

    /** Named constructor **/
    FairRingSorterTask(const char* name):
      FairTask(name),
      fSorter(0),
      fPersistance(kTRUE),
      fDigiPixelMCInfo(kFALSE),
      fNumberOfCells(1000),
      fWidthOfCells(10),
      fInputBranch(),
      fInputArray(0),
      fOutputBranch(),
      fFolder(),
      fOutputArray(0),
      fEntryNr(0) {
      SetVerbose(0);
    }

    FairRingSorterTask(Int_t numberOfCells, Double_t widthOfCells, TString inputBranch, TString outputBranch, TString folderName):
      FairTask("Sorter"),
      fSorter(0),
      fPersistance(kTRUE),
      fDigiPixelMCInfo(kFALSE),
      fNumberOfCells(numberOfCells),
      fWidthOfCells(widthOfCells),
      fInputBranch(inputBranch),
      fInputArray(0),
      fOutputBranch(outputBranch),
      fFolder(folderName),
      fOutputArray(0),
      fEntryNr(0) {
      SetVerbose(0);
    }

    /** Destructor **/
    virtual ~FairRingSorterTask() {
      if (fSorter!= 0) { delete fSorter; }
    }

    /** Virtual method Init **/
    virtual InitStatus Init();
    virtual InitStatus ReInit();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
    virtual void FinishEvent();
    virtual void FinishTask();

    virtual void SetParContainers() {};

    void SetPersistance(Bool_t p = kTRUE) {fPersistance=p;};
    Bool_t GetPersistance() {return fPersistance;};

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data) = 0;
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const  = 0;

  protected:

    FairRingSorter* fSorter;
    /** switch to turn on/off storing the arrays to a file*/
    Bool_t fPersistance;
    /** switch to turn on/off storing additional MC Info of Digis*/
    Bool_t fDigiPixelMCInfo;
    Int_t fNumberOfCells;
    Double_t fWidthOfCells; // in ns
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

    ClassDef(FairRingSorterTask,2);

};

#endif
