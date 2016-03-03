// -------------------------------------------------------------------------
// -----        FairTutorialDet4PointDraw header file                  -----
// -----            Created 02.03.16  by F. Uhlig                      -----
// -------------------------------------------------------------------------


/** FairTutorialDet4PointDraw
 * @author F. Uhlig
 * @since 02.03.16
 *   Task to display FairTutorialDet4Points stored in local
 *   or global coordinates.
 **
 **/

#ifndef FAIRTUTORIALDET4POINTDRAW_H
#define FAIRTUTORIALDET4POINTDRAW_H

#include "FairTask.h"                   // for FairTask, InitStatus
#include "Rtypes.h"                     // for Bool_t, Int_t, etc

class FairTutorialDet4GeoPar;
class FairTutorialDet4DigiPar;
class FairEventManager;
class FairTutorialDet4GeoHandler;

class TClonesArray;
class TEvePointSet;

class FairTutorialDet4PointDraw : public FairTask {

 public:

  /** Default constructor **/
  FairTutorialDet4PointDraw();

  /** Standard constructor
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairTutorialDet4PointDraw(const char* name, Color_t color ,
			    Style_t mstyle);

  /** Destructor **/
  virtual ~FairTutorialDet4PointDraw();

   /** Executed task **/
  virtual void Exec(Option_t* option);
  void Reset();

  virtual void SetParContainers() ;
  virtual InitStatus Init();
  /** Action after each event**/

  virtual void Finish() ;

private:

  TClonesArray *fPointList; //!
  FairTutorialDet4GeoPar *fGeoPar; //!
  FairEventManager *fEventManager;   //!
  TEvePointSet* fq;    //!
  Color_t fColor; //!
  Style_t fStyle; //!
  Bool_t fGlobalCoordinates; //!
  FairTutorialDet4GeoHandler* fGeoHandler; //!

  FairTutorialDet4PointDraw(const FairTutorialDet4PointDraw&);
  FairTutorialDet4PointDraw& operator=(const FairTutorialDet4PointDraw&);

  ClassDef(FairTutorialDet4PointDraw,1);

};


#endif


