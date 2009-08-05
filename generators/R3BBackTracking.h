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


#ifndef R3BBackTracking_h
#define R3BBackTracking_h 1

#include "TObject.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class R3BBackTracking : public TObject{
  
private:
  Double_t  px1; //unitary momentum components for proton
  Double_t  py1;
  Double_t  pz1;
  Double_t  pprim;
  Double_t   x1; //position in DCH2 (starting point)
  Double_t  y1;
  Double_t  z1;
  Double_t  x0; //position measured in target
  Double_t  y0;
  Double_t  z0; 

  ifstream* inputFile;
   
public:
  
  R3BBackTracking();
  ~R3BBackTracking();
  
  void ReadNewLine();

  Double_t GetPx1(){return px1;}
  Double_t GetPy1(){return py1;}
  Double_t GetPz1(){return pz1;}
  Double_t GetPPrim(){return pprim;}
  Double_t GetX1(){return x1;}
  Double_t GetY1(){return y1;}
  Double_t GetZ1(){return z1;}
  Double_t GetX0(){return x0;}
  Double_t GetY0(){return y0;}
  Double_t GetZ0(){return z0;}
  
  void SetPx1(Double_t p){px1=p;}
  void SetPy1(Double_t p){py1=p;}
  void SetPz1(Double_t p){pz1=p;}
  void SetPPrim(Double_t p){pprim=p;}
  void SetX1(Double_t p){x1=p;}
  void SetY1(Double_t p){y1=p;}
  void SetZ1(Double_t p){z1=p;}
  void SetX0(Double_t p){x0=p;}
  void SetY0(Double_t p){y0=p;}
  void SetZ0(Double_t p){z0=p;}

   ClassDef(R3BBackTracking,1) //ROOT CINT

};
#endif
