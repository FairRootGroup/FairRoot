/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairUrqmdGenerator source file                  -----
// -----                Created 24/06/04  by V. Friese                 -----
// -------------------------------------------------------------------------
#include "FairUrqmdGenerator.h"

#include "FairLogger.h"             // for logging
#include "FairMCEventHeader.h"      // for FairMCEventHeader
#include "FairPrimaryGenerator.h"   // for FairPrimaryGenerator

#include <TDatabasePDG.h>     // for TDatabasePDG
#include <TLorentzVector.h>   // for TLorentzVector
#include <TMath.h>            // for Sqrt, sqrt
#include <TParticlePDG.h>     // for TParticlePDG
#include <TString.h>          // for TString, operator+
#include <TVector3.h>         // for TVector3
#include <climits>            // for INT_MAX
#include <cmath>              // sqrt
#include <cstdlib>            // for getenv
#include <fstream>            // IWYU pragma: keep for ifstream

FairUrqmdGenerator::FairUrqmdGenerator()
    : FairGenerator()
    , fInputFile(nullptr)
    , fParticleTable()
    , fFileName(nullptr)
{}

FairUrqmdGenerator::FairUrqmdGenerator(const char* fileName)
    : FairGenerator()
    , fInputFile(nullptr)
    , fParticleTable()
    , fFileName(fileName)
{
    //  fFileName = fileName;
    LOG(info) << "FairUrqmdGenerator: Opening input file " << fileName;
    fInputFile = fopen(fFileName, "r");
    if (!fInputFile) {
        LOG(fatal) << "Cannot open input file.";
    }
    ReadConversionTable();
}

FairUrqmdGenerator::FairUrqmdGenerator(const char* fileName, const char* conversion_table)
    : FairGenerator()
    , fInputFile(nullptr)
    , fParticleTable()
    , fFileName(fileName)
{
    //  fFileName = fileName;
    LOG(info) << "FairUrqmdGenerator: Opening input file " << fileName;
    fInputFile = fopen(fFileName, "r");
    if (!fInputFile) {
        LOG(fatal) << "Cannot open input file.";
    }
    ReadConversionTable(conversion_table);
}

FairUrqmdGenerator::~FairUrqmdGenerator()
{
    //  LOG(debug) << "Enter Destructor of FairUrqmdGenerator";
    if (fInputFile) {
        fclose(fInputFile);
        fInputFile = nullptr;
    }
    fParticleTable.clear();
    //  LOG(debug) << "Leave Destructor of FairUrqmdGenerator";
}

namespace {
// silence fgets warnings (with a runtime error message if it actually happens)
// for correctness should be handled in the code instead, if this methods are still relevant in the future.
void skipBytes(char* bytes, size_t numBytes, FILE* file)
{
    if (fgets(bytes, numBytes, file) == nullptr) {
        LOG(error) << "Failed reading from file stream";
    }
}

}   // namespace

