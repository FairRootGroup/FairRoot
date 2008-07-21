// -------------------------------------------------------------------------
// -----                   CbmIonGenerator source file                 -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "CbmIonGenerator.h"

#include "CbmPrimaryGenerator.h"

#include "CbmIon.h"
#include "CbmRunSim.h"

#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TObjArray.h"
                      
#include "CbmRunSim.h"
#include "CbmIon.h"
#include <iostream>
#include "TParticle.h"
using std::cout;
using std::endl;

// -----   Initialsisation of static variables   --------------------------
Int_t CbmIonGenerator::fgNIon = 0;
// ------------------------------------------------------------------------



// -----   Default constructor   ------------------------------------------
CbmIonGenerator::CbmIonGenerator() {
//  cout << "-W- CbmIonGenerator: "
//      << " Please do not use the default constructor! " << endl;
}
// ------------------------------------------------------------------------

CbmIonGenerator::CbmIonGenerator(const Char_t* ionName, Int_t mult,
				 Double_t px, Double_t py, Double_t pz,  
				 Double_t vx, Double_t vy, Double_t vz)
 :fMult(0),          
  fPx(0), fPy(0), fPz(0),
  fVx(0), fVy(0), fVz(0),
  fIon(0),  fQ(0)		

 {

  CbmRunSim *fRun=CbmRunSim::Instance();
  TObjArray *UserIons=fRun->GetUserDefIons();
  TObjArray *UserParticles=fRun->GetUserDefParticles();
  CbmParticle *part=0;
  fIon =(CbmIon *) UserIons->FindObject(ionName);
  if(fIon){
     fgNIon++;
     fMult = mult;
     fPx   = Double_t(fIon->GetA()) * px;
     fPy   = Double_t(fIon->GetA()) * py;
     fPz   = Double_t(fIon->GetA()) * pz;
     fVx   = vx;
     fVy   = vy;
     fVz   = vz;

  }else{
     part= (CbmParticle *)UserParticles->FindObject(ionName);
     if(part){
        fgNIon++;
        TParticle *particle=part->GetParticle();
        fMult = mult;
        fPx   = Double_t(particle->GetMass()/0.92827231) * px;
        fPy   = Double_t(particle->GetMass()/0.92827231) * py;
        fPz   = Double_t(particle->GetMass()/0.92827231) * pz;
        fVx   = vx;
        fVy   = vy;
        fVz   = vz;
     }
  }
  if(fIon==0 && part==0 ){
     cout << "-E- CbmIonGenerator: Ion or Particle is not defined !" << endl;
     Fatal("CbmIonGenerator", "No CbmRun instantised!");      
  }
    
}
// ------------------------------------------------------------------------



// -----   Default constructor   ------------------------------------------
CbmIonGenerator::CbmIonGenerator(Int_t z, Int_t a, Int_t q, Int_t mult,
				 Double_t px, Double_t py, Double_t pz,  
 				 Double_t vx, Double_t vy, Double_t vz)
 :fMult(0),          
  fPx(0), fPy(0), fPz(0),
  fVx(0), fVy(0), fVz(0),
  fIon(0),  fQ(0)

 {
  fgNIon++;
  fMult = mult;
  fPx   = Double_t(a) * px;
  fPy   = Double_t(a) * py;
  fPz   = Double_t(a) * pz;
  fVx   = vx;
  fVy   = vy;
  fVz   = vz;
  char buffer[20];
  sprintf(buffer, "CbmIon%d", fgNIon);
  fIon= new CbmIon(buffer, z, a, q);
  CbmRunSim* run = CbmRunSim::Instance();
  if ( ! run ) {
    cout << "-E- CbmIonGenerator: No CbmRun instantised!" << endl;
    Fatal("CbmIonGenerator", "No CbmRun instantised!");
  }
  run->AddNewIon(fIon);
}
//_________________________________________________________________________



// -----   Destructor   ---------------------------------------------------
CbmIonGenerator::~CbmIonGenerator() {
 // if (fIon) delete fIon;
}
//_________________________________________________________________________



// -----   Public method SetExcitationEnergy   ----------------------------
void CbmIonGenerator::SetExcitationEnergy(Double_t eExc) {
  fIon->SetExcEnergy(eExc);
}
//_________________________________________________________________________



// -----   Public method SetMass   ----------------------------------------
void CbmIonGenerator::SetMass(Double_t mass) {
  fIon->SetMass(mass);
}
//_________________________________________________________________________



// -----   Public method ReadEvent   --------------------------------------
Bool_t CbmIonGenerator::ReadEvent(CbmPrimaryGenerator* primGen) {

 // if ( ! fIon ) {
 //   cout << "-W- CbmIonGenerator: No ion defined! " << endl;
 //   return kFALSE;
 // }

  TParticlePDG* thisPart = 
    TDatabasePDG::Instance()->GetParticle(fIon->GetName());
  if ( ! thisPart ) {
    cout << "-W- CbmIonGenerator: Ion " << fIon->GetName()
	 << " not found in database!" << endl;
    return kFALSE;
  }

  int pdgType = thisPart->PdgCode();

  cout << "-I- CbmIonGenerator: Generating " << fMult << " ions of type "
       << fIon->GetName() << " (PDG code " << pdgType << ")" << endl;
  cout << "    Momentum (" << fPx << ", " << fPy << ", " << fPz 
       << ") Gev from vertex (" << fVx << ", " << fVy
       << ", " << fVz << ") cm" << endl;

  for(Int_t i=0; i<fMult; i++)
    primGen->AddTrack(pdgType, fPx, fPy, fPz, fVx, fVy, fVz);
  
  return kTRUE;

}

//_____________________________________________________________________________


ClassImp(CbmIonGenerator)
