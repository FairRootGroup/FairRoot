/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Saul Beceiro Novo        saul.beceiro@rai.usc.es
//           
//*-- Date: 03/2008
//*-- Last Update: 25/03/08 by Saul Beceiro
// --------------------------------------------------------------
// Description:
//   Storage intermediate state in the iterations needed 
//   for the convergency of the momentum calculation
//
// --------------------------------------------------------------
// Comments:
// 
//   
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef R3BBackTrackingStorageState_h
#define R3BBackTrackingStorageState_h 1

#include "TROOT.h"  //for including Rtypes.h

#include "TObject.h"

#include <iostream>
#include <fstream>
#include <string>

//using namespace std;

class R3BBackTrackingStorageState : public TObject{ 
  
private:
  Double_t  p0; //central value of the theoretical momentum calculation
  Double_t  pcent;
  Double_t  pmax;//maximum value of the theoretical momentum calculation
  Double_t  pmin;//minimum value of the theoretical momentum calculation
  Double_t  pmaxabs;//maximum value of the theoretical momentum calculation
  Double_t  pminabs;//minimum value of the theoretical momentum calculation
  Double_t  pfinal;//calculated value for the momentum module
  Double_t  piter;//calculated value for the momentum module
  Int_t     niter;//iteration number
  Int_t     converg; //0 when it doesnt converge,1 when it does.

  Double_t  x0tar;//coordinates measured in the target (real measurement)
  Double_t  y0tar;
  Double_t  z0tar;
  Double_t pPrim;//real momentum (obtained with simulated data) 

  Double_t  xSim;//coordinates in the target taken during the backward simulation
  Double_t  ySim;
  Double_t  zSim;

public:
  
  R3BBackTrackingStorageState();
  ~R3BBackTrackingStorageState();
  
  void ReadNewLine();
  
  Double_t GetP0(){return p0;}
  Double_t GetPcent(){return pcent;}
  Double_t GetPmax(){return pmax;}
  Double_t GetPmin(){return pmin;}
  Double_t GetPmaxAbs(){return pmaxabs;}
  Double_t GetPminAbs(){return pminabs;}
  Double_t GetPfinal(){return pfinal;}
  Double_t GetPiter(){return piter;}
  Int_t GetNiter(){return niter;}
  Int_t GetConverg(){return converg;}
  Double_t GetX0(){return x0tar;}
  Double_t GetY0(){return y0tar;}
  Double_t GetZ0(){return z0tar;}
  Double_t GetPPrim(){return pPrim;}
  Double_t GetXSim(){return xSim;}
  Double_t GetYSim(){return ySim;}
  Double_t GetZSim(){return zSim;}
  
  void SetP0(Double_t p){p0=p;}
  void SetPcent(Double_t p){pcent=p;}
  void SetPmax(Double_t p){pmax=p;}
  void SetPmin(Double_t p){pmin=p;}
  void SetPmaxabs(Double_t p){pmaxabs=p;}
  void SetPminabs(Double_t p){pminabs=p;}
  void SetPfinal(Double_t p){pfinal=p;}
  void SetPiter(Double_t p){piter=p;}
  void SetNiter(Int_t p){niter=p;}
  void SetConverg(Int_t p){converg=p;}
  void SetX0(Double_t p){x0tar=p;}
  void SetY0(Double_t p){y0tar=p;}
  void SetZ0(Double_t p){z0tar=p;}
  void SetPPrim(Double_t p){pPrim=p;}
  void SetXSim(Double_t p){xSim=p;}
  void SetYSim(Double_t p){ySim=p;}
  void SetZSim(Double_t p){zSim=p;}
  
  ClassDef(R3BBackTrackingStorageState,1) //ROOT CINT

};
#endif
