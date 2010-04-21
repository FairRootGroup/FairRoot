// -------------------------------------------------------------------------
// -----                FairPrimaryGenerator source file                -----
// -----                 Created 23/06/04  by V. Friese                -----
// -------------------------------------------------------------------------

#include "FairPrimaryGenerator.h"

#include "FairGenerator.h"
#include "FairMCEventHeader.h"
#include "FairGenericStack.h"

#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TRandom.h"
#include "TMath.h"
#include "TF1.h"

#include <iostream>

using std::cout;
using std::endl;


// -----   Default constructor   -------------------------------------------
FairPrimaryGenerator::FairPrimaryGenerator() 
  :fBeamX0(0),
   fBeamY0(0),
   fBeamSigmaX(0),
   fBeamSigmaY(0),
   fTargetZ (new Double_t[1]),
   fNrTargets(1),
   fTargetDz(0),
   fVertex(TVector3(0.,0.,0.)),
   fNTracks(0),   
   fSmearVertexZ(kFALSE),
   fSmearVertexXY(kFALSE),
   fStack(NULL),
   fGenList(new TObjArray()),
   fListIter(fGenList->MakeIterator()),
   fEvent(0),
   fdoTracking(kTRUE),
   fEventTimeMin(0),
   fEventTimeMax(0),
   fEventTime(0),
   fEventMeanTime(0),
   fTimeProb(0)
 {
 
  fTargetZ[0] = 0.;
 
 }
// -------------------------------------------------------------------------



