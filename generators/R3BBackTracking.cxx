/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Saul Beceiro Novo        saul.beceiro@rai.usc.es
//           
//*-- Date: 03/2008
//*-- Last Update: 24/03/08 by Saul Beceiro
// --------------------------------------------------------------
// Description:
//   Back Tracking reconstruction generators interface
//
// --------------------------------------------------------------
// Comments:
// 
//   
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "R3BBackTracking.h"
#include <iostream>
#include "TSystem.h"
#include "TString.h"

using namespace std;

ClassImp(R3BBackTracking)


R3BBackTracking::R3BBackTracking(){
  //
  // Constructor
  //

  px1 = 0.; //unitary momentum components for particle 1
  py1 = 0.;
  pz1 = 0.;
  pprim = 0.;//real momentum (obtained with the simulation)
  x1 = 0.; //position in DCH2 (starting point)
  y1=0.;
  z1=0.;
  x0=0.; //position measured in target
  y0=0.;
  z0=0.;

    
  TString WorkDir = gSystem->Getenv("VMCWORKDIR");
  TString kine = WorkDir+"/input/kine/reconstructionSim.dat";
  inputFile = new ifstream(kine.Data());

  // cout << "Entrada en fichero"<< *inputFile.tellg() << endl;
  //while(!eof) *inputFile.peek();
  //cout << "Salida de fichero"<<*inputFile.tellg()<< endl; 
  }
 
R3BBackTracking::~R3BBackTracking(){
  //
  // Destructor
  //

  delete inputFile;
}

void R3BBackTracking::ReadNewLine(){
  //
  // Reads a new line from the CD input file
  //
  
  Char_t* myChar= new Char_t[256];

  //  cout << inputFile << "" << *inputFile << endl;  
  // cout << "Estoy en el caracter del fichero: "<< (*inputFile).tellg() << endl;  
  //(*inputFile).seekg((int)(12100000*0.00001));
  // cout << "y me muevo a: "<<(*inputFile).tellg() << endl;
  
  // cout << "mirame, tonto!" << endl;
  // cout << &myChar << "          "<< myChar << "             " <<*myChar << endl;

  (*inputFile).getline(myChar,256);

  //cout << myChar << " " <<*myChar << endl;

  *inputFile >> px1 >> py1 >> pz1 >> x1 >> y1 >> z1 >> x0 >> y0 >> z0 >>pprim;  
  //cout << "cuchufletas las justas!" << endl;
  
}
