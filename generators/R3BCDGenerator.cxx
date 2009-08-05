/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Saul Beceiro Novo        saul.beceiro@rai.usc.es
//             Hector Alvarez-Pol       hapol@fpddux.usc.es
//*-- Date: 03/2007
//*-- Last Update: 03/05/07 by Hector Alvarez
// --------------------------------------------------------------
// Description:
//   Coulomb Disociation generators interface
//
// --------------------------------------------------------------
// Comments:
// 
//    - 03/05/07 Cleaning and moving to svn repository
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "R3BCDGenerator.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TString.h"


using namespace std;



R3BCDGenerator::R3BCDGenerator(){
  //
  // Constructor
  //


  px1 = 0.; //momentum components for particle 1
  py1 = 0.;
  pz1 = 0.;
  E1 = 0.;  //energy for particle 1
  px2 = 0.; //momentum components for particle 2
  py2 = 0.;
  pz2 = 0.;
  E2 = 0.;
 
  
  TString WorkDir = gSystem->Getenv("VMCWORKDIR");
  TString kine = WorkDir+"/input/kine/sim_27P.dat";
  inputFile = new ifstream(kine.Data());

  }
 
R3BCDGenerator::~R3BCDGenerator(){
  //
  // Destructor
  //

  delete inputFile;
}

void R3BCDGenerator::ReadNewLine(){
  //
  // Reads a new line from the CD input file
  //
  
  Char_t * myChar= new Char_t[256];
   (*inputFile).seekg((int)(12100000*gRandom->Rndm()));
  
   (*inputFile).getline(myChar,256);
 
   *inputFile >> E1  >> px1 >> py1 >> pz1 
	      >> E2  >> px2 >> py2 >> pz2;	     
}


ClassImp(R3BCDGenerator)
