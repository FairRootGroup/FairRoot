/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairStack header file                    -----
// -----           Created 10/08/04  by D. Bertini / V. Friese         -----
// -------------------------------------------------------------------------

/** FairStack.h
 *@author D.Bertini <d.bertini@gsi.de>
 *@author V.Friese <v.friese@gsi.de>
 **
 ** Version 14/06/07 by V. Friese
 **
 ** This class handles the particle stack for the transport simulation.
 ** For the stack FILO functunality, it uses the STL stack. To store
 ** the tracks during transport, a TParticle arry is used.
 ** At the end of the event, tracks satisfying the filter criteria
 ** are copied to a FairMCTrack array, which is stored in the output.
 **
 ** The filtering criteria for the output tracks are:
 ** - primary tracks are stored in any case.
 ** - secondary tracks are stored if they have a minimal number of
 **   points (sum of all detectors) and a minimal energy, or are the
 **
 ** The storage of secondaries can be switched off.
 ** The storage of all mothers can be switched off.
 ** By default, the minimal number of points is 1 and the energy cut is 0.
 **/

#ifndef FAIRSTACK_H
#define FAIRSTACK_H

#include "FairDetectorList.h"   // for DetectorId
#include "FairGenericStack.h"   // for FairGenericStack

#include <Rtypes.h>       // for Int_t, Double_t, Bool_t, etc
#include <TMCProcess.h>   // for TMCProcess
#include <TParticle.h>
#include <map>       // for map, map<>::iterator
#include <stack>     // for stack
#include <utility>   // for pair

class TClonesArray;
class TRefArray;

class FairStack : public FairGenericStack
{
  public:
    /** Default constructor
     *param size  Estimated track number
     **/
    FairStack(Int_t size = 100);

    /** Destructor  **/
    virtual ~FairStack();

    /** Add a TParticle to the stack.
     ** Declared in TVirtualMCStack
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
    virtual void PushTrack(Int_t toBeDone,
                           Int_t parentID,
                           Int_t pdgCode,
                           Double_t px,
                           Double_t py,
                           Double_t pz,
                           Double_t e,
                           Double_t vx,
                           Double_t vy,
                           Double_t vz,
                           Double_t time,
                           Double_t polx,
                           Double_t poly,
                           Double_t polz,
                           TMCProcess proc,
                           Int_t& ntr,
                           Double_t weight,
                           Int_t is);

    virtual void PushTrack(Int_t toBeDone,
                           Int_t parentID,
                           Int_t pdgCode,
                           Double_t px,
                           Double_t py,
                           Double_t pz,
                           Double_t e,
                           Double_t vx,
                           Double_t vy,
                           Double_t vz,
                           Double_t time,
                           Double_t polx,
                           Double_t poly,
                           Double_t polz,
                           TMCProcess proc,
                           Int_t& ntr,
                           Double_t weight,
                           Int_t is,
                           Int_t secondParentId);

    /** Get next particle for tracking from the stack.
     ** Declared in TVirtualMCStack
     *@param  iTrack  index of popped track (return)
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopNextTrack(Int_t& iTrack);

    /** Get primary particle by index for tracking from stack
     ** Declared in TVirtualMCStack
     *@param  iPrim   index of primary particle
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopPrimaryForTracking(Int_t iPrim);

    /** Set the current track number
     ** Declared in TVirtualMCStack
     *@param iTrack  track number
     **/
    virtual void SetCurrentTrack(Int_t iTrack) { fCurrentTrack = iTrack; }

    /** Get total number of tracks
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetNtrack() const { return fNParticles; }

    /** Get number of primary tracks
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetNprimary() const { return fNPrimaries; }

    /** Get the current track's particle
     ** Declared in TVirtualMCStack
     **/
    virtual TParticle* GetCurrentTrack() const;

    /** Get the number of the current track
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetCurrentTrackNumber() const;   // { return fCurrentTrack; }

    /** Get the track number of the parent of the current track
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetCurrentParentTrackNumber() const;

    /** Add a TParticle to the fParticles array **/
    virtual void AddParticle(TParticle* part);

    /** Fill the MCTrack output array, applying filter criteria **/
    virtual void FillTrackArray();

    /** Update the track index in the MCTracks and MCPoints **/
    virtual void UpdateTrackIndex(TRefArray* detArray = 0);

