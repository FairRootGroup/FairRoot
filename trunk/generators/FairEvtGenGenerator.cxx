// -------------------------------------------------------------------------
// -----             FairEvtGenGenerator source file                      -----
// -----          Created 09/10/06  by S. Spataro                      -----
// -------------------------------------------------------------------------
#include "FairEvtGenGenerator.h"

#include "FairPrimaryGenerator.h"

#include <iostream>
#include <cstdio>

// New includes here:

#include "TMath.h"
#include "TRandom.h"

using std::cout;
using std::endl;
using std::max;





// -----   Default constructor   ------------------------------------------
FairEvtGenGenerator::FairEvtGenGenerator()
  : FairGenerator(),
    fFileName(""),
    fInputFile(NULL),
    fGasmode(0),
    fRsigma (0.),
    fDensityFunction(NULL)
{
}
// ------------------------------------------------------------------------

// -----   Standard constructor   -----------------------------------------
FairEvtGenGenerator::FairEvtGenGenerator(const char* fileName)
  :FairGenerator ("EvtGen", fileName),
   fFileName(fileName),
   fInputFile(NULL),
   fGasmode(0),
   fRsigma (0.),
   fDensityFunction(0)
{
  cout << "-I FairEvtGenGenerator: Opening input file " << fileName << endl;
  if ((fInputFile = fopen(fFileName,"r"))==NULL)
    //  fInputFile = new ifstream(fFileName);
    //  if ( ! fInputFile->is_open() )
  {
    Fatal("FairEvtGenGenerator","Cannot open input file.");
  }

  // fPDG=TDatabasePDG::Instance();
}
// ------------------------------------------------------------------------


// -----   Gas mode constructor   -----------------------------------------
FairEvtGenGenerator::FairEvtGenGenerator(const char* fileName, Double_t Rsigma, TF1* DensityFunction)
  :FairGenerator ("EvtGen", fileName),
   fFileName(fileName),
   fInputFile(NULL),
   fGasmode(1),
   fRsigma (Rsigma),
   fDensityFunction(DensityFunction)
{
  cout << "-I FairEvtGenGenerator: Opening input file " << fileName << endl;
  if ((fInputFile = fopen(fFileName,"r"))==NULL) {
    Fatal("FairEvtGenGenerator","Cannot open input file.");
  }

}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
FairEvtGenGenerator::~FairEvtGenGenerator()
{
  if(fDensityFunction) { delete fDensityFunction; }
  if(fInputFile) { fclose(fInputFile); }
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairEvtGenGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

  // Check for input file
  if (!fInputFile) {
    // if ( ! fInputFile->is_open() ) {
    cout << "-E FairEvtGenGenerator: Input file not open!" << endl;
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

    for (Int_t ll=0; ll<ntracks; ll++) {
      ncols = fscanf(fInputFile,"%d %d %d %d %d %d %d %g %f %f %f %f %f %f %f", &nLine, &pdgID, &nDecay, &nM1, &nM2, &nDF, &nDL, &fPx, &fPy, &fPz, &fE, &fT, &fVx, &fVy, &fVz);
//  cout << nLine << "\t" << pdgID << "\t" << nDecay << "\t" << nM1 << "\t" << nM2 << "\t" << nDF << "\t" << nDL <<
      //  "\t" << fPx << "\t" << fPy << "\t" << fPz << "\t" << fE << "\t" << fT << "\t" << fVx << "\t" << fVy << "\t" << fVz << endl;
      max_nr = max(max_nr, nDF);
      max_nr = max(max_nr, nDL);
      if ((nDF==-1) && (nDL==-1)) {

        /* Check if fGasmode is set */
        if (fGasmode == 1) {

          // Random 2D point in a circle of radius r (simple beamprofile)
          Double_t fX, fY, fZ, radius;
          radius = gRandom->Gaus(0,fRsigma);
          gRandom->Circle(fX, fY, radius);
          fVx = fVx + fX;
          fVy = fVy + fY;

          // calculate fZ according to some (probability) density function of the
          // gas
          fZ=fDensityFunction->GetRandom();
          fVz = fVz + fZ;

        }
//    printf("Insert coordinates: %f, %f, %f ...\n", fVx, fVy, fVz);
        primGen->AddTrack(pdgID, fPx, fPy, fPz, fVx, fVy, fVz);

      }
    }
  } else {
    cout << "-I FairEvtGenGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }


  // If end of input file is reached : close it and abort run
  if ( feof(fInputFile) ) {
    cout << "-I FairEvtGenGenerator: End of input file reached " << endl;
    CloseInput();
    return kFALSE;
  }

  /*
    cout << "-I FairEvtGenGenerator: Event " << eventID << ",  vertex = ("
    << vx << "," << vy << "," << vz << ") cm,  multiplicity "
    << ntracks << endl;
  */

  return kTRUE;
}
// ------------------------------------------------------------------------



// -----   Private method CloseInput   ------------------------------------
void FairEvtGenGenerator::CloseInput()
{
  if ( fInputFile ) {
    //if ( fInputFile->is_open() ) {
    {
      cout << "-I FairEvtGenGenerator: Closing input file "
           << fFileName << endl;
      //  fInputFile->close();

      fclose(fInputFile);
    }
    // delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------


ClassImp(FairEvtGenGenerator)

