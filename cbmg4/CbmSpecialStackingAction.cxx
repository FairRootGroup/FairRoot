//
//
// Class CbmSpecialStackingAction
// -----------------------
// See the class description in the header file.

#include "CbmSpecialStackingAction.h"
#include "TG4TrackingAction.h"
#include "TG4Globals.h"

#include "G4Track.hh"
#include "G4TrackStack.hh"
#include "G4StackedTrack.hh"
#include "G4StackManager.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4NeutrinoTau.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4AntiNeutrinoTau.hh"
#include <iostream>

using namespace std;

//_____________________________________________________________________________
CbmSpecialStackingAction::CbmSpecialStackingAction()
  : TG4Verbose("stackingAction",1),
    fStage(0), 
    fTrackingAction(0)
{
// 
  G4cout << "-I   CbmSpecialStackingAction called " << G4endl;

}

//_____________________________________________________________________________
CbmSpecialStackingAction::CbmSpecialStackingAction(const CbmSpecialStackingAction& right) 
  : TG4Verbose("stackingAction") {
//
  //TG4Globals::Exception("CbmSpecialStackingAction is protected from copying.");
}

//_____________________________________________________________________________
CbmSpecialStackingAction::~CbmSpecialStackingAction() {
// 
}

// operators

//_____________________________________________________________________________
CbmSpecialStackingAction& 
CbmSpecialStackingAction::operator=(const CbmSpecialStackingAction &right)
{
  // check assignement to self
  if (this == &right) return *this;
  
 // TG4Globals::Exception("CbmSpecialStackingAction is protected from assigning.");

  return *this;
}


G4ClassificationOfNewTrack 
CbmSpecialStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
   G4ClassificationOfNewTrack classification = fUrgent;

   // if(!(GlobalMessenger::GetInstance()->GetProcessSecondaries()))
   // return classification;

   // Only sec.
   // if (aTrack->GetParentID()) {

//       G4double energy_min = 50.0*MeV;  
//       G4double energy_max = 25000*MeV;
//       G4double tener = aTrack->GetTotalEnergy();
       //  G4ParticleDefinition *def = aTrack->GetDefinition();
         
//       if ( (tener < energy_min) )  classification = fKill; 
//       if ( (tener > energy_max) )  classification = fKill; 

  // }

  return classification;
}

//  ============================================================================


void CbmSpecialStackingAction::NewStage()
{;}
    
void CbmSpecialStackingAction::PrepareNewEvent()
{;}





// public methods


//_____________________________________________________________________________

/*
G4ClassificationOfNewTrack 
CbmSpecialStackingAction::ClassifyNewTrack(const G4Track* track)
{
// Classifies the new track.
// ---


  G4ClassificationOfNewTrack classification;
  if (fStage == 0) { 
    // move all primaries to PrimaryStack
     classification = fPostpone;

    // save primary particle info
    // (secondary particles are stored 
    //  by AlTrackingAction::PreUserTrackingAction() method)
    if (fTrackingAction->GetSavePrimaries()){
      fTrackingAction->TrackToStack(track);
      printf("-I save primaries to stack  \n");
     }  
  }  
  else {
     // exclude neutrinos
    G4ParticleDefinition* particle = track->GetDefinition();
    if( particle == G4NeutrinoE::NeutrinoEDefinition() ||
        particle == G4NeutrinoMu::NeutrinoMuDefinition() ||
        particle == G4NeutrinoTau::NeutrinoTauDefinition() ||
        particle == G4AntiNeutrinoE::AntiNeutrinoEDefinition() ||
        particle == G4AntiNeutrinoMu::AntiNeutrinoMuDefinition() ||
        particle == G4AntiNeutrinoTau::AntiNeutrinoTauDefinition()) {

        return fKill;	 
     }	

     G4int parentID = track->GetParentID();
     if (parentID ==0) { 
        return fUrgent; 
     }
     else { 
        return fWaiting; 
     }
  }
  return classification;
}


//_____________________________________________________________________________
void CbmSpecialStackingAction::NewStage()
{
// Called by G4 kernel at the new stage of stacking.
// ---

  fStage++;
  
  if (VerboseLevel() > 1) {
    G4cout << "CbmSpecialStackingAction::NewStage " << fStage 
           << " has been started." << G4endl;
  }

  if (stackManager->GetNUrgentTrack() == 0 &&
      stackManager->GetNPostponedTrack() != 0 ) {
      
      stackManager->TransferOneStackedTrack(fPostpone, fUrgent);
  }
}
   
//_____________________________________________________________________________
void CbmSpecialStackingAction::PrepareNewEvent()
{
// Called by G4 kernel at the beginning of event.
// ---

  fStage = 0;
  fTrackingAction = TG4TrackingAction::Instance();
}
*/

