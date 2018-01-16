/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairShieldGenerator source file                 -----
// -----                Created 15/09/06  by V. Friese                 -----
// -------------------------------------------------------------------------
#include "FairShieldGenerator.h"

#include "FairIon.h"                    // for FairIon
#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator
#include "FairRunSim.h"                 // for FairRunSim
#include "FairLogger.h"                 // for logging

#include "TDatabasePDG.h"               // for TDatabasePDG
#include "TParticlePDG.h"               // for TParticlePDG

#include <stdio.h>                      // for NULL, sprintf
#include <utility>                      // for pair
#include <climits>                      // for INT_MAX

using std::map;

// -----   Default constructor   ------------------------------------------
FairShieldGenerator::FairShieldGenerator()
  :FairGenerator(),
   fInputFile(NULL),
   fFileName(NULL),
   fPDG(NULL),
   fIonMap()
{
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
FairShieldGenerator::FairShieldGenerator(const char* fileName)
  :FairGenerator(),
   fInputFile(NULL),
   fFileName(fileName),
   fPDG(TDatabasePDG::Instance()),
   fIonMap()
{

  LOG(info) << "FairShieldGenerator: Opening input file " << fileName;
  fInputFile = new std::ifstream(fFileName);
  if ( ! fInputFile->is_open() ) {
    LOG(fatal) << "Cannot open input file.";
  }
  LOG(info) << "FairShieldGenerator: Looking for ions...";
  Int_t nIons = RegisterIons();
  LOG(info) << "FairShieldGenerator: " << nIons << " ions registered.";
  CloseInput();
  LOG(info) << "FairShieldGenerator: Reopening input file " << fileName;
  fInputFile = new std::ifstream(fFileName);
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
FairShieldGenerator::~FairShieldGenerator()
{
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairShieldGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

  // Check for input file
  if ( ! fInputFile->is_open() ) {
    LOG(error) << "FairShieldGenerator: Input file not open!";
    return kFALSE;
  }


  // Define event variable to be read from file
  Int_t    eventId = 0;
  Int_t    nTracks = 0;
  Double_t pBeam   = 0.;
  Double_t b       = 0.;

  // Define track variables to be read from file
  Int_t    iPid    = 0;
  Int_t    iMass   = 0;
  Int_t    iCharge = 0;
  Double_t px      = 0.;
  Double_t py      = 0.;
  Double_t pz      = 0.;
  Int_t    pdgType = 0;

  // Read event header line from input file
  *fInputFile >> eventId;
  *fInputFile >> nTracks;
  if (nTracks < 0 || nTracks > (INT_MAX-1)) LOG(fatal) << "Error reading the number of events from event header.";
  *fInputFile >> pBeam >> b;


  // If end of input file is reached : close it and abort run
  if ( fInputFile->eof() ) {
    LOG(info) << "FairShieldGenerator: End of input file reached ";
    CloseInput();
    return kFALSE;
  }

  LOG(info) << "FairShieldGenerator: Event " << eventId << ",  pBeam = "
	    << pBeam << "GeV, b = " << b << " fm, multiplicity " << nTracks;

  // Loop over tracks in the current event
  for (Int_t itrack=0; itrack<nTracks; itrack++) {

    // Read PID and momentum from file
    *fInputFile >> iPid >> iMass >> iCharge >> px >> py >> pz;

    // Case ion
    if ( iPid == 1000 ) {
      char ionName[20];
      sprintf(ionName, "Ion_%d_%d", iMass, iCharge);
      TParticlePDG* part = fPDG->GetParticle(ionName);
      if ( ! part ) {
        LOG(warn) << "FairShieldGenerator::ReadEvent: Cannot find "
		     << ionName << " in database!";
        continue;
      }
      pdgType = part->PdgCode();
    } else { pdgType = fPDG->ConvertGeant3ToPdg(iPid); } // "normal" particle

    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgType, px, py, pz, 0., 0., 0.);

  }


  return kTRUE;
}
// ------------------------------------------------------------------------



// -----   Private method CloseInput   ------------------------------------
void FairShieldGenerator::CloseInput()
{
  if ( fInputFile ) {
    if ( fInputFile->is_open() ) {
      LOG(info) << "FairShieldGenerator: Closing input file " << fFileName;
      fInputFile->close();
    }
    delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------



// -----   Private method RegisterIons   ----------------------------------
Int_t FairShieldGenerator::RegisterIons()
{

  Int_t nIons = 0;
  Int_t eventId, nTracks, iPid, iMass, iCharge;
  Double_t pBeam, b, px, py, pz;
  fIonMap.clear();

  while ( ! fInputFile->eof()) {

    *fInputFile >> eventId;
    *fInputFile >> nTracks;
    if (nTracks < 0 || nTracks > (INT_MAX-1)) LOG(fatal) << "Error reading the number of events from event header.";
    *fInputFile >> pBeam >> b;
    if ( fInputFile->eof() ) { continue; }
    for (Int_t iTrack=0; iTrack<nTracks; iTrack++) {
      *fInputFile >> iPid >> iMass >> iCharge >> px >> py >> pz;
      if ( iPid == 1000 ) { // ion
        char buffer[20];
        sprintf(buffer, "Ion_%d_%d", iMass, iCharge);
        TString ionName(buffer);
        if ( fIonMap.find(ionName) == fIonMap.end() ) { // new ion
          FairIon* ion = new FairIon(ionName, iCharge, iMass, iCharge);
          fIonMap[ionName] = ion;
          nIons++;
        }  // new ion
      }    // ion
    }      // track loop

  }        // event loop

  FairRunSim* run = FairRunSim::Instance();
  map<TString, FairIon*>::iterator mapIt;
  for (mapIt=fIonMap.begin(); mapIt!=fIonMap.end(); mapIt++) {
    FairIon* ion = (*mapIt).second;
    run->AddNewIon(ion);
  }

  return nIons;
}
// ------------------------------------------------------------------------






ClassImp(FairShieldGenerator)

