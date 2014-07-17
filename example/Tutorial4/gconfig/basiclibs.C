/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// $Id: basiclibs.C,v 1.1.1.1 2005/06/23 07:14:09 dbertini Exp $
//
// Macro for loading basic libraries used with both Geant3 and Geant4

void basiclibs()
{
 /* gSystem->Load("libGeom");
  gSystem->Load("libGeomPainter");
  
 
  gSystem->Load("libPhysics");
  gSystem->Load("libEG"); 
  gSystem->Load("libVMC");
  gSystem->Load("libEGPythia6");
  gSystem->Load("libPythia6");  
  gSystem->Load("libPluto");  
  gSystem->Load("libMinuit");
  gSystem->Load("libTree"); 
  */
  gSystem->Load("libRIO");
  gSystem->Load("libGeom");
  gSystem->Load("libGeomPainter");
  gSystem->Load("libVMC");
  gSystem->Load("libEG");
  gSystem->Load("libEGPythia6");
  gSystem->Load("libPythia6");  
  gSystem->Load("libPhysics");
  gSystem->Load("libNet");  
  gSystem->Load("libTree"); 
  gSystem->Load("libMinuit");
  gSystem->Load("libMathMore");

  gSystem->Load("libProof");
  gSystem->Load("libProofPlayer");
  gSystem->Load("libGX11TTF");
  gSystem->Load("libGX11");


}  
