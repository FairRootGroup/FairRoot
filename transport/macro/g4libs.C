/** Modified g4Libs.C for FairRoot: (M. Al-Turany)
* With G4.9.4 Cmake can be used to build the G4 aand there is no need 
* to build the granular libs. one cam also use the new utilites
* geant4-config to find out which libraries has to be loaded, however 
* the libG3toG4 has to be loaded separately. 
*/
// $Id: g4libs_old.C 529 2010-12-22 17:54:38Z ivana $

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file g4libs_old.C
/// \brief Old macro for loading Geant4 and Geant4 VMC libraries
///
/// Besides loading libraries, the macro also resets 
/// FPE mask to 0, in order to make sure than FPE for
/// FE_OVERFLOW is disabled what is required for Geant4.

//
// Macro for loading Geant4 and Geant4 VMC libraries

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>

#include <TSystem.h>
#include <TString.h>
#include <TApplication.h>
#include <TROOT.h>

#endif

void g4libs_global();

void g4libs()
{
/// Macro function for loading Geant4 granular libraries.
/// Change the comment if global libraries are used.

  //g4libs_granular();
  g4libs_global();
  
  gSystem->SetFPEMask(0); 
}   

Bool_t isSet(const char* variable)
{
/// Helper function which checks if the specified environment variable 
/// is set.
/// \param variable  The environment variable name

  TString value = gSystem->Getenv(variable);
  if ( value != "") return true;
  
  return false;
}  

Bool_t isLibrary(const char* libName)
{
/// Helper function which testes the existence of the given library
/// \param libName  The library name

  if (TString(gSystem->DynamicPathName(libName, kTRUE)) != TString(""))
    return kTRUE;
  else  
    return kFALSE;
}    

Bool_t isBatch()
{
/// Helper function which testes if Root was started in batch mode

  for ( Int_t i=0; i<gApplication->Argc(); ++i ) 
    if ( TString(gROOT->GetApplication()->Argv(i)) == "-b" ) return true;
  
  return false;
}    

void vgmlibs()
{ 
/// Macro function for loading VGM libraries.

  if (isSet("USE_VGM")) { 
    cout << "Loading VGM libraries ... " << endl;
    gSystem->Load("libClhepVGM");
    gSystem->Load("libBaseVGM");
    gSystem->Load("libGeant4GM");
    gSystem->Load("libRootGM");
    gSystem->Load("libXmlVGM");
  }  
}
  
void g4libs_global()
{
/// Macro function for loading Geant4 global libraries, Geant4 VMC library 
/// and external packages: CLHEP, graphics drivers, .. used by Geant4

  cout << "Loading Geant4 global libraries ...Our Macro" << endl;
 
   // CLHEP
  if(isLibrary("libCLHEP"))gSystem->Load("libCLHEP");

  // Geant4: use the geant4-config tool to load the libraries

  TString command = "geant4-config --libs";
  TString line= gSystem->GetFromPipe(command);
//  printf(" line = %s \n", line.Data());
  TString delim=" ";
  TObjArray *libs=line.Tokenize(delim);
  TObjString *objstr;
  TString *str;
  for (UInt_t i=1; i<libs->GetEntries();i++){
    objstr=(TObjString *)libs->At(i);
    str=objstr->String();
    str->Replace(0,2,"lib");
    gSystem->Load(str->Data());
   printf(" Loading Library %s \n",  str->Data());
   }

   gSystem->Load("libG3toG4");

   
  // VGM libraries
  vgmlibs();

  // G4Root library (if available)
  if ( isLibrary("libg4root") ) {   
    cout << "Loading g4root library ..." << endl;
    gSystem->Load("libg4root");
  }  

  // geant4 VMC
  gSystem->Load("libgeant4vmc");

  cout << "Loading libraries ... finished" << endl;
}













