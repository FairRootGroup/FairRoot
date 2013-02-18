#ifndef FAIRTUTORIALDETSTRAIGHTLINEFITTER_H
#define FAIRTUTORIALDETSTRAIGHTLINEFITTER_H

#include "FairTask.h"

class TClonesArray;

class FairTutorialDetStraightLineFitter : public FairTask
{
  public:

    /** Default constructor **/
    FairTutorialDetStraightLineFitter();

    /** Constructor with parameters (Optional)
    //  FairTutorialDetStraightLineFitter(Int_t verbose);


    /** Destructor **/
    ~FairTutorialDetStraightLineFitter();


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

    void SetVersion(Int_t val) {fVersion = val;}

  private:

    /** Input array from previous already existing data level **/
    TClonesArray* fHits;

    /** Output array to  new data level**/
    TClonesArray* fTracks;

    Int_t fVersion;

    Bool_t IsGoodEvent();

    FairTutorialDetStraightLineFitter(const FairTutorialDetStraightLineFitter&);
    FairTutorialDetStraightLineFitter operator=(const FairTutorialDetStraightLineFitter&);

    ClassDef(FairTutorialDetStraightLineFitter,1);
};

#endif
