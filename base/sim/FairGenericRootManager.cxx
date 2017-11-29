/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
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

/// \file FairGenericRootManager.cxx
/// \brief Implementation of the FairGenericRootManager class
///
/// TVirtualMCRootManager class adapted for FairRoot.
///
/// \author I. Hrivnacova; IPN Orsay

#include "FairGenericRootManager.h"
#include "TError.h"


                                Bool_t  FairGenericRootManager::fgDebug = false;
TMCThreadLocal FairGenericRootManager*  FairGenericRootManager::fgInstance = 0;

//_____________________________________________________________________________
FairGenericRootManager* FairGenericRootManager::Instance()
{
/// \return The singleton instance.

  return fgInstance;
}  

//
// ctors, dtor
//

//_____________________________________________________________________________
FairGenericRootManager::FairGenericRootManager()
{
/// Default constructor

  if ( fgInstance ) {
      Fatal("FairGenericRootManager",
            "Attempt to create two instances of singleton.");
    return;
  }  

  fgInstance = this;
}

//_____________________________________________________________________________
FairGenericRootManager::~FairGenericRootManager() 
{
/// Destructor

  fgInstance = 0;
}
