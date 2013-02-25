// -------------------------------------------------------------------------
// -----                 FairPlutoGenerator header file                 -----
// -----          Created 13/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/** FairPlutoGenerator.h
 *@author V.Friese <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *
 The FairPlutoGenerator reads the PLUTO output file (ROOT format)
 and inserts the tracks into the FairStack via the FairPrimaryGenerator.
 Derived from FairGenerator.
**/


#ifndef FAIR_PLUTOGENERATOR_H
#define FAIR_PLUTOGENERATOR_H


#include "FairGenerator.h"

class TClonesArray;
class TFile;
class TTree;
class TVirtualMCStack;
class FairPrimaryGenerator;



class FairPlutoGenerator : public FairGenerator
{

  public:

    /** Default constructor (should not be used) **/
    FairPlutoGenerator();


    /** Standard constructor
     ** @param fileName The input (PLUTO) file name
     **/
    FairPlutoGenerator(const Char_t* fileName);


    /** Destructor **/
    virtual ~FairPlutoGenerator();


    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    Int_t iEvent;      //! Event number
    const Char_t* fFileName;   //! Input file name
    TFile* fInputFile;        //! Pointer to input file
    TTree* fInputTree;        //! Pointer to input tree
    TClonesArray* fParticles;  //! Particle array from PLUTO

    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();

    FairPlutoGenerator(const FairPlutoGenerator&);
    FairPlutoGenerator& operator=(const FairPlutoGenerator&);

    ClassDef(FairPlutoGenerator,1);

};

#endif
