
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
    FairRingSorterTask():FairTask("SorterTask"), fNumberOfCells(1000), fWidthOfCells(10),fEntryNr(0) {
      SetVerbose(3);
      SetPersistance();
    }

    /** Named constructor **/
    FairRingSorterTask(const char* name):
      FairTask(name), fNumberOfCells(1000), fWidthOfCells(10), fEntryNr(0) {
      SetPersistance();
    };

    FairRingSorterTask(Int_t numberOfCells, Double_t widthOfCells, TString inputBranch, TString outputBranch, TString folderName):
      FairTask("Sorter"), fNumberOfCells(numberOfCells), fWidthOfCells(widthOfCells), fInputBranch(inputBranch), fOutputBranch(outputBranch), fFolder(folderName) {
      SetPersistance();
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
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) = 0;

  protected:

    FairRingSorter* fSorter;

    Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
    Bool_t fDigiPixelMCInfo; // switch to turn on/off storing additional MC Info of Digis

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


    ClassDef(FairRingSorterTask,2);

};

#endif
