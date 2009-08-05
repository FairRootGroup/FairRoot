/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Saul Beceiro Novo        saul.beceiro@rai.usc.es
//             Hector Alvarez-Pol       hapol@fpddux.usc.es
//*-- Date: 03/2007
//*-- Last Update: 07/05/07 by Hector Alvarez
// --------------------------------------------------------------
// Description:
//   Coulomb Disociation generators interface
//
// --------------------------------------------------------------
// Comments:
// 
//     - 07/05/07 Adding setters for including emittance
//     - 03/05/07 Cleaning and moving to svn repository
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef R3BCDGenerator_h
#define R3BCDGenerator_h 1

#include "TObject.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class R3BCDGenerator :  public TObject {
  
private:
  Double_t  px1; //momentum components for particle 1
  Double_t  py1;
  Double_t  pz1;
  Double_t  E1;  //energy for particle 1
  Double_t  px2; //momentum components for particle 2
  Double_t  py2;
  Double_t  pz2;
  Double_t  E2;  //energy for particle 1

  ifstream* inputFile;
   
public:
  
  R3BCDGenerator();
  ~R3BCDGenerator();
  
  void ReadNewLine();

  Double_t GetPx1(){return px1;}
  Double_t GetPy1(){return py1;}
  Double_t GetPz1(){return pz1;}
  Double_t GetE1(){return E1;}
  Double_t GetPx2(){return px2;}
  Double_t GetPy2(){return py2;}
  Double_t GetPz2(){return pz2;}
  Double_t GetE2(){return E2;}

  void SetPx1(Double_t px){px1=px;}
  void SetPy1(Double_t py){py1=py;}
  void SetPz1(Double_t pz){pz1=pz;}
  void SetE1(Double_t E){E1=E;}
  void SetPx2(Double_t px){px2=px;}
  void SetPy2(Double_t py){py2=py;}
  void SetPz2(Double_t pz){pz2=pz;}
  void SetE2(Double_t E){E2=E;}
  

  ClassDef(R3BCDGenerator,1);
};
#endif
