/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairAsciiGenerator source file                  -----
// -----          Created 09/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairAsciiGenerator.h"

#include "FairPrimaryGenerator.h"   // for FairPrimaryGenerator

#include <climits>   // for INT_MAX
#include <fairlogger/Logger.h>
#include <fstream>

FairAsciiGenerator::FairAsciiGenerator()
    : FairGenerator()
    , fInputFile(nullptr)
    , fFileName("")
{}

FairAsciiGenerator::FairAsciiGenerator(const char* fileName)
    : FairGenerator()
    , fInputFile(0)
    , fFileName(fileName)
{
    //  fFileName  = fileName;
    LOG(info) << "FairAsciiGenerator: Opening input file " << fileName;
    fInputFile = new std::ifstream(fFileName);
    if (!fInputFile->is_open()) {
        LOG(fatal) << "Cannot open input file.";
    }

    // fPDG=TDatabasePDG::Instance();
}

FairAsciiGenerator::~FairAsciiGenerator() { CloseInput(); }

Bool_t FairAsciiGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
    // Check for input file
    if (!fInputFile->is_open()) {
        LOG(error) << "FairAsciiGenerator: Input file not open!";
        return kFALSE;
    }

    // Define event variable to be read from file
    Int_t ntracks = 0, eventID = 0;
    Double_t vx = 0., vy = 0., vz = 0.;

    // Define track variables to be read from file
    Int_t pdgID = 0;
    Double_t px = 0., py = 0., pz = 0.;

    // Read event header line from input file
    *fInputFile >> ntracks;
    if (fInputFile->fail() || ntracks < 0 || ntracks > (INT_MAX - 1))
        LOG(fatal) << "Error reading the number of events from event header.";
    *fInputFile >> eventID >> vx >> vy >> vz;

    // If end of input file is reached : close it and abort run
    if (fInputFile->eof()) {
        LOG(info) << "FairAsciiGenerator: End of input file reached ";
        CloseInput();
        return kFALSE;
    }

    LOG(info) << "FairAsciiGenerator: Event " << eventID << ",  vertex = (" << vx << "," << vy << "," << vz
              << ") cm,  multiplicity " << ntracks;

    // Loop over tracks in the current event
    for (Int_t itrack = 0; itrack < ntracks; itrack++) {

        // Read PID and momentum from file
        *fInputFile >> pdgID >> px >> py >> pz;
        // convert Geant3 code to PDG code

        // Int_t pdg= fPDG->ConvertGeant3ToPdg(pdgID);

        // Give track to PrimaryGenerator
        primGen->AddTrack(pdgID, px, py, pz, vx, vy, vz);
    }

    return kTRUE;
}

void FairAsciiGenerator::CloseInput()
{
    if (fInputFile) {
        if (fInputFile->is_open()) {
            LOG(info) << "FairAsciiGenerator: Closing input file " << fFileName;
            fInputFile->close();
        }
        delete fInputFile;
        fInputFile = nullptr;
    }
}
