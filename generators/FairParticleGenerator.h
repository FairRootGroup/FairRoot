// -------------------------------------------------------------------------
// -----                FairParticleGenerator header file               -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**  FairParticleGenerator.h
 *@author V.Friese  <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *
 The FairParticleGenerator generates a single particle type with given
 momentum components, vertex and multiplicity per event.
 Derived from FairGenerator.
**/


#ifndef FAIR_PARTICLEGENERATOR_H
#define FAIR_PARTICLEGENERATOR_H


#include "FairGenerator.h"

class FairPrimaryGenerator;



class FairParticleGenerator : public FairGenerator
{

  public:

    /** Default constructor. **/
    FairParticleGenerator();


    /** Constructor with PDG-ID, multiplicity and momentum
     ** (optionally vertex)
     **@param pdgid Particle type (PDG encoding)
     **@param mult  Multiplicity
     **@param px,py,pz Momentum components [GeV]
     **@param vx,vy,vz Vertex coordinates [cm], Default (0,0,0)
     **/
    FairParticleGenerator(Int_t pdgid, Int_t mult, Double32_t px,
                          Double32_t py, Double32_t pz, Double32_t vx = 0.,
                          Double32_t vy = 0., Double32_t vz = 0.);


    /** Destructor **/
    virtual ~FairParticleGenerator() {};



    /** Modifiers **/
    void SetPDGType(Int_t pdg)       {fPDGType = pdg;  };
    void SetMultiplicity(Int_t mult) {fMult    = mult; };
    void SetMomentum(Double32_t px, Double32_t py, Double32_t pz);
    void SetVertex(Double32_t vx, Double32_t vy, Double32_t vz);


    /** Creates an event with given type and multiplicity.
     **@param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    Int_t      fPDGType;       // Particle type (PDG encoding)
    Int_t      fMult;          // Multiplicity
    Double32_t fPx, fPy, fPz;  // Momentum components [GeV]
    Double32_t fVx, fVy, fVz;  // Vertex coordinates [cm]


    ClassDef(FairParticleGenerator,1);

};


#endif


