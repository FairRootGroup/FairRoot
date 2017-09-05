/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2013, 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file FairRootManagerSim.cxx
/// \brief Implementation of the FairRootManagerSim class
///
/// TMCRootManager class adapted for FairRoot.
///
/// \author I. Hrivnacova; IPN Orsay

#include "FairRootManagerSim.h"
#include "FairRootManager.h"
#include "FairWriteoutBuffer.h"
#include "TClonesArray.h"
#include "TError.h"

#include <cstdio>

//
// ctors, dtor
//

//_____________________________________________________________________________
FairRootManagerSim::FairRootManagerSim()
  : FairGenericRootManager(),
    fRootManager(0)
{
/// Standard constructor
  if ( fgDebug ) printf("FairRootManagerSim::FairRootManagerSim %p \n", this);
  fRootManager = FairRootManager::Instance();
  if ( ! fRootManager ) {
    std::cout << "Creating FairRootManager" << std::endl;
      fRootManager = FairRootManager::Instance();
  } else {
    std::cout << "Got FairRootManager existing" << std::endl;
  }
  if ( fgDebug ) printf("Done FairRootManagerSim::FairRootManagerSim %p \n", this);
}

//_____________________________________________________________________________
FairRootManagerSim::~FairRootManagerSim() 
{
/// Destructor

  // Delete Root manager
  if ( fgDebug ) printf("Going to Delete fRootManager in  %p \n", this);
  delete fRootManager;
  if ( fgDebug ) printf("Done Delete fRootManager in %p \n", this);
}

//
// public methods
//

//_____________________________________________________________________________
void FairRootManagerSim::Register(const char* name, const char* folderName, TNamed* obj, Bool_t toFile)
{
  fRootManager->Register(name, folderName, obj, toFile);
}

//_____________________________________________________________________________
void FairRootManagerSim::Register(const char* name, const char* folderName, TCollection* obj, Bool_t toFile)
{
  fRootManager->Register(name, folderName, obj, toFile);
}

//_____________________________________________________________________________
void FairRootManagerSim::RegisterInputObject(const char* name, TObject* obj)
{
  fRootManager->RegisterInputObject(name,obj);
}

//_____________________________________________________________________________
TClonesArray*  FairRootManagerSim::Register(TString branchName, TString className, TString folderName, Bool_t toFile)
{
  return fRootManager->Register(branchName, className, folderName, toFile);
}

//_____________________________________________________________________________
FairWriteoutBuffer* FairRootManagerSim::RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer)
{
  return fRootManager->RegisterWriteoutBuffer(branchName, buffer);
}

//_____________________________________________________________________________
void  FairRootManagerSim::Fill()
{
/// Fill the Root tree.

  fRootManager->Fill();
}  

//_____________________________________________________________________________
void FairRootManagerSim::Write()
{
/// Write the Root tree in the file.

  fRootManager->Write();
}  

//_____________________________________________________________________________
void FairRootManagerSim::CloseOutFile()
{
/// Close the Root file.

  fRootManager->CloseOutFile();
}  

//_____________________________________________________________________________
Int_t FairRootManagerSim::GetBranchId(TString const & brName)
{
/// Return branch Id

  return fRootManager->GetBranchId(brName);
}

// //_____________________________________________________________________________
// void FairRootManagerSim:: WriteAndClose()
// {
// /// Write the Root tree in the file and close the file.

//   fRootManager->Write();
//   fRootManager->CloseOutFile();
// }  

// //_____________________________________________________________________________
// TObject*  FairRootManagerSim::GetObject(const char* branchName)
// {
//   return fRootManager->GetObject(branchName);
// }

// //_____________________________________________________________________________
// TClonesArray*  FairRootManagerSim::GetTClonesArray(TString branchName)
// {
//   return fRootManager->GetTClonesArray(branchName);
// }

// //_____________________________________________________________________________
// void  FairRootManagerSim::ReadEvent(Int_t i)
// {
// /// Read the event data for \em i -th event for all connected branches.
// /// \param i  The event to be read

//   fRootManager->ReadEvent(i);
// }
