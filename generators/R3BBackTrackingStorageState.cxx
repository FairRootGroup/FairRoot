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

#include "R3BBackTrackingStorageState.h"
#include <iostream>

using namespace std;


ClassImp(R3BBackTrackingStorageState)


  //using namespace std;

R3BBackTrackingStorageState::R3BBackTrackingStorageState(){
  //
  // Constructor
  //
  
  p0=1101.; //central value of the theoretical momentum calculation
  pcent=1101.;
  pmaxabs=1250.;//maximum value of the theoretical momentum calculation
  pminabs=950.;//minimum value of the theoretical momentum calculation
  pmax=1250.;//maximum value of the theoretical momentum calculation
  pmin=950.;//minimum value of the theoretical momentum calculation
  

  //  pmaxabs=1500.;//maximum value of the theoretical momentum calculation
  //  pminabs=850.;//minimum value of the theoretical momentum calculation
  //  pmax=1500.;//maximum value of the theoretical momentum calculation
  //  pmin=850.;//minimum value of the theoretical momentum calculation




  pfinal=0.;//calculated value for the momentum module
  piter=0.;//Momentum in each iteration
  niter=0;//iteration number
  x0tar=0.;
  y0tar=0.;
  z0tar=0.;
  pPrim=0.;
  converg=1;
  xSim=0.;
  ySim=0.;
  zSim=0.;

 
  }
 
R3BBackTrackingStorageState::~R3BBackTrackingStorageState(){
  //
  // Destructor
  //

 
}

void R3BBackTrackingStorageState::ReadNewLine(){
 
    cout << "-I- R3BBackTrackingStorageState::ReadNewLine() not implemented " << endl;

}
