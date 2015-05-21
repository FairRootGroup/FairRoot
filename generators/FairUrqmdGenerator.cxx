/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairUrqmdGenerator source file                  -----
// -----                Created 24/06/04  by V. Friese                 -----
// -------------------------------------------------------------------------
#include "FairUrqmdGenerator.h"

#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator
#include "FairLogger.h"                 // for logging

#include "Riosfwd.h"                    // for ostream, ifstream
#include "TDatabasePDG.h"               // for TDatabasePDG
#include "TLorentzVector.h"             // for TLorentzVector
#include "TMath.h"                      // for Sqrt, sqrt
#include "TParticlePDG.h"               // for TParticlePDG
#include "TString.h"                    // for TString, operator+
#include "TVector3.h"                   // for TVector3

#include <stdlib.h>                     // for getenv
#include <fstream>                      // IWYU pragma: keep for ifstream

// -----   Default constructor   ------------------------------------------
FairUrqmdGenerator::FairUrqmdGenerator()
  :FairGenerator(),
   fInputFile(NULL),
   fParticleTable(),
   fFileName(NULL)
{
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
FairUrqmdGenerator::FairUrqmdGenerator(const char* fileName)
  :FairGenerator(),
   fInputFile(NULL),
   fParticleTable(),
   fFileName(fileName)
{
  //  fFileName = fileName;
  LOG(INFO) << "FairUrqmdGenerator: Opening input file " 
	    << fileName << FairLogger::endl;
  fInputFile = fopen(fFileName, "r");
  if ( ! fInputFile ) { 
    LOG(FATAL) << "Cannot open input file."
	       << FairLogger::endl; 
  }
  ReadConversionTable();
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
FairUrqmdGenerator::~FairUrqmdGenerator()
{
  //  LOG(DEBUG) << "Enter Destructor of FairUrqmdGenerator"
  //             << FairLogger::endl;
  if ( fInputFile ) {
    fclose(fInputFile);
    fInputFile = NULL;
  }
  fParticleTable.clear();
  //  LOG(DEBUG) << "Leave Destructor of FairUrqmdGenerator"
  //             << FairLogger::endl;
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairUrqmdGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

  // ---> Check for input file
  if ( ! fInputFile ) {
    LOG(ERROR) << "FairUrqmdGenerator: Input file not open! " 
	       << FairLogger::endl;
    return kFALSE;
  }

  // ---> Check for primary generator
  if ( ! primGen ) {
    LOG(ERROR) << "FairUrqmdGenerator::ReadEvent: "
	       << "No PrimaryGenerator!" << FairLogger::endl;
    return kFALSE;
  }

  // ---> Define event variables to be read from file
  int evnr=0, ntracks=0, aProj=0, zProj=0, aTarg=0, zTarg=0;
  float b = 0., ekin = 0.;

  int ityp=0, i3=0, ichg=0, pid=0;
  float ppx=0., ppy=0., ppz=0., m=0.;

  // ---> Read and check first event header line from input file
  char read[200];
  fgets(read, 200, fInputFile);
  if ( feof(fInputFile) ) {
    LOG(INFO) << "FairUrqmdGenerator : End of input file reached." 
	      << FairLogger::endl;
    fclose(fInputFile);
    fInputFile = NULL;
    return kFALSE;
  }
  if ( read[0] != 'U' ) {
    LOG(ERROR) << "FairUrqmdGenerator: Wrong event header" 
	       << FairLogger::endl;
    return kFALSE;
  }

  Int_t retval = 0;

  // ---> Read rest of event header
  fgets(read, 26, fInputFile);
  retval = fscanf(fInputFile, "%d", &aProj);
  CheckReturnValue(retval);
  retval = fscanf(fInputFile, "%d", &zProj);
  CheckReturnValue(retval);
  fgets(read, 25, fInputFile);
  retval = fscanf(fInputFile, "%d", &aTarg);
  CheckReturnValue(retval);
  retval = fscanf(fInputFile, "%d", &zTarg);
  CheckReturnValue(retval);
  fgets(read, 200, fInputFile);
  fgets(read, 200, fInputFile);
  fgets(read, 36, fInputFile);
  retval = fscanf(fInputFile, "%f", &b);
  CheckReturnValue(retval);
  fgets(read, 200, fInputFile);
  fgets(read, 39, fInputFile);
  retval = fscanf(fInputFile, "%e", &ekin);
  CheckReturnValue(retval);
  fgets(read, 200, fInputFile);
  fgets(read, 7, fInputFile);
  retval = fscanf(fInputFile, "%d", &evnr);
  CheckReturnValue(retval);
  fgets(read, 200, fInputFile);
  for (int iline=0; iline<8; iline++)  { fgets(read, 200,fInputFile); }
  retval = fscanf(fInputFile, "%d", &ntracks);
  CheckReturnValue(retval);
  fgets(read, 200, fInputFile);
  fgets(read, 200, fInputFile);

  // ---> Calculate beta and gamma for Lorentztransformation
  TDatabasePDG* pdgDB = TDatabasePDG::Instance();
  TParticlePDG* kProton = pdgDB->GetParticle(2212);
  Double_t kProtonMass=kProton->Mass();

  Double_t eBeam   = ekin + kProtonMass;
  Double_t pBeam   = TMath::Sqrt(eBeam*eBeam - kProtonMass*kProtonMass);
  Double_t betaCM  = pBeam / (eBeam + kProtonMass);
  Double_t gammaCM = TMath::Sqrt( 1. / ( 1. - betaCM*betaCM) );

  LOG(INFO) << "FairUrqmdGenerator: Event " << evnr << ",  b = " << b
	    << " fm,  multiplicity " << ntracks  << ", ekin: " 
	    << ekin << FairLogger::endl;

  // Set event id and impact parameter in MCEvent if not yet done
  FairMCEventHeader* event = primGen->GetEvent();
  if ( event && (! event->IsSet()) ) {
    event->SetEventID(evnr);
    event->SetB(b);
    event->MarkSet(kTRUE);
  }


  // ---> Loop over tracks in the current event
  for(int itrack=0; itrack<ntracks; itrack++) {

    // Read momentum and PID from file
    fgets(read, 81, fInputFile);
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
    fgets(read, 200, fInputFile);

    // Convert UrQMD type and charge to unique pid identifier
    if (ityp >= 0) { pid =  1000 * (ichg+2) + ityp; }
    else { pid = -1000 * (ichg+2) + ityp; }

    // Convert Unique PID into PDG particle code
    if (fParticleTable.find(pid) == fParticleTable.end()) {
      LOG(WARNING) << "FairUrqmdGenerator: PID " << ityp << " charge "
		   << ichg << " not found in table (" << pid << ")" 
		   << FairLogger::endl;
      continue;
    }
    Int_t pdgID = fParticleTable[pid];

    // Lorentztransformation to lab
    Double_t mass = Double_t(m);
    Double_t px   = Double_t(ppx);
    Double_t py   = Double_t(ppy);
    Double_t pz   = Double_t(ppz);
    Double_t e    = sqrt( mass*mass + px*px + py*py + pz*pz );
    pz = gammaCM * ( pz + betaCM * e );
    Double_t ee = sqrt( mass*mass + px*px + py*py + pz*pz );

    TVector3 aa(px,py,pz);
    TLorentzVector pp;
    pp.SetPx( px );
    pp.SetPy( py );
    pp.SetPz( pz);
    pp.SetE( ee );

    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgID, px, py, pz, 0., 0., 0.);

  }

  return kTRUE;
}
// ------------------------------------------------------------------------


// -----   Public method ReadEvent   --------------------------------------
Bool_t FairUrqmdGenerator::SkipEvents(Int_t count)
{
  if (count<=0) { return kTRUE; }

  for(Int_t ii=0; ii<count; ii++) {
    // ---> Check for input file
    if ( ! fInputFile ) {
      LOG(ERROR) << "FairUrqmdGenerator: Input file not open! " 
		 << FairLogger::endl;
      return kFALSE;
    }

    // ---> Define event variables to be read from file
    int evnr=0, ntracks=0, aProj=0, zProj=0, aTarg=0, zTarg=0;
    float b = 0., ekin = 0.;

    // ---> Read and check first event header line from input file
    char read[200];
    fgets(read, 200, fInputFile);
    if ( feof(fInputFile) ) {
      LOG(INFO) << "FairUrqmdGenerator : End of input file reached." 
		<< FairLogger::endl;
      fclose(fInputFile);
      fInputFile = NULL;
      return kFALSE;
    }
    if ( read[0] != 'U' ) {
      LOG(ERROR) << "FairUrqmdGenerator: Wrong event header" 
		 << FairLogger::endl;
      return kFALSE;
    }

    Int_t retval = 0;

    // ---> Read rest of event header
    fgets(read, 26, fInputFile);
    retval = fscanf(fInputFile, "%d", &aProj);
    CheckReturnValue(retval);
    retval = fscanf(fInputFile, "%d", &zProj);
    CheckReturnValue(retval);
    fgets(read, 25, fInputFile);
    retval = fscanf(fInputFile, "%d", &aTarg);
    CheckReturnValue(retval);
    retval = fscanf(fInputFile, "%d", &zTarg);
    CheckReturnValue(retval);
    fgets(read, 200, fInputFile);
    fgets(read, 200, fInputFile);
    fgets(read, 36, fInputFile);
    retval = fscanf(fInputFile, "%f", &b);
    CheckReturnValue(retval);
    fgets(read, 200, fInputFile);
    fgets(read, 39, fInputFile);
    retval = fscanf(fInputFile, "%e", &ekin);
    CheckReturnValue(retval);
    fgets(read, 200, fInputFile);
    fgets(read, 7, fInputFile);
    retval = fscanf(fInputFile, "%d", &evnr);
    CheckReturnValue(retval);
    fgets(read, 200, fInputFile);
    for (int iline=0; iline<8; iline++)  { fgets(read, 200,fInputFile); }
    retval = fscanf(fInputFile, "%d", &ntracks);
    CheckReturnValue(retval);
    fgets(read, 200, fInputFile);
    fgets(read, 200, fInputFile);

    LOG(INFO) << "FairUrqmdGenerator: Event " << evnr << " skipped!" 
	      << FairLogger::endl;

    // ---> Loop over tracks in the current event
    for(int itrack=0; itrack<ntracks; itrack++) {

      // Read momentum and PID from file
      fgets(read, 81, fInputFile);
      fgets(read, 200, fInputFile);
    }
  }
  return kTRUE;
}
// ------------------------------------------------------------------------

// -----   Private method ReadConverisonTable   ---------------------------
void FairUrqmdGenerator::ReadConversionTable()
{

  TString work      = getenv("VMCWORKDIR");
  TString fileName  = work + "/input/urqmd_pdg.dat";
  std::ifstream* pdgconv = new std::ifstream(fileName.Data());

  if (!pdgconv->good()) {
    LOG(FATAL) << "Could not open Urqmd->PDG input file " 
	       << fileName << FairLogger::endl;
  }

  Int_t index = 0;
  Int_t pdgId = 0;

  while ( ! pdgconv->eof() ) {
    index =pdgId =0 ;
    *pdgconv >> index >> pdgId ;
    fParticleTable[index] = pdgId;
  }

  pdgconv->close();
  delete pdgconv;

  LOG(INFO) << "FairUrqmdGenerator: Particle table for conversion from "
	    << "UrQMD loaded" <<  FairLogger::endl;

}
// ------------------------------------------------------------------------

void FairUrqmdGenerator::CheckReturnValue(Int_t retval)
{
  if (1 != retval) { 
    LOG(ERROR) << "Error when reading variable from input file"
	       << FairLogger::endl;
  } 
} 

ClassImp(FairUrqmdGenerator);
