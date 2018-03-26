/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Configuration macro for Geant4 VirtualMC
void Config()
{
///    Create the run configuration
/// In constructor user has to specify the geometry input
/// and select geometry navigation via the following options:
/// - geomVMCtoGeant4   - geometry defined via VMC, G4 native navigation
/// - geomVMCtoRoot     - geometry defined via VMC, Root navigation
/// - geomRoot          - geometry defined via Root, Root navigation
/// - geomRootToGeant4  - geometry defined via Root, G4 native navigation
/// - geomGeant4        - geometry defined via Geant4, G4 native navigation
///
/// The second argument in the constructor selects physics list:
/// - emStandard         - standard em physics (default)
/// - emStandard+optical - standard em physics + optical physics
/// - XYZ                - selected hadron physics list ( XYZ = LHEP, QGSP, ...)
/// - XYZ+optical        - selected hadron physics list + optical physics
///
/// The third argument activates the special processes in the TG4SpecialPhysicsList,
/// which implement VMC features:
/// - stepLimiter       - step limiter (default) 
/// - specialCuts       - VMC cuts
/// - specialControls   - VMC controls for activation/inactivation selected processes
/// - stackPopper       - stackPopper process
/// When more than one options are selected, they should be separated with '+'
/// character: eg. stepLimit+specialCuts.

   Bool_t mtMode = FairRunSim::Instance()->IsMT();
   Bool_t specialStacking = false;
   TG4RunConfiguration* runConfiguration 
           = new TG4RunConfiguration("geomRoot", "QGSP_BERT_EMV", "stepLimiter+specialCuts+specialControls",
                                      specialStacking, mtMode);

/// Create the G4 VMC 
   TGeant4* geant4 = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration);
   cout << "Geant4 has been created." << endl;

/// create the Specific stack
   FairStack *stack = new FairStack(1000); 
   stack->StoreSecondaries(kTRUE);
   stack->SetMinPoints(0);
   geant4->SetStack(stack);

   if(FairRunSim::Instance()->IsExtDecayer()){
      TVirtualMCDecayer* decayer = TPythia6Decayer::Instance();
      geant4->SetExternalDecayer(decayer);
   }
  
/// Customise Geant4 setting
/// (verbose level, global range cut, ..)

   TString configm(gSystem->Getenv("CONFIG_DIR"));
   TString configm1 = configm + "/g4config.in";
   cout << " -I g4Config() using g4conf  macro: " << configm1 << endl;

   //set geant4 specific stuff
  geant4->SetMaxNStep(10000);  // default is 30000
  geant4->ProcessGeantMacro(configm1.Data());

}
