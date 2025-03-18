/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimModel source file                    -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------

#include "FairFastSimModel.h"

#include "FairGenericStack.h"
#include "FairLogger.h"
#include "FairMCApplication.h"
#include "FairTrajFilter.h"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4ParticleTable.hh"
#include "G4StackManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"

#include <TClonesArray.h>   // for TClonesArray
#include <TGeoManager.h>
#include <TParticle.h>
#include <TVector3.h>   // for TVector3
#include <TVirtualMC.h>
#include <tuple>   // for tie, tuple

// I.H. make this optional
// #include "G4GDMLParser.hh"

FairFastSimModel::FairFastSimModel(G4String modelName, G4Region* envelope)
    : G4VFastSimulationModel(modelName, envelope)
{}

FairFastSimModel::FairFastSimModel(G4String modelName)
    : G4VFastSimulationModel(modelName)
{}

FairFastSimModel::~FairFastSimModel() {}

// I.H. make this optional
// void FairFastSimModel::WriteGeometryToGDML(
// 		G4VPhysicalVolume* physicalVolume) {

// 	G4GDMLParser* parser = new G4GDMLParser();
// 	remove("garfieldGeometry.gdml");
// 	parser->Write("garfieldGeometry.gdml", physicalVolume, false);
// 	delete parser;
// }

G4bool FairFastSimModel::IsApplicable([[gnu::unused]] const G4ParticleDefinition& particleType)
{
    return true;
}

G4bool FairFastSimModel::ModelTrigger([[gnu::unused]] const G4FastTrack& fastTrack)
{
    return true;
}

void FairFastSimModel::DoIt(const G4FastTrack& fastTrack, G4FastStep& fastStep)
{
    LOG(debug) << "FairFastSimModel::DoIt() called";
    // G4TouchableHandle theTouchable =
    //     fastTrack.GetPrimaryTrack()->GetTouchableHandle();
    // G4String name = theTouchable->GetVolume()->GetName();

    int firstSecondary(0);
    int nofSecondaries(0);
    int movedParticleIndex(0);
    std::tie(movedParticleIndex, firstSecondary, nofSecondaries) =
        ((FairGenericStack*)(TVirtualMC::GetMC()->GetStack()))->FastSimGetMovedIndex();
    if (movedParticleIndex == -2) {
        FairMCApplication::Instance()->Stepping();
        std::tie(movedParticleIndex, firstSecondary, nofSecondaries) =
            ((FairGenericStack*)(TVirtualMC::GetMC()->GetStack()))->FastSimGetMovedIndex();
    }
    TClonesArray* particles = ((FairGenericStack*)(TVirtualMC::GetMC()->GetStack()))->GetListOfParticles();
    if (nofSecondaries != 0) {
        fastStep.SetNumberOfSecondaryTracks(nofSecondaries);

        int addedParticleIndex = firstSecondary;
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        for (int ipart = 0; ipart < nofSecondaries; ipart++) {
            if (addedParticleIndex == movedParticleIndex)
                addedParticleIndex++;   // added protection in case user adds, moves and adds again
            TParticle* particle = (TParticle*)particles->At(addedParticleIndex);

            G4ParticleDefinition* particleDefinition = 0;
            particleDefinition = particleTable->FindParticle(particle->GetPdgCode());
            if (!particleDefinition)
                LOG(fatal) << "FairFastSimModel::DoIt() PDG " << particle->GetPdgCode() << " unknown!";
            G4ThreeVector pos(
                particle->Vx() * 10., particle->Vy() * 10., particle->Vz() * 10.);   // change from cm to mm
            G4ThreeVector mom(particle->Px() * 1000., particle->Py() * 1000., particle->Pz() * 1000.);
            TVector3 polVect;
            particle->GetPolarisation(polVect);
            G4ThreeVector pol(polVect.X(), polVect.Y(), polVect.Z());   // get polarisation
            G4double tim = particle->T() * 10.e9;                       // change from ns to s
            G4double ek = particle->Ek() * 1000.;
            G4DynamicParticle dynParticle(particleDefinition, mom.unit(), ek);
            G4Track* tempTrack = fastStep.CreateSecondaryTrack(dynParticle, pos, tim, false);
            tempTrack->SetTouchableHandle(fastTrack.GetPrimaryTrack()->GetTouchableHandle());
            addedParticleIndex++;
        }
    }

    LOG(debug) << "FairFastSimModel::DoIt() moving particle "
               << TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber() << " (pos #" << movedParticleIndex << ").";
    if (movedParticleIndex != -1) {
        TParticle* particle = (TParticle*)particles->At(movedParticleIndex);

        LOG(debug) << "FAST SIM (moving particle to <" << particle->Vx() << "," << particle->Vy() << ","
                   << particle->Vz() << "," << particle->T() << "> with p=<" << particle->Px() << "," << particle->Py()
                   << "," << particle->Pz() << "," << particle->Ek() << ">)";

        G4ThreeVector pos(particle->Vx() * 10., particle->Vy() * 10., particle->Vz() * 10.);   // change from cm to mm
        G4ThreeVector mom(particle->Px() * 1000., particle->Py() * 1000., particle->Pz() * 1000.);
        G4ThreeVector pol(0., 0., 0.);          // get polarisation
        G4double tim = particle->T() * 10.e9;   // change from ns to s
        G4double len = 0.;
        G4double ek = particle->Ek() * 1000.;

        fastStep.ProposePrimaryTrackFinalPosition(pos, false);
        fastStep.ProposePrimaryTrackFinalTime(tim);
        fastStep.ProposePrimaryTrackFinalProperTime(tim);
        fastStep.ProposePrimaryTrackFinalMomentumDirection(mom, false);
        fastStep.ProposePrimaryTrackFinalKineticEnergy(ek);
        //    fastStep.SetPrimaryTrackFinalKineticEnergyAndDirection (G4double, const G4ThreeVector &, G4bool
        //    localCoordinates=true);
        fastStep.ProposePrimaryTrackFinalPolarization(pol, false);
        fastStep.ProposePrimaryTrackPathLength(len);

        if (FairTrajFilter::Instance()->IsAccepted(particle)) {
            FairTrajFilter::Instance()->GetCurrentTrk()->AddPoint(
                particle->Vx(), particle->Vy(), particle->Vz(), particle->T());
        }

        gGeoManager->SetCurrentPoint(particle->Vx(), particle->Vy(), particle->Vz());
    }
    ((FairGenericStack*)(TVirtualMC::GetMC()->GetStack()))->FastSimClearMovedIndex();
}
