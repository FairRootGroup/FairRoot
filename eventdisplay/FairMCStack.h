// -------------------------------------------------------------------------
// -----                      FairMCStack header file                 -----
// -----                Created 09/10/08  by M. Al-Turany              -----
// -------------------------------------------------------------------------


/** FairMCStack
 * @author M. Al-Turany, Denis Bertini
 * @since 10.12.07
 *   MVD event display object
 **
 **/

#ifndef FairMCStack_H
#define FairMCStack_H


#include "CbmTask.h"
#include "TEveTrackPropagator.h"
#include "TString.h"
class CbmGeanePro;
class TGeant3;
class TEveTrackList;
class FairEventManager;
class TObjArray;
class CbmTrajFilter;

//class TEveElementList;
class FairMCStack : public CbmTask {

 public:

  /** Default constructor **/
  FairMCStack();



  /** Standard constructor 
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairMCStack(const char* name, Int_t iVerbose = 1);

  /** Destructor **/
  virtual ~FairMCStack();

  /** Set verbosity level. For this task and all of the subtasks. **/
  void SetVerbose(Int_t iVerbose);
   /** Executed task **/ 
  virtual void Exec(Option_t* option);
   virtual InitStatus Init();
   virtual void SetParContainers();
  
  /** Action after each event**/
  virtual void Finish();
  void Reset();
  TEveTrackList *GetTrGroup(TParticle *P);

protected:


  TClonesArray  *fTrackList;  //!
  TEveTrackPropagator *fTrPr; 
  FairEventManager * fEventManager; //!
  TObjArray *fEveTrList;
  TString fEvent; //!
  TEveTrackList *fTrList;  //!
  //TEveElementList *fTrackCont;
	Float_t x1[3];
	Float_t p1[3];
	Float_t ein[15];
	Float_t x2[3];
	Float_t p2[3];
	 TGeant3 *gMC3; //!
   Double_t MinEnergyLimit;
   Double_t MaxEnergyLimit;
   Double_t PEnergy;
   CbmGeanePro *fPro;//!
   CbmTrajFilter *fTrajFilter;//!
   ClassDef(FairMCStack,1);
    
};
                                  

#endif