    /** Resets arrays and stack and deletes particles and tracks **/
    virtual void Reset();

    /** Register the MCTrack array to the Root Manager  **/
    virtual void Register();

    /** Output to screen
     **@param iVerbose: 0=events summary, 1=track info
     **/
    virtual void Print(Option_t*) const;

    /** Modifiers  **/
    void StoreSecondaries(Bool_t choice = kTRUE) { fStoreSecondaries = choice; }
    void SetMinPoints(Int_t min) { fMinPoints = min; }
    void SetEnergyCut(Double_t eMin) { fEnergyCut = eMin; }
    void StoreMothers(Bool_t choice = kTRUE) { fStoreMothers = choice; }

    /** Increment number of points for the current track in a given detector
     *@param iDet  Detector unique identifier
     **/
    void AddPoint(DetectorId iDet);

    /** Increment number of points for an arbitrary track in a given detector
     *@param iDet    Detector unique identifier
     *@param iTrack  Track number
     **/
    void AddPoint(DetectorId iDet, Int_t iTrack);

    /** Accessors **/
    TParticle* GetParticle(Int_t trackId) const;
    TClonesArray* GetListOfParticles() { return fParticles; }

    void SetParticleArray(TClonesArray* partArray)
    {
        for (Int_t ipart = 0; ipart < partArray->GetEntries(); ipart++) {
            ((TParticle*)(partArray->At(ipart)))->SetUniqueID(fNPrimaries);
            fStack.push((TParticle*)partArray->At(ipart));
            AddParticle((TParticle*)partArray->At(ipart));
            fNParticles++;
            fNPrimaries++;
        }
    }

    void SetParticleArray(TClonesArray* partArray, Int_t partFrom, Int_t partTo)
    {
        for (Int_t ipart = partFrom; ipart < partTo; ipart++) {
            ((TParticle*)(partArray->At(ipart)))->SetUniqueID(fNPrimaries);
            ((TParticle*)(partArray->At(ipart)))->SetStatusCode(fNPrimaries);
            fStack.push((TParticle*)partArray->At(ipart));
            AddParticle((TParticle*)partArray->At(ipart));
            fNParticles++;
            fNPrimaries++;
        }
    }

    /** Clone this object (used in MT mode only) */
    virtual FairGenericStack* CloneStack() const
    {
        FairStack* clonedStack = new FairStack();
        clonedStack->StoreSecondaries(fStoreSecondaries);
        clonedStack->SetMinPoints(fMinPoints);
        clonedStack->SetEnergyCut(fEnergyCut);
        clonedStack->StoreMothers(fStoreMothers);
        return clonedStack;
    }

  private:
    /** STL stack (FILO) used to handle the TParticles for tracking **/
    std::stack<TParticle*> fStack;   //!

    /** Array of TParticles (contains all TParticles put into or created
     ** by the transport
     **/
    TClonesArray* fParticles;   //!

    /** Array of FairMCTracks containg the tracks written to the output **/
    TClonesArray* fTracks;

    /** STL map from particle index to storage flag  **/
    std::map<Int_t, Bool_t> fStoreMap;              //!
    std::map<Int_t, Bool_t>::iterator fStoreIter;   //!

    /** STL map from particle index to track index  **/
    std::map<Int_t, Int_t> fIndexMap;              //!
    std::map<Int_t, Int_t>::iterator fIndexIter;   //!

    /** STL map from track index and detector ID to number of MCPoints **/
    std::map<std::pair<Int_t, Int_t>, Int_t> fPointsMap;   //!

    /** Some indizes and counters **/
    Int_t fCurrentTrack;   //! Index of current track
    Int_t fNPrimaries;     //! Number of primary particles
    Int_t fNParticles;     //! Number of entries in fParticles
    Int_t fNTracks;        //! Number of entries in fTracks
    Int_t fIndex;          //! Used for merging

    /** Variables defining the criteria for output selection **/
    Bool_t fStoreSecondaries;
    Int_t fMinPoints;
    Double32_t fEnergyCut;
    Bool_t fStoreMothers;

    /** Mark tracks for output using selection criteria  **/
    void SelectTracks();

    FairStack(const FairStack&);
    FairStack& operator=(const FairStack&);

    ClassDef(FairStack, 1);
};

#endif