Bool_t FairUrqmdGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
    // ---> Check for input file
    if (!fInputFile) {
        LOG(error) << "FairUrqmdGenerator: Input file not open! ";
        return kFALSE;
    }

    // ---> Check for primary generator
    if (!primGen) {
        LOG(error) << "FairUrqmdGenerator::ReadEvent: "
                   << "No PrimaryGenerator!";
        return kFALSE;
    }

    // ---> Define event variables to be read from file
    int evnr = 0, ntracks = 0, aProj = 0, zProj = 0, aTarg = 0, zTarg = 0;
    float b = 0., ekin = 0.;

    int ityp = 0, i3 = 0, ichg = 0, pid = 0;
    float ppx = 0., ppy = 0., ppz = 0., m = 0.;

    // ---> Read and check first event header line from input file
    char read[200];
    skipBytes(read, 200, fInputFile);
    if (feof(fInputFile)) {
        LOG(info) << "FairUrqmdGenerator : End of input file reached.";
        fclose(fInputFile);
        fInputFile = nullptr;
        return kFALSE;
    }
    if (read[0] != 'U') {
        LOG(error) << "FairUrqmdGenerator: Wrong event header";
        return kFALSE;
    }

    Int_t retval = 0;

    // ---> Read rest of event header
    skipBytes(read, 26, fInputFile);
    retval = fscanf(fInputFile, "%d", &aProj);
    CheckReturnValue(retval);
    retval = fscanf(fInputFile, "%d", &zProj);
    CheckReturnValue(retval);
    skipBytes(read, 25, fInputFile);
    retval = fscanf(fInputFile, "%d", &aTarg);
    CheckReturnValue(retval);
    retval = fscanf(fInputFile, "%d", &zTarg);
    CheckReturnValue(retval);
    skipBytes(read, 200, fInputFile);
    skipBytes(read, 200, fInputFile);
    skipBytes(read, 36, fInputFile);
    retval = fscanf(fInputFile, "%f", &b);
    CheckReturnValue(retval);
    skipBytes(read, 200, fInputFile);
    skipBytes(read, 39, fInputFile);
    retval = fscanf(fInputFile, "%e", &ekin);
    CheckReturnValue(retval);
    skipBytes(read, 200, fInputFile);
    skipBytes(read, 7, fInputFile);
    retval = fscanf(fInputFile, "%d", &evnr);
    CheckReturnValue(retval);
    skipBytes(read, 200, fInputFile);
    for (int iline = 0; iline < 8; iline++) {
        skipBytes(read, 200, fInputFile);
    }
    retval = fscanf(fInputFile, "%d", &ntracks);
    if (ntracks < 0 || ntracks > (INT_MAX - 1))
        LOG(fatal) << "Error reading the number of events from event header.";
    CheckReturnValue(retval);
    skipBytes(read, 200, fInputFile);
    skipBytes(read, 200, fInputFile);

    // ---> Calculate beta and gamma for Lorentztransformation
    TDatabasePDG* pdgDB = TDatabasePDG::Instance();
    TParticlePDG* kProton = pdgDB->GetParticle(2212);
    Double_t kProtonMass = kProton->Mass();

    Double_t eBeam = ekin + kProtonMass;
    Double_t pBeam = TMath::Sqrt(eBeam * eBeam - kProtonMass * kProtonMass);
    Double_t betaCM = pBeam / (eBeam + kProtonMass);
    Double_t gammaCM = TMath::Sqrt(1. / (1. - betaCM * betaCM));

    LOG(info) << "FairUrqmdGenerator: Event " << evnr << ",  b = " << b << " fm,  multiplicity " << ntracks
              << ", ekin: " << ekin;

    // Set event id and impact parameter in MCEvent if not yet done
    FairMCEventHeader* event = primGen->GetEvent();
    if (event && (!event->IsSet())) {
        event->SetEventID(evnr);
        event->SetB(b);
        event->MarkSet(kTRUE);
    }

    // ---> Loop over tracks in the current event
    for (int itrack = 0; itrack < ntracks; itrack++) {

        // Read momentum and PID from file
        skipBytes(read, 81, fInputFile);
        retval = fscanf(fInputFile, "%e", &ppx);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%e", &ppy);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%e", &ppz);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%e", &m);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%d", &ityp);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%d", &i3);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%d", &ichg);
        CheckReturnValue(retval);
        skipBytes(read, 200, fInputFile);

        // Convert UrQMD type and charge to unique pid identifier
        if (ityp >= 0) {
            pid = 1000 * (ichg + 2) + ityp;
        } else {
            pid = -1000 * (ichg + 2) + ityp;
        }

        // Convert Unique PID into PDG particle code
        if (fParticleTable.find(pid) == fParticleTable.end()) {
            LOG(warn) << "FairUrqmdGenerator: PID " << ityp << " charge " << ichg << " not found in table (" << pid
                      << ")";
            continue;
        }
        Int_t pdgID = fParticleTable[pid];

        // Lorentztransformation to lab
        Double_t mass = Double_t(m);
        Double_t px = Double_t(ppx);
        Double_t py = Double_t(ppy);
        Double_t pz = Double_t(ppz);
        Double_t e = sqrt(mass * mass + px * px + py * py + pz * pz);
        pz = gammaCM * (pz + betaCM * e);
        Double_t ee = sqrt(mass * mass + px * px + py * py + pz * pz);

        TVector3 aa(px, py, pz);
        TLorentzVector pp;
        pp.SetPx(px);
        pp.SetPy(py);
        pp.SetPz(pz);
        pp.SetE(ee);

        // Give track to PrimaryGenerator
        primGen->AddTrack(pdgID, px, py, pz, 0., 0., 0.);
    }

    return kTRUE;
}

