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


#include "FairHitDraw.h"
#include "TClonesArray.h"

class FairTrackCandDraw : public FairHitDraw {

 public:

  /** Default constructor **/
  FairTrackCandDraw(){};


  /** Standard constructor
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairTrackCandDraw(const char* TrackCandName, Int_t iVerbose = 1);

  /** Destructor **/
  virtual ~FairTrackCandDraw();
  virtual InitStatus Init();

protected:
	  //virtual TVector3 GetVector(TObject* obj);
	  virtual TVector3 GetVector(Int_t detId, Int_t hitId);
	  //virtual Int_t GetValue(TObject* obj,Int_t i);
	  virtual void AddBoxes(TEveBoxSet* set, TObject* obj, Int_t i = 0);

  TClonesArray *fPixPointList; //!
  TClonesArray *fStripPointList; //!
  TClonesArray *fTrackCandList; //!
  TClonesArray *fTpcClusterList;

  ClassDef(FairTrackCandDraw,1);

};


#endif
