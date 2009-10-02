// -------------------------------------------------------------------------
// -----              FairBoxSetDraw header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSetDraw
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *	 One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *	 to place the points.
 *	 If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *	 an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FAIRBOXSETDRAW_H
#define FAIRBOXSETDRAW_H


#include "FairTask.h"
#include "TEveBoxSet.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "FairEventManager.h"



class FairBoxSetDraw : public FairTask {

 public:

  /** Default constructor **/
  FairBoxSetDraw();


  /** Standard constructor
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairBoxSetDraw(const char* name, Int_t iVerbose = 1);

  /** Destructor **/
  virtual ~FairBoxSetDraw();

  /** Set verbosity level. For this task and all of the subtasks. **/
  void SetVerbose(Int_t iVerbose){fVerbose = fVerbose;};
  void SetBoxDimensions(Double_t x, Double_t y, Double_t z){
	  fX = x; fY = y; fZ = z;
  }
   /** Executed task **/
  virtual void Exec(Option_t* option);

  TEveBoxSet* CreateBoxSet();

  void Reset();

protected:

  Int_t   fVerbose;       //  Verbosity level
  virtual void SetParContainers() ;
  virtual InitStatus Init();
  /** Action after each event**/
  virtual void Finish();

  virtual TVector3 GetVector(TObject* obj) = 0;
  virtual Int_t GetValue(TObject* obj,Int_t i);
  virtual void AddBoxes(TEveBoxSet* set, TObject* obj, Int_t i = 0);

  TClonesArray *fList; //!
  FairEventManager *fEventManager;   //!
  FairRootManager* fManager;
  TEveBoxSet* fq;    //!
  Double_t fX, fY, fZ;
  ClassDef(FairBoxSetDraw,1);

};


#endif
