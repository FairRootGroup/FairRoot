// -------------------------------------------------------------------------
// -----                CbmAsciiGenerator source file                  -----
// -----          Created 09/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "CbmAsciiGenerator.h"

#include "CbmPrimaryGenerator.h"

#include "TDatabasePDG.h"

#include <iostream>

using std::cout;
using std::endl;

// -----   Default constructor   ------------------------------------------
CbmAsciiGenerator::CbmAsciiGenerator() 
:fInputFile(0),
fFileName("")
{
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
CbmAsciiGenerator::CbmAsciiGenerator(const char* fileName) 
:fInputFile(0),
fFileName( fileName)
{
  fFileName  = fileName;
  cout << "-I CbmAsciiGenerator: Opening input file " << fileName << endl;
  fInputFile = new ifstream(fFileName);
  if ( ! fInputFile->is_open() ) 
    Fatal("CbmAsciiGenerator","Cannot open input file.");
    
  // fPDG=TDatabasePDG::Instance();
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
CbmAsciiGenerator::~CbmAsciiGenerator() {
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t CbmAsciiGenerator::ReadEvent(CbmPrimaryGenerator* primGen) {

  // Check for input file
  if ( ! fInputFile->is_open() ) {
    cout << "-E CbmAsciiGenerator: Input file not open!" << endl;
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
    cout << "-I CbmAsciiGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }

  cout << "-I CbmAsciiGenerator: Event " << eventID << ",  vertex = ("
       << vx << "," << vy << "," << vz << ") cm,  multiplicity "
       << ntracks << endl;

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
void CbmAsciiGenerator::CloseInput() {
  if ( fInputFile ) {
    if ( fInputFile->is_open() ) {
       cout << "-I CbmAsciiGenerator: Closing input file " 
	    << fFileName << endl;
       fInputFile->close();
    }
    delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------


ClassImp(CbmAsciiGenerator)

