// -------------------------------------------------------------------------
// -----             FairPlutoReactionGenerator header file            -----
// -----          Created 05/07/08  by I. Froehlich                    -----
// -------------------------------------------------------------------------

/** FairPlutoReactionGenerator.h
 *@author I. Froehlich
 *
 The FairPlutoReactionGenerator inserts an inline PReaction
 and thus connects Pluto with the FairPrimaryGenerator.
 Derived from FairGenerator.
**/


#ifndef FAIR_PLUTOREACTIONGENERATOR_H
#define FAIR_PLUTOREACTIONGENERATOR_H


#include "FairGenerator.h"

class TClonesArray;
class TFile;
class TTree;
class TVirtualMCStack;
class FairPrimaryGenerator;

#include "PUtils.h"
/** Backward compatibility **/
#ifdef PLUTOVERSION_FOR_FAIR
#include "PFairGenerator.h"
#include "PReaction.h"
#else
class PReaction;
#endif


class FairPlutoReactionGenerator : public FairGenerator
{

  public:

    /** Default constructor (should not be used) **/
    FairPlutoReactionGenerator();


    /** Standard constructor
     ** @param reaction Pointer to PLUTO inline reaction
     **/
    FairPlutoReactionGenerator(PReaction* reaction);


    /** Destructor **/
    virtual ~FairPlutoReactionGenerator();


    /** Reads on event from the Pluto reaction and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    Int_t iEvent;      //! Event number
#ifdef PLUTOVERSION_FOR_FAIR
    PFairGenerator* fPlutoFairGenerator; //!Pointer to interface
#endif
    PReaction* fReaction;     //! Pointer to the Pluto inline reaction

    FairPlutoReactionGenerator(const FairPlutoReactionGenerator&);
    FairPlutoReactionGenerator operator=(const FairPlutoReactionGenerator&);

    ClassDef(FairPlutoReactionGenerator,1);

};

#endif