Bool_t FairUrqmdGenerator::SkipEvents(Int_t count)
{
    if (count <= 0) {
        return kTRUE;
    }

    for (Int_t ii = 0; ii < count; ii++) {
        // ---> Check for input file
        if (!fInputFile) {
            LOG(error) << "FairUrqmdGenerator: Input file not open! ";
            return kFALSE;
        }

        // ---> Define event variables to be read from file
        int evnr = 0, ntracks = 0, aProj = 0, zProj = 0, aTarg = 0, zTarg = 0;
        float b = 0., ekin = 0.;

        // ---> Read and check first event header line from input file
        char read[200];
        skipBytes(read, 200, fInputFile);
        if (feof(fInputFile)) {
            LOG(info) << "FairUrqmdGenerator : End of input file reached.";
            fclose(fInputFile);
            fInputFile = nullptr;
            return kFALSE;
        }
        if (read[0] != 'U') {
            LOG(error) << "FairUrqmdGenerator: Wrong event header";
            return kFALSE;
        }

        Int_t retval = 0;

        // ---> Read rest of event header
        skipBytes(read, 26, fInputFile);
        retval = fscanf(fInputFile, "%d", &aProj);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%d", &zProj);
        CheckReturnValue(retval);
        skipBytes(read, 25, fInputFile);
        retval = fscanf(fInputFile, "%d", &aTarg);
        CheckReturnValue(retval);
        retval = fscanf(fInputFile, "%d", &zTarg);
        CheckReturnValue(retval);
        skipBytes(read, 200, fInputFile);
        skipBytes(read, 200, fInputFile);
        skipBytes(read, 36, fInputFile);
        retval = fscanf(fInputFile, "%f", &b);
        CheckReturnValue(retval);
        skipBytes(read, 200, fInputFile);
        skipBytes(read, 39, fInputFile);
        retval = fscanf(fInputFile, "%e", &ekin);
        CheckReturnValue(retval);
        skipBytes(read, 200, fInputFile);
        skipBytes(read, 7, fInputFile);
        retval = fscanf(fInputFile, "%d", &evnr);
        CheckReturnValue(retval);
        skipBytes(read, 200, fInputFile);
        for (int iline = 0; iline < 8; iline++) {
            skipBytes(read, 200, fInputFile);
        }
        retval = fscanf(fInputFile, "%d", &ntracks);
        if (ntracks < 0 || ntracks > (INT_MAX - 1))
            LOG(fatal) << "Error reading the number of events from event header.";
        CheckReturnValue(retval);
        skipBytes(read, 200, fInputFile);
        skipBytes(read, 200, fInputFile);

        LOG(info) << "FairUrqmdGenerator: Event " << evnr << " skipped!";

        // ---> Loop over tracks in the current event
        for (int itrack = 0; itrack < ntracks; itrack++) {

            // Read momentum and PID from file
            skipBytes(read, 81, fInputFile);
            skipBytes(read, 200, fInputFile);
        }
    }
    return kTRUE;
}

void FairUrqmdGenerator::ReadConversionTable(TString conversion_table)
{
    TString work = getenv("VMCWORKDIR");
    TString fileName;

    if (conversion_table.IsNull()) {
        fileName = work + "/input/urqmd_pdg.dat";
    } else {
        fileName = conversion_table.Data();
    }

    std::ifstream* pdgconv = new std::ifstream(fileName.Data());

    if (!pdgconv->good()) {
        LOG(fatal) << "Could not open Urqmd->PDG input file " << fileName;
    }

    Int_t index = 0;

    Int_t pdgId = 0;

    while (!pdgconv->eof()) {
        index = pdgId = 0;
        *pdgconv >> index >> pdgId;
        fParticleTable[index] = pdgId;
    }

    pdgconv->close();
    delete pdgconv;

    LOG(info) << "FairUrqmdGenerator: Particle table for conversion from "
              << "UrQMD loaded";
}

void FairUrqmdGenerator::CheckReturnValue(Int_t retval)
{
    if (1 != retval) {
        LOG(error) << "Error when reading variable from input file";
    }
}
