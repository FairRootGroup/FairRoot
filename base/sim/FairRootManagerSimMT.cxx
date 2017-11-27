/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *             GNU Lesser General Public Licence (LGPL) version 3,              *  
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

/// \file FairRootManagerSimMT.cxx
/// \brief Implementation of the FairRootManagerSimMT class
///
/// Implemented according to TMCRootManagerMT from Geant4 VMC.
///
/// \author I. Hrivnacova; IPN Orsay

#include "FairRootManagerSimMT.h"
#include "FairRootManager.h"
#include "FairWriteoutBuffer.h"
#include "TClonesArray.h"
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
#include "TMCAutoLock.h"
#endif
#include "TMCtls.h"
#include "TThread.h"
#include "TError.h"
#include "RVersion.h"

#include <cstdio>

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
namespace {
  TMCMutex createMutex = TMCMUTEX_INITIALIZER;
  TMCMutex deleteMutex = TMCMUTEX_INITIALIZER;
  TMCMutex registerMutex = TMCMUTEX_INITIALIZER;
  TMCMutex fillMutex  = TMCMUTEX_INITIALIZER;
  TMCMutex tmpFillMutex  = TMCMUTEX_INITIALIZER;
  TMCMutex writeMutex = TMCMUTEX_INITIALIZER;
  TMCMutex closeMutex = TMCMUTEX_INITIALIZER;
  TMCMutex getMutex =  TMCMUTEX_INITIALIZER;
}  
#endif

pthread_mutex_t counter_mutex;
pthread_mutex_t fill_lock_mutex;

//
// static data, methods
//

Int_t   FairRootManagerSimMT::fgCounter = 0; 
Bool_t  FairRootManagerSimMT::fgIsFillLock = true; 
std::vector<Bool_t>* FairRootManagerSimMT::fgIsFillLocks = 0;

//
// ctors, dtor
//

//_____________________________________________________________________________
FairRootManagerSimMT::FairRootManagerSimMT()
  : FairGenericRootManager(),
    fId(0),
    fRootManager(0)
{
/// Standard constructor

  // Check if TThread was initialized
  //if ( ! TThread::IsInitialized() ) {
  //   Fatal("FairRootManagerSimMT", "TThread::Initialize() must be called first.");
  //}

  if ( fgDebug ) {
    LOG(INFO) << "FairRootManagerSimMT::FairRootManagerSimMT: going to lock " 
      << this << FairLogger::endl;
  }
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&createMutex);
#endif

  // Set Id
  fId = fgCounter;

  // Get  FairRootManager (created via FairRun object)
  fRootManager = FairRootManager::Instance();
  if ( ! fRootManager ) {
    LOG(ERROR) << "FairRootManager::Instance() does not exist, creating new instance in " 
      << fId << " " << this << FairLogger::endl;
      fRootManager = FairRootManager::Instance();
  }

  if ( fgDebug ) {
    LOG(INFO) << "Done get fRootManager " << fRootManager << " in " 
      << fId << " " << this << FairLogger::endl;
  }

  // Increment counter
  if ( ! fgCounter ) {
    fgIsFillLocks = new std::vector<Bool_t>();
  } 
  ++fgCounter;
  fgIsFillLocks->push_back(true);  

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  if ( fgDebug ) {
    LOG(INFO) << "Released lock and done FairRootManagerSimMT::FairRootManagerSimMT in "
      << fId << " " << this << FairLogger::endl;
  }
}

//_____________________________________________________________________________
FairRootManagerSimMT::~FairRootManagerSimMT() 
{
/// Destructor

  if ( fgDebug ) {
    LOG(INFO) << "FairRootManagerSimMT::~FairRootManagerSimMT: going to lock " 
      << fId << " " << this << FairLogger::endl;
  }
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&deleteMutex);
#endif

  // Delete Root manager
  if ( fgDebug ) {
    LOG(INFO) << "Going to Delete fRootManager in " 
      << fId << " " << this << FairLogger::endl;
  }
  delete fRootManager;
  if ( fgDebug ) {
    LOG(INFO) << "Done Delete fRootManager in " 
      << fId << " " << this << FairLogger::endl;
  }

  // Global cleanup 
  --fgCounter;
  if ( ! fgCounter ) {
    delete fgIsFillLocks;
    fgIsFillLocks = 0;
  } 

  //  
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  if ( fgDebug ) {
    LOG(INFO) << "Released lock and done FairRootManagerSimMT::~FairRootManagerSimMT in "
      << fId << " " << this << FairLogger::endl;
  }
}

//
// private methods
//

//_____________________________________________________________________________
void  FairRootManagerSimMT::LogMessage(const TString& message)
{
/// Output one line log message followed with the instance Id and pointer

  if ( fgDebug ) {
    LOG(INFO) << message << " in " << fId << " " << this << FairLogger::endl;
  }
}


