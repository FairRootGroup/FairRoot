/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#include "TDatabasePDG.h"               // for TDatabasePDG
#include "TParticlePDG.h"               // for TParticlePDG

#include <stdio.h>                      // for NULL, sprintf
#include <iostream>                     // for cout
#include <utility>                      // for pair

using std::cout;
using std::endl;
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

  //  fPDG=TDatabasePDG::Instance();
  //  fFileName  = fileName;
  cout << "-I- FairShieldGenerator: Opening input file " << fileName << endl;
  fInputFile = new ifstream(fFileName);
  if ( ! fInputFile->is_open() ) {
    Fatal("FairShieldGenerator","Cannot open input file.");
  }
  cout << "-I- FairShieldGenerator: Looking for ions..." << endl;
  Int_t nIons = RegisterIons();
  cout << "-I- FairShieldGenerator: " << nIons << " ions registered."
       << endl;
  CloseInput();
  cout << "-I- FairShieldGenerator: Reopening input file " << fileName
       << endl;
  fInputFile = new ifstream(fFileName);
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
    cout << "-E- FairShieldGenerator: Input file not open!" << endl;
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
  *fInputFile >> eventId >> nTracks >> pBeam >> b;

  // If end of input file is reached : close it and abort run
  if ( fInputFile->eof() ) {
    cout << "-I- FairShieldGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }

  cout << "-I- FairShieldGenerator: Event " << eventId << ",  pBeam = "
       << pBeam << "GeV, b = " << b << " fm, multiplicity " << nTracks
       << endl;

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
        cout << "-W- FairShieldGenerator::ReadEvent: Cannot find "
             << ionName << " in database!" << endl;
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
      cout << "-I- FairShieldGenerator: Closing input file "
           << fFileName << endl;
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

    *fInputFile >> eventId >> nTracks >> pBeam >> b;
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

