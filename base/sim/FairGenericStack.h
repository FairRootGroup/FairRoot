/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairGenericStack header file            -----
// -----           Created 10/08/04  by D. Bertini                     -----
// -------------------------------------------------------------------------


/** FairGenericStack.h
 *@author D.Bertini <d.bertini@gsi.de>
 * Generic MC stack class
 **/


#ifndef FAIRGENERICSTACK_H
#define FAIRGENERICSTACK_H

#include "TClonesArray.h" 
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TMCProcess.h"                 // for TMCProcess

#include <stddef.h>                     // for NULL

class FairLogger;
class TParticle;
class TRefArray;
class TIterator;


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
     ** This function has an extra argument wrt to the function defined in the base class.
     *@param toBeDone         Flag for tracking
     *@param parentID         Index of mother particle
     *@param pdgCode          Particle type (PDG encoding)
     *@param px,py,pz         Momentum components at start vertex [GeV]
     *@param e                Total energy at start vertex [GeV]
     *@param vx,vy,vz         Coordinates of start vertex [cm]
     *@param time             Start time of track [s]
     *@param polx,poly,polz   Polarisation vector
     *@param proc             Production mechanism (VMC encoding)
     *@param ntr              Track number (filled by the stack)
     *@param weight           Particle weight
     *@param is               Generation status code (whatever that means)
     *@param secondparentID   used fot the index of mother of primery in the list
     **/
    virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                           Double_t px, Double_t py, Double_t pz,
                           Double_t e, Double_t vx, Double_t vy,
                           Double_t vz, Double_t time, Double_t polx,
                           Double_t poly, Double_t polz, TMCProcess proc,
                           Int_t& ntr, Double_t weight, Int_t is, Int_t secondparentID) = 0;


    /** Fill the MCTrack output array, applying filter criteria **/
    virtual void FillTrackArray() {}


    /** Update the track index in the MCTracks and MCPoints **/
    virtual void UpdateTrackIndex(TRefArray* detArray=0) {}


    /** Set the list of detectors to be used for filltering the stack*/
    void SetDetArrayList(TRefArray* detArray);

    /** Allow a stack to perform a clean-up after a primary particle is finished **/
    virtual void FinishPrimary() {}

    /** Resets arrays and stack and deletes particles and tracks **/
    virtual void Reset() {}

    /** Register the MCTrack array to the Root Manager  **/
    virtual void Register() {}

    virtual TClonesArray* GetListOfParticles() { return 0; }

    /** Clone this object (used in MT mode only) */
    virtual FairGenericStack* CloneStack() const;

  protected:
    /** Copy constructor */
    FairGenericStack(const FairGenericStack&);
    /** Assignment operator */
    FairGenericStack& operator=(const FairGenericStack&);

    /** Fair Logger */
    FairLogger*  fLogger;//!

    /** List of detectors registering hits in the simulation */
    TRefArray*  fDetList;  //!

    /** Iterator for the detector list*/
    TIterator* fDetIter;

    /**Verbosity level*/
    Int_t fVerbose;

    ClassDef(FairGenericStack,1)
};

#endif
