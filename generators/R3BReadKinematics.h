/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Oleg Kiselev		O.Kiselev@gsi.de
//*-- Date: 11/2005
//*-- Last Update: 20/07/05 Hector Alvarez
// --------------------------------------------------------------
// Description:
//   Event generator kinematics reader
//
// --------------------------------------------------------------
// Comments:
// 
// --------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////

#ifndef READKINEM_H
#define READKINEM_H

#include "TObject.h"
#include <fstream>
#include <iostream>
#include <string>

class R3BReadKinematics : public TObject
{
  public:
    R3BReadKinematics();
   ~R3BReadKinematics();
   
  public:
//    File *pFile;
		Double_t LabAngle[1000];
		Double_t LabEnergy[1000];
			Double_t T_xsec[5000];
			Double_t CrossSection_t[5000];
			//Integrated matrix (cross section) 
      Double_t Icross_section[5000];

  ClassDef(R3BReadKinematics,1) //ROOT CINT

};
#endif