//_____________________________________________________________________________
void  FairRootManagerSimMT::FillWithTmpLock()
{
/// Fill the Root tree.

  LogMessage("Going to lock for Fill");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&tmpFillMutex);
#endif

  LogMessage("Fill");
  fRootManager->Fill();
  LogMessage("Done Fill");
  
  if ( fgIsFillLock ) {
    // the access to TFile and TTree needs to be locked only until 
    // __after__ the first Fill
    (*fgIsFillLocks)[fId] = false;
    Bool_t isDoneAll = true;
    Int_t counter = 0;
    while ( isDoneAll && counter < fgCounter ) {
      isDoneAll = ! (*fgIsFillLocks)[counter++];
    }
    if ( isDoneAll ) {
      LogMessage("... Switching off locking of Fill()");
      fgIsFillLock = false;
    }
  }

  LogMessage("Exiting Fill");

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Fill");
}  

//_____________________________________________________________________________
void  FairRootManagerSimMT::FillWithLock()
{
/// Fill the Root tree.

  LogMessage("Going to lock for Fill");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&fillMutex);
#endif

  LogMessage("Fill");
  fRootManager->Fill();
  LogMessage("Done Fill");
  
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Fill");
}  

//_____________________________________________________________________________

void  FairRootManagerSimMT::FillWithoutLock()
{
  LogMessage("Fill");
  fRootManager->Fill();
  LogMessage("Done Fill");
}

//
// public methods
//

//_____________________________________________________________________________
void FairRootManagerSimMT::Register(const char* name, const char* folderName, TNamed* obj, Bool_t toFile)
{
  LogMessage("Going to lock for Register (1)");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&registerMutex);
#endif

  LogMessage(TString("Register ") + name);
  fRootManager->Register(name, folderName, obj, toFile);
  LogMessage(TString("Done Register") + name);

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Register");
}

//_____________________________________________________________________________
void FairRootManagerSimMT::Register(const char* name, const char* folderName, TCollection* obj, Bool_t toFile)
{
  LogMessage("Going to lock for Register (2)");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&registerMutex);
#endif

  LogMessage(TString("Register ") + name);
  fRootManager->Register(name, folderName, obj, toFile);
  LogMessage(TString("Done Register") + name);

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Register (2)");
}

//_____________________________________________________________________________
void FairRootManagerSimMT::RegisterInputObject(const char* name, TObject* obj)
{
  LogMessage("Going to lock for Register (3)");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&registerMutex);
#endif

  LogMessage(TString("Register ") + name);
  fRootManager->RegisterInputObject(name,obj);
  LogMessage(TString("Done Register") + name);

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Register (3)");
}

//_____________________________________________________________________________
TClonesArray*  FairRootManagerSimMT::Register(TString branchName, TString className, TString folderName, Bool_t toFile)
{
  LogMessage("Going to lock for Register (4)");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&registerMutex);
#endif

  LogMessage(TString("Register ") + branchName);
  TClonesArray* result
    = fRootManager->Register(branchName, className, folderName, toFile);
  LogMessage(TString("Done Register") + branchName);

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Register (4)");

  return result;
}

//_____________________________________________________________________________
FairWriteoutBuffer* FairRootManagerSimMT::RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer)
{
  LogMessage("Going to lock for RegisterWriteoutBuffer");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&registerMutex);
#endif

  LogMessage("RegisterWriteoutBuffer");
  FairWriteoutBuffer* result
    = fRootManager->RegisterWriteoutBuffer(branchName, buffer);
  LogMessage("Done RegisterWriteoutBuffer");

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for RegisterWriteoutBuffer");

  return result;
}

//_____________________________________________________________________________
void  FairRootManagerSimMT::Fill()
{
/// Fill the Root tree.

  // Fill with lack untill first call on all threads
  if ( fgIsFillLock ) {
    FillWithTmpLock();
  }  
  else {
    FillWithoutLock();
  }

  // Fill with lock during the whole run
  // FillWithLock();
}  

//_____________________________________________________________________________
void FairRootManagerSimMT:: Write()
{
/// Write the Root tree in the file.

  LogMessage("Going to lock for Write");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&writeMutex);
#endif

  LogMessage("Write");
  fRootManager->Write();
  LogMessage("Done Write");

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for Write");
}  

//_____________________________________________________________________________
void FairRootManagerSimMT:: CloseOutFile()
{
/// Close the Root file.

  LogMessage("Going to lock for CloseOutFile");
#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  TMCAutoLock lk(&closeMutex);
#endif

  LogMessage("CloseOutFile");
  fRootManager->CloseOutFile();
  LogMessage("Done CloseOutFile");

#if ( ROOT_VERSION_CODE >= ROOT_VERSION(6,9,3) )
  lk.unlock();
#endif
  LogMessage("Released lock for CloseOutFile");
}

//_____________________________________________________________________________
Int_t FairRootManagerSimMT::GetBranchId(TString const & brName)
{
/// Return branch Id

  return fRootManager->GetBranchId(brName);
}
