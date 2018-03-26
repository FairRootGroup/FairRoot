/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairIonGenerator header file                 -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**
 * 24.10.07  implement constructor with ion name. M. Al-Turany
*/

#ifndef FAIRIONGENERATOR_H
#define FAIRIONGENERATOR_H

#include "FairGenerator.h"              // for FairGenerator

#include "Rtypes.h"                     // for Double_t, Int_t, etc

class FairIon;
class FairPrimaryGenerator;

class FairIonGenerator : public FairGenerator
{

  public:

    /** Default constructor **/
    FairIonGenerator();


    /** Constructor with ion name
      ** For the generation of ions with pre-defined FairIon
     ** By default, the  excitation energy is zero. This can be changed with the
     ** respective modifiers.
     **@param ionName  Ion name
     **@param mult      Number of ions per event
     **@param px,py,pz  Momentum components [GeV] per nucleon!
     **@param vx,vy,vz  Vertex coordinates [cm]
     **/
    FairIonGenerator(const Char_t* ionName, Int_t mult, Double_t px,
                     Double_t py, Double_t pz,  Double_t vx = 0,
                     Double_t vy = 0, Double_t vz = 0);


    /** Default constructor
     ** For the generation of ions with atomic number z and mass number a.
     ** By default, the mass equals a times the proton mass and the
     ** excitation energy is zero. This can be changed with the
     ** respective modifiers.
     **@param z         Atomic number
     **@param a         Atomic mass
     **@param q         Electric charge [e]
     **@param mult      Number of ions per event
     **@param px,py,pz  Momentum components [GeV] per nucleon!
     **@param vx,vy,vz  Vertex coordinates [cm]
     **/
    FairIonGenerator(Int_t z, Int_t a, Int_t q, Int_t mult, Double_t px,
                     Double_t py, Double_t pz,  Double_t vx = 0,
                     Double_t vy = 0, Double_t vz = 0);


    /** Destructor **/
    virtual ~FairIonGenerator();


    /** Modifiers **/
    void SetCharge(Int_t charge) {fQ=charge;}
    void SetExcitationEnergy(Double_t eExc);
    void SetMass(Double_t mass);


    /** Method ReadEvent
     ** Generates <mult> of the specified ions and hands hem to the
     ** FairPrimaryGenerator.
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

    /** Clone this object (used in MT mode only) */
    virtual FairGenerator* CloneGenerator() const;

  private:

    static Int_t fgNIon;     //! Number of the instance of this class
    Int_t    fMult;          // Multiplicity per event
    Double_t fPx, fPy, fPz;  // Momentum components [GeV] per nucleon
    Double_t fVx, fVy, fVz;  // Vertex coordinates [cm]
    FairIon*   fIon;          // Pointer to the FairIon to be generated
    Int_t    fQ;    // Electric charge [e]

    FairIonGenerator(const FairIonGenerator&);
    FairIonGenerator& operator=(const FairIonGenerator&);

    ClassDef(FairIonGenerator,1)

};


#endif


