/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol     hapol@fpddux.usc.es
//*-- Date: 05/2007
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

#ifndef R3BBeamInfo_H
#define R3BBeamInfo_H 1

#include "TROOT.h"  //for including Rtypes.h

#include "TObject.h" 

class R3BBeamInfo : public TObject {
  
private:

  Double_t theta;              // theta emission angle in vertex
  Double_t phi;                // phi emission angle in vertex

  Double_t xPos;         //vertex position
  Double_t yPos;
  Double_t zPos;
  
public:
  
  R3BBeamInfo();
  ~R3BBeamInfo();
  
  inline Double_t GetTheta() const { return theta; }
  inline Double_t GetPhi() const { return phi; }

  inline Double_t GetXPos() const { return xPos; }
  inline Double_t GetYPos() const { return yPos; }
  inline Double_t GetZPos() const { return zPos; }

  inline void SetTheta(Double_t t) { theta = t; }
  inline void SetPhi(Double_t p) { phi = p; }

  inline void SetXPos(UInt_t x) { xPos = x; }
  inline void SetYPos(UInt_t y) { yPos = y; }
  inline void SetZPos(UInt_t z) { zPos = z; }

  void SetVertexPosition(Double_t ,Double_t ,Double_t );
  void SetAngles(Double_t ,Double_t );

  void print(void);

  ClassDef(R3BBeamInfo,1) //ROOT CINT    
};
#endif
