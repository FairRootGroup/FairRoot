// -------------------------------------------------------------------------
// -----                      FairTrackCandDraw header file                    -----
// -----          Created 10/12/07  by M. Al-Turany                    -----
// -------------------------------------------------------------------------


/** FairTrackCandDraw
 * @author M. Al-Turany
 * @since 03.01.08
 *   Task to display MC points
 **
 **/

#ifndef FairTrackCandDraw_H
#define FairTrackCandDraw_H


#include "FairTask.h"
#include "TClonesArray.h"

#include <string>

class FairEventManager;
class TEveQuadSet;
class FairTrackCandDraw : public FairTask {

 public:

  /** Default constructor **/
  FairTrackCandDraw();


  /** Standard constructor
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairTrackCandDraw(const char* TrackCandName, Int_t iVerbose = 1);

  /** Destructor **/
  virtual ~FairTrackCandDraw();

  /** Set verbosity level. For this task and all of the subtasks. **/
  void SetVerbose(Int_t iVerbose);
   /** Executed task **/
  virtual void Exec(Option_t* option);
  void Reset();
protected:

  Int_t   fVerbose;       //  Verbosity level
  virtual void SetParContainers() ;
  virtual InitStatus Init();
  /** Action after each event**/
  virtual void Finish() ;
  TClonesArray *fPixPointList; //!
  TClonesArray *fStripPointList; //!
  TClonesArray *fTrackCandList; //!
  TClonesArray *fTpcClusterList;
  FairEventManager *fEventManager;   //!
  TEveQuadSet* fq;    //!
  ClassDef(FairTrackCandDraw,1);

};


#endif
