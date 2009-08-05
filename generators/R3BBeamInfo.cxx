/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol     hapol@fpddux.usc.es
//*-- Date: 01/2006
//*-- Last Update: 07/05/07 by Hector Alvarez
// --------------------------------------------------------------
// Description:
//   The information from the beam parameters used for the reaction
//   vertex. Information to be accessed in the ROOT file per event
//
// --------------------------------------------------------------
// Comments:
//
//     - 07/05/07 Data structure for beam parameters  
//
/////////////////////////////////////////////////////////////////

#include "R3BBeamInfo.h"

ClassImp(R3BBeamInfo)
  
R3BBeamInfo::R3BBeamInfo() {
  //
  // Init values
  //
  theta = 0;        
  phi =0;          

  xPos = 0.;
  yPos = 0.;
  zPos = 0.;
}


R3BBeamInfo::~R3BBeamInfo(){
  //
  // Destructor. Makes nothing
  //
}


void R3BBeamInfo::print(void){
  //
  // Prints info
  //
}


void R3BBeamInfo::SetVertexPosition(Double_t x, Double_t y, Double_t z) {
  //
  // Sets the position of the vertex (origin of the primary particle)
  //
  xPos = x;
  yPos = y;
  zPos = z;
}


void R3BBeamInfo::SetAngles(Double_t angleTheta, Double_t anglePhi){
  //
  // Sets the 4momentum
  //
  theta = angleTheta;
  phi = anglePhi;
}
