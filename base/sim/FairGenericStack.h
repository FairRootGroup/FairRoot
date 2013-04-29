// -------------------------------------------------------------------------
// -----                       FairStack header file                    -----
// -----           Created 10/08/04  by D. Bertini                     -----
// -------------------------------------------------------------------------


/** FairStack.h
 *@author D.Bertini <d.bertini@gsi.de>
 * Generic MC stack class
 **/


#ifndef FAIRGENERICSTACK_H
#define FAIRGENERICSTACK_H


//#include <map>
//#include <stack>
//#include <iostream>
//#include "TClonesArray.h"
#include "TVirtualMCStack.h"
#include "FairLogger.h"


class TParticle;
class TRefArray;


class FairGenericStack : public TVirtualMCStack
{

  public:

    /** Default constructor  **/
    FairGenericStack();


    /** Destructor with estimated array size  **/
    FairGenericStack(Int_t size);


    /** Destructor  **/
    virtual ~FairGenericStack();

    /** Virtual method PushTrack.
     ** Add a TParticle to the stack.
     *@param toBeDone  Flag for tracking
     *@param parentID  Index of mother particle
     *@param pdgCode   Particle type (PDG encoding)
     *@param px,py,pz  Momentum components at start vertex [GeV]
     *@param e         Total energy at start vertex [GeV]
     *@param vx,vy,vz  Coordinates of start vertex [cm]
     *@param time      Start time of track [s]
     *@param polx,poly,polz Polarisation vector
     *@param proc      Production mechanism (VMC encoding)
     *@param ntr       Track number (filled by the stack)
     *@param weight    Particle weight
     *@param is        Generation status code (whatever that means)
     **/
    virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                           Double_t px, Double_t py, Double_t pz,
                           Double_t e, Double_t vx, Double_t vy,
                           Double_t vz, Double_t time, Double_t polx,
                           Double_t poly, Double_t polz, TMCProcess proc,
                           Int_t& ntr, Double_t weight, Int_t is);

    virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                           Double_t px, Double_t py, Double_t pz,
                           Double_t e, Double_t vx, Double_t vy,
                           Double_t vz, Double_t time, Double_t polx,
                           Double_t poly, Double_t polz, TMCProcess proc,
                           Int_t& ntr, Double_t weight, Int_t is, Int_t secondparentID);


    /** Virtual method PopNextTrack.
     ** Gets next particle for tracking from the stack.
     *@param  iTrack  index of popped track
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopNextTrack(Int_t& iTrack);


    /** Virtual method PopPrimaryForTracking.
     ** Gets primary particle by index for tracking from stack.
     *@param  iPrim   index of primary particle
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopPrimaryForTracking(Int_t iPrim);


    /** Add a TParticle to the fParticles array **/
    void AddParticle(TParticle* part);


    /** Fill the MCTrack output array, applying filter criteria **/
    virtual void FillTrackArray();


    /** Update the track index in the MCTracks and MCPoints **/
    virtual void UpdateTrackIndex(TRefArray* detArray);


    /** Resets arrays and stack and deletes particles and tracks **/
    virtual void Reset();


    /** Register the MCTrack array to the Root Manager  **/
    virtual void Register();


    /** Output to screen
     **@param iVerbose: 0=events summary, 1=track info
     **/
    virtual void Print(Int_t iVerbose=0) const;


    /** Modifiers  **/
    virtual void SetCurrentTrack(Int_t iTrack);
    /*  void StoreSecondaries(Bool_t choice = kTRUE) { fStoreSecondaries = choice; }
      void SetMinPoints(Int_t min)                 { fMinPoints        = min;    }
      void SetEnergyCut(Double_t eMin)             { fEnergyCut        = eMin;   }
      void StoreMothers(Bool_t choice = kTRUE)     { fStoreMothers     = choice; }
    */

    /** Accessors **/
    virtual Int_t GetNtrack() const;   // Total number of tracks
    virtual Int_t GetNprimary() const; // Number of primaries
    virtual TParticle* GetCurrentTrack() const;
    virtual Int_t GetCurrentTrackNumber() const;
    virtual Int_t GetCurrentParentTrackNumber() const;
    virtual TParticle* GetParticle(Int_t trackID) const { return NULL; }


  protected:
    /** Fair Logger */
    FairLogger*            fLogger;//!

    Int_t fVerbose;

  private:
    FairGenericStack(const FairGenericStack&);
    FairGenericStack& operator=(const FairGenericStack&);

    ClassDef(FairGenericStack,1)


};

#endif
