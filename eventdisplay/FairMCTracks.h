// -------------------------------------------------------------------------
// -----                      FairMCTracks header file                 -----
// -----                Created 10/12/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------


/** FairMCTracks
 * @author M. Al-Turany
 * @since 10.12.07
 *   MVD event display object
 **
 **/

#ifndef FAIRMCTRACKS_H
#define FAIRMCTRACKS_H

#include "FairTask.h"
#include "TEveTrackPropagator.h"
#include "TString.h"

class FairEventManager;

//class TEveTrackPropagator;
class TEveTrackList;
class TObjArray;
class TParticle;

class FairMCTracks : public FairTask
{

  public:

    /** Default constructor **/
    FairMCTracks();


    /** Standard constructor
    *@param name        Name of task
    *@param iVerbose    Verbosity level
    **/
    FairMCTracks(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FairMCTracks();

    /** Set verbosity level. For this task and all of the subtasks. **/
    void SetVerbose(Int_t iVerbose) {fVerbose = iVerbose;}
    /** Executed task **/
    virtual void Exec(Option_t* option);
    virtual InitStatus Init();
    virtual void SetParContainers();

    /** Action after each event**/
    virtual void Finish();
    void Reset();
    TEveTrackList* GetTrGroup(TParticle* P);

  protected:


    TClonesArray*  fTrackList;  //!
    TEveTrackPropagator* fTrPr;
    FairEventManager* fEventManager;  //!
    TObjArray* fEveTrList;
    TString fEvent; //!
    TEveTrackList* fTrList;  //!
    //TEveElementList *fTrackCont;

    Double_t MinEnergyLimit;
    Double_t MaxEnergyLimit;
    Double_t PEnergy;

  private:
    FairMCTracks(const FairMCTracks&);
    FairMCTracks& operator=(const FairMCTracks&);

    ClassDef(FairMCTracks,1);

};


#endif
