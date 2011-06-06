// -------------------------------------------------------------------------
// -----                FairPlutoGenerator source file                  -----
// -----          Created 13/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairPlutoGenerator.h"

#include "FairPrimaryGenerator.h"

#include "TClonesArray.h"
#include "TDatabasePDG.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TVector3.h"
#include "PParticle.h"

#include <iostream>

// -----   Default constructor   ------------------------------------------
FairPlutoGenerator::FairPlutoGenerator()
  :FairGenerator(),
   iEvent(0),
   fFileName(NULL),
   fInputFile(NULL),
   fInputTree(NULL),
   fParticles(NULL)
{
  /*
  iEvent     = 0;
  fInputFile = NULL;
  fInputTree = NULL;
  */
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
FairPlutoGenerator::FairPlutoGenerator(const Char_t* fileName)
  :FairGenerator(),
   iEvent(0),
   fFileName(fileName),
   fInputFile(new TFile(fileName)),
   fInputTree(NULL),
   fParticles(new TClonesArray("PParticle",100))
{
  /*
  iEvent     = 0;
  fFileName  = fileName;
  fInputFile = new TFile(fFileName);
  */
  fInputTree = (TTree*) fInputFile->Get("data");
  //  fParticles = new TClonesArray("PParticle",100);
  fInputTree->SetBranchAddress("Particles", &fParticles);
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
FairPlutoGenerator::~FairPlutoGenerator()
{
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairPlutoGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{

  // Check for input file
  if ( ! fInputFile ) {
    cout << "-E FairPlutoGenerator: Input file nor open!" << endl;
    return kFALSE;
  }

  // Check for number of events in input file
  if ( iEvent > fInputTree->GetEntries() ) {
    cout << "-E FairPlutoGenerator: No more events in input file!" << endl;
    CloseInput();
    return kFALSE;
  }
  TFile*  g=gFile;
  fInputFile->cd();
  fInputTree->GetEntry(iEvent++);
  g->cd();

  // Get PDG database
  TDatabasePDG* dataBase = TDatabasePDG::Instance();

  // Get number of particle in TClonesrray
  Int_t nParts = fParticles->GetEntriesFast();

  // Loop over particles in TClonesArray
  for (Int_t iPart=0; iPart < nParts; iPart++) {
    PParticle* part = (PParticle*) fParticles->At(iPart);
    Int_t pdgType = dataBase->ConvertGeant3ToPdg( part->ID() );

    // Check if particle type is known to database
    if ( ! pdgType ) {
      cout << "-W FairPlutoGenerator: Unknown type " << part->ID()
           << ", skipping particle." << endl;
      continue;
    }

    TLorentzVector mom = part->Vect4();
    Double_t px = mom.Px();
    Double_t py = mom.Py();
    Double_t pz = mom.Pz();

    TVector3 vertex = part->getVertex();
    Double_t vx = vertex.x();
    Double_t vy = vertex.y();
    Double_t vz = vertex.z();

    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgType, px, py, pz, vx, vy, vz);

  }        //  Loop over particle in event

  return kTRUE;

}
// ------------------------------------------------------------------------




// -----   Private method CloseInput   ------------------------------------
void FairPlutoGenerator::CloseInput()
{
  if ( fInputFile ) {
    cout << "-I FairPlutoGenerator: Closing input file " << fFileName
         << endl;
    fInputFile->Close();
    delete fInputFile;
  }
  fInputFile = NULL;
}
// ------------------------------------------------------------------------



ClassImp(FairPlutoGenerator)
