/*
 * FairBaseMCGenerator.h
 *
 *  Created on: 16 mar 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRBASEMCGENERATOR_H_
#define FAIRBASEMCGENERATOR_H_

#include "FairGenerator.h"

/**
 * abstract class for generators that use user input to generate partcles
 */
class FairBaseMCGenerator : public FairGenerator{
public:
	enum eVertexSmear{
		kBox,
		kGauss,
		kExp
	};
	FairBaseMCGenerator();
	FairBaseMCGenerator(const FairBaseMCGenerator &other);
	FairBaseMCGenerator& operator=(const FairBaseMCGenerator &rhs);
	/**
	 * set PDG code of generated particles
	 * @param pdg
	 */
	void SetPDGType(Int_t pdg);
	/**
	 * set vertex position and algorithm of vertex generation
	 * @param vx, vy, vz Vertex coordinates [cm]
	 * @param evx, evy, evz Vertex dispersion [cm]
	 * @param sm distribution of vertex, gaussian or box
	 */
	void SetVertex(Double_t vx, Double_t vy, Double_t vz,
			Double_t evx=0, Double_t evy=0, Double_t evz=0, eVertexSmear sm = kBox);
	/**
	 * set number of particles per event
	 * @param mult
	 */
    void SetMultiplicity(Int_t mult){fMult = mult;};
    virtual Bool_t Init();
	virtual ~FairBaseMCGenerator();
protected:
	Int_t GetPDGType()const{return fPDGType;};
	Int_t GetMultiplicity()const{return fMult;};
	Double_t GetPDGMass()const{return fPDGMass;};
	/**
	 * generate event parameters like current event
	 */
	void GenerateEventParameters();
    Double32_t fX, fY, fZ;           // current vertex coordinates [cm]
private:
    Int_t fPDGType;	// Particle type (PDG encoding)
	Int_t fMult;			//Multiplicity;
	eVertexSmear fVertexSmear;
	Double_t fPDGMass;
	Double_t fVx, fVy,fVz;
	Double_t fVex, fVey, fVez;
	ClassDef(FairBaseMCGenerator,1)
};

#endif /* FAIRBASEMCGENERATOR_H_ */
