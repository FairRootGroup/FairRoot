// -------------------------------------------------------------------------
// -----             CbmEvtGenGenerator source file                      -----
// -----          Created 09/10/06  by S. Spataro                      -----
// -------------------------------------------------------------------------
#include "CbmEvtGenGenerator.h"

#include "CbmPrimaryGenerator.h"

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;
using std::max;

// -----   Default constructor   ------------------------------------------
CbmEvtGenGenerator::CbmEvtGenGenerator() {}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
CbmEvtGenGenerator::CbmEvtGenGenerator(const char* fileName) {
  fFileName  = fileName;
  cout << "-I CbmEvtGenGenerator: Opening input file " << fileName << endl;
  if ((fInputFile = fopen(fFileName,"r"))==NULL)
    //  fInputFile = new ifstream(fFileName);
    //  if ( ! fInputFile->is_open() ) 
    Fatal("CbmEvtGenGenerator","Cannot open input file.");
  
  // fPDG=TDatabasePDG::Instance();
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
CbmEvtGenGenerator::~CbmEvtGenGenerator() {
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t CbmEvtGenGenerator::ReadEvent(CbmPrimaryGenerator* primGen) {

  // Check for input file
  if (!fInputFile) {
    // if ( ! fInputFile->is_open() ) {
    cout << "-E CbmEvtGenGenerator: Input file not open!" << endl;
    return kFALSE;
  }
  
  // Define event variable to be read from file
   Int_t ntracks = 0, eventID = 0, ncols = 0;
 
  // Define track variables to be read from file
  Int_t nLine = 0, pdgID = 0, nDecay = 0, nM1 = -1, nM2 = -1, nDF = -1, nDL = -1;
  Float_t fPx = 0., fPy = 0., fPz = 0., fE = 0.;
  Float_t fVx = 0., fVy = 0., fVz = 0., fT = 0.;
  
  // Read event header line from input file

  Int_t max_nr = 0;
  
  Text_t buffer[200];
  ncols = fscanf(fInputFile,"%d\t%d", &eventID, &ntracks);
  
  if (ncols && ntracks>0) {
    
   // cout << "Event number: " << eventID << "\tNtracks: " << ntracks << endl;
    for (Int_t ii=0; ii<15; ii++) {
      ncols = fscanf(fInputFile,"%s",buffer);
   //   cout << buffer << "\t" ;
    }
    //cout << endl;
     
    for (Int_t ll=0; ll<ntracks; ll++) 
      {
	ncols = fscanf(fInputFile,"%d %d %d %d %d %d %d %g %f %f %f %f %f %f %f", &nLine, &pdgID, &nDecay, &nM1, &nM2, &nDF, &nDL, &fPx, &fPy, &fPz, &fE, &fT, &fVx, &fVy, &fVz);
//	cout << nLine << "\t" << pdgID << "\t" << nDecay << "\t" << nM1 << "\t" << nM2 << "\t" << nDF << "\t" << nDL <<
	//  "\t" << fPx << "\t" << fPy << "\t" << fPz << "\t" << fE << "\t" << fT << "\t" << fVx << "\t" << fVy << "\t" << fVz << endl;
	max_nr = max(max_nr, nDF);
	max_nr = max(max_nr, nDL);
	if ((nDF==-1) && (nDL==-1))  
	  primGen->AddTrack(pdgID, fPx, fPy, fPz, fVx, fVy, fVz);
      }
  }
  else {
    cout << "-I CbmEvtGenGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }
  

  // If end of input file is reached : close it and abort run
  if ( feof(fInputFile) ) {
    cout << "-I CbmEvtGenGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }
  
  /*
    cout << "-I CbmEvtGenGenerator: Event " << eventID << ",  vertex = ("
    << vx << "," << vy << "," << vz << ") cm,  multiplicity "
    << ntracks << endl;
  */
  
  return kTRUE;
}
// ------------------------------------------------------------------------



// -----   Private method CloseInput   ------------------------------------
void CbmEvtGenGenerator::CloseInput() {
  if ( fInputFile ) {
    //if ( fInputFile->is_open() ) {
    {
      cout << "-I CbmEvtGenGenerator: Closing input file " 
	   << fFileName << endl;
      //  fInputFile->close();
      
      fclose(fInputFile);
    }
    delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------


ClassImp(CbmEvtGenGenerator)