// -----   Constructor with title and name   -------------------------------
FairPrimaryGenerator::FairPrimaryGenerator(const char* name, const char* title) 
  :TNamed(name,title),
   fBeamX0(0),
   fBeamY0(0),
   fBeamSigmaX(0),
   fBeamSigmaY(0),
   fTargetZ (new Double_t[1]),
   fNrTargets(1),
   fTargetDz(0),
   fVertex(TVector3(0.,0.,0.)),
   fNTracks(0),   
   fSmearVertexZ(kFALSE),
   fSmearVertexXY(kFALSE),
   fStack(NULL),
   fGenList(new TObjArray()),
   fListIter(fGenList->MakeIterator()),
   fEvent(0),
   fdoTracking(kTRUE),
   fEventTimeMin(0),
   fEventTimeMax(0),
   fEventTime(0),
   fEventMeanTime(0),
   fTimeProb(0)
{
  fTargetZ[0] = 0.;
  
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairPrimaryGenerator::~FairPrimaryGenerator() {
  delete fListIter;
  if (1 == fNrTargets) {
    delete fTargetZ;
  } else {
    delete[] fTargetZ;
  }
}
// -------------------------------------------------------------------------



// -----   Public method GenerateEvent   -----------------------------------
Bool_t FairPrimaryGenerator::GenerateEvent(FairGenericStack* pStack) {
  // Check for MCEventHeader
  if ( ! fEvent) {
    cout << " \033[5m\033[31m -E- FairPrimaryGenerator::GenerateEvent: No MCEventHeader branch! \033[0m" << endl;
    Fatal("GenerateEvent", "No MCEventHeader branch");
  }

  // Initialise
  fStack   = pStack;
  fNTracks = 0;
  fEvent->Reset();

  // Create event vertex
  MakeVertex();
  fEvent->SetVertex(fVertex);

  // Call the ReadEvent methods from all registered generators
  fListIter->Reset();
  TObject* obj = 0;
  FairGenerator* gen = 0;
  while( (obj = fListIter->Next()) ) {
    gen = dynamic_cast<FairGenerator*> (obj);
    if ( ! gen ) return kFALSE;
    const char* genName = gen->GetName();
    Bool_t test = gen->ReadEvent(this);
    if ( ! test ) {
      cout << " \033[5m\033[31m -E FairPrimaryGenerator: ReadEvent failed for generator \033[0m"
	   << genName << endl;
      return kFALSE;
    }
  }

  if(fTimeProb!=0){
     fEventTime = fEventTime + fTimeProb->GetRandom();
  }else{
     fEventTime = fEventTime + gRandom->Uniform( fEventTimeMin,  fEventTimeMax);
  }
  
  fEvent->SetTime(fEventTime);
	 
  // Screen output
	
  cout << "-I FairPrimaryGenerator: " << fNTracks << " primary tracks "
       << "from vertex (" <<  fVertex.X() << ", " << fVertex.Y() << ", "
       << fVertex.Z() << ")" << "Event Time = " << fEventTime <<  "(ns) "<< endl;
  
  fEvent->SetNPrim(fNTracks);

  return kTRUE;
}
// -------------------------------------------------------------------------



// -----   Public method AddTrack   ----------------------------------------
void FairPrimaryGenerator::AddTrack(Int_t pdgid, Double_t px, Double_t py,
				   Double_t pz, Double_t vx, Double_t vy,
				   Double_t vz) {

  // ---> Add event vertex to track vertex
  vx += fVertex.X();
  vy += fVertex.Y();
  vz += fVertex.Z();

  // ---> Convert K0 and AntiK0 into K0s and K0L
  if ( pdgid == 311 || pdgid == -311 ) {
    Double_t test = gRandom->Uniform(0.,1.);
    if (test >= 0.5) pdgid = 310;    // K0S
    else             pdgid = 130;    // K0L
  }

  // ---> Check whether particle type is in PDG Database
  TDatabasePDG* pdgBase = TDatabasePDG::Instance();
  if ( ! pdgBase ) Fatal("FairPrimaryGenerator", 
			 "No TDatabasePDG instantiated");
  TParticlePDG* pdgPart = pdgBase->GetParticle(pdgid);
  if ( ! pdgPart ) {
    cout << "\033[5m\033[31m -E FairPrimaryGenerator: PDG code " << pdgid << " not found in database. Discarding particle. \033[0m " << endl;
    return;
  }

  // ---> Get mass and calculate energy of particle
  Double_t mass = pdgBase->GetParticle(pdgid)->Mass();
  Double_t e = TMath::Sqrt( px*px + py*py + pz*pz + mass*mass );

  // ---> Set all other parameters required by PushTrack
  Int_t    doTracking =  1;   // Go to tracking
  if(!fdoTracking) doTracking = 0 ;
  Int_t    parent     = -1;   // Primary particle
  Double_t tof        =  0.;  // Time of flight
  Double_t polx       =  0.;  // Polarisation
  Double_t poly       =  0.;
  Double_t polz       =  0.;
  Int_t    ntr        =  0;   // Track number; to be filled by the stack
  Double_t weight     =  1.;  // Weight
  Int_t    status     =  0;   // Generation status

  // Add track to stack
  fStack->PushTrack(doTracking, parent, pdgid, px, py, pz, e, vx, vy, vz,
		    tof, polx, poly, polz, kPPrimary, ntr, weight, status);
  fNTracks++;

}
// -------------------------------------------------------------------------  
		       


// -----   Public method SetBeam   -----------------------------------------
void FairPrimaryGenerator::SetBeam(Double_t x0, Double_t y0,
				  Double_t sigmaX, Double_t sigmaY) {
  fBeamX0     = x0;
  fBeamY0     = y0;
  fBeamSigmaX = sigmaX;
  fBeamSigmaY = sigmaY;
}
// -------------------------------------------------------------------------



// -----   Public method SetTarget   ---------------------------------------
void FairPrimaryGenerator::SetTarget(Double_t z, Double_t dz) {
  
  fTargetZ[0] = z;
  fTargetDz = dz;
}
// -------------------------------------------------------------------------

// -----   Public method SetMultTarget   -----------------------------------
void FairPrimaryGenerator::SetMultTarget(Int_t nroftargets, Double_t *targetpos, Double_t dz) {

  if (1 == fNrTargets) {
    delete fTargetZ;
  } else {
    delete[] fTargetZ;
  }

  fNrTargets = nroftargets;
  
  fTargetZ = new Double_t[nroftargets];
  for (Int_t i=0; i<nroftargets; i++) {
    fTargetZ[i]  = targetpos[i];
  }
  fTargetDz = dz;
  
}
// -------------------------------------------------------------------------



// -----   Private method MakeVertex   -------------------------------------
void FairPrimaryGenerator::MakeVertex() {
  Double_t vx = fBeamX0;
  Double_t vy = fBeamY0;
  Double_t vz;
  if (1 == fNrTargets) {
    vz = fTargetZ[0];
  } else {
    Int_t Target = (Int_t)gRandom->Uniform(fNrTargets);
    vz = fTargetZ[Target];
  }

  if (fSmearVertexZ) vz = gRandom->Uniform(vz - fTargetDz/2., 
					    vz + fTargetDz/2.);

  if (fSmearVertexXY) {
    if (fBeamSigmaX != 0.) vx = gRandom->Gaus(fBeamX0, fBeamSigmaX);
    if (fBeamSigmaY != 0.) vy = gRandom->Gaus(fBeamY0, fBeamSigmaY);
  }

  fVertex = TVector3(vx,vy,vz);
}
// -------------------------------------------------------------------------

void FairPrimaryGenerator::SetEventTimeInterval(Double_t min, Double_t max)
{
   fEventTimeMin=min;
   fEventTimeMax=max;

}
// -------------------------------------------------------------------------

void  FairPrimaryGenerator::SetEventMeanTime(Double_t mean)
{
   fEventMeanTime =mean;
   TString form="(1/";
   form+= mean;
   form+=")*exp(-x/";
   form+=mean;
   form+=")";
   fTimeProb= new TF1("TimeProb.", form.Data(), 0., mean*10);
   
}

ClassImp(FairPrimaryGenerator)

