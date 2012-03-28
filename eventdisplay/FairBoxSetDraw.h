// -------------------------------------------------------------------------
// -----              FairBoxSetDraw header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSetDraw
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *   to place the points.
 *   If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *   an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FAIRBOXSETDRAW_H
#define FAIRBOXSETDRAW_H


#include "FairTask.h"

#include "FairTSBufferFunctional.h"

class FairBoxSet;
class TObject;
class TVector3;
class TClonesArray;
class FairEventManager;
class FairRootManager;

class FairBoxSetDraw : public FairTask
{

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

    virtual Double_t GetTimeWindowPlus() {return fTimeWindowPlus;}
    virtual Double_t GetTimeWindowMinus() {return fTimeWindowMinus;}

    /** Set verbosity level. For this task and all of the subtasks. **/
    virtual void SetVerbose(Int_t iVerbose) {fVerbose = iVerbose;};
    virtual void SetBoxDimensions(Double_t x, Double_t y, Double_t z) {
      fX = x;
      fY = y;
      fZ = z;
    }

    virtual void SetTimeWindowMinus(Double_t val);
    virtual void SetTimeWindowPlus(Double_t val);
    virtual void SetStartTime(Double_t val) {fStartTime = val;}
    virtual void UseEventTimeAsStartTime(Bool_t val = kTRUE) {fUseEventTime = val;}

    /** Executed task **/
    virtual void Exec(Option_t* option);

    FairBoxSet* CreateBoxSet();

    void Reset();

  protected:

    Int_t   fVerbose;       //  Verbosity level
    virtual void SetParContainers() ;
    virtual InitStatus Init();
    /** Action after each event**/
    virtual void Finish();

    virtual TVector3 GetVector(TObject* obj) = 0;
    virtual Int_t GetValue(TObject* obj,Int_t i);
    virtual void AddBoxes(FairBoxSet* set, TObject* obj, Int_t i = 0);

    TClonesArray* fList; //!
    FairEventManager* fEventManager;   //!
    FairRootManager* fManager;
    FairBoxSet* fq;    //!
    Double_t fX, fY, fZ;

    Double_t fTimeWindowPlus;
    Double_t fTimeWindowMinus;
    Double_t fStartTime;
    Bool_t fUseEventTime;


  private:
    FairBoxSetDraw(const FairBoxSetDraw&);
    FairBoxSetDraw& operator=(const FairBoxSetDraw&);
    BinaryFunctor* fStartFunctor;
    BinaryFunctor* fStopFunctor;

    ClassDef(FairBoxSetDraw,1);

};


#endif
