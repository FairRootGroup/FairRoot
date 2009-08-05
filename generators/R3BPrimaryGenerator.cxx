/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Marc Labiche		labi-ph0@paisley.ac.uk
//	       Oleg Kiselev		O.Kiselev@gsi.de
//             Hector Alvarez-Pol       hapol@fpddux.usc.es
//             Saúl Beceiro             saul.beceiro@rai.usc.es
//             Denis Bertini            <D.Bertini@gsi.de>
//*-- Date: 08/2009
//*-- Last Update: 03/08/2009 <D.Bertini@gsi.de>
// --------------------------------------------------------------
// Description:
//   Event generator interface for R3B
//
// --------------------------------------------------------------
// Comments:
//   - 03/08/09 Adapting to R3Broot event generator factory
//     <D.Bertini@gsi.de>
//
//   - 11/04/08 Adding a methode to do back tracking momentum
//     reconstruction. Positions after magnet are taken to give
//     initial trajectories.
//   - 05/01/06 Adding a simple primary particle for testing
//   - 27/01/05 Cleaning and improving calculations
//   - 25/11/04 Created based on example/novice/N01 structure
// 
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "FairPrimaryGenerator.h"
#include "R3BPrimaryGenerator.h"
#include "R3BBeamInfo.h"
#include "TRandom.h"

#include "FairRunSim.h"
#include "FairIon.h"
#include "R3BBackTrackingStorageState.h"

R3BPrimaryGenerator::R3BPrimaryGenerator()
  :gammasFlag("off"),decaySchemeFlag("off"),reactionFlag("off"),reactionType("Elas"),
   dissociationFlag("off"), backTrackingFlag("off"),beamInteractionFlag("off"),rndmFlag("off"),
   rndmEneFlag("off"),boostFlag("off"),fPDGType(2212),
    simEmittanceFlag("off"),sigmaXInEmittance(10),sigmaXPrimeInEmittance(0.001),
    fPDGMass(0.),fMult(1),fP(0.),fPdir(0.,0.,1.),fCharge(0),fPol(0.,0.,0.),
    fPos(0.,0.,0.),fTime(0.) {

  //
  // Constructor: init values are filled
  //  


  //Initial Values
  TVector3 zero;
  kinEnergyPrim = 1e-03;      // GeV - kinetic energy of the primary
  meanKinEnergyBeam = 700. * 1e-03;// GeV - kinetic energy mean of the beam (per nucleon)
  sigmaKinEnergyBeam = 1.e-03 ; // GeV - kinetic energy sigma of the beam
  
  Int_t n_particle = 1;

  //init value for targets (final values come from ROOT Macros)
  targetType = "Parafin0Deg";
  targetHalfThicknessPara =(0.11/2.)/10.; // cm
  targetThicknessLiH = 3.5;  // cm
  targetRadius = 1.;   // cm


  cout << "-I- R3BPrimaryGenerator::R3BPrimaryGenerator() Ion Defs... " << endl;

  // Define the ion for CD
  Char_t buffer[20];
  sprintf(buffer, "FairIon%d", 99);
  Int_t z = 14;
  Int_t a = 26;
  Int_t q = 14;
  FairIon* fIon= new FairIon(buffer, z, a, q);
  FairRunSim* run = FairRunSim::Instance();
  if ( ! run ) {
    cout << "-E- R3BPrimaryGenerator: No FairRun instantiated!" << endl;
    Fatal("R3BPrimaryGenerator", "No FairRun instantiateed!");
  }
  // - add the Ion definition
  run->AddNewIon(fIon);

 }

R3BPrimaryGenerator::~R3BPrimaryGenerator() {
  //
  // Simple destructor
  //
}

void R3BPrimaryGenerator::Init()
{
  Int_t verboselevel;
 // Set User setting
  cout <<  "-I- R3BPrimaryGenerator::Init() -> Set User Settings ..." << endl;
  PrintParameters();

  // reading now the input files

  cout << " -I- R3BPrimaryGenerator::Init() ->  Reading Kinematics  ... " << endl;
  pReadKinematics = new R3BReadKinematics();
  cout << " -I- R3BPrimaryGenerator::Init() ->  Coulomb Dissocation Loaded ..." << endl;
  pCDGenerator = new R3BCDGenerator();
  cout << " -I- R3BPrimaryGenerator::Init() ->  Back Tracking loaded ...  " << endl;
  pBackTrackingGenerator = new R3BBackTracking();
  
 // Check for User Particle type
  TDatabasePDG* pdgBase = TDatabasePDG::Instance();
  TParticlePDG *particle = pdgBase->GetParticle(fPDGType);
  if (! particle){
      Fatal("R3BPrimaryGenerator","PDG code %d not defined.",fPDGType);

  } else {
      fPDGMass = particle->Mass();
      cout << " -I- R3BGenerator PDG Particle defined: " << fPDGType
	  << " Mass: " << fPDGMass << endl;
  }

}

