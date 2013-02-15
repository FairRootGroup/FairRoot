#ifndef FAIRTUTORIALDETMILLEWRITER_H
#define FAIRTUTORIALDETMILLEWRITER_H

#include "FairTask.h"

class Mille;

class TClonesArray;

class FairTutorialDetMilleWriter : public FairTask
{
  public:

    /** Default constructor **/
    FairTutorialDetMilleWriter();

    /** Constructor with parameters (Optional)
    //  FairTutorialDetMilleWriter(Int_t verbose);


    /** Destructor **/
    ~FairTutorialDetMilleWriter();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();


    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    void SetWriteAscii(Bool_t val) {fWriteAscii = val;}

    void SetVersion(Int_t val) {fVersion = val;}

  private:

    void ExecVersion1(Option_t* opt);
    void StraightLine1Dim(Option_t* opt);
    void StraightLine2Dim(Option_t* opt);

    /** Input array from previous already existing data level **/
    TClonesArray* fTracks;

    /** Input array from previous already existing data level **/
    TClonesArray* fHits;

    Mille* fMille;

    Bool_t fWriteAscii;

    Int_t fVersion;

    /** Output array to  new data level**/
    //  TClonesArray* <OutputDataLevel>;

    FairTutorialDetMilleWriter(const FairTutorialDetMilleWriter&);
    FairTutorialDetMilleWriter operator=(const FairTutorialDetMilleWriter&);

    ClassDef(FairTutorialDetMilleWriter,1);
};

#endif
