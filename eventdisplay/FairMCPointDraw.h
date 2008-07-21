// -------------------------------------------------------------------------
// -----                      FairMCPointDraw header file                    -----
// -----          Created 10/12/07  by M. Al-Turany                    -----
// -------------------------------------------------------------------------


/** FairMCPointDraw         
 * @author M. Al-Turany
 * @since 03.01.08
 *   Task to display MC points 
 **
 **/

#ifndef FAIRMCPOINTDRAW_H
#define FAIRMCPOINTDRAW_H


#include "CbmTask.h"

class FairEventManager;
class TClonesArray;
class TEvePointSet;
class FairMCPointDraw : public CbmTask {

 public:

  /** Default constructor **/
  FairMCPointDraw();


  /** Standard constructor 
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairMCPointDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1);

  /** Destructor **/
  virtual ~FairMCPointDraw();

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
  TClonesArray *fPointList; //!
  FairEventManager *fEventManager;   //!
  TEvePointSet* fq;    //!
  Color_t fColor; //!
  Style_t fStyle; //!
  ClassDef(FairMCPointDraw,1);
    
};

                            
#endif