// ------------------------------------------------------------------------
Bool_t R3BPrimaryGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
  Int_t verboseLevel=0;

  // Particle Multiplicity
 for (Int_t ll = 0 ; ll < fMult; ll++ ) {

  // -- Beam Info class
  R3BBeamInfo* localBeamInfo = new R3BBeamInfo();

  // -- Use this rotation matrix to change the particle
  //    momentum due to the beam emittance
  TRotation rotMomenta;

  // -- Use this parameters for the vertex position
    Double_t x0=0.,y0=0.,z0=0.;
    Double_t theta0=0.,phi0=0.;


  // --  Emittance  Flag  test

  if(simEmittanceFlag == "on") {
       Double_t radi;
       Double_t angleRandom;
       do {
	   radi= TMath::Abs(gRandom->Gaus(0.,sigmaXInEmittance));
	   angleRandom= gRandom->Uniform(0.,2*TMath::Pi());
	   x0= radi*TMath::Cos(angleRandom);
	   y0= radi*TMath::Sin(angleRandom);
       }while(radi>3*sigmaXInEmittance  || radi<-3*sigmaXInEmittance);

       //here a connection with the target maximum radius would be needed
       //to avoid reactions outside the target!!

       do {
	   theta0= TMath::Abs(gRandom->Gaus(0.,sigmaXPrimeInEmittance));
	   phi0= gRandom->Uniform(0.,2*TMath::Pi());
       }while( theta0>3*sigmaXPrimeInEmittance ||
	      theta0<-3*sigmaXPrimeInEmittance);

       localBeamInfo->SetVertexPosition(x0,y0,z0);
       localBeamInfo->SetAngles(theta0,phi0);

       //Now, we have the incident beam parameters... use the position (x0,y0)
       //mixed with any z0 calculated from the beam interaction with the target
       //For the angles, transform the output particles momentum according to
       //the (already normalized) components of the incoming momentum
       // <D.Bertini@gsi.de >
       // - choosing a convention for Euler Angles
       // - Using the Landau convention for
       // - Euler Rotation (1:Z,2:X,3:Y)
       rotMomenta = rotMomenta.RotateXEulerAngles( phi0,theta0,-phi0 );

  } //! Emittance (on)


  //------------------------------------------------------------------------------------------
  //                              Reaction Generator
  //------------------------------------------------------------------------------------------

  if(reactionFlag=="on"){
  // --- Reactions definition
    Double_t targetThicknessPara  = targetHalfThicknessPara*2.;
    
    Double_t particle_energy = 50.; // keep MeV for Xsection
    
    Double_t momentum_x = 1.;
    Double_t momentum_y = 0.;
    Double_t momentum_z = 1.5;
    
    x0=4.;
    y0=0.;
    z0=-2.;
    
    Double_t MaxEnergy = 400.; // keep Mev for XSection
    Double_t	LabParticleAngle = 85.0;
    LabParticleAngle = LabParticleAngle * TMath::Pi() / 180.;
    
    Double_t phi= 0. ;
    Int_t i;

  // --- Reaction types

    // ----  Elastic scattering type
    if (reactionType == "Elas") {
       // Define energy from the kinematics - flat cross section
      for(i=0;i<1000;i++) {
	if(i > 0 && (pReadKinematics->LabEnergy[i]) == 0. && 
	   (pReadKinematics->LabEnergy[i-1]) != 0. ) {
	  MaxEnergy = (pReadKinematics->LabEnergy[i-1]);
	}
      }//!for (i)
      particle_energy = gRandom->Uniform(0.,MaxEnergy);
      
      // Define energy from the kinematics - real cross section
      Double_t T_min = 0.076;      // Keep MeV : T minimum 40 MeV
      Double_t T_max = 0.75;       // Keep MeV : T maximum
      Int_t Bin_min = 0;
      Int_t Bin_max = 0;
      Int_t Nbin = 0;
      
      for(i=0;i<5000;i++) {
	if((pReadKinematics->T_xsec[i]) > 0 && 
	   (pReadKinematics->T_xsec[i]) < T_min) {
	  Bin_min = i;
	}
	if((pReadKinematics->T_xsec[i]) > 0 && 
	   (pReadKinematics->T_xsec[i]) < T_max) {
	  Bin_max = i;
	}
      }//! for (i)

      //cout << "Bin_min " << Bin_min << "Bin_max " << Bin_max << endl;
      
      // Define the energy (in t units) from the
      // normalized and inversed cross section
      Double_t probability = 0.;
      probability = gRandom->Rndm();
      
      while( probability < (pReadKinematics->Icross_section[Bin_min]) || 
	     probability > (pReadKinematics->Icross_section[Bin_max]) ) {
	probability = gRandom->Rndm();
      }//! while (proba)
      
      for(i=0;i<5000;i++) {
	if( (pReadKinematics->Icross_section[i]) > 0 && 
	    probability > (pReadKinematics->Icross_section[i]) ) {
	  //cout << "i " << i << " probability " << probability << " Icross_section " <<
	  //pReadKinematics->Icross_section[i] << endl;
	  Nbin =	i;
	}
      }//! for(i)

      //cout << "NBin " << Nbin << endl;
      
      particle_energy = (pReadKinematics->T_xsec[Nbin]);  // in MeV
      //cout <<  " New particle_energy " << particle_energy<< endl;
      
      //Additional smearing to avoid discrete energies
      for(i=Bin_min;i<Bin_max+1;i++) {
	if( particle_energy == (pReadKinematics->T_xsec[i]) ) {
	  particle_energy = particle_energy + (gRandom->Rndm() - 0.5) *
	    ( (pReadKinematics->T_xsec[i+1]) - (pReadKinematics->T_xsec[i-1]) );
	}
      }//! for(i)

      // Proton energy - in MeV
      particle_energy = particle_energy / 2. / 0.938272 * 1000.;
      //cout <<"particle_energy MeV "<< particle_energy<< endl;
      
      for(i=0;i<1000;i++) {
	if(particle_energy > (pReadKinematics->LabEnergy[i-1]) &&
	   particle_energy < (pReadKinematics->LabEnergy[i])) {
	  LabParticleAngle = (particle_energy - (pReadKinematics->LabEnergy[i-1]))/
	    ((pReadKinematics->LabEnergy[i]) - (pReadKinematics->LabEnergy[i-1])) *
	    ((pReadKinematics->LabAngle[i]) - (pReadKinematics->LabAngle[i-1])) +
	    (pReadKinematics->LabAngle[i-1]);
	}
      }//! for(i)
      
      LabParticleAngle = LabParticleAngle * TMath::Pi() / 180.;
      
      phi = gRandom->Uniform(0,2*TMath::Pi());
      
      // momentum_x = sin(LabParticleAngle);
      momentum_x = TMath::Sin(LabParticleAngle)*TMath::Cos(phi);
      momentum_y = TMath::Sin(LabParticleAngle)*TMath::Sin(phi);
      momentum_z = TMath::Cos(LabParticleAngle);
      
      x0=0.;
      y0=0.;
      z0=0.;
    } // ! Reaction type "Elastic"
    
    
    //--- Isotropic proton source
    if (reactionType == "iso") {
      //Double_t aperture =180; // isotropic
      Double_t aperture = 90.; // semi-isotropic
      Double_t theta = 0. ;
      
      // source position
      x0 = 0.;
      y0 = 0.;
      z0 = 0.;
      
      if(aperture > 0.) {
	  theta = TMath::ACos(1.+(TMath::Cos(aperture/180.*TMath::Pi())-1.)
			      *gRandom->Rndm());
	phi = gRandom->Uniform(0.,2*TMath::Pi());
	//         cout << "pi = " << pi << endl;
	//         cout << "twopi   = " << twopi   << endl;
      }
      
      momentum_x = TMath::Sin(theta)*TMath::Cos(phi);
      momentum_y = TMath::Sin(theta)*TMath::Sin(phi);
      momentum_z = TMath::Cos(theta);
      
      particle_energy=MaxEnergy*gRandom->Rndm(); // 0-400 MeV
      LabParticleAngle = theta;
      //cout << "i= " << i << endl;
      //cout << "Energy in= " << particleGun->GetParticleEnergy() << endl;
      //cout << "theta = " << theta << endl;
      //cout << "phi   = " << phi   << endl;  
    } // ! Reaction "Iso"
    
    // --- Transfer Reaction
    if (reactionType == "Trans") {
      // Polar angle:
      // Random number between 0 and 1
      Double_t theta=0.;
      Double_t NRJ=0.;
      Double_t randnum = 0.;
      Double_t slop1=0.,slop2=0.,offset1=0.,offset2=0.;
      
      randnum = gRandom->Rndm();
      
      for(Int_t i=0;i<181;i++) {
        
	if(randnum>=pReadKinematics->Icross_section[i] && 
	   randnum<pReadKinematics->Icross_section[i+1]) {
	  slop1=(pReadKinematics->LabAngle[i+1]-
		 pReadKinematics->LabAngle[i])/(pReadKinematics->Icross_section[i+1]-
						pReadKinematics->Icross_section[i]);
	  offset1= pReadKinematics->LabAngle[i]-
	    slop1*pReadKinematics->Icross_section[i];
	  theta=randnum*slop1+offset1;
	  
	  for(Int_t j=0; j<181; j++) {
	    if(theta>=pReadKinematics->LabAngle[j] && 
	       theta<pReadKinematics->LabAngle[j+1]) {
	      slop2=(pReadKinematics->LabEnergy[int(pReadKinematics->LabAngle[j+1])]-
		     pReadKinematics->LabEnergy[int(pReadKinematics->LabAngle[j])])/
		(pReadKinematics->LabAngle[j+1]-pReadKinematics->LabAngle[j]);
	      offset2= pReadKinematics->LabEnergy[int(pReadKinematics->LabAngle[j])]-
		slop2*pReadKinematics->LabAngle[j];

	      NRJ=theta*slop2+offset2; // Energy in MeV
	    }
	  }
	  
	  theta=theta*TMath::Pi()/180.;   // Polar angle in radian
	}
      }
      
      // Azimuthal angle:
      phi = gRandom->Uniform(0.,2*TMath::Pi());
      
      momentum_x = TMath::Sin(theta)*TMath::Cos(phi);
      momentum_y = TMath::Sin(theta)*TMath::Sin(phi);
      momentum_z = TMath::Cos(theta);
      
      particle_energy = NRJ;  // Energy in MeV
      LabParticleAngle = theta;  
    } //! Reaction Trans
    
    //
    if("Elas" == reactionType || "Trans" == reactionType) {
	Double_t FWHM  = 1.;
	Double_t sigma = FWHM/2.35;

	// ----  Lead target Definition
	if (targetType=="leadTarget") {
	    Double_t R;
	    Double_t teta;

	    while( x0>1.6  || y0>1.2 ||
		  x0<-1.6 || y0<-1.2 ) {
		R= TMath::Abs(gRandom->Gaus(0.,sigma));
		teta= gRandom->Uniform(0., 2*TMath::Pi());

		z0= gRandom->Rndm()*(0.008810) - (0.008810)/2;
		x0= R*TMath::Cos(teta);
		y0= R*TMath::Sin(teta);
	    }
	} // ! Lead Target

	// ----  unrotated PARAFIN target
	if (targetType=="Parafin0Deg") {
	    Double_t R;
	    R= TMath::Abs(gRandom->Gaus(0.,sigma));

	    while(R > targetRadius ) {
		R= TMath::Abs(gRandom->Gaus(0.,sigma));
	    }
	    Double_t teta;
	    teta= gRandom->Rndm() * 2*TMath::Pi();
	    z0= gRandom->Rndm()*(targetThicknessPara) - (targetThicknessPara)/2;
	    x0= R*TMath::Cos(teta);
	    y0= R*TMath::Sin(teta);
	} //! Parafin 0 deg

	// ----  rotated PARAFIN target
	if (targetType=="Parafin45Deg") {
	    Double_t TargetSizeX = 2.9;
	    Double_t TargetSizeY = 2.;
	    Double_t ParaPosZ = 0.;
	    Double_t anglerad = 45.* TMath::Pi()/180.;
	    Double_t GaussX = gRandom->Gaus(0.,sigma);
	    while( TMath::Abs(GaussX) >  ( TargetSizeX/2. * sin(anglerad) ) ) {
		GaussX= gRandom->Gaus(0.,sigma);
	    }

	    Double_t GaussY = gRandom->Gaus(0.,sigma);
	    while( TMath::Abs(GaussY) > TargetSizeY/2.) {
		GaussY= gRandom->Gaus(0.,sigma);
	    }

	    Double_t UnifZ = -GaussX + ParaPosZ
		- targetThicknessPara/2. + gRandom->Rndm()*targetThicknessPara;

	    x0= GaussX;
	    y0= GaussY;
	    z0= UnifZ;

	} //! Parafin 45 deg

	// ----  LiH Target
	if (targetType=="LiH") {
	    Double_t ThicknessMyl = 0.15*1./10.; // cm
	    Double_t RL;
	    RL= TMath::Abs(gRandom->Gaus(0.,sigma));
	    while(RL > targetRadius ) {
		RL= TMath::Abs(gRandom->Gaus(0.,sigma));
	    }

	    Double_t tetaL;
	    tetaL= gRandom->Uniform(0.,2*TMath::Pi());

	    z0= gRandom->Rndm() * ( targetThicknessLiH ) + ThicknessMyl;
	    x0= RL*TMath::Cos(tetaL);
	    y0= RL*TMath::Sin(tetaL);

	} //! LiH Target

    } //! ( Trans || Elas )

    // Adding Particle to Primary Stack
    Double_t fE=particle_energy/1000. + fPDGMass; // Etot_part in GeV!
    Double_t mom = TMath::Sqrt((fE*fE)+(fPDGMass*fPDGMass));

    Double_t px = mom * momentum_x;
    Double_t py = mom * momentum_y;
    Double_t pz = mom * momentum_z;

    Double_t fX = x0;
    Double_t fY = y0;
    Double_t fZ = z0;

    printf(" -I- R3BPrimaryGenerator : Pdg=%d, p=(%.2f, %.2f, %.2f) GeV, x=(%.1f, %.1f, %.1f) cm \n",
	     fPDGType, px, py, pz, fX, fY, fZ);

    // Add Particle in primary stack
    if ( primGen ){
    primGen->AddTrack(fPDGType, px, py, pz, fX, fY, fZ);
    }else{
       cout << "-E- R3BPrimaryGenerator , base class not defined " << endl;
       exit(0);
    }

  } //! Reaction Flag (on)

  //------------------------------------------------------------------------------------------
  //                              Gamma Generator
  //------------------------------------------------------------------------------------------

  else if(gammasFlag=="on"){
      //
      // Isotropic gamma emmiter for testing calorimeter
      // Particle definition (a "gamma" assign is here required as the default value
      // is changed to proton for compatibility with Marc code)

      // Check for particle type
      TDatabasePDG* pdgBase = TDatabasePDG::Instance();
      TParticlePDG *particle = pdgBase->GetParticle(fPDGType);
      if (! particle) Fatal("R3BPrimaryGenerator","PDG code %d not defined.",fPDGType);

      TVector3 direction;
      //Randomize in emission angle (if not, emission is normal to beam line)
      if (rndmFlag == "on")  {
	  Double_t theta = TMath::ACos(1-2*gRandom->Rndm());     //flat in cos(theta)
	  Double_t phi = 6.283185307  *gRandom->Rndm();   //flat in phi
	  direction = TVector3(TMath::Sin(theta)*TMath::Cos(phi),
			       TMath::Sin(theta)*TMath::Sin(phi),
			       TMath::Cos(theta));
      }
      else{
	  // parallel to beam line!!!!!
	  // direction = Vector(0,1,0); //parallel to beam line!!!!!
	  // Against the crystal centers for the MADRID TEST!!!
	  direction = TVector3(0.,0.,1.);
      }

      //
      //Energy of the emitted gamma
      //

      // Energy in GeV
      Double_t kinEnergyLAB = kinEnergyPrim; // Energy in GeV

      Int_t doNotBoost = 0; //this variable remove the boost for the noise
      //if a decayScheme with noise is used.
      //if a decay scheme is implemented, the information is here considered
      if(decaySchemeFlag == "on"){
	  //
	  // This is an example of how a decaying scheme enters in a simple way
	  // Still there are only one gamma per event and the scheme is fixed
	  // during compilation (both details should be solved in next future)
	  //
	  //The scheme corresponds to the 23O scheme, as was implemented for
	  //the miniball simulation during the preparation of S245

	  Double_t distribution = 183.*gRandom->Rndm();
	  if(distribution < 100.)       kinEnergyLAB = 3.199*1e-03;   //100% in GeV
	  else if(distribution < 146.)  kinEnergyLAB = 1.383*1e-03;   //46%  in GeV
	  else if(distribution < 147.6) kinEnergyLAB = 1.710*1e-03;   //1.6% in GeV

	  //in case of 10% noise, change the line above for the three lines below
	  //and change the shoot(0.,166.6) for a shoot(0.,183.) a few lines above
	  else if(distribution < 166.6) kinEnergyLAB = 2.601*1e-03;   //19% in GeV
	  else kinEnergyLAB = 4*gRandom->Rndm()*1e-03;  //around 10% of total gammas GeV
	  if(distribution > 166.6) doNotBoost = 1;

      }

      Double_t energyLAB = kinEnergyLAB + fPDGMass ;  // GeV
      //momentum module:  P^2 = E^2 - M^2 = (T + M)^2 - M^2
      Double_t momModuleLAB =
	  TMath::Sqrt(energyLAB*energyLAB -
		      fPDGMass*fPDGMass);  // GeV

      TVector3 momLAB(momModuleLAB*direction.X(),
		      momModuleLAB*direction.Y(),
		      momModuleLAB*direction.Z());

      //Randomize in energy...still not implemented
      if (rndmEneFlag == "on"){
	  //not yet implemented
	  cout << "rndmEneFlag: Not yet implemented" << endl;
      }

      //Lorentz boost
      if(boostFlag == "on" && !doNotBoost){
	  //atomic mass unit  or proton mass
	  //G4double amu = 931.494013 * MeV; // amu
	  //G4double amu = 938.2723 * MeV;     // approx. proton mass
	  Double_t amu = 0.;
	  fPDGType = 2212;
	  pdgBase->GetParticle(fPDGType);
	  TParticlePDG *particle = pdgBase->GetParticle(fPDGType);
	  if (! particle) Fatal("R3BPrimaryGenerator","PDG code %d not defined.",fPDGType);
	  amu = particle->Mass();  // Mass in GeV


	  //beta is obtained from the kinetic energy mean of the beam (T)
	  //As T = E - M    ->   beta^2 = 1 - M^2 / (T + M)^2
	  Double_t betasquared = 1. - (amu*amu) /
	      ((meanKinEnergyBeam+amu)*(meanKinEnergyBeam+amu));  // Energy in GeV

	  //TODO: Beam kinetic energy dispersion is not introduced yet for simplicity
	  TVector3 beta(0.,0.,sqrt(betasquared));

	  //momentum module in CM (equivalent calculation than previous in LAB)
	  Double_t momModuleCM = momModuleLAB;

	  //momentum in CM (equivalent calculation than previous in LAB)
	  TVector3 momCM = momLAB;

	  //total energy in CM (equivalent calculation than previous in LAB)
	  Double_t energyCM = energyLAB;

	  //Lorentz transformation Pz(lab) = gamma * Pz(cm) + gamma * beta * E
	  //As each Lorentz transformation can be performed sequencially,
	  //we can separate the gamma factor corresponding to each direction
	  momLAB = TVector3( (momCM.X() + beta.X()*energyCM) /
			    TMath::Sqrt(1-beta.X()*beta.X()),
			    (momCM.Y() + beta.Y()*energyCM) /
			    TMath::Sqrt(1-beta.Y()*beta.Y()),
			    (momCM.Z() + beta.Z()*energyCM) /
			    TMath::Sqrt(1-beta.Z()*beta.Z()));

	  //new LAB energy
	  energyLAB = TMath::Sqrt(momLAB.Mag2() +
				  particle->Mass()*particle->Mass()); //GeV

	  //Lab kinetic energy T = E - M = sqrt(P^2 + M^2) - M
	  kinEnergyLAB = energyLAB - particle->Mass(); // GeV

	  //output
	  if (verboseLevel >0){
	      cout << endl << "______________ INFO PRIMARY ____________"<< endl;
	      cout << " Primary particle: "<< particle->GetName()
		  << endl;
	      cout << " momCM (" << momCM.X() << ", " << momCM.Y() << ", "
		  << momCM.Z() << ") with module "
		  << momModuleCM << endl;
	      cout  << " kinEnergyCM "  << kinEnergyPrim
		  << endl;
	      cout  << " energyCM " << energyCM
		  << endl;
	      cout << " momLAB ("<< momLAB.X() << ", " << momLAB.Y() << ", "
		  << momLAB.Z() << ") with module "
		  << momLAB.Mag() << endl;
	      cout  << " kinEnergyLAB " << kinEnergyLAB
		  << endl;
	      cout  << " energyLAB " << energyLAB
		  << endl
		  <<          "________________________________________"
		  << endl;
	  }
      } //end of    if(boostFlag == "on"){
      else{
	  //output
	  if (verboseLevel >0){
	      cout << endl << "______________ INFO PRIMARY ____________"<< endl;
	      cout << " Primary particle: "<< particle->GetName()
		  << endl;
	      cout << " momLAB (" << momLAB.X() << ", " << momLAB.Y() << ", "
		  << momLAB.Z() << ") with module "
		  << momModuleLAB << endl;
	      cout << " kinEnergyLAB " << kinEnergyLAB
		  << endl;
	      cout << " energyLAB " << energyLAB
		  << endl;
	      cout << "There is no Lorentz boost requested"
		  << endl
		  <<          "________________________________________"
		  << endl;
	  }
      }

      if(beamInteractionFlag == "on") {
	  //Some beam parameters, still hardcoded
	  Double_t FWHM  = 1.;  //cm
	  Double_t sigma = FWHM/2.35; //cm

	  if (targetType=="leadTarget") {
	      Double_t R;
	      Double_t teta;
	      do {
		  R= TMath::Abs(gRandom->Gaus(0.,sigma));
		  teta= gRandom->Uniform(0., 2*TMath::Pi());

		  z0= gRandom->Rndm()*(0.008810) - (0.008810)/2.;
		  x0= R*TMath::Cos(teta);
		  y0= R*TMath::Sin(teta);
	      }while( x0>1.6 || y0>1.2 ||
		     x0<-1.6 || y0<-1.2 );
	  }

	  if (targetType=="Parafin0Deg") {      // unrotated PARAFIN target
	      Double_t R= TMath::Abs(gRandom->Gaus(0.,sigma));
	      while(R > targetRadius )
		  R= TMath::Abs(gRandom->Gaus(0.,sigma));

	      Double_t tarPhi = gRandom->Uniform(0., 2*TMath::Pi());
	      z0 = gRandom->Rndm()*(2.*targetHalfThicknessPara) - targetHalfThicknessPara;
	      x0 = R*TMath::Cos(tarPhi);
	      y0 = R*TMath::Sin(tarPhi);
	  }

	  if (targetType=="Parafin45Deg") {///  rotated PARAFIN target
	      Double_t TargetSizeX = 2.9;
	      Double_t TargetSizeY = 2.;
	      Double_t ParaPosZ = 0.;
	      Double_t anglerad = 45.* TMath::Pi()/180.;

	      Double_t GaussX = gRandom->Gaus(0.,sigma);
	      while( fabs(GaussX) >  ( TargetSizeX/2. * TMath::Sin(anglerad) ) )
		  GaussX= gRandom->Gaus(0.,sigma);

	      Double_t GaussY = gRandom->Gaus(0.,sigma);
	      while( TMath::Abs(GaussY) > TargetSizeY/2.)
		  GaussY= gRandom->Gaus(0.,sigma);

	      Double_t UnifZ = -GaussX + ParaPosZ
		  - targetHalfThicknessPara + gRandom->Rndm()*2.*targetHalfThicknessPara;

	      x0 = GaussX;
	      y0 = GaussY;
	      z0 = UnifZ;
	  }

	  if (targetType=="LiH") {//  LiH Target
	      Double_t ThicknessMyl = 0.15*1./10.;

	      Double_t RL= TMath::Abs(gRandom->Gaus(0.,sigma));
	      while(RL > targetRadius )
		  RL= TMath::Abs(gRandom->Gaus(0.,sigma));

	      Double_t tarPhi;
	      tarPhi = gRandom->Uniform(0., 2*TMath::Pi());
	      z0 = gRandom->Rndm() * ( targetThicknessLiH ) + ThicknessMyl;
	      x0 = RL*TMath::Cos(tarPhi);
	      y0 = RL*TMath::Sin(tarPhi);
	  }
      }

      // Adding to Primary Stack
      Double_t fE=kinEnergyLAB + fPDGMass; // Etot_part in GeV!
      Double_t mom = TMath::Sqrt((fE*fE)+(fPDGMass*fPDGMass));

      Double_t px = mom * momLAB.X();
      Double_t py = mom * momLAB.Y();
      Double_t pz = mom * momLAB.Z();

      Double_t fX = x0;
      Double_t fY = y0;
      Double_t fZ = z0;

      printf(" -I- RR3PrimaryGenerator :\
	     Pdg=%d, p=(%.2f, %.2f, %.2f) GeV, x=(%.1f, %.1f, %.1f) cm\n",
	     fPDGType, px, py, pz, fX, fY, fZ);

      // Add Particle in primary stack
      if ( primGen ){
	  primGen->AddTrack(fPDGType, px, py, pz, fX, fY, fZ);
      }else{
	  cout << "-E- R3BPrimaryGenerator , base class not defined " << endl;
	  exit(0);
      }

  }//end of photons for testing calorimeter


  //------------------------------------------------------------------------------------------
  //                              Coulomb Dissocation Generator (S. Typel )
  //------------------------------------------------------------------------------------------

  else if(dissociationFlag=="on"){ 

      pCDGenerator->ReadNewLine();
      // gives a verbosity levels?
      cout << "##################################################################"
	  << endl
	  << "#################  R3BCDGenerator::ReadNewLine() #################"
	  << endl;
      cout << "Energy/momentum of particle 1: " << pCDGenerator->GetE1() << ", "
	  << pCDGenerator->GetPx1() << ", " << pCDGenerator->GetPy1() << ", "
	  << pCDGenerator->GetPz1() << endl
	  << "Energy/momentum of particle 2: " << pCDGenerator->GetE2() << ", "
	  << pCDGenerator->GetPx2() << ", " << pCDGenerator->GetPy2() << ", "
	  << pCDGenerator->GetPz2() << endl;
      cout << "##################################################################"
	  << endl;


      if(simEmittanceFlag == "on") {
	  //applying a rotation to the emitted particles given by the beam parameters

	  //testing
	  /*
	   cout << endl << "##################################################################"<< endl
	   << "##########  Testing the emittance parameters (CoulDiss) ##########" << endl;
	   cout << " Proton momentum = (" << pCDGenerator->GetPx1() << ", "
	   << pCDGenerator->GetPy1() << ", "<< pCDGenerator->GetPz1() << ")" << endl;
	   cout << " Si momentum = (" << pCDGenerator->GetPx2() << ", "
	   << pCDGenerator->GetPy2() << ", "<< pCDGenerator->GetPz2() << ")" << endl << endl;
	   cout << " The rotation is:" << rotMomenta << endl;
	   */
	  //end of testing

	  TVector3 mom1( pCDGenerator->GetPx1(), pCDGenerator->GetPy1(), pCDGenerator->GetPz1() );
	  TVector3 mom2( pCDGenerator->GetPx2(), pCDGenerator->GetPy2(), pCDGenerator->GetPz2() );
	  TVector3 res1 = (rotMomenta * mom1);
	  TVector3 res2 = (rotMomenta * mom2);

	  pCDGenerator->SetPx1( res1.x() );
	  pCDGenerator->SetPy1( res1.y() );
	  pCDGenerator->SetPz1( res1.z() );
	  pCDGenerator->SetPx2( res2.x() );
	  pCDGenerator->SetPy2( res2.y() );
	  pCDGenerator->SetPz2( res2.z() );

	  //testing
	  /*
	   cout << " New proton momentum = (" << pCDGenerator->GetPx1() << ", "
	   << pCDGenerator->GetPy1() << ", "<< pCDGenerator->GetPz1() << ")" << endl;
	   cout << " New Si momentum = (" << pCDGenerator->GetPx2() << ", "
	   << pCDGenerator->GetPy2() << ", "<< pCDGenerator->GetPz2() << ")" << endl;
	   cout << "##################################################################" << endl << endl;
	   */
	  //end of testing
      }

      // first the proton
      fPDGType = 2212;
      TDatabasePDG* pdgBase = TDatabasePDG::Instance();
      TParticlePDG *particle = pdgBase->GetParticle(fPDGType);
      if (! particle) Fatal("R3bPrimaryGenerator","PDG code %d not defined.",fPDGType);


      // Adding Particles to Primary Stack

      //   1- Proton case
      Double_t fE=pCDGenerator->GetE1()/1000. + fPDGMass; // Etot_part in GeV!
      Double_t px = pCDGenerator->GetPx1()/1000.;
      Double_t py = pCDGenerator->GetPy1()/1000.;
      Double_t pz = pCDGenerator->GetPz1()/1000.;
      Double_t fX = x0;
      Double_t fY = y0;
      Double_t fZ = z0;

      printf(" -I- RR3PrimaryGenerator : \
	     Pdg=%d, p=(%.2f, %.2f, %.2f) GeV, x=(%.1f, %.1f, %.1f) cm\n",
	     fPDGType, px, py, pz, fX, fY, fZ);

      // Add Particle in primary stack
      if ( primGen ){
	  primGen->AddTrack(fPDGType, px, py, pz, fX, fY, fZ);
      }else{
	  cout << "-E- R3BPrimaryGenerator , base class not defined " << endl;
	  exit(0);
      }

      //   2- Ion case
      TParticlePDG* thisPart =
	  TDatabasePDG::Instance()->GetParticle("FairIon99");

      if ( ! thisPart ) {
	  cout << "-W- R3BPrimaryGenerator: Ion  FairIon99"
	      << " not found in database!" << endl;
	  return kFALSE;
      }

      Int_t pdgType = thisPart->PdgCode();

      fE=pCDGenerator->GetE2()/1000. + thisPart->Mass(); // Etot_part in GeV!
      px = pCDGenerator->GetPx2()/1000.;
      py = pCDGenerator->GetPy2()/1000.;
      pz = pCDGenerator->GetPz2()/1000.;

      fX = x0;
      fY = y0;
      fZ = z0;

      // Add Particle in primary stack
      if ( primGen ){
	  primGen->AddTrack(pdgType, px, py, pz, fX, fY, fZ);
      }else{
	  cout << "-E- R3BPrimaryGenerator , base class not defined " << endl;
	  exit(0);
      }

  } // ! CD

  //------------------------------------------------------------------------------------------
  //                               Momentum Reco. using Back Tracking
  //------------------------------------------------------------------------------------------

  else if(backTrackingFlag=="on"){

      //Set the ROOTAnalysis for doing backTracking
      // if(gR3BROOTAnalysis){
      //   gR3BROOTAnalysis->SetBackTrackingFlag("on");
      // }

      R3BBackTrackingStorageState* localptoStorageState=
	  new R3BBackTrackingStorageState();
      //   if(gR3BROOTAnalysis){
      //     localptoStorageState=gR3BROOTAnalysis->GetBackTrackingStorageState();
      //   }


      //    const G4int verboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
      //cout << endl << " ______ VerboseLevel  _______" <<verboseLevel<< endl;


      //particle definition
      // particleGun->SetNumberOfParticles(1);

      if(localptoStorageState->GetConverg()==1){
	  pBackTrackingGenerator->ReadNewLine();
      }

      if(verboseLevel >0) {
	  cout << "##################################################################"
	      << endl
	      << "#################  R3BBackTracking::ReadNewLine() #################"
	      << endl;
	  cout << "momentum of particle 1: " << localptoStorageState->GetPiter()*pBackTrackingGenerator->GetPx1() << ", "
	      <<  localptoStorageState->GetPiter()*pBackTrackingGenerator->GetPy1() << ", "
	      << localptoStorageState->GetPiter()*pBackTrackingGenerator->GetPz1() << endl;
	  cout << "initial position of particle 1: " << pBackTrackingGenerator->GetX1() << ", "
	      << pBackTrackingGenerator->GetY1() << ", "
	      << pBackTrackingGenerator->GetZ1() << endl;
	  cout << "##################################################################"
	      << endl;
      }

      // The proton definition
      fPDGType = 2212;
      TDatabasePDG* pdgBase = TDatabasePDG::Instance();
      TParticlePDG *particle = pdgBase->GetParticle(fPDGType);
      if (! particle) Fatal("R3bPrimaryGenerator","PDG code %d not defined.",fPDGType);

      //final settings for proton
      //Double_t fE=pBackTrackingGenerator->GetE1()/1000. + particle->Mass(); // Etot_part in GeV!

      Double_t px = (localptoStorageState->GetPiter()*pBackTrackingGenerator->GetPx1())  * 1./1000.;
      Double_t py = (localptoStorageState->GetPiter()*pBackTrackingGenerator->GetPy1())  * 1./1000.;
      Double_t pz = (localptoStorageState->GetPiter()*pBackTrackingGenerator->GetPy1())  * 1./1000.;

      Double_t fX = x0;
      Double_t fY = y0;
      Double_t fZ = z0;

      printf(" -I- RR3PrimaryGenerator : \
	     Pdg=%d, p=(%.2f, %.2f, %.2f) GeV, x=(%.1f, %.1f, %.1f) cm\n",
	     fPDGType, px, py, pz, fX, fY, fZ);

      // Add Particle in primary stack
      if ( primGen ){
	  primGen->AddTrack(fPDGType, px, py, pz, fX, fY, fZ);
      }else{
	  cout << "-E- R3BPrimaryGenerator , base class not defined " << endl;
	  exit(0);
      }

     // ReStore variables
      localptoStorageState->SetX0(pBackTrackingGenerator->GetX0());
      localptoStorageState->SetY0(pBackTrackingGenerator->GetY0());
      localptoStorageState->SetZ0(pBackTrackingGenerator->GetZ0());
      localptoStorageState->SetPPrim(pBackTrackingGenerator->GetPPrim());
  } // ! testing back tracking


  //------------------------------------------------------------------------------------------
  //                               No Option has been Given (dummy)
  //------------------------------------------------------------------------------------------

  else{
    cout << " -I- R3BPrimaryGenerator incomplete definition for the particle generation !... " << endl;
      exit(0);
  }


  }// ! Mutliplicity

}



