/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairAsciiGenerator source file                  -----
// -----          Created 09/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairAsciiGenerator.h"

#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator
#include "FairLogger.h"

#include <stddef.h>                     // for NULL

// -----   Default constructor   ------------------------------------------
FairAsciiGenerator::FairAsciiGenerator()
  :FairGenerator(),
   fInputFile(NULL),
   fFileName("")
{
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
FairAsciiGenerator::FairAsciiGenerator(const char* fileName)
  :FairGenerator(),
   fInputFile(0),
   fFileName(fileName)
{
  //  fFileName  = fileName;
  LOG(INFO) << "FairAsciiGenerator: Opening input file " 
	    << fileName << FairLogger::endl;
  fInputFile = new std::ifstream(fFileName);
  if ( ! fInputFile->is_open() ) {
    LOG(FATAL) << "Cannot open input file." << FairLogger::endl;
  }

  // fPDG=TDatabasePDG::Instance();
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
FairAsciiGenerator::~FairAsciiGenerator()
{
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairAsciiGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

  // Check for input file
  if ( ! fInputFile->is_open() ) {
    LOG(ERROR) << "FairAsciiGenerator: Input file not open!" 
	       << FairLogger::endl;
    return kFALSE;
  }


  // Define event variable to be read from file
  Int_t ntracks = 0, eventID = 0;
  Double_t vx = 0., vy = 0., vz = 0.;

  // Define track variables to be read from file
  Int_t pdgID = 0;
  Double_t px = 0., py = 0., pz = 0.;

  // Read event header line from input file
  *fInputFile >> ntracks >> eventID >>  vx >>  vy >>  vz;

  // If end of input file is reached : close it and abort run
  if ( fInputFile->eof() ) {
    LOG(INFO) << "FairAsciiGenerator: End of input file reached " 
	      << FairLogger::endl;
    CloseInput();
    return kFALSE;
  }

  LOG(INFO) << "FairAsciiGenerator: Event " << eventID << ",  vertex = ("
	    << vx << "," << vy << "," << vz << ") cm,  multiplicity "
	    << ntracks << FairLogger::endl;

  // Loop over tracks in the current event
  for (Int_t itrack=0; itrack<ntracks; itrack++) {

    // Read PID and momentum from file
    *fInputFile >> pdgID >> px >> py >> pz;
    // convert Geant3 code to PDG code

    // Int_t pdg= fPDG->ConvertGeant3ToPdg(pdgID);

    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgID, px, py, pz, vx, vy, vz);

  }


  return kTRUE;
}
// ------------------------------------------------------------------------



// -----   Private method CloseInput   ------------------------------------
void FairAsciiGenerator::CloseInput()
{
  if ( fInputFile ) {
    if ( fInputFile->is_open() ) {
      LOG(INFO) << "FairAsciiGenerator: Closing input file "
		<< fFileName << FairLogger::endl;
      fInputFile->close();
    }
    delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------


ClassImp(FairAsciiGenerator)

