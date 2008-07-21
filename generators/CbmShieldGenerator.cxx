// -------------------------------------------------------------------------
// -----                CbmShieldGenerator source file                 -----
// -----                Created 15/09/06  by V. Friese                 -----
// -------------------------------------------------------------------------
#include "CbmShieldGenerator.h"

#include "CbmPrimaryGenerator.h"
#include "CbmIon.h"
#include "CbmRunSim.h"

#include "TDatabasePDG.h"
#include "TParticlePDG.h"

#include <iostream>

using std::cout;
using std::endl;
using std::map;

// -----   Default constructor   ------------------------------------------
CbmShieldGenerator::CbmShieldGenerator() {}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
CbmShieldGenerator::CbmShieldGenerator(const char* fileName) {

  fPDG=TDatabasePDG::Instance();
  fFileName  = fileName;
  cout << "-I- CbmShieldGenerator: Opening input file " << fileName << endl;
  fInputFile = new ifstream(fFileName);
  if ( ! fInputFile->is_open() ) 
    Fatal("CbmShieldGenerator","Cannot open input file.");
  cout << "-I- CbmShieldGenerator: Looking for ions..." << endl;
  Int_t nIons = RegisterIons();
  cout << "-I- CbmShieldGenerator: " << nIons << " ions registered." 
       << endl;
  CloseInput();
  cout << "-I- CbmShieldGenerator: Reopening input file " << fileName 
       << endl;
  fInputFile = new ifstream(fFileName);
   
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
CbmShieldGenerator::~CbmShieldGenerator() {
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t CbmShieldGenerator::ReadEvent(CbmPrimaryGenerator* primGen) {

  // Check for input file
  if ( ! fInputFile->is_open() ) {
    cout << "-E- CbmShieldGenerator: Input file not open!" << endl;
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
    cout << "-I- CbmShieldGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }

  cout << "-I- CbmShieldGenerator: Event " << eventId << ",  pBeam = "
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
	cout << "-W- CbmShieldGenerator::ReadEvent: Cannot find "
	     << ionName << " in database!" << endl;
	continue;
      }
      pdgType = part->PdgCode();
    }
    else pdgType = fPDG->ConvertGeant3ToPdg(iPid);  // "normal" particle
    
    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgType, px, py, pz, 0., 0., 0.);

  }


  return kTRUE;
}
// ------------------------------------------------------------------------



// -----   Private method CloseInput   ------------------------------------
void CbmShieldGenerator::CloseInput() {
  if ( fInputFile ) {
    if ( fInputFile->is_open() ) {
       cout << "-I- CbmShieldGenerator: Closing input file " 
	    << fFileName << endl;
       fInputFile->close();
    }
    delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------



// -----   Private method RegisterIons   ----------------------------------
Int_t CbmShieldGenerator::RegisterIons() {

  Int_t nIons = 0;
  Int_t eventId, nTracks, iPid, iMass, iCharge;
  Double_t pBeam, b, px, py, pz;
  fIonMap.clear();

  while ( ! fInputFile->eof()) {
    
    *fInputFile >> eventId >> nTracks >> pBeam >> b;
    if ( fInputFile->eof() ) continue;
    for (Int_t iTrack=0; iTrack<nTracks; iTrack++) {
      *fInputFile >> iPid >> iMass >> iCharge >> px >> py >> pz;
      if ( iPid == 1000 ) { // ion
	char buffer[20];
	sprintf(buffer, "Ion_%d_%d", iMass, iCharge);
	TString ionName(buffer);
	if ( fIonMap.find(ionName) == fIonMap.end() ) { // new ion
	  CbmIon* ion = new CbmIon(ionName, iCharge, iMass, iCharge);
	  fIonMap[ionName] = ion;
	  nIons++;
	}  // new ion
      }    // ion
    }      // track loop

  }        // event loop

  CbmRunSim* run = CbmRunSim::Instance();
  map<TString, CbmIon*>::iterator mapIt;
  for (mapIt=fIonMap.begin(); mapIt!=fIonMap.end(); mapIt++) {
    CbmIon* ion = (*mapIt).second;
    run->AddNewIon(ion);
  }

  return nIons;
}
// ------------------------------------------------------------------------


      
 


ClassImp(CbmShieldGenerator)