void R3BPrimaryGenerator::PrintParameters()
{

  TString off("off");

  Int_t pdg_id  =   GetPrimPDGCode();
  if (pdg_id != 0 ) {
                   fPDGType = pdg_id ;
   }else {

     cout<<"-I- R3BPrimaryGenerator::Init() : no Primary Particle defined ! " << endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : assuming a Proton beam ... "<< endl;
  }

  // flags definitions

   TString flag = GetBeamInteractionFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(BeamInteraction) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(BeamInteraction) -> "<< flag.Data() << endl;
  }

   flag = GetRndmFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Rndm) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Rndm) -> "<< flag.Data() << endl;
  }

   flag = GetRndmEneFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Rndm) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Rndm) -> "<< flag.Data() << endl;
  }


   flag = GetBoostFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Boost) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Boost) -> "<< flag.Data() << endl;
  }


   flag =  GetReactionFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Reaction) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Reaction) -> "<< flag.Data() << endl;
  }


   flag = GetGammasFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Gammas) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Gammas) -> "<< flag.Data() << endl;
  }


   flag = GetDecaySchemeFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(DecayScheme) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(DecayScheme) -> "<< flag.Data() << endl;
  }


   flag = GetDissociationFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Dissociation) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(Dissociation) -> "<< flag.Data() << endl;
  }


   flag = GetBackTrackingFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(BackTracking) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(BackTracking) -> "<< flag.Data() << endl;
  }

   flag = GetSimEmittanceFlag() ;
  if ( flag.CompareTo(off) == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(SimEmittance) -> OFF"<< endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : FLAG(SimEmittance) -> "<< flag.Data() << endl;
  }

  // Target & Reaction type

  flag =  GetTargetType() ;
  if ( flag.CompareTo("") == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : TYPE(Target) -> not User defined! "<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : TYPE(Target) -> Parafin 0 Deg (Default) " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : TYPE(Target) -> "<< flag.Data() << endl;
  }

  flag = GetReactionType();
  if ( flag.CompareTo("") == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : TYPE(Reaction) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : TYPE(Target) -> Elastic (Default) " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : TYPE(Reaction) -> "<< flag.Data() << endl;
  }

  // Parameters

  Double_t val = GetBeamEnergy();
  if ( val == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(BeamEnergy) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(BeamEnergy) -> 0.7 GeV (Default)  " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(BeamEnergy) -> "<< val << endl;
  }


   val = GetEnergyPrim();
  if ( val == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(PrimEnergy) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(PrimEnergy) -> 1. e-03 GeV (Default)  " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(PrimEnergy) -> "<< val << endl;
  }

  val = GetNumberOfParticles();
  if ( val == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(Multiplicity) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(Multiplicity) -> 1. (Default)  " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(Multiplicity) -> "<< val << endl;
  }


   val = GetTargetHalfThicknessPara();
  if ( val == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargHalf) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargHalf) -> 0.11/2. mm (Default)  " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargHalf) -> "<< val << endl;
  }


   val = GetTargetThicknessLiH();
  if ( val == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargLiH) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargLiH) -> 3.5 cm (Default)  " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargLiH) -> "<< val << endl;
  }



   val = GetTargetRadius();
  if ( val == 0 ) {
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargRadius) -> not User defined !"<< endl;
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargRadius) -> 1. cm (Default)  " << endl;
  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(TargRadius) -> "<< val << endl;
  }



   val = GetSigmaXInEmittance();
  if ( (val == 0) && (GetSimEmittanceFlag().CompareTo(off) == 0) ) {
     cout<<"-E- R3BPrimaryGenerator::Init() : PARAM(SigmaEmittance) -> not defined !"<< endl;
     cout<<"-E- R3BPrimaryGenerator::Init() : Sigma Emittance needs definition ..." << endl;

  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(SigmaEmittance) -> "<< val << endl;
  }


   val = GetSigmaXPrimeInEmittance();

  if ( (val == 0) && (GetSimEmittanceFlag().CompareTo(off) == 0) ) {
     cout<<"-E- R3BPrimaryGenerator::Init() : PARAM(SigmaPrimEmittance) -> not defined !"<< endl;
     cout<<"-E- R3BPrimaryGenerator::Init() : Sigma Prim. Emittance needs definition ..." << endl;

  }else{
     cout<<"-I- R3BPrimaryGenerator::Init() : PARAM(SigmaPrimEmittance) -> "<< val << endl;
  }




}

ClassImp(R3BPrimaryGenerator)
