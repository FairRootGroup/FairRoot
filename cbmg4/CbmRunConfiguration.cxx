// $Id: CbmRunConfiguration.cxx,v 1.2 2006/03/30 12:13:07 dbertini Exp $
// Category: run
//
// Author: I. Hrivnacova
//
// Class CbmRunConfiguration
// -------------------------
// See the class description in the header file.

#include "CbmRunConfiguration.h"

#include "CbmSpecialStackingAction.h"

#include "TG4DetConstruction.h"
#include "TG4SDConstruction.h"
#include "TG4PrimaryGeneratorAction.h"
#include "TG4RunAction.h"
#include "TG4EventAction.h"
#include "TG4TrackingAction.h"
#include "TG4SteppingAction.h"
#include "TG4ModularPhysicsList.h"
//#include "TG4PhysicsConstructorHadron.h"
//#include "TG4SpecialStackingAction.h"


// H.P.Wellish 
//#include "GeneralPhysics.hh"
//#include "EMPhysics.hh"
//#include "MuonPhysics.hh"
//#include "IonPhysics.hh"
//#include "HadronPhysicsQGSP.hh"
//#include "RichTbPhysicsList.h"

ClassImp(CbmRunConfiguration)

//_____________________________________________________________________________
CbmRunConfiguration::CbmRunConfiguration()
  : TG4RunConfiguration("geomRoot",kFALSE)
{
//
//  CreateUserConfiguration();
}

//_____________________________________________________________________________
CbmRunConfiguration::~CbmRunConfiguration() {
//
}

//
// protected methods
//


//_____________________________________________________________________________
//void CbmRunConfiguration::CreateUserConfiguration()
//{
// Creates the mandatory Geant4 classes and 
// the other user action classes. 
// ---
/*
  G4cout << "CbmRunConfiguration::CreateUserConfiguration()" << G4endl;


  // create mandatory Geant4 classes
  fDetectorConstruction = new TG4DetConstruction();
  fSDConstruction = new TG4SDConstruction();
  fPhysicsList = new TG4ModularPhysicsList();
  fPrimaryGenerator = new TG4PrimaryGeneratorAction();

  // create the other user action classes
  fRunAction  = new TG4RunAction();
  fEventAction  = new TG4EventAction();
  fTrackingAction = new TG4TrackingAction(); 
  fSteppingAction = new TG4SteppingAction();
  fStackingAction = new CbmSpecialStackingAction();
   
  // Set Max nof Steps
 
  int maxNofSteps = 10000;
  //  G4Double stepsize = 0.01*mm;
  fSteppingAction->SetMaxNofSteps(maxNofSteps);
  // Set custom physics list
  TG4ModularPhysicsList* tg4fPhysicsList
     = dynamic_cast<TG4ModularPhysicsList*>(fPhysicsList);

   
   cout << "####### take my physic definition ############################### " << endl;
 // tg4fPhysicsList->SetDefaultCutValue(1. *mm);
  tg4fPhysicsList->SetRangeCut( 0.01*mm );
  cout << " -I my physics SetRange Cut " << endl;
  
  tg4fPhysicsList->SetVerboseLevel(6);



  // register user defined physics constructor
  // General Physics
  tg4fPhysicsList->RegisterPhysics( new GeneralPhysics("general"));

  // EM Physics
  tg4fPhysicsList->RegisterPhysics( new EMPhysics("standard EM"));

  // Muon Physics 
   tg4fPhysicsList->RegisterPhysics( new MuonPhysics("muon"));

  // Hadron Physics
   tg4fPhysicsList->RegisterPhysics( new HadronPhysicsQGSP("hadron"));
 //  tg4fPhysicsList->RegisterPhysics( new ExN04HadronPhysics("hadron") );

  // Ion Physics
   tg4fPhysicsList->RegisterPhysics( new IonPhysics("ion"));

   RichTbPhysicsList * ct =  new RichTbPhysicsList();
   tg4fPhysicsList->RegisterPhysics( (G4VPhysicsConstructor*) ct );


  cout << " -I Custom Physics list created " << endl;


    // old physics list from ExN04
   //
   //  tg4fPhysicsList->RegisterPhysics( new ExN04GeneralPhysics("general") );
   //  tg4fPhysicsList->RegisterPhysics( new ExN04EMPhysics("standard EM"));
   //   tg4fPhysicsList->RegisterPhysics(  new ExN04MuonPhysics("muon"));
   // tg4fPhysicsList->RegisterPhysics(new ExN04HadronPhysics("hadron"));  
   //  tg4fPhysicsList->RegisterPhysics( new ExN04IonPhysics("ion"));                  
 



*/
//}


