/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimModel source file                    -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#include <iostream>
#include "FairFastSimModel.h"
#include "G4VPhysicalVolume.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"

#include "G4SystemOfUnits.hh"

#include "FairGenericStack.h"
#include "FairLogger.h"
#include "FairMCApplication.h"
#include "FairTrajFilter.h"
#include "TGeoManager.h"
#include "TParticle.h"
#include "TVirtualMC.h"

// I.H. make this optional
// #include "G4GDMLParser.hh"

FairFastSimModel::FairFastSimModel(G4String modelName,
		G4Region* envelope) :
		G4VFastSimulationModel(modelName, envelope) {
}

FairFastSimModel::FairFastSimModel(G4String modelName) :
		G4VFastSimulationModel(modelName) {
}

FairFastSimModel::~FairFastSimModel() {
}

// I.H. make this optional
// void FairFastSimModel::WriteGeometryToGDML(
// 		G4VPhysicalVolume* physicalVolume) {

// 	G4GDMLParser* parser = new G4GDMLParser();
// 	remove("garfieldGeometry.gdml");
// 	parser->Write("garfieldGeometry.gdml", physicalVolume, false);
// 	delete parser;
// }

G4bool FairFastSimModel::IsApplicable(
		const G4ParticleDefinition& particleType) {
    return true;
}

G4bool FairFastSimModel::ModelTrigger(
		const G4FastTrack& fastTrack) {
    return true;
}

void FairFastSimModel::DoIt(const G4FastTrack& fastTrack,
                            G4FastStep& fastStep) {

    LOG(debug) << "FairFastSimModel::DoIt() called";
    // G4TouchableHandle theTouchable =
    //     fastTrack.GetPrimaryTrack()->GetTouchableHandle();
    // G4String name = theTouchable->GetVolume()->GetName();

    int movedParticleIndex = ((FairGenericStack*)(gMC->GetStack()))->FastSimGetMovedIndex();
    if ( movedParticleIndex == -2 ) {
        FairMCApplication::Instance()->Stepping();
        movedParticleIndex = ((FairGenericStack*)(gMC->GetStack()))->FastSimGetMovedIndex();
    }

    LOG(debug) << "FairFastSimModel::DoIt() moving particle " << gMC->GetStack()->GetCurrentTrackNumber() << " (pos #" << movedParticleIndex << ").";
    if ( movedParticleIndex != -1 ) {
        TClonesArray* particles = ((FairGenericStack*)(gMC->GetStack()))->GetListOfParticles();

        TParticle* particle = (TParticle*)particles->At(movedParticleIndex);

        LOG(debug) << "FAST SIM (moving particle to <" << particle->Vx() << "," << particle->Vy() << "," << particle->Vz() << "," << particle->T() << "> with p=<"
                   << particle->Px() << "," << particle->Py() << "," << particle->Pz() << "," << particle->Ek() << ">)";
        
        G4ThreeVector pos(particle->Vx()*10.,particle->Vy()*10.,particle->Vz()*10.); //change from cm to mm
        G4ThreeVector mom(particle->Px()*1000.,particle->Py()*1000.,particle->Pz()*1000.);
        G4ThreeVector pol(0.,0.,0.); // get polarisation
        G4double      tim = particle->T()*10.e9;  // change from ns to s
        G4double      len = 0.;
        G4double      ek  = particle->Ek()*1000.;
        
        fastStep.SetPrimaryTrackFinalPosition      (pos,false);
        fastStep.SetPrimaryTrackFinalTime          (tim);
        fastStep.SetPrimaryTrackFinalProperTime    (tim);
        fastStep.SetPrimaryTrackFinalMomentum      (mom,false);
        fastStep.SetPrimaryTrackFinalKineticEnergy (ek);
        //    fastStep.SetPrimaryTrackFinalKineticEnergyAndDirection (G4double, const G4ThreeVector &, G4bool localCoordinates=true);
        fastStep.SetPrimaryTrackFinalPolarization  (pol,false);
        fastStep.SetPrimaryTrackPathLength         (len);

        if ( FairTrajFilter::Instance()->IsAccepted(particle) ) {
            FairTrajFilter::Instance()->GetCurrentTrk()->AddPoint(particle->Vx(),particle->Vy(),particle->Vz(),particle->T());
        }
        
        gGeoManager->SetCurrentPoint(particle->Vx(),particle->Vy(),particle->Vz());
    }
    ((FairGenericStack*)(gMC->GetStack()))->FastSimClearMovedIndex();
}
